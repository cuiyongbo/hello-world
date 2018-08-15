**********
Gdb Basics
**********

#. Frequently used commands
   
   Here are some of the most frequently needed GDB commands::

      help [name]
         Show information about GDB command name, or general information about using GDB.
     
      break [file:]functiop
      Set a breakpoint at function (in file).
   
      run [arglist]
      Start your program (with arglist, if specified).
   
      c   Continue running your program (after stopping, e.g. at a breakpoint).
   
      bt  Backtrace: display the program stack.
   
      print expr
      Display the value of an expression.
   
      edit [file:]function
         look at the program line where it is presently stopped.
   
      list [file:]function
         type the text of the program in the vicinity of where it is presently stopped.
   
      next
         Execute next program line (after stopping); step over any function calls in the line.
   
      step
         Execute next program line (after stopping); step into any function calls in the line.
   
      quit
         Exit from GDB.


#. breakpoint howto

   +---------------------+--------------------------------------------------------------+
   | Command             | Description                                                  |
   +=====================+==============================================================+
   | b file.c: N         | Set a breakpoint at line number N of file “file.c”           |
   +---------------------+--------------------------------------------------------------+
   | b file.c: funcname  | Set a breakpoint at funcname of file “file.c”                |
   +---------------------+--------------------------------------------------------------+
   | b class\:\:function | Set a breakpoint at class\:\:function                        |
   +---------------------+--------------------------------------------------------------+
   | b N if condition    | Set a conditional breakpoint at line N of the current file   |
   +---------------------+--------------------------------------------------------------+
   | info break          | List all breakpoints                                         |
   +---------------------+--------------------------------------------------------------+
   | enable/disable N    | Enable or disable breakpoint number N                        |
   +---------------------+--------------------------------------------------------------+
   | enable N once       | Enable given breakpoint once, and disable it after it is hit |
   +---------------------+--------------------------------------------------------------+
   | delete              | delete all breakpoints, watchpoints or catchpoints           |
   +---------------------+--------------------------------------------------------------+
   | d N                 | Remove breakpoint number N                                   |
   +---------------------+--------------------------------------------------------------+

#. Other commands
   
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