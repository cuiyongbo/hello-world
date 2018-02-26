/******************************************************************************
* FILE: bug4fix.c
* DESCRIPTION:
*   This is just one way to resolve the synchronization problem demonstrated
*   by bug4.c. A check is made in watch_routine to make sure the pthread_cond_wait() 
*   call is not made if the value of count is not what it expects. Its work is
*   also placed after it is awakened, while count is locked.
* SOURCE: 07/06/05 Blaise Barney
* LAST REVISED: 03/07/17  Blaise Barney
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/* Define and scope what needs to be seen by everyone */
#define NUM_THREADS  3
#define ITERATIONS 10
#define THRESHOLD 12

int count = 0;
double finalResult=0.0;
pthread_mutex_t count_mutex;
pthread_cond_t count_condvar;

void *watch_routine(void *t)
{
  long tid = (long)t;

  /*
  Lock mutex and wait for signal only if count is what is expected.  Note
  that the pthread_cond_wait routine will automatically and atomically
  unlock mutex while it waits. Also, note that if THRESHOLD is reached
  before this routine is run by the waiting thread, the loop will be skipped
  to prevent pthread_cond_wait from never returning, and that this thread's
  work is now done within the mutex lock of count.
  */
  pthread_mutex_lock(&count_mutex);

  while(count != THRESHOLD)
  {
    printf("watch_routine: thread=%ld going into wait. count=%d\n",tid,count);
    pthread_cond_wait(&count_condvar, &count_mutex);
    printf("watch_routine: thread=%ld Condition variable signal received.",tid);
  }

  /* do some work */
  sleep(1);

  count++;
  printf("watch_routine: thread=%ld now count=%d finalResult=%e. Done.\n", tid,count,finalResult);
  
  pthread_mutex_unlock(&count_mutex);
  pthread_exit(NULL);
}

void *work_routine(void *t) 
{
  long tid = (long)t;
  double myresult=0.0;

  for (int i=0; i<ITERATIONS; i++) 
  {
    for (int j=0; j<100000; j++)
      myresult += sin(j) * tan(i);
    
    pthread_mutex_lock(&count_mutex);
    finalResult += myresult;
    count++;
    /* 
    Check the value of count and signal waiting thread when condition is
    reached.  Note that this occurs while mutex is locked. 
    */
    if (count == THRESHOLD) 
    {
      printf("work_routine: thread=%ld Threshold reached. count=%d. ",tid,count);
      pthread_cond_signal(&count_condvar);
      printf("Just sent signal.\n");
    }
    else
      printf("work_routine: thread=%ld did work. count=%d\n",tid,count);

    pthread_mutex_unlock(&count_mutex);
  }
  printf("work_routine: thread=%ld  myresult=%e. Done. \n",tid, myresult);
  pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&count_mutex, NULL);
  pthread_cond_init (&count_condvar, NULL);

  /* For portability, explicitly create threads in a joinable state */
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_t threads[3];
  long t1=1, t2=2, t3=3;
  pthread_create(&threads[0], &attr, watch_routine, (void *)t1);
  pthread_create(&threads[1], &attr, work_routine, (void *)t2);
  pthread_create(&threads[2], &attr, work_routine, (void *)t3);

  /* Wait for all threads to complete */
  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  printf ("Main(): Waited on %d threads. Final result=%e. Done.\n", NUM_THREADS,finalResult);

  /* Clean up and exit */
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&count_mutex);
  pthread_cond_destroy(&count_condvar);
  pthread_exit (NULL);
}
