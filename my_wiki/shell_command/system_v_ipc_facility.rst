***************************
System V IPC Status Command
***************************

.. contents::
   :local:

.. note::

   Unix System V, commonly abbreviated SysV (and usually pronounced—though rarely written—as "System Five"), 
   is one of the first commercial versions of the Unix operating system. It was originally developed by 
   :abbr:`AT&T (American Telephone & Telegraph)` and first released in 1983.
   While :abbr:`POSIX (Portable Operating System Interface)` is the name of a family of related standards 
   specified by the IEEE to define the API.

ipcs - show information on IPC facilities
=========================================

**DESCRIPTION**
       
   ipcs shows information on the inter-process communication facilities for which
   the calling process has read access. By default it shows information about all
   three resources: shared memory segments, message queues, and semaphore arrays.

**OPTIONS**

   .. option:: -i, --id id

      Show full details on just the one resource element identified by id.
      This option needs to be combined with one of the three resource
      options: -m, -q or -s.

   .. option:: -m, --shmems

      Write information about active shared memory segments.

   .. option:: -q, --queues

      Write information about active message queues.

   .. option:: -s, --semaphores

      Write information about active semaphore sets.

   .. option:: -a, --all

      Write information about all three resources (default).

   The following options controle output formats, and of these
   options only one takes effect: the last one specified.

      .. option:: -c, --creator

         Show creator and owner.
   
      .. option:: -l, --limits

         Show resource limits.
   
      .. option:: -p, --pid

         Show PIDs of creator and last operator.
   
      .. option:: -t, --time

         Write time information. The time of the last control operation that changed
         the access permissions for all facilities, the time of the last ``msgsnd()``
         and ``msgrcv()`` operations on message queues, the time of the last ``shmat()``
         and ``shmdt()`` operations on shared memory, and the time of the last ``semop()``
         operation on semaphores.
   
      .. option:: -u, --summary

         Show status summary.

   The following options affect only the -l (--limits) option

      .. option:: -b, --bytes

         Print sizes in bytes.

      .. option:: --human

         Print sizes in human-readable format.

ipcrm - remove certain IPC resources
====================================

**DESCRIPTION**

   ipcrm removes System V IPC objects and associated data structures from the system.
   In order to delete such objects, you must be superuser, or the creator or owner
   of the object.

   System V IPC objects are of three types: shared memory, message queues, and semaphores.
   Deletion of a message queue or semaphore object is immediate (regardless of whether any
   process still holds an IPC identifier for the object). A shared memory object is only
   removed after all currently attached processes have detached (:manpage:`shmdt(2)`)
   the object from their virtual address space.**OPTIONS**

   Option::

      -M, --shmem-key shmkey
         Remove the shared memory segment created with shmkey
         after the last detach is performed.
   
      -m, --shmem-id shmid
         Remove the shared memory segment identified by shmid
         after the last detach is performed.
   
      -Q, --queue-key msgkey
         Remove the message queue created with msgkey.
   
      -q, --queue-id msgid
         Remove the message queue identified by msgid.
   
      -S, --semaphore-key semkey
         Remove the semaphore created with semkey.
   
      -s, --semaphore-id semid
         Remove the semaphore identified by semid.