*****************
exit system calls
*****************

#. atexit - register a function to be called at normal process termination
   
   .. code-block:: c

      /*
         int atexit(void (*function)(void));

         The atexit() function registers the given function to be called at normal process 
         termination, either via exit(3) or via return from the program's main(). Functions 
         so registered are called in the reverse order of their registration; no arguments are
         passed. The same function may be registered multiple times: it is called once for each 
         registration.

         When a child process is created via fork(2), it inherits copies of its parent's registrations.  
         Upon a successful call to one of the exec(3) functions, all registrations are removed.
      */

      #include <stdio.h>
      #include <stdlib.h>
      
      void exit_handle_1()
      {
          printf("exit_handle_1\n");
      }
      
      void exit_handle_2()
      {
          printf("exit_handle_2\n");
      }
      
      int main()
      {
          atexit(exit_handle_2);    
          atexit(exit_handle_1);    
          atexit(exit_handle_1);    
          printf("Hello world\n");
          return 0;
      }

   Output::

      Hello world
      exit_handle_1
      exit_handle_1
      exit_handle_2
      0