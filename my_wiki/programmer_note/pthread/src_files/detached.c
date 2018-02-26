/*****************************************************************************
* FILE: detached.c
* DESCRIPTION:
*   This example demonstrates how to explicitly create a thread in a 
*   detached state. This might be done to conserve some system resources
*   if the thread never needs to join later. Compare with the join.c program
*   where the threads are created joinable.
* AUTHOR: 01/30/08 Blaise Barney
* LAST REVISED: 01/29/09  
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	4

void* BusyWork(void *t)
{
  double result=0.0;
  long tid = (long)t;
  printf("Thread %ld starting...\n",tid);

  for (long i=0; i<1000000; i++)
    result = result + sin(i) * tan(i);

   printf("Thread %ld done. Result = %e\n",tid, result);
}

int main(int argc, char *argv[])
{
  /* Initialize and set thread detached attribute */
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  
  pthread_t thread[NUM_THREADS];
  for(long t=0; t<NUM_THREADS; t++) 
  {
    printf("Main: creating thread %ld\n", t);
    int rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
    if (rc) 
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  
  /* We're done with the attribute object, so we can destroy it */
  pthread_attr_destroy(&attr);
  
  /* The main thread is done, so we need to call pthread_exit explicitly to
  *  permit the working threads to continue even after main completes.
  */
  printf("Main: program completed. Exiting.\n");
  pthread_exit(NULL);
}
