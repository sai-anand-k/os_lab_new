#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<ctype.h>
#include<string.h>



char* changecase(char *str)
{
    int i=0;
    for (i=0;i<strlen(str);i++)
    {
        if (isupper(str[i]))
            str[i]=tolower(str[i]);
        else 
            str[i]=toupper(str[i]);
    }
    return str;
}

int main()
{
    int fd1[2];
    int fd2[2];
    pid_t pid;
    char buffer1[200];
    char buffer2[200];
    char result[200];
    int n;

    if (pipe(fd1)==-1)
       printf("Error in creating pipe 1");
    if (pipe(fd2)==-1)
       printf("Error in creating pipe 2");
    
    pid = fork();

    if (pid == -1)
       printf("error in creating process");

    if (pid > 0)
    {
        close(fd1[0]);
        close(fd2[1]);

        printf("enter no.of strings : ");
        scanf("%d",&n);

        printf("enter the strings : ");
        for (int i=0; i<n ; i++)
        {
            scanf("%s",buffer1);
            write(fd1[1],buffer1,200);
        }
        

        close(fd1[1]);
        
        wait(NULL);

        printf("\ncase changed strings are :\n");
        while (read(fd2[0],result,200)>0)
        {
            printf("%s\n",result);
        }
        close(fd2[0]);
    }
    else
    {
        sleep(5);
        close(fd1[1]);
        close(fd2[0]);
        char temp[200];


        while (read(fd1[0],buffer2,200)>0)
        {
                strcpy(temp, changecase(buffer2));
                write(fd2[1],temp,200);

        }
        close(fd2[1]);
    }


}