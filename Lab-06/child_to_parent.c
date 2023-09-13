#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
    if (pid > 0)
    {
        // parent
        // we don't need the write end of the pipe
        close(pd[1]);
        char message[100];
        ssize_t msg_len = read(pd[0], message, 100);
        if (msg_len == -1)
        {
            perror("read");
            return 1;
        }
        message[msg_len] = '\0';
        printf("Message from child: %s\n", message);
        close(pd[0]);
    }
    else
    {
        // child
        // we don't need the read end of the pipe
        close(pd[0]);
        char *message = "I am your Child!";
        ssize_t msg_len = write(pd[1], message, strlen(message));
        if (msg_len == -1)
        {
            perror("write");
            return 1;
        }
        close(pd[1]);
    }
    return 0;
}