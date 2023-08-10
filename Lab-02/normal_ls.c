#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buf[100];
    char *currentDir = getcwd(buf, sizeof(buf));
    DIR *dir = opendir(currentDir);

    if (dir != NULL)
    {
        struct dirent *dirent = readdir(dir);
        while (dirent != NULL)
        {
            char *p = dirent->d_name;
            if (p[0] != '.')
            {
                printf("%s\n", p);
            }
            dirent = readdir(dir);
        }
    }
    else
    {
        printf("%s\n", "Error: No directory specified");
    }

    return 0;
}
