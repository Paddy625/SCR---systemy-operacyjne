//Autor: Adam Twardowski

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h> 
#define NTHREADS	25
#define DIM             2
#define MEGEXTRA        100
#define ITER            1000000

pthread_attr_t attr;
double pi_t[NTHREADS];

void *Hello(void *threadid)
{
   double A[DIM];
   double rand, pi;
   double circle = 0.0; 
   double square = 0.0;
   int i;
   long tid;
   size_t mystacksize;
   srand48(time(NULL));
   tid = (long)threadid;
   for (i=0; i<ITER; i++)
   {
   A[0] = drand48() - 0.5;
   A[1] = drand48() - 0.5;
   square = square + 1.0;
   if ( sqrt(A[0]*A[0]+A[1]*A[1]) <= 0.5)
     {
      circle = circle + 1.0;
     }
   }
   pi_t[tid] = circle / square * 4.0;
   pthread_attr_getstacksize (&attr, &mystacksize);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NTHREADS];
   size_t stacksize;
   int rc; 
   long t;
   double pi_s = 0.0;
   double pi_e = 0.0;
   void *status;
   pthread_attr_init(&attr);
   stacksize = DIM*sizeof(double) + MEGEXTRA;
   pthread_attr_setstacksize (&attr, stacksize);
   pthread_attr_getstacksize (&attr, &stacksize);
   for(t=0;t<NTHREADS;t++){
     rc = pthread_create(&threads[t], &attr, Hello, (void *)t);
       if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
         }
     }
   pthread_attr_destroy(&attr);
   for(t=0; t<NTHREADS; t++) {
     rc = pthread_join(threads[t], &status);
       if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
         }
     }

   for(t=0;t<NTHREADS;t++){
     pi_s = pi_s + pi_t[t];
     printf("%ld: pi = %f\n", t, pi_t[t]);
     }
   pi_e = pi_s / NTHREADS;
   printf("Created %ld threads.\n", t);
   printf("Estimated pi = %f\n" , pi_e);
   pthread_exit(NULL);
}
