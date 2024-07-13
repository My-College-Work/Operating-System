#include <pthread.h>
#include <stdio.h>

int global_var = 0;
pthread_mutex_t mutex;

void *increment()
{
    pthread_mutex_lock(&mutex);
    global_var++;
    printf("Global variable: %d\n", global_var);
    pthread_mutex_unlock(&mutex);
}
int main()
{
    pthread_t threads[5];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, (void *)increment, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Final value of global_var: %d\n", global_var);
    return 0;
}
