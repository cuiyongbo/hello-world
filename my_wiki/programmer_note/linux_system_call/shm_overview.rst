****************************
POSIX shared memory overview
****************************

**DESCRIPTION**

   The POSIX shared memory API allows processes to communicate information
   by sharing a region of memory. The interfaces employed in the API are:

      shm_open(3)
         Create and open a new object, or open an existing object. This is analogous to open(2).
         The call returns a file descriptor for use by the other interfaces listed below.

      ftruncate(2)
         Set the size of the shared memory object. (A newly created shared memory object has
         a length of zero)

      mmap(2)        
         Map the shared memory object into the virtual address space of the calling process.

      munmap(2)      
         Unmap the shared memory object from the virtual address space of the calling process.

      shm_unlink(3)
         Remove a shared memory object name.

      close(2)       
         Close the file descriptor allocated by :manpage:`shm_open(3)` when it is no longer needed.

      fstat(2)       
         Obtain a stat structure that describes the shared memory object.
         Among the information returned by this call are the object's size (st_size),
         permissions (st_mode), owner (st_uid), and group (st_gid).

      fchown(2)      
         To change the ownership of a shared memory object.

      fchmod(2)      
         To change the permissions of a shared memory object.

   POSIX shared memory objects have kernel persistence: a shared memory object will exist
   until the system is shutdown, or until all processes have unmapped the object and it
   has been deleted with :manpage:`shm_unlink(3)`.

   On Linux, shared memory objects are created in a virtual filesystem(*tmpfs*),
   normally mounted under :file:`/dev/shm` or :file:`/run/shm`.

**NOTES**
       
   Typically, processes must synchronize their access to a shared memory object,
   using,for example, POSIX semaphores.

   System V shared memory (shmget(2), shmop(2), etc.) is an older shared memory API.
   POSIX shared memory provides a simpler, and better designed interface; on the other
   hand POSIX shared memory is somewhat less widely available (especially on older systems)
   than System V shared memory.

.. toctree::
   
   posix_shm_management_api
   ftruncate_info
   memory_mapped_io_note
   fstat_info
