
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

 int main (int argc, char **argv)
 {
     
    int childPid;
    char * cmdLine;
    char *info;

    char file1[256];
     while (1){
    
            cmdLine= readline(">"); 
            //printf("%s",cmdLine);
            //info = parse(cmdLine);
            //char a[5]="/bin/";
            //info=strcat(a,cmdLine);
            //printf("%s",info);
            childPid = fork();
            //har *av[]={cmdLine,*argv,NULL};
            //char * nw=(char*)malloc(sizeof(char));
 
            if (childPid == 0){
        
              char * cpyCmd;
              strcpy(cpyCmd,cmdLine);
              char * word=strtok(cpyCmd, " ");
  
              //printf("%s",word);
                if (strcmp(cmdLine, "pwd") == 0) {
        
                    char* av[]={"pwd",NULL};
                    execvp("pwd",av);}
       
                else if(strcmp(word,"cd")==0) {
                    //printf("%s",cmdLine);
                    //        char* word = strtok(cmdLine, " ");
                    word = strtok(NULL, " ");
                    // printf("%s",cmdLine);
                    //printf("%s",word);
                    chdir(word);
                    // exit(0);
                    }
                else if(strcmp(word,"nano")==0){
                     // char* word = strtok(cmdLine, " ");
                    word=  strtok(NULL, " ");
                    //  printf("%s",cmdLine);
                     creat(word,  0644);
                    //printf("%s",strtok(cmdLine,"nano ")); 
                    //printf("%s", cmdLine);
                 }
                else if(strstr(cmdLine,"cat >")){
                    //char* word = strtok(cmdLine, " ");
                    word = strtok(NULL, " ");
                    word = strtok(NULL, " ");
                    //printf("%s",word);
                    creat(word,  0644);  
                    // printf("%s",strtok(cmdLine,"cat > ")); 
                    //printf("%s", cmdLine);
                }
                else if(strcmp(word,"cat")==0)
                {

                    //char* word = strtok(cmdLine, " ");
                    word = strtok(NULL, " ");
                    execl("/bin/cat", "cat", word, NULL);
 
<<<<<<< HEAD
            }
            else if(strcmp(word,"wc")==0){
                 word = strtok(NULL, " ");
                 strcpy(file1,word);
                 word = strtok(NULL, " ");
                 execlp("wc","wc",file1,word,NULL);
               
            }
            else if(strcmp(word,"cp")==0){
                printf("hi");
                word=strtok(NULL, " ");
                //printf("%s",word);
                 strcpy(file1,word);
                 word=strtok(NULL, " ");
                //  printf("%s",nw);
                //  strcpy(file2,word);
                //file2=strtok(NULL, " ");
                execl("/bin/cp", "cp", file1,word, NULL);
            }
=======
                }
>>>>>>> 13f3d0b43bb7ed24555371b9cfd20d3948c3050d



                else if(strcmp(word,"cp")==0){


                    word=strtok(NULL, " ");
                    strcpy(file1,word);
                    word=strtok(NULL, " ");
                    //  printf("%s",nw);
                    //  strcpy(file2,word);
                    //file2=strtok(NULL, " ");
                    execl("/bin/cp", "cp", file1,word, NULL);
                }


                else if(strcmp(word,"sort")==0){
                    word=strtok(NULL, " ");
                    if (strcmp(word,"-r")==0){
                        word=strtok(NULL, " ");
                        execlp("sort","sort","-r", word,NULL);

                    }
                    else
                    {
                        execlp("sort","sort",word,NULL);
                    }

            }


// else if(strcmp(word,"wc")==0){

//     word=strtok(NULL, " ");
//  execlp("wc","wc",word,NULL);

// }



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