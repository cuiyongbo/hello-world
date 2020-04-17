*****************
Parsing File Path
*****************

#. readlink - print resolved symbolic links or canonical file names

   SYNOPSIS: ``readlink [OPTION]... FILE...``
   
   Print value of a symbolic link or canonical file name.
   
   Hot options::
   
      -f, --canonicalize
      canonicalize by following every symlink in every component of the given name recursively; 
      all but the last component must exist
   
      -e, --canonicalize-existing
      ditto, except that all components must exist
   
      -m, --canonicalize-missing
      ditto,  without requirements on components existence
   
      -z, --zero
      separate output with NUL rather than newline
   
#. dirname - strip last component from file name

   SYNOPSIS: ``dirname [OPTION] NAME...``
   
   Output each NAME with its last non-slash component 
   and trailing slashes removed; if NAME contains no /'s, 
   output '.' (meaning the current directory).
   
   Hot options::
   
      -z, --zero
      separate output with NUL rather than newline

.. code-block:: sh
   :caption: Examples

   $ readlink -f start.sh | xargs -0 dirname
   /etc/slider/coke_cola_package
   $ readlink -f start.sh 
   /etc/slider/coke_cola_package/start.sh
   $ dirname /etc/slider/start.sh
   /etc/slider
   $ dirname start.sh
   .

   # Change the working directory to where the command locates
   $ cd `dirname $(readlink -f $0)`

