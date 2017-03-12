#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sstream>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1


int main()
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int ans_final =0;
   
    pid_t pid;
    pid=getpid(); 
    printf("Main process ID: %d.\n",pid);
    printf("------------------------------------------------------------\n");
    for(int i=0; i<3; i++)
    {
        int fd[2];
        if(pipe(fd)==-1)
        {
            fprintf(stderr,"Pipe Failed");
            return 1;
        }
        pid = fork();
        if(pid<0)
        {
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if(pid == 0)
        {
            pid = getpid();
            printf("I'm the child %d.\n",pid);
            close(fd[READ_END]);
            char tmp [4] ;
            sprintf(tmp,"%d",fd[WRITE_END]);
            execlp("/u/cs/103/0316321/OS/1-2/calculate.o","./calculate.o",tmp,NULL);
        }
        else
        {
            pid=getpid();
            wait(NULL);
            close(fd[WRITE_END]);
            read(fd[READ_END],read_msg,BUFFER_SIZE);
            close(fd[READ_END]);
            std:: stringstream ss; int ans;
            ss << read_msg; ss >> ans;
            ans_final += ans;
        }
    }
    pid=getpid();
    printf("I'm th parent %d.\n",pid);
    printf("Sum of results from three child processes : %d\n",ans_final);
    printf("-----------------------------------------------------------\n");
    return 0;
}
