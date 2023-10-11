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
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        execl("/bin/pwd", "pwd", NULL, NULL);
    }
    else
    {
        execl("/bin/ls", "ls", "-l", NULL);
        // wait(NULL);
        // printf("Child process finished\n");
    }
    return 0;
}