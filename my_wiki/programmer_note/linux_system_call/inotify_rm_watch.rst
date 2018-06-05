****************
inotify_rm_watch
****************

**NAME**
       
   inotify_rm_watch - remove an existing watch from an inotify instance

**SYNOPSIS**

   .. code-block:: c

      #include <sys/inotify.h>
      int inotify_rm_watch(int fd, int wd);

**DESCRIPTION**

   *inotify_rm_watch()* removes the watch associated with the watch descriptor *wd* 
   from the inotify instance associated with the file descriptor *fd*.

   Removing a watch causes an *IN_IGNORED* event to be generated for this watch descriptor. 

**RETURN VALUE**

   On success, **inotify_rm_watch()** returns zero.  
   On error, -1 is returned and *errno* is set to indicate the cause of the error.

**ERRORS**

   EBADF  

      *fd* is not a valid file descriptor.

   EINVAL 

      The watch descriptor *wd* is not valid; 
      or *fd* is not an inotify file descriptor.
