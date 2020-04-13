
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
  

                if (strcmp(cmdLine, "pwd") == 0) {
        
                    char* av[]={"pwd",NULL};
                    execvp("pwd",av);}
       
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
                else if(strstr(cmdLine,"cat >")){
                    word = strtok(NULL, " ");
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

            else if(strcmp(word,"cat")==0)
                {
                    word = strtok(NULL, " ");
                    execl("/bin/cat", "cat", word, NULL);
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
            
                else if(strcmp(cmdLine, "exit") == 0){

                    kill(0,1);
                }

                else{
                    printf("\'%s\' command is not supported\n",cmdLine);
                    exit(0);
                }
    }
        else
        {
            waitpid(childPid);
        }
            }

 return 0;
 }