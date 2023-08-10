#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }
    if (pid == 0)
    {
        printf("Hello \n");
        printf("my id = %d, parent_id = %d \n", getpid(), getppid());
    }
    else
    {
        printf("Hello \n");
        printf("my_id = %d, child_id=%d, parent_id=%d\n", getpid(), pid, getppid());
    }
    return 0;
}
