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
        printf("Hello from child\n");
        printf("my id = %d, parent_id = %d \n", getpid(), getppid());
    }
    else
    {
        printf("Hello from parent\n");
        printf("my_id = %d, child_id=%d, parent_id=%d\n", getpid(), pid, getppid());
        // sleep(1);
    }
    return 0;
}
