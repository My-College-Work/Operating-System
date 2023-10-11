#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // open file
    char *filename = "test.txt";
    int fd = open(filename, O_WRONLY | O_CREAT, 0666);
    dup2(fd, 1);
    printf("Hello Again\n");
    return 0;
}