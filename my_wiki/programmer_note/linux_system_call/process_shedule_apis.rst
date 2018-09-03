****************
Process Schedule
****************

#. nice - change process priority

   .. code-block:: c

      #include <unistd.h>
      int nice(int inc);

   nice()  adds  inc to the nice value for the calling process. (A higher nice value means a low priority.)  
   Only the superuser may specify a negative increment, or priority increase. The range for nice values is 
   described in getpriority(2).

   Since glibc 2.2.4, nice() is implemented as a library function that calls getpriority(2) to obtain the 
   new nice value to be returned to the caller. With this implementation, a successful call can legitimately 
   return -1.  To reliably detect an error, set errno to 0 before the call, and check its value when nice() 
   returns -1.

   .. code-block:: c
      :caption: Taken from *Advanced Programming in UNIX Environment*

      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>
      #include <errno.h>
      #include <unistd.h>
      #include <sys/param.h>
      #include <sys/time.h>
      
      unsigned long long g_count;
      struct timeval g_endTime;
      
      static void checkTime(const char* str)
      {
          struct timeval tv;
          gettimeofday(&tv, NULL);
          if(tv.tv_sec >= g_endTime.tv_sec && tv.tv_usec >= g_endTime.tv_usec)
          {
              printf("%s count = %lld\n", str, g_count);
              exit(0);
          }
      }
      
      void err_sys(const char* msg)
      {
          perror(msg);
          exit(1);
      }
      
      int main(int argc, char* argv[])
      {
          setvbuf(stdout, NULL, _IONBF, 0);
      
          int nzero;
      #if defined(NZERO)
          nzero = NZERO;
      #elif defined(_SC_NZERO)
          nzero = sysconf(_SC_NZERO);
      #else
      #error  NZERO undefined
      #endif
      
          printf("NZERO = %d\n", nzero);
          int adj = 0;
          if(argc == 2)
              adj = strtol(argv[1], NULL, 10);
          gettimeofday(&g_endTime, NULL);
          g_endTime.tv_sec += 10; /* run for 10 seconds*/
      
          const char* id = NULL;
          pid_t pid;
          if((pid = fork()) < 0)
          {
              err_sys("fork");
          }
          else if(pid == 0)
          {
              id = "child";
              printf("current nice value in child: %d, adjusting by %d\n", 
                      nice(0) + nzero, adj);
              errno = 0;
              int ret;
              if((ret=nice(adj)) == -1 && errno != 0)
                  err_sys("child set scheduling priority");
              printf("now child nice value is %d\n", ret + nzero);
          }
          else
          {
              id = "parent";
              printf("current nice value in parent is %d\n", nice(0) + nzero);
          }
      
          for(;;)
          {
              if(++g_count == 0) {
                  printf("%s counter wrap", id);
                  exit(1);
              }
              checkTime(id);
          }
      }

