#include <unistd.h>
#include <stdio.h>

int main()
{
    int pd[2];
    if (pipe(pd) == -1)
    {
        perror("pipe");
        return 1;
    }
    perror("pipe");
    printf("pd[0] = %d\n", pd[0]);
    printf("pd[1] = %d\n", pd[1]);
    return 0;
}