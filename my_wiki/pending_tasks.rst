*************
Pending tasks
*************

#. speed up ti tile compilation
   - extract PointMap building
   - Grid splitting

#. review json code.

#. https://en.wikipedia.org/wiki/Jordan_curve_theorem

#. introduction to algorithm - data structure
   
#. http://geomalgorithms.com/
#. http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
   
#. https://en.wikipedia.org/wiki/Normal_distribution
#. https://en.wikipedia.org/wiki/Discrete_uniform_distribution

#. https://en.wikipedia.org/wiki/Selection_algorithm
   
#. http://www.kohala.com/start/

#. http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.22.6768 (about float point number)
    
#. http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html (C++ Input/Output)
   

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>


void* thread_func(void* )
{
   while(1)
   {
      sleep(5);
   }
   pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
   pthread_t tid;
   if(pthread_create(&tid, NULL, thread_func, NULL ) != 0)
   {
      perror("pthread_create"); 
      exit(EXIT_FAILURE);
   }

   pid_t pid = fork();
   if (pid == -1)
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      printf("Hello, this is the child process<%d>, inheriting parent process<%d>",
                                             (int)getpid(), (int)getppid());
      //exit(EXIT_SUCCESS);
   }
   else
   {
      printf("Hello, this is parent process<%d>, creating child process<%d>", (int)getpid(), (int)pid);
      int status;
      pid_t childId = wait(&status);
      if(childId != -1)
         printf("Child process<%#x> terminated with %d", childId, status);
   }

   pthread_join(tid, NULL);

   return 0;
}
