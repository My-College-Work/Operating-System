#include <pthread.h>
#include <stdio.h>

void *hello()
{
    printf("Hello from thread!\n");
}

int main()
{
    pthread_t thread1, thread2;
    printf("Hello from main!\n");
    pthread_create(&thread1, NULL, hello, NULL);
    pthread_create(&thread2, NULL, hello, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}