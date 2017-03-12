#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>


int main()
{
 //   FILE * pFile;
 //   pFile = fopen("hw1_1.txt","w");
    pid_t pid, parent, child;
    
    pid =getpid();
//    fprintf(pFile,"Main process ID: %d\n\n", pid);
    printf("Main process ID: %d\n\n", pid);


    for(int i=1; i<4 ; i++)
    {
        parent = getpid();
        pid = fork();
        if(pid<0)
        {
            fprintf(stderr, "Fork Failed");
            return 1;
         }
         else if(pid == 0) //child process
         {
             child = getpid(); //child pid
    //         fprintf(pFile,"fork %d. I'm the child %d , my parent is %d .\n",i,child, parent);
             printf("fork %d. I'm the child %d , my parent is %d .\n",i,child, parent);

        }
         else  //parent process
         {
             child = pid;
             parent = getpid(); //parent pid
           //  fprintf(pFile,"fork %d. I'm the parent %d , my child is %d .\n",i, parent, child);
             printf("fork %d. I'm the parent %d , my child is %d .\n",i, parent, child);
             wait(NULL);
             // printf("Child Complete\n");
          }
    }    
  //  fclose(pFile);
    return 0;
}
