#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argv, char *filename[])
{
    if (argv == 1)
    {
        while (1)
        {
            char buf[1];
            int n = read(0, buf, sizeof(buf));
            int print = write(1, buf, n);
        }
    }
    int i = 1;
    while (i < argv)
    {
        char buf[1000];
        int fd = open(filename[i], O_RDONLY);
        int n = read(fd, buf, sizeof(buf));
        write(1, buf, n);
        i++;
    }
    return 0;
}
