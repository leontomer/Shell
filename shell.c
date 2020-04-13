
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
 void executeWord(char * word,FILE* f,char* file1){
        if (strcmp(word, "pwd") == 0) {
                char* av[]={"pwd",NULL};
                execvp("pwd",av);
            }
       
        else if(strcmp(word,"cd")==0) {
                    word = strtok(NULL, " ");
                    chdir(word);
            }

        else if(strcmp(word,"grep")==0) {
                 printf("entered here\n");
                 word = strtok(NULL, " ");
                 strcpy(file1,word);
                 word = strtok(NULL, " ");
                 execlp("grep","grep",file1,word,NULL);
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
                 execlp("wc","wc",file1,word,NULL);
               
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
             else{
                execlp("sort","sort",word,NULL);
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
     for(int i=0;word[i]!=0;i++){
         printf("%c\n",word[i]);
         if(word[i]=='|'){
             printf("matched!\n");
             return 1;
         }
     }
     return 0;
 }
 int main (int argc, char **argv)
 {
     
    int childPid;
    char * cmdLine;
    char *info;
    FILE *f;
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
                  printf("has |\n");
              }
              executeWord(word,f,file1);   
         }

        else{
            waitpid(childPid);
        }
    }

 return 0;
 }