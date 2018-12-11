*************
Unix Concepts
*************

.. toctree::
   
   linux_filesystem_hierarchy
   unix_configure_file

#. Real User ID and Real Group ID
   
   Each user on the system is identified by a positive integer
   termed the real user ID.

   Each user is also a member of one or more groups. One of these
   groups is distinguished from others and used in implementing
   accounting facilities. The positive integer corresponding to
   this distinguished group is termed the real group ID.

   All processes have a real user ID and real group ID. These are
   initialized from the equivalent attributes of the process that
   created it.

#. Effective User Id, Effective Group Id, and Group Access List
             
   Access to system resources is governed by two values: 
   **the effective user ID, and the group access list.**  
   The first member of the group access list is also known 
   as the effective group ID. (In POSIX.1, the group access 
   list is known as the set of **supplementary group IDs,** 
   and it is unspecified whether the effective group ID is 
   a member of the list.)

   The effective user ID and effective group ID are initially the
   process's real user ID and real group ID respectively. Either
   may be modified through execution of a set-user-ID or set-group-ID 
   file (possibly by one its ancestors) (see execve(2)). By convention, 
   the effective group ID is duplicated, so that the execution of a 
   set-group-ID program does not result in the loss of the original (real)
   group ID.

   The group access list is a set of group IDs used only in determining 
   resource accessibility. Access checks are performed as described below 
   in **File Access Permissions**.

#. Saved Set User ID and Saved Set Group ID
   
   When a process executes a new file, the effective user ID is set
   to the owner of the file if the file is set-user-ID, and the
   effective group ID is set to the group of the file if the file 
   is set-group-ID. The effective user ID of the process is then 
   recorded as the saved set-user-ID, and the effective group ID of 
   the process is recorded as the saved set-group-ID. These values may 
   be used to regain those values as the effective user or group ID after
   reverting to the real ID (see setuid(2)). (In POSIX.1, the saved
   set-user-ID and saved set-group-ID are optional, and are used in
   setuid and setgid, but this does not work as desired for the super-user.)

#. File Access Permissions
   
   Every file in the file system has a set of access permissions.  
   These permissions are used in determining whether a process may 
   perform a requested operation on the file (such as opening a file 
   for writing).  Access permissions are established at the time a 
   file is created. They may be changed at some later time through 
   the chmod(2) call.

   File access is broken down according to whether a file may be: 
   **read, written, or executed.**  Directory files use the execute 
   permission to control if the directory may be searched.

   File access permissions are interpreted by the system 
   as they apply to three different classes of users: **the owner of
   the file, those users in the file's group, anyone else.**  
   Every file has an independent set of access permissions for
   each of these classes. When an access check is made, the system 
   decides if permission should be granted by checking the access 
   information applicable to the caller.

   Read, write, and execute/search permissions on a file are granted to a process if:

      The process's effective user ID is that of the super-user. 
      (**Note**: even the super-user cannot execute a non-executable file.)

      The process's effective user ID matches the user ID of the owner of 
      the file and the owner permissions allow the access.

      The process's effective user ID does not match the user ID of 
      the owner of the file, and either the process's effective group ID 
      matches the group ID of the file, or the group ID of the file is in 
      the process's group access list, and the group permissions allow the access.

      Neither the effective user ID nor effective group ID and group access list 
      of the process match the corresponding user ID and group ID of the file, 
      but the permissions for **other users** allow access.

      Otherwise, permission is denied.

#. Session
             
   A session is a set of one or more process groups.  
   A session is created by a successful call to setsid(2), 
   which causes the caller to become the only member of the 
   only process group in the new session.

#. Session leader
        
   A process that has created a new session by a successful call to setsid(2), 
   is known as a session leader. Only a session leader may acquire a terminal 
   as its controlling terminal (see termios(4)).

#. Controlling process
   
   A session leader with a controlling terminal is a controlling process.

#. Controlling terminal
   
   A terminal that is associated with a session is known as the 
   controlling terminal for that session and its members.
