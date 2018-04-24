************
vfork Manual
************

**NAME**
  
   vfork - create a child process and block parent

**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      #include <sys/types.h>
      pid_t vfork(void);

**DESCRIPTION**

   ``vfork()``, just like :manpage:`fork(2)`, creates a child process of the calling process.
   For details and return value and errors, see :manpage:`fork(2)`.

   ``vfork()`` is a special case of :manpage:`clone(2)`. It is used to create new processes
   without copying the page tables of the parent process. It may be useful in performance-sensitive
   applications where a child is created which then immediately issues an :manpage:`execve(2)`.

   ``vfork()`` differs from ``fork()`` in that the calling thread is suspended until the child terminates
   (either normally, by calling :manpage:`_exit(2)`, or abnormally, after delivery of a fatal signal), or
   it makes a call to :manpage:`execve(2)`. Until that point, the child shares all memory with its parent,
   including the stack. The child must not return from the current function or call :manpage:`exit(3)`,
   but may call :manpage:`_exit(2)`.

   As with ``fork()``, the child process created by ``vfork()`` inherits copies of various of the caller's
   process attributes (e.g., file descriptors, signal dispositions, and current working directory); the ``vfork()``
   call differs only in the treatment of the virtual address space, as described above.

   Signals sent to the parent arrive after the child releases the parent's memory (i.e., after the child
   terminates or calls :manpage:`execve(2)`).

   Under Linux, ``fork()`` is implemented using copy-on-write pages, so the only penalty incurred by ``fork()``
   is the time and memory required to duplicate the parent's page tables, and to create a unique task structure
   for the child. However, in the bad old days a ``fork()`` would require making a complete copy of the caller's
   data space, often needlessly, since usually immediately afterward an :manpage:`exec(3)` is done. Thus, for
   greater efficiency, BSD introduced the ``vfork()`` system call, which did not fully copy the address space of
   the parent process, but borrowed the parent's memory and thread of control until a call to ``execve()`` or an
   exit occurred. The parent process was suspended while the child was using its resources. The use of ``vfork()``
   was tricky: for example, not modifying data in the parent process depended on knowing which variables were held
   in a register.

**CONFORMING TO**

   The requirements put on ``vfork()`` by the standards are weaker than those put on ``fork()``,
   so an implementation where the two are synonymous is compliant. In particular, the programmer
   cannot rely on the parent remaining blocked until the child either terminates or calls ``execve()``,
   and cannot rely on any specific behavior with respect to shared memory.

**NOTES**

   Some consider the semantics of ``vfork()`` to be an architectural blemish, and the 4.2BSD man page
   stated: "This system call will be eliminated when proper system sharing mechanisms are implemented.
   Users should not depend on the memory sharing semantics of ``vfork()`` as it will, in that case,
   be made synonymous to ``fork()``."  However, even though modern memory management hardware has
   decreased the performance difference between ``fork()`` and ``vfork()``, there are various reasons
   why Linux and other systems have retained ``vfork()``:

      * Some performance-critical applications require the small performance advantage conferred by ``vfork()``.

      * ``vfork()`` can be implemented on systems that lack a :abbr:`MMU (memory-management unit)`, but ``fork()``
        can't be implemented on such systems.

**BUGS**

   Details of the signal handling are obscure and differ between systems. The BSD man page
   states: "To avoid a possible deadlock situation, processes that are children in the middle
   of a ``vfork()`` are never sent ``SIGTTOU`` or ``SIGTTIN`` signals; rather, output or
   ioctls are allowed and input attempts result in an end-of-file indication."

**SEE ALSO**

   clone(2), execve(2), fork(2), unshare(2), wait(2)
