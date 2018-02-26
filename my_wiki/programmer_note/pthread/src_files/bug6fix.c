/*****************************************************************************
* FILE: bug6fix.c
* DESCRIPTION:
*   This example demonstrates a race condition with a global variable that
*   gives obviously wrong results. Figure out how to fix the problem - or see
*   bug6fix.c for one solution. The dotprod_mutex.c example provides a much
*   more efficient way of solving this problem than bug6fix.c (FYI).
* SOURCE: 07/06/05 Blaise Barney
* LAST REVISED: 01/29/09 Blaise Barney
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Define global data where everyone can see them */
#define NUMTHRDS 8
#define VECLEN 100000
int *a, *b; 
long sum=0;
pthread_mutex_t sum_mutex;


void *dotprod(void *arg)
{
  /* Each thread works on a different set of data.
   * The offset is specified by the arg parameter. The size of
   * the data for each thread is indicated by VECLEN.
   */
   long tid = (long)arg;
   int offset = tid;
   int len = VECLEN;
   int start = offset*len;
   int end   = start + len;

/* Perform my section of the dot product */
   printf("thread: %ld starting. start=%d end=%d\n",tid,start,end-1);
   for (int i=start; i<end ; i++) 
   {
      pthread_mutex_lock(&sum_mutex);
      sum += (a[i] * b[i]);
      pthread_mutex_unlock(&sum_mutex);
   }
   printf("thread: %ld done. Global sum now is=%ld\n",tid,sum);

   pthread_exit((void*) 0);
}



int main (int argc, char *argv[])
{
  
  /* Assign storage and initialize values */
  a = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
  b = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
    
  for (long i=0; i<VECLEN*NUMTHRDS; i++)
    a[i]= b[i]=1;
  
  pthread_mutex_init(&sum_mutex, NULL);
  /* Create threads as joinable, each of which will execute the dot product
   * routine. Their offset into the global vectors is specified by passing
   * the "i" argument in pthread_create().
   */
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  pthread_t threads[NUMTHRDS];
  for(long i=0; i<NUMTHRDS; i++) 
    pthread_create(&threads[i], &attr, dotprod, (void *)i); 
  
  pthread_attr_destroy(&attr);
  
  /* Wait on the threads for final result */
  for(long i=0; i<NUMTHRDS; i++) 
    pthread_join(threads[i], NULL);
  
  /* After joining, print out the results and cleanup */
  pthread_mutex_destroy(&sum_mutex);
  printf ("Final Global Sum=%ld\n",sum);
  free (a);
  free (b);
  pthread_exit(NULL);
}   
