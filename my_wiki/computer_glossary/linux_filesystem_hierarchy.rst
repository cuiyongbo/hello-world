*****************************
Filesystem Hierarchy Standard
*****************************

The :abbr:`FHS (Filesystem Hierarchy Standard)` defines the directory structure and directory 
contents in Linux distributions. For further information, see :manpage:`hier(7).`

**Directory structure**

In the FHS, all files and directories appear under the root directory(/),
even if they are stored on different physical or virtual devices. Some of
these directories only exist on a particular system if certain subsystems,
such as the X Window System, are installed.

Most of these directories exist in all UNIX operating systems and are generally
used in much the same way; however, the descriptions here are those used specifically
for the FHS, and are not considered authoritative for platforms other than Linux.

   :file:`/`
      Primary hierarchy root and root directory of the entire file system hierarchy.

   :file:`/bin`
      Essential command binaries that need to be available in single user mode;
      for all users, e.g., :command:`cat`, :command:`ls`, :command:`cp`.

   :file:`/boot`
      Boot loader files, e.g., kernels, initrd.

   :file:`/dev`
      Essential device files, e.g., :file:`/dev/null`.

   :file:`/etc`
      Host-specific system-wide configuration files.
      There has been controversy over the meaning of the name itself.
      In early versions of the UNIX Implementation Document from Bell labs,
      :file:`/etc` is referred to as the etcetera directory, as this directory
      historically held everything that did not belong elsewhere (however, the
      FHS restricts :file:`/etc` to static configuration files and may not contain
      binaries). Since the publication of early documentation, the directory name
      has been re-explained in various ways. Recent interpretations include backronyms
      such as "Editable Text Configuration" or "Extended Tool Chest".

   :file:`/etc/opt`
      Configuration files for add-on packages that are stored in :file:`/opt`.

   :file:`/home`
      Users' home directories, containing saved files, personal settings, etc.

   :file:`/lib`
      Libraries essential for the binaries in :file:`/bin` and :file:`/sbin`.

   :file:`/media`
      Mount points for removable media such as CD-ROMs (appeared in FHS-2.3 in 2004).
      e.g. the shared folder was mounted to :file:`/media/psf` on *Parallel Desktop*
      , by default.

   :file:`/mnt`
      Temporarily mounted filesystems. e.g. On vmware, after you have enabled a shared folder,
      you can mount one or more directories or subdirectories in the shared folder to any
      location in the file system in addition to the default location of :file:`/mnt/hgfs`.

   :file:`/opt`
      Optional application software packages.

   :file:`/proc`
      Virtual filesystem providing process and kernel information as files.
      In Linux, corresponds to a procfs mount. Generally automatically generated
      and populated by the system, on the fly. for further information, see :manpage:`proc(5).`

   :file:`/root`
      Home directory for the root user.

   :file:`/run`
      Run-time variable data: Information about the running system since last boot,
      e.g., currently logged-in users and running daemons. Files under this directory
      must be either removed or truncated at the beginning of the boot process; but
      this is not necessary on systems that provide this directory as 
      a :abbr:`tmpfs (temporary filesystem)`.

   :file:`/sbin`
      Essential system binaries, e.g., :file:`fsck`, :file:`init`, :file:`route`.
   
   :file:`/srv`
      Site-specific data served by this system, such as data and scripts for web servers,
      data offered by FTP servers, and repositories for version control systems (appeared
      in FHS-2.3 in 2004).

   :file:`/sys`
      Contains information about devices, drivers, and some kernel features.

   :file:`/tmp`
      Temporary files (see also :file:`/var/tmp`). Often not preserved between
      system reboots, and may be severely size restricted.

   :file:`/usr`
      Secondary hierarchy for read-only user data; contains the majority of
      (multi-)user utilities and applications.

   :file:`/usr/bin`
      Non-essential command binaries (not needed in single user mode); for all users.

   :file:`/usr/include`
      Standard include files.

   :file:`/usr/lib`
      Libraries for the binaries in :file:`/usr/bin` and :file:`/usr/sbin`.

   :file:`/usr/local`
      Tertiary hierarchy for local data, specific to this host. Typically
      has further subdirectories, e.g., bin, lib, share.

   :file:`/usr/sbin`
      Non-essential system binaries, e.g., daemons for various network-services.

   :file:`/usr/share`
      Architecture-independent (shared) data.

   :file:`/usr/src`
      Source code, e.g., the kernel source code with its header files.

   :file:`/var`
      Variable files—files whose content is expected to continually change
      during normal operation of the system—such as logs, spool files, and
      temporary e-mail files.

   :file:`/var/cache`
      Application cache data. Such data are locally generated as a result of
      time-consuming I/O or calculation. The application must be able to regenerate
      or restore the data. The cached files can be deleted without loss of data.

   :file:`/var/lib`
      State information. Persistent data modified by programs as they run,
      e.g., databases, packaging system metadata, etc.

   :file:`/var/lock`
      Lock files. Files keeping track of resources currently in use.

   :file:`/var/log`
      Log files. Various logs.

   :file:`/var/mail`
      Mailbox files. In some distributions, these files may be located
      in the deprecated :file:`/var/spool/mail`.

   :file:`/var/opt`
      Variable data from add-on packages that are stored in :file:`/opt`.

   :file:`/var/run`
      Run-time variable data. This directory contains system information data
      describing the system since it was booted. In FHS 3.0, :file:`/var/run`
      is replaced by :file:`/run`; a system should either continue to provide
      a :file:`/var/run` directory, or provide a symbolic link from :file:`/var/run`
      to :file:`/run`, for backwards compatibility.

   :file:`/var/spool`
      Spool for tasks waiting to be processed, e.g., print queues and outgoing mail queue.

   :file:`/var/spool/mail`
      Deprecated location for users' mailboxes. Maybe a symbolic link to :file:`/var/mail`.

   :file:`/var/tmp`
      Temporary files to be preserved between reboots.

#. /dev/null
   
   In some operating systems, the null device is a device file that 
   discards all data written to it but reports that the write operation 
   succeeded. The null device is typically used for disposing of unwanted 
   output streams of a process, or as a convenient empty file for input 
   streams. This is usually done by redirection.

#. /dev/zero
   
   /dev/zero is a special file in Unix-like operating systems that provides as 
   many null characters (ASCII NUL, 0x00) as are read from it. One of the typical 
   uses is to provide a character stream for initializing data storage.

   Unlike /dev/null, /dev/zero may be used as a source, not only as a sink for data. 
   All write operations to /dev/zero succeed with no other effects. 
   However, /dev/null is more commonly used for this purpose.

   When /dev/zero is memory-mapped, e.g., with mmap, to the virtual address space, 
   it is equivalent to using anonymous memory; i.e. memory not connected to any file.
