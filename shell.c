
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


 void executeWord(char * word,FILE* f,char* file1){
        if (strcmp(word, "pwd") == 0) {
                word=strtok(NULL," ");
                if(!word)
                    execlp("pwd","pwd",NULL);
                else
                {
                    printf("pwd should not receive any parameters/options\n");
                    exit(0); 
                }
            }
       
        else if(strcmp(word,"cd")==0) {
                    word = strtok(NULL, " ");
                    chdir(word);
            }

        else if(strcmp(word,"grep")==0) {
                 word = strtok(NULL, " ");
                 strcpy(file1,word);
                 word = strtok(NULL, " ");
                 if(execlp("grep","grep",file1,word,NULL)==-1){
                     printf("failed grep\n");
                 };
            }

        else if(strcmp(word,"nano")==0){
                 word=  strtok(NULL, " ");
                execlp("nano","nano",word,NULL);
            }

        else if(strcmp(word,"cat")==0){
                 word = strtok(NULL, " ");
                if(strcmp(word,">")==0){
                    word = strtok(NULL, " ");
                    f = fopen(word, "w");
                    if(!f){
                       creat(word,0644);
                       f = fopen(word, "w");
                    }
                    while (fgets(file1, 1000, stdin) != NULL) {
                         fputs(file1,f);
                    }
                    fclose(f);
                }
                else{
                    execl("/bin/cat", "cat", word, NULL);
                }
           }

        else if(strcmp(word,"wc")==0){
                 word = strtok(NULL, " ");
                 strcpy(file1,word);
                 word = strtok(NULL, " ");
                 if(execlp("wc","wc",file1,word,NULL)==-1){
                     printf("error\n");
                 };
               
            }

        else if(strcmp(word,"cp")==0){
                word=strtok(NULL, " ");
                strcpy(file1,word);
                word=strtok(NULL, " ");
                execl("/bin/cp", "cp", file1,word, NULL);
            }

        else if(strcmp(word,"sort")==0){
             word=strtok(NULL, " ");
             if (strcmp(word,"-r")==0){
                word=strtok(NULL, " ");
                execlp("sort","sort","-r", word,NULL);
                }
               else if(!strstr(word,"-")){
                execlp("sort","sort",word,NULL);
            }
                        else{
            printf("option \'%s\' is not supported\n",word);
            exit(0); 
            }

        }

        else if(strcmp(word,"man")==0){
                 word=strtok(NULL, " ");
                    if((strcmp(word,"pwd")==0)||(strcmp(word,"cd")==0)||(strcmp(word,"cat")==0)||(strcmp(word,"nano")==0)||(strcmp(word,"wc")==0)||(strcmp(word,"man")==0)||(strcmp(word,"cp")==0)||(strcmp(word,"sort")==0||(strcmp(word,"grep")==0)))
                        execlp("man","man", word,NULL);
        } 

        else if(strcmp(word, "exit") == 0){
                 kill(0,1);
        }

        else{
            printf("\'%s\' command is not supported\n",word);
            exit(0);
        }

 }
 int checkIfNeedPipe(char* word){
     int pipeCount=0;
     for(int i=0;word[i]!=0;i++){
         if(word[i]=='|'){
             pipeCount++;
         }
     }
     if(pipeCount>1){
         printf("Multiple pipes are not supported\n");
         exit(0);
     }
     else if(pipeCount==1){
         return 1;
     }
     return 0;
 }

 void handlePipe(char * cmdLine,FILE* f,char* file1){
    char* firstCommand,*secondCommand;
    firstCommand=strtok_r(cmdLine,"|",&secondCommand);
    secondCommand=strtok(secondCommand, " ");
    firstCommand=strtok(firstCommand, " ");
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid=fork();
    if(pid==-1){
        printf("fork failed\n");
        exit(1);
    }
    if(pid==0){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        executeWord(firstCommand,f,file1);
    }
    else{
        pid=fork();
        if(pid==-1){
            printf("fork failed\n");
        }
        if(pid==0){
            dup2(fd[0],STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            executeWord(secondCommand,f,file1);
        }
        else{
            int status;
            close(fd[0]);
            close(fd[1]);
            waitpid(pid,&status,0);
        }
    }
 }

 int main (int argc, char **argv)
 {
     
    int childPid;
    char * cmdLine;
    char *info;
    FILE *f;
    int status;
    char file1[256];
     while (1){
            printf("\nENTER YOUR COMMAND: \n");
            cmdLine= readline(">"); 
            childPid = fork();
        if (childPid == 0){
              char * cpyCmd;
              strcpy(cpyCmd,cmdLine);
              char * word=strtok(cpyCmd, " ");
              if(checkIfNeedPipe(cmdLine)){
                  handlePipe(cmdLine,f,file1);
              }
              else{
                executeWord(word,f,file1);  
              }
         
         }

        else{
            waitpid(childPid,&status,0);
        }
    }

 return 0;
 }