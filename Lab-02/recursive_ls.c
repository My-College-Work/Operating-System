#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 1000

int main(int argc, char **argv)
{
    char buf[MAX_PATH_LENGTH];
    char *currentDir = getcwd(buf, sizeof(buf));
    char *temp[1000];

    temp[0] = strdup(currentDir); // Use strdup to dynamically allocate memory for the currentDir path
    int i = 0;
    int cnt = 1;

    while (i < cnt)
    {
        DIR *dir = opendir(temp[i]);
        if (dir == NULL)
        {
            perror("Error opening directory");
            return 1;
        }

        printf("%s\n", temp[i]);

        struct dirent *dirent = readdir(dir);
        while (dirent != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
                printf("%s ", dirent->d_name);
                if (dirent->d_type == DT_DIR)
                {
                    char *p = (char *)malloc(MAX_PATH_LENGTH); // Allocate memory for the new path
                    if (p == NULL)
                    {
                        perror("Memory allocation error");
                        return 1;
                    }
                    snprintf(p, MAX_PATH_LENGTH, "%s/%s", temp[i], dirent->d_name);
                    temp[cnt++] = p;
                }
            }
            dirent = readdir(dir);
        }
        printf("\n\n");
        closedir(dir);

        i++;
    }

    // Free dynamically allocated memory for path strings
    for (int j = 0; j < cnt; j++)
    {
        if (temp[j] != currentDir) // Only free dynamically allocated paths
            free(temp[j]);
    }

    return 0;
}
