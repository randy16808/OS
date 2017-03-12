#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sstream>
#include<unistd.h>
#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 25

int main(int argc,char ** argv)
{
    int n=0, ans=1;
    char write_msg[BUFFER_SIZE];
    int fd =0 ;
    std:: stringstream ss;
    ss << argv[1]; ss >> fd;
    printf("I can receive the input! Please enter a number.\n\n");
    scanf("%d", &n);
    while(n) {ans *= n; n--;}
    printf("\nThe output number is: %d.\n",ans);
    printf("-----------------------------------------------------------\n");
    sprintf(write_msg,"%d",ans);
    write(fd,write_msg,strlen(write_msg)+1);
    close(fd);
    return 0;
}
