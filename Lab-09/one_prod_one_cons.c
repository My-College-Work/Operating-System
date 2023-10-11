#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>


int buf[4];
sem_t s, n, size;


void *producer()
{
   while (1)
   {
       sem_wait(&size);
       sem_wait(&s);
       printf("Producer\n");
       sem_post(&s);
       sem_post(&n);
       sleep(1);
   }
}


void *consumer()
{
   while (1)
   {
       sem_wait(&n);
       sem_wait(&s);
       printf("Consumer\n");
       sem_post(&s);
       sem_post(&size);
       sleep(1);
   }
}


int main()
{
   sem_init(&s, 0, 1);
   sem_init(&n, 0, 0);
   sem_init(&size, 0, 4);
   pthread_t pr, con;


   pthread_create(&pr, NULL, producer, NULL);
   pthread_create(&con, NULL, consumer, NULL);


   pthread_join(pr, NULL);
   pthread_join(con, NULL);
   return 0;
}
