#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>


int buf[4];
sem_t s, n;


void *producer(void *i)
{
   int id = (*(int *)i);
   while (1)
   {
       // sem_wait(&size);
       sem_wait(&s);
       printf("Producer : %d\n", id);
       sem_post(&s);
       sem_post(&n);
       sleep(2);
   }
}


void *consumer(void *i)
{
   int id = (*(int *)i);
   while (1)
   {
       sem_wait(&n);
       sem_wait(&s);
       printf("Consumer : %d\n", id);
       sem_post(&s);
       // sem_post(&size);
       sleep(1);
   }
}


int main()
{
   sem_init(&s, 0, 1);
   sem_init(&n, 0, 0);
   // sem_init(&size, 0, 4);
   pthread_t pr[5], con[5];
   int pro_id[5];
   int con_id[5];


   for (int i = 0; i < 5; i++)
   {
       pro_id[i] = i;
       pthread_create(&pr[i], NULL, producer, (void *)&pro_id[i]);
   }


   for (int i = 0; i < 5; i++)
   {
       con_id[i] = i;
       pthread_create(&con[i], NULL, consumer, (void *)&con_id[i]);
   }


   for (int i = 0; i < 5; i++)
   {
       pthread_join(pr[i], NULL);
   }


   for (int i = 0; i < 5; i++)
   {
       pthread_join(con[i], NULL);
   }


   return 0;
}
