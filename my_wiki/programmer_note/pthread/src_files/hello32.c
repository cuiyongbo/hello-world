/******************************************************************************
* FILE: hello32.c
* DESCRIPTION:
*   A "hello world" Pthreads program which creates a large number of 
*   threads per process.  A sleep() call is used to ensure that all
*   threads are in existence at the same time.  Each thread does some
*   work to demonstrate how the OS scheduler behavior affects thread 
*   completion order.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS	32

void *Hello(void *threadid)
{
  double result=0.0;
  sleep(3);
  for (int i=0; i<10000; i++)
    result = result + sin(i) * tan(i);

  printf("%ld: Hello World!\n", (long)threadid);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NTHREADS];
  long t;
  for(t=0;t<NTHREADS;t++)
  {
    int rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
    if (rc)
    {
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      printf("Code %d= %s\n",rc,strerror(rc));
      exit(-1);
    }
  }
  printf("main(): Created %ld threads.\n", t);
  pthread_exit(NULL);
}