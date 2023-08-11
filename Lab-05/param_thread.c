#include <pthread.h>
#include <stdio.h>

void *message_print(void *ptr)
{
    char *message;
    message = (char *)ptr;
    printf("%s", message);
}

int main()
{
    pthread_t thread;
    char *message = "Hello I am param message!\n";
    printf("Hello from main!\n");
    pthread_create(&thread, NULL, message_print, (void *)message);
    pthread_join(thread, NULL);
    return 0;
}