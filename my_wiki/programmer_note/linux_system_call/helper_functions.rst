getpid & getppid
================

**NAME**

   getpid, getppid -- get parent or calling process identification


**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>

      pid_t getpid(void);
      pid_t getppid(void);


**DESCRIPTION**

   ``getpid()`` returns the process ID of the calling process. 
   The ID is guaranteed to be unique and is useful for
   constructing temporary file names.

   ``getppid()`` returns the process ID of the parent
   of the calling process.


**ERRORS**

   The ``getpid()`` and ``getppid()`` functions are always successful,
   and no return value is reserved to indicate an error.


**SEE ALSO**

   :manpage:`gethostid(2)`, :manpage:`compat(5)`


