#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc , char* argv[]) {
    int source;
    int dest;
    char buffer;
    char c;
    int start;
    int end;
    int i = 1;

    source = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT, 0644);

    if (source == -1 || dest == -1) {
        printf("error");
        exit(1); 
    }
    
    printf("Enter starting line : ");
    scanf("%d", &start);

    printf("Enter ending line : ");
    scanf("%d", &end);

    off_t start_pos = 0;
    off_t end_pos = 0;


    while (i < start) {
        read(source, &c, 1);
        start_pos = lseek(source, 0, SEEK_CUR);
        if (c == '\n') {
            i++;
        }
    }
    
    i = start;


    while (i <= end) {
        read(source, &c, 1);
        end_pos = lseek(source, 0, SEEK_CUR);
        if (c == '\n') {
            i++;
        }
    }
  
    lseek(source, start_pos, SEEK_SET);

    while (start_pos < end_pos) {
        read(source, &buffer, 1);
        write(dest, &buffer, 1);
        start_pos++;
    }

    printf("success\n");

    close(source);
    close(dest);

    return 0;
}
