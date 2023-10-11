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
        dup2(pd[1], 1);
        execl("/bin/ls", "ls", "-l", NULL);
        close(pd[1]);
    }
    else
    {
        wait(NULL);
        close(pd[1]);
        dup2(pd[0], 0);
        execl("/bin/sort", "sort", "-k", "9,9", NULL);
        close(pd[0]);
    }
    return 0;
}
