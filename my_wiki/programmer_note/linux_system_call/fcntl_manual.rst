************
fcntl Manual
************

**NAME**
   
   fcntl - manipulate file descriptor

**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      #include <fcntl.h>
      int fcntl(int fd, int cmd, ... /* arg */ );

**DESCRIPTION**

   *fcntl()* performs one of the operations described below on the open file descriptor *fd*.  
   The operation is determined by *cmd*.

   *fcntl()*  can take an optional third argument. Whether or not this argument is required is determined by *cmd*.  
   The required argument type is indicated in parentheses after each cmd name (in most cases, the required type is *int*, 
   and we identify the argument using the name *arg*), or void is specified if the argument is not required.

   **File descriptor flags**

      The following commands manipulate the flags associated with a file descriptor. 
      Currently, only one such flag is defined: FD_CLOEXEC, the close-on-exec flag:: 

         F_GETFD (void)
         Read the file descriptor flags; arg is ignored.
   
         F_SETFD (int)
         Set the file descriptor flags to the value specified by arg.

   **File status flags**

      Each open file description has certain associated status flags, initialized by *open(2)* 
      and possibly modified by *fcntl()*. The file status flags and their semantics are described 
      in *open(2)* ::

         F_GETFL (void)
         Get the file access mode and the file status flags; arg is ignored.
   
         F_SETFL (int)
         Set the file status flags to the value specified by arg. 
         File access mode (O_RDONLY, O_WRONLY, O_RDWR) and file creation flags 
         (i.e., O_CREAT, O_EXCL, O_NOCTTY, O_TRUNC) in arg are ignored. On Linux 
         this command can change only the O_APPEND, O_ASYNC, O_DIRECT, O_NOATIME, 
         and O_NONBLOCK flags.
  

**RETURN VALUE**

   For a successful call, the return value depends on the operation.
   On error, -1 is returned, and errno is set appropriately.

**NOTES**
   
   The original Linux *fcntl()* system call was not designed to handle large file offsets (in the flock structure).  
   Consequently, an *fcntl64()* system call was added in Linux 2.4. The newer system call employs a different structure 
   for file locking, flock64, and corresponding commands, F_GETLK64, F_SETLK64, and F_SETLKW64. However, these details 
   can be ignored by applications using glibc, whose fcntl() wrapper function transparently employs the more recent system 
   call where it is available.
