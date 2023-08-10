#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argv, char *filename[])
{
    char buf[1024];
    int read_fd = open(filename[1], O_RDONLY);
    int n = read(read_fd, buf, sizeof(buf));
    int write_fd = open(filename[2], O_WRONLY | O_CREAT, 777);
    write(write_fd, buf, n);
    return 0;
}