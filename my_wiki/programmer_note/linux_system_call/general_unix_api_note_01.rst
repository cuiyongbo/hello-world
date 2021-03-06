*******************
General Unix API 01
*******************

.. contents::
   :local:

open and possibly create a file or device
=========================================

**DESCRIPTION**

   .. code-block:: sh

      #include <sys/types.h>
      #include <sys/stat.h>
      #include <fcntl.h>
      int open(const char *pathname, int flags);
      int open(const char *pathname, int flags, mode_t mode);
      int creat(const char *pathname, mode_t mode);

   Given a pathname for a file, *open()* returns a file descriptor, 
   a small, nonnegative integer for use in subsequent system calls.  
   The file descriptor returned by a successful call will be the 
   lowest-numbered file descriptor not currently open for the process.

   By default, the new file descriptor is set to remain open across an execve(2) 
   (the FD_CLOEXEC file descriptor flag described in fcntl(2) is initially disabled; 
   the O_CLOEXEC flag can be used to change this default). The file offset is set to the 
   beginning of the file.

   A call to open() creates a new open file description, an entry in the system-wide table of open files.  
   **This entry records the file offset and the file status flags (modifiable via the fcntl(2) F_SETFL operation).**  
   A file descriptor is a reference to one of these entries; this reference is unaffected if *pathname* is 
   subsequently removed or modified to refer to a different file. The new open file description is initially not 
   shared with any other process, but sharing may arise via fork(2).

   The argument flags **MUST** include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR. 

   In addition, zero or more file creation flags and file status flags can be bitwise-or'd in flags. 
   The **file creation flags** are O_CLOEXEC, O_CREAT, O_DIRECTORY, O_EXCL, O_NOCTTY, O_NOFOLLOW, O_TRUNC, 
   and O_TTY_INIT. The **file status flags** are all of the remaining flags. 
   **The distinction between these two groups of flags is that the file status flags can be retrieved and modified using fcntl().** 
   For the full list of file creation flags and file status flags, refer to *open(2)* man page.

   *creat()* is equivalent to *open()* with flags equal to O_CREAT|O_WRONLY|O_TRUNC.

**RETURN VALUE**

   *open()* and *creat()* return the new file descriptor, or -1 if an error occurred
   (in which case, *errno* is set appropriately).

**NOTES**

   Under Linux, the *O_NONBLOCK* flag indicates that one wants to open but does not necessarily 
   have the intention to read or write. This is typically used to open devices in order to get
   a file descriptor for use with *ioctl(2)*.

   Unlike the other values that can be specified in flags, the access mode values O_RDONLY, O_WRONLY, and O_RDWR, 
   do not specify individual bits. Rather, they define the low order two bits of flags, and are defined respectively 
   as 0, 1, and 2. In other words, the combination O_RDONLY | O_WRONLY is a logical error, and certainly does not 
   have the same meaning as O_RDWR. Linux reserves the special, nonstandard access mode 3 (binary 11) in flags to mean: 
   check for read and write permission on the file and return a descriptor that can't be used for reading or writing.  
   This nonstandard access mode is used by some Linux drivers to return a descriptor that is to be used only for
   device-specific *ioctl(2)* operations.

   Note that *open()* can open device special files, but *creat()* cannot create them; use *mknod(2)* instead.

   On NFS filesystems with UID mapping enabled, open() may return a file descriptor but, for example, read(2) 
   requests are denied with EACCES. This is because the client performs open() by checking the permissions, 
   but UID mapping is performed by the server upon read and write requests.

   If the file is newly created, its st_atime, st_ctime, st_mtime fields (respectively, time of last access, 
   time of last status change, and time of last modification; see stat(2)) are set to the current time, and 
   so are the st_ctime and st_mtime fields of the parent directory. Otherwise, if the file is modified because 
   of the O_TRUNC flag, its st_ctime and st_mtime fields are set to the current time.

**BUGS**
   
   Currently, it is not possible to enable signal-driven I/O by specifying O_ASYNC when calling open(); 
   use fcntl(2) to enable this flag.


read - read from a file descriptor
==================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      ssize_t read(int fd, void *buf, size_t count);

   *read()* attempts to read up to *count* bytes from file descriptor *fd* into the buffer starting at *buf*.

   On files that support seeking, the read operation commences at the current file offset, and the file offset 
   is incremented by the number of bytes read. If the current file offset is at or past the end of file, no bytes 
   are read, and *read()* returns zero.

   If count is greater than *SSIZE_MAX*, the result is unspecified.

**RETURN VALUE**

   On success, the number of bytes read is returned (zero indicates end of file), 
   and the file position is advanced by this number. It is not an error if this number 
   is smaller than the number of bytes requested; this may happen for example because fewer
   bytes are actually available right now (maybe because we were close to end-of-file, or 
   because we are reading from a pipe, or from a terminal), or because *read()* was interrupted 
   by a signal. On error, -1 is returned, and *errno* is set appropriately. In this case it is 
   left unspecified whether the file position (if any) changes.


