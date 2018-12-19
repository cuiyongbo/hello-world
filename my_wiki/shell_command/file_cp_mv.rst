************************
File Copy & Move Command
************************

#. cp - copy files and directories

   SYNPOSIS: ``cp [OPTION]... SOURCE... DIRECTORY``

   Copy *SOURCE* to *DEST*, or multiple *SOURCE*(s) to *DIRECTORY*.

   Hot options::

      --parents
      use full source file name under DIRECTORY,
      **keep file hierarchy**.

      -R, -r, --recursive
      copy directories recursively.
      If SOURCE designates a directory, cp copies the directory 
      and the entire subtree connected at that point.  If the SOURCE 
      ends in a /, the contents of the directory are copied rather 
      than the directory itself.

      -n, --no-clobber
      do not overwrite an existing file (overrides a 
      previous -i option).

      -f, --force
      if an existing destination file cannot be opened,
      remove it and try again (this option is ignored 
      when the -n option is also used)

      -u, --update
      copy only when the SOURCE file is newer than the destination 
      file or when the destination file is missing

      -l, --link
      hard link files instead of copying

      -s, --symbolic-link
      make symbolic links instead of copying

      -L, --dereference
      always follow symbolic links in SOURCE

      -P, --no-dereference
      never follow symbolic links in SOURCE


#. mv - move files

   SYNOPSIS: ``mv [OPTION]... SOURCE... DIRECTORY`` 

   Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.

   Hot options::

      --backup[=CONTROL], -b, -S, --suffix=SUFFIX
      same as cp.

      -i
      prompt before overwrite.

      -n, --no-clobber
      do not overwrite an existing file.

      -f, --force
      do not prompt before overwriting.

      -u, --update
      move only when the SOURCE file is newer than the destination
      file or when the destination file is missing

#. mkdir - make directories
   
   SYNOPSIS: ``mkdir [OPTION]... DIRECTORY...``

   Create the DIRECTORY(ies), if they do not already exist.

   Options::

      -p, --parents
      no error if existing, make parent directories as needed
