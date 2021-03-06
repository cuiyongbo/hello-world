***************
Get file status
***************

**DESCRIPTION**

   .. code-block:: c

      #include <sys/types.h>
      #include <sys/stat.h>
      #include <unistd.h>

      int stat(const char *pathname, struct stat *buf);
      int fstat(int fd, struct stat *buf);
      int lstat(const char *pathname, struct stat *buf);

      #include <fcntl.h>           /* Definition of AT_* constants */
      #include <sys/stat.h>

      int fstatat(int dirfd, const char *pathname, struct stat *buf, int flags);

   These functions return information about a file, in the buffer pointed to by *buf*.
   No permissions are required on the file itself, but—in the case of ``stat()``,
   ``fstatat()``, and ``lstat()``—execute (search) permission is required on all
   of the directories in *pathname* that lead to the file.

   ``stat()`` and ``fstatat()`` retrieve information about the file pointed to by
   *pathname*; the differences for ``fstatat()`` are described below.

   ``lstat()`` is identical to ``stat()``, except that if *pathname* is a symbolic link,
   then it returns information about the link itself, not the file that it refers to.

   ``fstat()`` is identical to ``stat()``, except that the file about which information
   is to be retrieved is specified by the file descriptor *fd*.

   All of these system calls return a stat structure, which contains
   the following fields::

      struct stat {
         dev_t     st_dev;         /* ID of device containing file */
         ino_t     st_ino;         /* inode number */
         mode_t    st_mode;        /* protection & file type */
         nlink_t   st_nlink;       /* number of hard links */
         uid_t     st_uid;         /* user ID of owner */
         gid_t     st_gid;         /* group ID of owner */
         dev_t     st_rdev;        /* device ID (if special file) */
         off_t     st_size;        /* total size, in bytes, for regular file */
         blksize_t st_blksize;     /* blocksize for filesystem I/O */
         blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

         /* Since Linux 2.6, the kernel supports nanosecond
            precision for the following timestamp fields.
            For the details before Linux 2.6, see NOTES. */

         struct timespec st_atim;  /* time of last access */
         struct timespec st_mtim;  /* time of last modification, file content changes*/
         struct timespec st_ctim;  /* time of last status change, permission changes */

         #define st_atime st_atim.tv_sec      /* Backward compatibility */
         #define st_mtime st_mtim.tv_sec
         #define st_ctime st_ctim.tv_sec
      };

   Note: the order of fields in the stat structure varies somewhat across architectures.
   In addition, the definition above does not show the padding bytes that may be present
   between some fields on various architectures. Consult the glibc and kernel source code
   if you need to know the details.

   Note: For performance and simplicity reasons, different fields in the stat structure may
   contain state information from different moments during the execution of the system call.
   For example, if *st_mode* or *st_uid* is changed by another process by calling :manpage:`chmod(2)`
   or :manpage:`chown(2)`, ``stat()`` might return the old *st_mode* together with the new *st_uid*,
   or the old *st_uid* together with the new *st_mode*.

   The *st_dev* field describes the device on which this file resides. (The :manpage:`major(3)`
   and :manpage:`minor(3)` macros may be useful to decompose the device ID in this field.)

   The *st_rdev* field describes the device that this file (inode) represents.

   The *st_size* field gives the size of the file (if it is a regular file or a symbolic link)
   in bytes. The size  of a symbolic link is the length of the *pathname* it contains, without
   a terminating null byte. [not true, the file size the link directs to]

   The *st_blocks* field indicates the number of blocks allocated to the file, 512-byte units.
   (This may be smaller than ``st_size/512`` when the file has holes.)

   The *st_blksize* field gives the "preferred" blocksize for efficient filesystem I/O.
   (Writing to a file in smaller chunks may cause an inefficient read-modify-rewrite.)

   Not all of the Linux filesystems implement all of the time fields.  Some filesystem types
   allow mounting in such a way that file and/or directory accesses do not cause an update of
   the *st_atime* field. (See noatime, nodiratime, and relatime in :manpage:`mount(8)`, and
   related information in :manpage:`mount(2)`.)  In addition, *st_atime* is not updated if a
   file is opened with the ``O_NOATIME``; see :manpage:`open(2)`.

   The field *st_atime* is changed by file accesses, for example, by execve(2), mknod(2), pipe(2),
   utime(2), and read(2) (of more than zero bytes). Other routines, like :manpage:`mmap(2)`, may
   or may not update *st_atime*.

   The field *st_mtime* is changed by file modifications, for example, by mknod(2), truncate(2),
   utime(2), and write(2) (of more than zero bytes). Moreover, *st_mtime* of a directory is changed
   by the creation or deletion of files in that directory. The *st_mtime* field is not changed for
   changes in owner, group, hard link count, or mode.

   The field *st_ctime* is changed by writing or by setting inode information (i.e., owner, group,
   link count, mode, etc.).

   POSIX refers to the *st_mode* bits corresponding to the mask ``S_IFMT`` (see below) as the file type,
   the 12 bits corresponding to the mask ``07777`` as the file mode bits and the least significant 9
   bits (``0777``) as the file permission bits.

   The following mask values are defined for the file type of the *st_mode* field::

      S_IFMT     0170000   bit mask for the file type bit field

      S_IFSOCK   0140000   socket
      S_IFLNK    0120000   symbolic link
      S_IFREG    0100000   regular file
      S_IFBLK    0060000   block device
      S_IFDIR    0040000   directory
      S_IFCHR    0020000   character device
      S_IFIFO    0010000   FIFO

   Thus, to test for a regular file (for example), one could write::

      stat(pathname, &sb);
      if ((sb.st_mode & S_IFMT) == S_IFREG) {
          /* Handle regular file */
      }

   Because tests of the above form are common, additional macros are defined by POSIX
   to allow the test of the file type in *st_mode* to be written more concisely::

      S_ISREG(m)  is it a regular file?
      S_ISDIR(m)  directory?
      S_ISCHR(m)  character device?
      S_ISBLK(m)  block device?
      S_ISFIFO(m) FIFO (named pipe)?
      S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
      S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

   The preceding code snippet could thus be rewritten as::

      stat(pathname, &sb);
      if (S_ISREG(sb.st_mode)) {
          /* Handle regular file */
      }

   The following mask values are defined for the file mode component
   of the *st_mode* field::

      S_ISUID     04000   set-user-ID bit
      S_ISGID     02000   set-group-ID bit (see below)
     
      S_ISVTX     01000   sticky bit (see below)
     
      S_IRWXU     00700   owner has read, write, and execute permission
      S_IRUSR     00400   owner has read permission
      S_IWUSR     00200   owner has write permission
      S_IXUSR     00100   owner has execute permission
     
      S_IRWXG     00070   group has read, write, and execute permission
      S_IRGRP     00040   group has read permission
      S_IWGRP     00020   group has write permission
      S_IXGRP     00010   group has execute permission
     
      S_IRWXO     00007   others (not in group) have read,  write,  and
      S_IROTH     00004   others have read permission
      S_IWOTH     00002   others have write permission
      S_IXOTH     00001   others have execute permission

   The set-group-ID bit (``S_ISGID``) has several special uses. For a directory,
   it indicates that BSD semantics is to be used for that directory: files created
   there inherit their group ID from the directory, not from the effective roup ID
   of the creating process, and directories created there will also get the ``S_ISGID``
   bit set. For a file that does not have the group execution bit (``S_IXGRP``) set,
   the set-group-ID bit indicates mandatory file/record locking.

   The sticky bit (``S_ISVTX``) on a directory means that a file in that directory
   can be renamed or deleted only by the owner of the file, by the owner of the
   directory, and by a privileged process.

   fstate::

      The ``fstatat()`` system call operates in exactly the same way as ``stat()``,
      except for the differences described here.
   
      If the *pathname* given in pathname is relative, then it is interpreted relative to the directory  referred  to  by
      the file  descriptor  dirfd (rather than relative to the current working directory of the calling process, as is
      done by stat() for a relative pathname).

       If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is  interpreted  relative  to  the
       current working directory of the calling process (like stat()).

       If pathname is absolute, then dirfd is ignored.

       flags can either be 0, or include one or more of the following flags ORed:

       AT_EMPTY_PATH (since Linux 2.6.39)
              If  pathname  is  an  empty string, operate on the file referred to by dirfd (which may have been obtained
              using the open(2) O_PATH flag).  If dirfd is AT_FDCWD, the call operates on the current working directory.
              In  this  case,  dirfd  can refer to any type of file, not just a directory.  This flag is Linux-specific;
              define _GNU_SOURCE to obtain its definition.

       AT_NO_AUTOMOUNT (since Linux 2.6.38)
              Don't automount the terminal ("basename") component of pathname if it is a directory that is an  automount
              point.   This  allows  the  caller to gather attributes of an automount point (rather than the location it
              would mount).  This flag can be used in tools that scan directories  to  prevent  mass-automounting  of  a
              directory of automount points.  The AT_NO_AUTOMOUNT flag has no effect if the mount point has already been
              mounted over.  This flag is Linux-specific; define _GNU_SOURCE to obtain its definition.

       AT_SYMLINK_NOFOLLOW
              If pathname is a symbolic link, do not dereference it: instead return information about the  link  itself,
              like lstat().  (By default, fstatat() dereferences symbolic links, like stat().)

   See openat(2) for an explanation of the need for fstatat().