write - write to a file descriptor
==================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      ssize_t write(int fd, const void *buf, size_t count);

   *write()* writes up to *count* bytes from the buffer pointed *buf* to the file 
   referred to by the file descriptor *fd*.

   The number of bytes written may be less than *count* if, for example, there is insufficient 
   space on the underlying physical medium, or the *RLIMIT_FSIZE* resource limit is encountered, 
   or the call was interrupted by a signal handler after having written less than *count* bytes.

   For a seekable file writing takes place at the current file offset, and the file offset is 
   incremented by the number of bytes actually written. If the file was open(2)ed with O_APPEND, 
   the file offset is first set to the end of the file before writing. The adjustment of the file 
   offset and the write operation are performed as an atomic step.

**RETURN VALUE**

   On success, the number of bytes written is returned (zero indicates nothing was written).  
   On error, -1 is returned, and *errno* is set appropriately.

**NOTES**

   A successful return from **write()** does not make any guarantee that data has been committed to disk.  
   In fact, on some buggy implementations, it does not even guarantee that space has successfully been 
   reserved for the data. The only way to be sure is to call *fsync(2)* after you are done writing all your data.

   If a *write()* is interrupted by a signal handler before any bytes are written, then the call fails 
   with the error *EINTR*; if it is interrupted after at least one byte has been written, the call succeeds, 
   and returns the number of bytes written.


pread, pwrite - read from or write to a file descriptor at a given offset
=========================================================================

**DESCRIPTION**

   .. code-block:: c
   
      #include <unistd.h>
      ssize_t pread(int fd, void *buf, size_t count, off_t offset);
      ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);

   *pread()* reads up to *count* bytes from file descriptor *fd* at offset *offset* 
   (**from the start of the file**) into the buffer starting at *buf*. 
   **The file offset is not changed.**

   *pwrite()* writes up to *count* bytes from the buffer starting at *buf* 
   to the file descriptor fd at offset *offset*. **The file offset is not changed.**

   The file referenced by fd must be capable of seeking.

**RETURN VALUE**

   On success, *pread()* returns the number of bytes read 
   (a return of zero indicates end of file) and 
   *pwrite()* returns the number of bytes written.
   Note that is not an error for a successful call to 
   transfer fewer bytes than requested.
   On error, -1 is returned and *errno* is set to indicate the cause of the error.

**NOTES**

   The *pread()* and *pwrite()* system calls are especially 
   useful in multithreaded applications. They allow multiple 
   threads to perform I/O on the same file descriptor without  
   being affected by changes to the file offset by other threads.

**BUGS**

   POSIX requires that opening a file with the ``O_APPEND`` flag 
   should have no effect on the location at which *pwrite()* writes data.  
   However, on Linux, if a file is opened with ``O_APPEND``,  ``pwrite()``
   appends data to the end of the file, regardless of the value of offset.


close - close a file descriptor
===============================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      int close(int fd);

   *close()* closes a file descriptor, so that it no longer refers to any file and may be reused.  
   Any record locks (see *fcntl(2)*) held on the file it was associated with, and owned by the process, 
   are removed (regardless of the file descriptor that was used to obtain the lock).

   If *fd* is the last file descriptor referring to the underlying open file description (see open(2)), 
   the resources associated with the open file description are freed; if the descriptor was the last 
   reference to a file which has been removed using *unlink(2)* the file is deleted.

**RETURN VALUE**

   close() returns zero on success. On error, -1 is returned, and *errno* is set appropriately.

**NOTES**
   
   Not checking the return value of *close()* is a common but nevertheless serious programming error.  
   It is quite possible that errors on a previous *write(2)* operation are first reported at the final 
   *close()*. Not checking the return value when closing the file may lead to silent loss of data.  
   This can especially be observed with NFS and with disk quota.

   A successful close does not guarantee that the data has been successfully saved to disk, 
   as the kernel defers writes. It is not common for a filesystem to flush the buffers when 
   the stream is closed. If you need to be sure that the data is physically stored use fsync(2). 
   It will depend on the disk hardware at this point.

   It is probably unwise to close file descriptors while they may be in use by system calls in other 
   threads in the same process. Since a file descriptor may be reused, there are some obscure race 
   conditions that may cause unintended side effects.


link - make a new name for a file
=================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      int link(const char *oldpath, const char *newpath);

   *link()* creates a new link (also known as a hard link) to an existing file.
   If *newpath* exists it will not be overwritten.

   This new name may be used exactly as the old one for any operation; 
   both names refer to the same file (and so have the same permissions 
   and ownership) and it is impossible to tell which name was the "original".

**RETURN VALUE**

   On success, zero is returned. 
   On error, -1 is returned, and **errno** is set appropriately.


unlink - delete a name and possibly the file it refers to
=========================================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      int unlink(const char *pathname);

   *unlink()* deletes a name from the filesystem.  
   If that name was the last link to a file and 
   no processes have the file open the file is 
   deleted and the space it was using is made 
   available for reuse.

   If the name was the last link to a file but any processes 
   still have the file open the file will remain in existence 
   until the last file descriptor referring to it is closed.

   If the name referred to a symbolic link the link is removed.
   If the name referred to a socket, fifo or device the name 
   for it is removed but processes which have the object open 
   may continue to use it.

**RETURN VALUE**

   On success, zero is returned.  
   On error, -1 is returned, and *errno* is set appropriately.
