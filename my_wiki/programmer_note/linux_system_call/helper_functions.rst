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


gethostname & sethostname
=========================

**NAME**

   gethostname, sethostname -- get/set name of current host


**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      int gethostname(char *name, size_t namelen);
      int sethostname(const char *name, int namelen);


**DESCRIPTION**

   The ``gethostname()`` function returns the standard host name for the current processor,
   as previously set by ``sethostname()``.  The *namelen* argument specifies the size of the
   *name* array.  The returned *name* is null-terminated, unless insufficient space is provided.

   The ``sethostname()`` function sets the name of the host machine to be *name*, which has
   length *namelen*. This call is restricted to the super-user and is normally used only
   when the system is bootstrapped.

   Host names are limited in length to {``sysconf(_SC_HOST_NAME_MAX)``} characters, not
   including the trailing null, currently 255.


**RETURN VALUES**

   Upon successful completion, the value ``0`` is returned; otherwise the value ``-1`` is
   returned and the global variable ``errno`` is set to indicate the error.

**ERRORS**

   [EFAULT]           
      The *name* or *namelen* argument gave an invalid address.

   [ENAMETOOLONG]     
      The current host name is longer than namelen.  (For ``gethostname()`` only.)

   [EPERM]            
      The caller tried to set the host name and was not the super-user.


**SEE ALSO**

   :manpage:`sysconf(3)`, :manpage:`sysctl(3)`
