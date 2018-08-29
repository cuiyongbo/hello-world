***************
Special Process
***************

Zombie process
==============

On Unix and Unix-like computer operating systems, a **zombie process or defunct process** is a process 
that has completed execution (via the exit system call) but still has an entry in the process table: 
it is a process in the "Terminated state". This occurs for child processes, where the entry is still 
needed to allow the parent process to read its child's exit status: once the exit status is read via 
the wait system call, the zombie's entry is removed from the **process table** and it is said to be "reaped". 
A child process always first becomes a zombie before being removed from the resource table. In most cases, 
under normal system operation zombies are immediately waited on by their parent and then reaped by the 
system – processes that stay zombies for a long time are generally an error and cause a resource leak.

The term zombie process derives from the common definition of zombie — an undead person. 
In the term's metaphor, the child process has "died" but has not yet been "reaped". 
Also, unlike normal processes, **the kill command has no effect on a zombie process.**

Zombie processes should not be confused with **orphan processes:** an orphan process 
is a process that is still executing, but whose parent has died. These do not remain 
as zombie processes; instead, they are adopted by **init** (process ID 1), which waits 
on its children. The result is that a process that is both a zombie and an orphan 
will be reaped automatically.

.. code-block:: c

   /*
      Synchronously waiting for the specific child processes in a (specific) order 
      may leave zombies present longer than the above-mentioned "short period of time". 
      It is not necessarily a program bug.
   */

   #include <sys/wait.h>
   #include <stdlib.h>
   #include <unistd.h>
   
   int main(void)
   {
      pid_t pids[10];
      int i;
   
      for (i = 9; i >= 0; --i) {
         pids[i] = fork();
         if (pids[i] == 0) {
            sleep(i+1);
            _exit(0);
         }
      }
   
      for (i = 9; i >= 0; --i)
         waitpid(pids[i], NULL, 0);
   
      return 0;
   }

.. code-block:: c
   :caption: Taken from Advanced Programming in UNIX Environment

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   
   int main()
   {
       pid_t pid = fork();
       if(pid < 0)
       {
           perror("fork");
           exit(EXIT_FAILURE);
       }
       else if(pid == 0)
       {
           exit(EXIT_SUCCESS);
       }
   
       sleep(4);
       system("ps -o pid,ppid,status,tty,command");
       exit(EXIT_SUCCESS);
   }


Orphan process
==============

In a Unix-like operating system any orphaned process will be immediately adopted by the special init system process: 
the kernel sets the parent to init. This operation is called re-parenting and occurs automatically. Even though technically 
the process has the "init" process as its parent, it is still called an orphan process since the process that originally 
created it no longer exists. In other systems orphaned processes are immediately terminated by the kernel. In modern Linux 
systems, an orphan process may be reparented to a "subreaper" process instead of init.

A process can be orphaned unintentionally, such as when the parent process terminates or crashes. The process group mechanism 
in most Unix-like operating systems can be used to help protect against accidental orphaning, where in coordination with the 
user's shell will try to terminate all the child processes with the "hangup" signal (**SIGHUP**), rather than letting them 
continue to run as orphans. More precisely, as part of job control, when the shell exits, because it is the "session leader" 
(its session id equals its process id), the corresponding login session ends, and the shell sends SIGHUP to all its jobs 
(internal representation of process groups).

It is sometimes desirable to intentionally orphan a process, usually to allow a long-running job to complete without further 
user attention, or to start an indefinitely running service or agent; such processes (without an associated session) are known 
as **daemons,** particularly if they are indefinitely running. **A low-level approach is to fork twice, running the desired process 
in the grandchild, and immediately terminating the child. The grandchild process is now orphaned, and is not adopted by its grandparent, 
but rather by init.** Higher-level alternatives circumvent the shell's hangup handling, either telling the child process to ignore **SIGHUP,** 
or removing the job from the job table or telling the shell to not send SIGHUP on session end. 
In any event, the session id (process id of the session leader, the shell) does not change, and the process id of the session that has ended 
is still in use until all orphaned processes either terminate or change session id.

A server process is also said to be orphaned when the client that initiated the request unexpectedly crashes 
after making the request while leaving the server process running. These orphaned processes waste server resources
and can potentially leave a server starved for resources. However, there are several solutions to the orphan 
process problem:

   - Extermination is the most commonly used technique; in this case the orphan is killed.
   
   - Reincarnation is a technique in which machines periodically try to locate the parents 
     of any remote computations; at which point orphaned processes are killed.

   - Expiration is a technique where each process is allotted a certain amount of time 
     to finish before being killed. If need be a process may "ask" for more time to finish 
     before the allotted time expires.