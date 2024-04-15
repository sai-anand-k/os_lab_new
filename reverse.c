#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc , char* argv[])
{
    int source;
    int dest;
    char buffer;

    source = open(argv[1],O_RDWR );
    dest = open(argv[2],O_RDWR | O_CREAT);

    if (source == -1 || dest == -1)
    {
        printf("error");
    }

    off_t size = lseek(source,0,SEEK_END);
    for (off_t i = size - 1 ; i>=0 ; i--)
    {
        lseek(source , i , SEEK_SET);
        read(source,&buffer,1);
        write(dest,&buffer,1);
    }



}
