/******************************************************************************
* FILE: bug2fix.c
* DESCRIPTION:
*   This is just one way to fix the "hello world" Pthreads program that dumps 
*   core.  Things to note:
*     - attr variable and its scoping
*     - use of the pthread_attr_setstacksize routine
*     - initialization of the attr variable with pthread_attr_init
*     - passing the attr variable to pthread_create
* AUTHOR: 9/98 Blaise Barney 
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS	8
#define ARRAY_SIZE      5000000
#define MEGEXTRA        10000000

pthread_attr_t attr;

void *Hello(void *threadid)
{
  sleep(3);
  double A[ARRAY_SIZE];
  for (int i=0; i<ARRAY_SIZE; i++)
    A[i] = i * 1.0;
   
  long tid = (long)threadid;
  printf("%ld: Hello World!   %f\n", tid, A[ARRAY_SIZE-1]);
  size_t mystacksize;
  pthread_attr_getstacksize (&attr, &mystacksize);
  printf("%ld: Thread stack size = %d bytes \n", tid, (int)mystacksize);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_attr_init(&attr);
  size_t stacksize = ARRAY_SIZE*sizeof(double) + MEGEXTRA;
  pthread_attr_setstacksize (&attr, stacksize);
  pthread_attr_getstacksize (&attr, &stacksize);
  printf("Thread stack size = %d bytes.\n", (int)stacksize);
  
  long t;
  pthread_t threads[NTHREADS];
  for(t=0;t<NTHREADS;t++)
  {
    int rc = pthread_create(&threads[t], &attr, Hello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  printf("Created %ld threads.\n", t);
  pthread_exit(NULL);
}