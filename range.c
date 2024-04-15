#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int validate(int n ,int a ,int b)
{
    if (n<=b && n>=a)
    {
        return 1;
    }
    else
        return 0;
}

int main()
{
    int fd1[2];
    int fd2[2];
    pid_t pid;
    int num1;
    int num2;
    int result;
    int n;
    int a;
    int b;
    int temp1,temp2;

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

        printf("enter no.of numbers : ");
        scanf("%d",&n);

        printf("Enter the range : ");
        scanf("%d%d",&a,&b);

        write(fd1[1],&a,sizeof(int));
        write(fd1[1],&b,sizeof(int));

        printf("enter the numbers : ");
        for (int i=0; i<n ; i++)
        {
            scanf("%d",&num1);
            write(fd1[1],&num1,sizeof(int));
        }
        

        close(fd1[1]);
        
        wait(NULL);

        printf("\nValid numbers received within range are :\n");
        while (read(fd2[0],&result,sizeof(int))>0)
        {
            printf("%d\n",result);
        }
        close(fd2[0]);
    }
    else
    {
        sleep(5);
        close(fd1[1]);
        close(fd2[0]);
        
        read(fd1[0],&temp1,sizeof(int));
        read(fd1[0],&temp2,sizeof(int));


        while (read(fd1[0],&num2,sizeof(int))>0)
        {
            if (validate(num2,temp1,temp2)==1)
            {
                write(fd2[1],&num2,sizeof(int));
            }
        }
        close(fd2[1]);
    }


}