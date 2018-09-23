***************
Non-local jumps
***************

.. warning::

   Following APIs make programs hard to understand and maintain.  
   If possible, an alternative should be used.

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
      
      /*    
         setjmp, sigsetjmp - save stack context for nonlocal goto
         longjmp, siglongjmp - nonlocal jump to a saved stack context
      */
      #include <setjmp.h>
      int setjmp(jmp_buf env);
      void longjmp(jmp_buf env, int val);

      int sigsetjmp(sigjmp_buf env, int savesigs);
      void siglongjmp(sigjmp_buf env, int val);

   *setjmp()* and *longjmp()* are useful for dealing with errors and interrupts 
   encountered in a low-level subroutine of a program. 

   *setjmp()* saves the stack context/environment in *env* for 
   later use by *longjmp().* The stack context will be invalidated 
   if the function which called *setjmp()* returns.

   *longjmp()* restores the environment saved by the last call of *setjmp()* 
   with the corresponding *env* argument. After *longjmp()* is completed, 
   program execution continues as if the corresponding call of *setjmp()* 
   had just returned the value *val.* *longjmp()* cannot cause 0 to be returned.  
   If *longjmp()* is invoked with a second argument of 0, 1 will be returned instead.

   *sigsetjmp()* is similar to *setjmp().* If, and only if, savesigs is nonzero, 
   the process's current signal mask is saved in *env* and will be restored if 
   a *siglongjmp()* is later performed with this *env.*

   *siglongjmp()* is similar to *longjmp()* except for the type of its *env* argument.  

**RETURN VALUE**
       
   *setjmp()* and *sigsetjmp()* return 0 if returning directly, 
   and nonzero when returning from *longjmp() or siglongjmp()* 
   using the saved context.

**EXAMPLE**

.. code-block:: c
   :caption: Taken from *Advanced Programming in UNIX Environment*

   #include "apue.h"
   #include <setjmp.h>
   
   #define TOK_ADD 5
   
   static jmp_buf env;
   char* tok_ptr; /* global pointer for get_token() */
   
   void do_line(char*);
   void cmd_add();
   int get_token();
   
   int main()
   {
      if(setjmp(env) != 0)
         err_sys("setjmp");
      
      char line[MAXLINE];
      while(fgets(line, MAXLINE, stdin) != NULL)
         do_line(line);
      exit(0);
   }
   
   void do_line(char* ptr)
   {
      int cmd;
      tok_ptr = ptr; 
      while((cmd = get_token()) > 0)
      {
         switch(cmd)
         {
            case TOK_ADD:
               cmd_add();
               break;
         }
      }
   }
   
   void cmd_add()
   {
      int token = get_token();
      if(token < 0) /* an error has occurred*/
         longjmp(env, 1);
      /* rest of processing for this command*/
   }
   
   int get_token()
   {
      /* fetch next token from line pointed by tok_ptr */
   }

.. code-block:: none
   :caption: stack change

   bottom of stack
   +--------------------------+
   | statck frame for main    | higher address
   +--------------------------+
   | statck frame for do_line |
   +--------------------------+
   | statck frame for cmd_add |
   +--------------------------+
   |                          | lower address

   /* execute longjmp() in cmd_add */

   bottom of stack
   +--------------------------+
   | statck frame for main    | higher address
   +--------------------------+
   |                          | lower address

