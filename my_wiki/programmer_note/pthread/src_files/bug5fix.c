/******************************************************************************
* FILE: bug5fix.c
* DESCRIPTION:
*   bug5.c is simply missing a pthread_exit call at the end of main. 
*   As a result, when main finishes, it goes away as do all of its threads. 
*   Adding a pthread_exit routine at the end of main will solve the problem.
* AUTHOR: 07/06/05 Blaise Barney
* LAST REVISED: 07/11/12
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
  printf("thread=%ld: starting...\n", (long)threadid);
  
  double myresult=0.0;
  for (int i=0; i<1000000; i++)
     myresult += sin(i) * tan(i);

  printf("thread=%ld result=%e. Done.\n",(long)threadid, myresult);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  for(long t=0;t<NUM_THREADS;t++)
  {
    printf("Main: creating thread %ld\n", t);
    int rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  printf("Main: Done.\n");
  pthread_exit(NULL);
}