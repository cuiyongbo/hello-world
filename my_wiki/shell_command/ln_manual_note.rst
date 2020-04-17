*****************************
ln - make links between files
*****************************

**DESCRIPTION**

   .. code-block:: sh

      ln [OPTION]... [-T] TARGET LINK_NAME

   **ln** command creates a link to TARGET with the name LINK_NAME. 
   Create hard links by default, symbolic links with ``--symbolic.``  
   By default, each destination (name of new link) should not already exist.  
   When creating hard links, each TARGET must exist. Symbolic links can hold 
   arbitrary text; if later resolved, a relative link is interpreted 
   in relation to its parent directory.

   A "hard link" is another name for an existing file; the link and the
   original are indistinguishable.  Technically speaking, they share the
   same inode, and the inode contains all the information about a
   file--indeed, it is not incorrect to say that the inode _is_ the file.
   Most systems prohibit making a hard link to a directory; on those where
   it is allowed, only the super-user can do so (and with caution, since
   creating a cycle will cause problems to many other utilities).  Hard
   links cannot cross file system boundaries.  (These restrictions are not
   mandated by POSIX, however.)
   
   "Symbolic links" ("symlinks" for short), on the other hand, are a
   special file type (which not all kernels support: System V release 3
   (and older) systems lack symlinks) in which the link file actually
   refers to a different file, by name.  When most operations (opening,
   reading, writing, and so on) are passed the symbolic link file, the
   kernel automatically "dereferences" the link and operates on the target
   of the link.  But some operations (e.g., removing) work on the link
   file itself, rather than on its target.  The owner and group of a
   symlink are not significant to file access performed through the link,
   but do have implications on deleting a symbolic link from a directory
   with the restricted deletion bit set.  On the GNU system, the mode of a
   symlink has no significance and cannot be changed, but on some BSD
   systems, the mode can be changed and will affect whether the symlink
   will be traversed in file name resolution. 
   
   Symbolic links can contain arbitrary strings; a "dangling symlink"
   occurs when the string in the symlink does not resolve to a file.
   There are no restrictions against creating dangling symbolic links.
   There are trade-offs to using absolute or relative symlinks.  An
   absolute symlink always points to the same file, even if the directory
   containing the link is moved.  However, if the symlink is visible from
   more than one machine (such as on a networked file system), the file
   pointed to might not always be the same.  A relative symbolic link is
   resolved in relation to the directory that contains the link, and is
   often useful in referring to files on the same device without regards
   to what name that device is mounted on when accessed via networked
   machines.
   
   When creating a relative symlink in a different location than the
   current directory, the resolution of the symlink will be different than
   the resolution of the same string from the current directory.
   Therefore, many users prefer to first change directories to the
   location where the relative symlink will be created, so that
   tab-completion or other file resolution will find the same target as
   what will be placed in the symlink.


**HOT OPTIONS**


   .. option:: --backup[=CONTROL]
      
      make a backup of each existing destination file

   .. option:: -b     

      like --backup but does not accept an argument

   .. option:: -d, -F, --directory
              
      allow the superuser to attempt to hard link directories 
      (note: will probably fail due to system restrictions, even for the superuser)

   .. option:: -f, --force
      
      remove existing destination files

   .. option:: -r, --relative
              
      create symbolic links relative to link location

   .. option:: -s, --symbolic
      
      make symbolic links instead of hard links


.. code-block:: sh
   :caption: **EXAMPLE**

   $ ln /run/shm/cokeMap id_list_ln
   ln: failed to create hard link ‘id_list_ln’ => ‘/run/shm/cokeMap’: Invalid cross-device link