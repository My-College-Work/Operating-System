#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// print n processes fannings

int main()
{
    printf("Hello \n");
    pid_t parent = getpid();
    for (int i = 0; i < 9; i++)
    {
        pid_t pid = fork();
        if (pid > 0)
        {
            int status = -1;
            wait(&status);
            _exit(getpid());
        }
        else
        {
            printf("my id = %d, parent_id = %d \n", getpid(), getppid());
        }
    }

    return 0;
}
