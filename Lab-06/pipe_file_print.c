#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int pd[2];
    __pid_t pid;
    if (pipe(pd) == -1)
    {
        perror("pipe");
        return 1;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        // child
        // we don't need the write end of the pipe
        close(pd[1]);
        char filename[100];
        ssize_t len = read(pd[0], filename, 100);
        if (len == -1)
        {
            perror("read");
            return 1;
        }

        // print contents of file
        int fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            return 1;
        }
        char buffer[100];
        ssize_t bytes_read = read(fd, buffer, 100);
        if (bytes_read == -1)
        {
            perror("read");
            return 1;
        }
        buffer[bytes_read] = '\0';
        printf("Contents of file: %s\n", buffer);

        close(pd[0]);
    }
    else
    {
        // parent
        // we don't need the read end of the pipe
        close(pd[0]);
        char *filename = "temp.txt";
        ssize_t len = write(pd[1], filename, strlen(filename));
        if (len == -1)
        {
            perror("write");
            return 1;
        }
        close(pd[1]);
    }
    return 0;
}