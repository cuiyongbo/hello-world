**********
Gdb Tricks
**********

#. select executable file
   
   .. code-block:: sh

      file executableName

   .. note:: 

      :command:`file` without arguments discard symbol table
      of current executable.


#. set / show args
   
   Lauch debugging with multi-arguments: ``gdb --args executable args``.

   Show the arguments to give your program when it is started: ``show args``.

   ``set args argumentList`` Specify the arguments to be used the next time
   your program is run. If ``set args`` has no arguments, run executes your
   program with no arguments. Once you have run your program with arguments,
   using ``set args`` before the next run is the only way to run it again
   without arguments.


#. Launch gdb without front materials: 
   
   .. code-block:: sh

      gdb --silent


#. Execute shell command
   
   .. code-block:: sh

      shell command args

#. Miscellaneous commands
   
   +------------------+----------------------------------------------------------------------+
   | Command          | Description                                                          |
   +==================+======================================================================+
   | info threads     | Display information about current thread                             |
   +------------------+----------------------------------------------------------------------+
   | info watchpoints | Display list of watchpoints                                          |
   +------------------+----------------------------------------------------------------------+
   | info register    | Display processor register content                                   |
   +------------------+----------------------------------------------------------------------+
   | finish           | Runs untill the current function is finished                         |
   +------------------+----------------------------------------------------------------------+
   | step N           | Runs the next N lines of program                                     |
   +------------------+----------------------------------------------------------------------+
   | set var=val      | Assign “val” to the variable “var”                                   |
   +------------------+----------------------------------------------------------------------+
   | watch condition  | Set a watchpoint for given condition, suspend when condition is true |
   +------------------+----------------------------------------------------------------------+
