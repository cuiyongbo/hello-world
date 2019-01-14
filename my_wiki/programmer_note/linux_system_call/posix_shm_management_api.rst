*********************
shm_open & shm_unlink
*********************

**NAME**
   
    shm_open, shm_unlink - create/open or unlink POSIX shared memory objects

**SYNOPSIS**

    .. code-block:: c

        #include <sys/mman.h>
        #include <sys/stat.h>        /* For mode constants */
        #include <fcntl.h>           /* For O_* constants */

        /*Link with -lrt*/
        int shm_open(const char *name, int oflag, mode_t mode);
        int shm_unlink(const char *name);

**DESCRIPTION**

    ``shm_open()`` creates and opens a new, or opens an existing, POSIX shared memory object.
    A POSIX shared memory object is in effect a handle which can be used by unrelated processes
    to :manpage:`mmap(2)` the same region of shared memory. The ``shm_unlink()`` function performs
    the converse operation, removing an object previously created by ``shm_open()``.

    The operation of ``shm_open()`` is analogous to that of :manpage:`open(2)`. *name* specifies the
    shared memory object to be created or opened. For portable use, a shared memory object should
    be identified by a name of the form */somename*; that is, a null-terminated string of up to
    ``NAME_MAX`` (i.e., 255) characters consisting of an initial slash, followed by one or more
    characters, none of which are slashes.

    *oflag* is a bit mask created by ORing together exactly one of ``O_RDONLY`` or ``O_RDWR`` and
    any of the other flags listed here::

        O_RDONLY
        Open the object for read access.
        A shared memory object opened in this way
        can be mmap(2)ed only for read (``PROT_READ``) access.
   
        O_RDWR     
        Open the object for read-write access.
   
        O_CREAT    
        Create the shared memory object if it does not exist.
        A new shared memory object initially has zero length—the size of the object can
        be set using :manpage:`ftruncate(2)`. The newly allocated bytes of a shared memory
        object are automatically initialized to 0.

        O_EXCL 
        If ``O_CREAT`` was also specified, and a shared memory object with the given name
        already exists, return an error. The check for the existence of the object,
        and its creation if it does not exist, are performed atomically.

        O_TRUNC
        If the shared memory object already exists, truncate it to zero bytes.

    Definitions of these flag values can be obtained by including :file:`<fcntl.h>`.

    On successful completion ``shm_open()`` returns a new file descriptor referring to the
    shared memory object. This file descriptor is guaranteed to be the lowest-numbered file
    descriptor not previously opened within the process. The ``FD_CLOEXEC`` flag (see
    :manpage:`fcntl(2)`) is set for the file descriptor.

    The file descriptor is normally used in subsequent calls to :manpage:`ftruncate(2)`
    (for a newly created object) and :manpage:`mmap(2)`.  **After a call to mmap(2)
    the file descriptor may be closed without affecting the memory mapping.**

    The operation of ``shm_unlink()`` is analogous to ``unlink(2)``: it removes a shared memory
    object *name*, and, once all processes have unmapped the object, deallocates and destroys
    the contents of the associated memory region. After a successful ``shm_unlink()``, attempts
    to `shm_open()` an object with the same name will fail (unless ``O_CREAT`` was specified,
    in which case a new, distinct object is created).

**RETURN VALUE**

    On success, ``shm_open()`` returns a nonnegative file descriptor.
    On failure, ``shm_open()`` returns -1.  ``shm_unlink()`` returns 0
    on success, or -1 on error.
