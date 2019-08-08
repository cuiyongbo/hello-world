:orphan:

***********************************
umask - set file mode creation mask
***********************************

**SYNOPSIS**

    .. code-block:: c

        #include <sys/types.h>
        #include <sys/stat.h>
        mode_t umask(mode_t mask);

**DESCRIPTION**

   ``umask()`` sets the calling process's file mode creation mask (umask)
   to ``mask & 0777`` (i.e., only the file permission bits of mask are used),
   and returns the previous value of the mask.

   The *umask* is used by :manpage:`open(2)`, :manpage:`mkdir(2)`, and other
   system calls that create files to modify the permissions placed on newly
   created files or directories. Specifically, permissions in the *umask* are
   turned off from the *mode* argument to :manpage:`open(2)`, :manpage:`mkdir(2)`.

   Alternatively, if the parent directory has a default ACL (see :manpage:`acl(5)`),
   the *umask* is ignored, the default ACL is inherited, the permission bits are set
   based on the inherited ACL, and permission bits absent in the *mode* argument are
   turned off. For example, the following default ACL is equivalent to a 
   *umask* of 022: ``u::rwx,g::r-x,o::r-x``.

   Combining the effect of this default ACL with a *mode* argument of ``0666 (rw-rw-rw-)``,
   the resulting file permissions would be ``0644 (rw-r--r--)``.

   The constants that should be used to specify mask are described under :manpage:`stat(2)`.

   The typical default value for the process umask is ``S_IWGRP | S_IWOTH`` (octal 022). 
   In the usual case where the *mode* argument to :manpage:`open(2)` is specified as::

      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

   (octal 0666) when creating a new file, the permissions on the resulting file will be::

      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

   (because 0666 & ~022 = 0644; i.e., rw-r--r--).


**RETURN VALUE**

   This system call always succeeds and the previous value of the mask is returned.

**NOTES**

   A child process created via :manpage:`fork(2)` inherits its parent's umask.
   The *umask* is left unchanged by :manpage:`execve(2)`.

   The umask setting also affects the permissions assigned to POSIX IPC objects
   (:manpage:`mq_open(3)`, :manpage:`sem_open(3)`, :manpage:`shm_open(3)`),
   FIFOs (:manpage:`mkfifo(3)`), and UNIX domain sockets (:manpage:`unix(7)`)
   created by the process. The umask does not affect the permissions assigned
   to System V IPC objects created by the process (using :manpage:`msgget(2)`,
   :manpage:`semget(2)`, :manpage:`shmget(2)`).

   You may refer to acl(5) for further information