**RETURN VALUE**

   On success, zero is returned.  On error, -1 is returned,
   and *errno* is set appropriately.

**EXAMPLE**

   The following program calls ``stat()`` and displays selected fields
   in the returned stat structure::

      #include <sys/types.h>
      #include <sys/stat.h>
      #include <time.h>
      #include <stdio.h>
      #include <stdlib.h>

      int main(int argc, char *argv[])
      {
         if (argc != 2) {
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
            exit(EXIT_FAILURE);
         }

         struct stat sb;
         if (stat(argv[1], &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
         }

         printf("File type: ");
         switch (sb.st_mode & S_IFMT) {
         case S_IFBLK:  printf("block device\n");            break;
         case S_IFCHR:  printf("character device\n");        break;
         case S_IFDIR:  printf("directory\n");               break;
         case S_IFIFO:  printf("FIFO/pipe\n");               break;
         case S_IFLNK:  printf("symlink\n");                 break;
         case S_IFREG:  printf("regular file\n");            break;
         case S_IFSOCK: printf("socket\n");                  break;
         default:       printf("unknown?\n");                break;
         }

         printf("I-node number:%ld\n", (long) sb.st_ino);
         printf("Mode:%lo (octal)\n", (unsigned long) sb.st_mode);
         printf("Link count:%ld\n", (long) sb.st_nlink);
         printf("Ownership:UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
         printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
         printf("File size: %lld bytes\n", (long long) sb.st_size);
         printf("Blocks allocated:%lld\n", (long long) sb.st_blocks);
         printf("Last status change:%s", ctime(&sb.st_ctime));
         printf("Last file access:%s", ctime(&sb.st_atime));
         printf("Last file modification:%s", ctime(&sb.st_mtime));
         printf("Device ID: %lld, Major: %u, minor: %u\n", (long long)sb.st_dev, major(sb.st_dev), minor(sb.st_dev));
         printf("rDevice ID: %lld, Major: %u, minor: %u\n", (long long)sb.st_rdev, major(sb.st_rdev), minor(sb.st_rdev));
         exit(EXIT_SUCCESS);
      }


**********************
Manage a device number
**********************

**DESCRIPTION**

   .. code-block:: c

      #define _BSD_SOURCE             /* See feature_test_macros(7) */
      #include <sys/types.h>

      dev_t makedev(int maj, int min);
      unsigned int major(dev_t dev);
      unsigned int minor(dev_t dev);


   A device ID consists of two parts: a major ID, identifying the class of the device,
   and a minor ID, identifying a specific instance of a device in that class.
   A device ID is represented using the type ``dev_t``.

   Given major and minor device IDs, ``makedev()`` combines these to produce a device ID,
   returned as the function result. This device ID can be given to :manpage:`mknod(2)`, for example.

   The ``major()`` and ``minor()`` functions perform the converse task: given a device ID, they return,
   respectively, the major and minor components. These macros can be useful to, for example, decompose
   the device IDs in the structure returned by :manpage:`stat(2)`.

**NOTES**
   
   These interfaces are defined as macros.  Since glibc 2.3.3, they have been aliases for three
   GNU-specific functions: ``gnu_dev_makedev()``, ``gnu_dev_major()``, and ``gnu_dev_minor()``. 
   The latter names are exported, but the traditional names are more portable.
