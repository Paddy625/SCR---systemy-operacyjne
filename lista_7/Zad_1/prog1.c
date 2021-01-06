#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define NTHREADS 8

void *hello(void *threadid)
{
   printf("Hello SCR. Written by thread %d\n", threadid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
int rc; 
int t;

for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, hello, (void *)t);
  if (rc != 0){
    printf("Blad podczas tworzenia watku");
    exit(1);
    }
   }
 
printf("Program utworzył ilosc watkow rowna: %d\n", t);
pthread_exit(NULL);

}
