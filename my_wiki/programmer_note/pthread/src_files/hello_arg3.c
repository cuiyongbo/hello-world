/*****************************************************************************
* FILE: hello_arg3.c
* DESCRIPTION:
*   This "hello world" Pthreads program demonstrates an unsafe (incorrect)
*   way to pass thread arguments at thread creation.  In this case, the
*   argument variable is changed by the main thread as it creates new threads.
* AUTHOR: Blaise Barney
* LAST REVISED: 07/16/14
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS     8

void *PrintHello(void *threadid)
{
   sleep(1);
   long taskid = *(long *)threadid;
   printf("Hello from thread %ld\n", taskid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  for(long t=0;t<NUM_THREADS;t++) 
  {
    printf("Creating thread %ld\n", t);
    int rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
    if (rc) 
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}
