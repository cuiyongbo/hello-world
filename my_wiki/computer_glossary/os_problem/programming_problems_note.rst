*****************************
Programming Problem Solutions
*****************************

#. See the default system page size

   .. code-block:: sh

      getconf PAGESIZE
      4096

   .. note::

      Find more interesting features about :command:`getconf` by ``man getconf``, some examples:

         .. code-block:: sh

            getconf NAME_MAX /tmp # display the maximum length of a filename in the /tmp directory
            255
            getconf CHAR_BIT
            8

#. ".infig.status: error: cannot find input file: \ " when execute ``./configure``
   
   This happens because of the invalid file format of configure.ac / configure.in,
   simply execute following commands::

      $ vi congfigure.ac
         vi > set fileformat=unix
         vi > wq
      $ aclocal
      $ autoconf
      $ automake -a
      $ ./configure  

#. make: warning: Clock skew detected. Your build may be incomplete.
   
   That message is usually an indication that some of your files have modification times
   newer than the current system time. Since make decides which files to compile when
   performing an incremental build by checking if a source files has been modified more
   recently than its object file, this situation can cause unnecessary files to be built,
   or worse, necessary files to not be built. you can fix it by executing::

      find . -exec touch \{\} \+
