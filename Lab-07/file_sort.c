#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int pd[2];
    if (pipe(pd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        close(pd[0]);

        char buffer[100];
        int fd = open("test.txt", O_RDONLY);
        read(fd, buffer, 100);

        write(pd[1], buffer, sizeof(buffer));

        close(pd[1]);
    }
    else
    {
        wait(NULL);
        close(pd[1]);
        dup2(pd[0], 0);
        execl("/bin/sort", "sort", NULL, NULL);

        close(pd[0]);
    }
    return 0;
}