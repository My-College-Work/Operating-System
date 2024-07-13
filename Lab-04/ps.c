#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    DIR *dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("Error opening directory");
        return 1;
    }
    else
    {
        struct dirent *dirent = readdir(dir);
        while (dirent != NULL)
        {
            char *buf = dirent->d_name;
            if (isdigit(buf[0]))
            {
                char p[] = "/proc/";
                strcat(p, buf);
                strcat(p, "/stat");
                FILE *f = fopen(p, "r");
                if (f == NULL)
                {
                    printf("Error opening");
                }
                char data[1000];
                int i;
                char c;
                int size = fscanf(f, "%d %s %c", &i, data, &c);
                if (c == 'R')
                    printf("Process Id: %d Name:%s\n", i, data);
            }
            dirent = readdir(dir);
        }
    }
    return 0;
}
