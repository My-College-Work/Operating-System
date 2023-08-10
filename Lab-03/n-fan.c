#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int n = 5;
// print n processes fannings

int main()
{
    printf("Hello \n");
    pid_t parent = getpid();
    // int status = -1;
    // wait(&status);
    for (int i = 0; i < n; i++)
    {
        pid_t pid;
        if (getpid() == parent)
            pid = fork();
        if (pid > 0)
        {
            // printf("my_id = %d, child_id=%d, parent_id=%d\n", getpid(), pid, getppid());
        }
        else
        {
            printf("my id = %d, parent_id = %d \n", getpid(), getppid());
            _exit(getpid());
        }
    }

    return 0;
}
