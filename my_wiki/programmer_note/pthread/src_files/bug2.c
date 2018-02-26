/******************************************************************************
* FILE: bug2.c
* DESCRIPTION:
*   A "hello world" Pthreads program that dumps core.  Figure out why and
*   then fix it - or else see the solution bug2fix.c.
* AUTHOR: 9/98 Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS	8
#define ARRAY_SIZE      5000000

void *Hello(void *threadid)
{
   sleep(3);
   double A[ARRAY_SIZE];
   for (int i=0; i<ARRAY_SIZE; i++)
      A[i] = i * 1.0;

   printf("%ld: Hello World!   %f\n", (long)threadid, A[ARRAY_SIZE-1]);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  size_t stacksize;
  pthread_attr_getstacksize (&attr, &stacksize);
  printf("Thread stack size = %d bytes (hint, hint)\n", (int)stacksize);
  
  long t;
  pthread_t threads[NTHREADS];
  for(t=0;t<NTHREADS;t++)
  {
    int rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  printf("Created %ld threads.\n", t);
  pthread_exit(NULL);
}