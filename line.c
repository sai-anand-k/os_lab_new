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
    char c;
    int bytes;
    int start;
    int end;
    int i;
    int size;

    source = open(argv[1],O_RDONLY );
    dest = open(argv[2],O_WRONLY | O_CREAT);

    if (source == -1 || dest == -1)
    {
        printf("error");
    }
    
    printf("Enter starting line : ");
    scanf("%d",&start);

    printf("Enter ending line : ");
    scanf("%d",&end);

    off_t start_pos = 0;
    off_t end_pos = 0;

    for (int i = 1; i < start; i++) {
        read(source, &c, 1);
        if (c == '\n') {
            start_pos = lseek(source, 0, SEEK_CUR);
        }
    }

    for (int i = start; i <= end; i++) {
        read(source, &c, 1);
        if (c == '\n') {
            end_pos = lseek(source, 0, SEEK_CUR);
        }
    }

    lseek(source,start_pos,SEEK_SET);

    while (start_pos < end_pos)
    {
        lseek(source,start_pos,SEEK_SET);
        read(source,&buffer,1);
        write(dest,&buffer,1);
        start_pos++;
    }
    if (start_pos==end_pos)
    {
        printf("success");
    }


}