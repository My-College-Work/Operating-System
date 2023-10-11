#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t x, wsem;
int readCount = 0;
int data = 0;
void * reader(void *i) {
   int k = (*(int *)i);
   while(1) {
       sem_wait(&x);
           readCount++;
           if(readCount == 1)
               sem_wait(&wsem);
       sem_post(&x);
       printf("Reader: %d, data: %d\n", k, data);
       sem_wait(&x);
           readCount--;
           if(readCount == 0)
               sem_post(&wsem);
       sem_post(&x);
       sleep(1);
   }
}




void * writer(void *i) {
   int k = (*(int *)i);
   while(1) {
       sem_wait(&wsem);
       printf("Writer: %d, data: %d\n", k, ++data);
       sem_post(&wsem);
       sleep(1);
   }
}


int main() {
   sem_init(&x, 0, 1);
   sem_init(&wsem, 0, 1);
   pthread_t red[5], wrt[5];
   int reader_id[5], writer_id[5];


   for(int i = 0; i < 5; i++) {
       reader_id[i] = i;
       pthread_create(&red[i], NULL, reader, (void*)&reader_id[i]);
   }


   for(int i = 0; i < 5; i++) {
       writer_id[i] = i;
       pthread_create(&wrt[i], NULL, writer, (void*)&writer_id[i]);
   }


   for(int i = 0; i < 5; i++) {
       pthread_join(red[i], NULL);
   }


   for(int i = 0; i < 5; i++) {
       pthread_join(wrt[i], NULL);
   }
   return 0;
}
