GDB tutorial
============

#. Add debug symbols: ``gcc –g main.c –o main``
#. Launch gdb: ``gdb main``
#. Print source code in debug mode: ``list LOCATION (linenum or function name)``
#. Set breakpoint: ``break LOCATION (linenum or function name)``
#. Run the program with argument(s) *args*: ``run args``
#. Print variable value: ``print var``
#. Print backtrace of all stack frames: ``backtrace``
#. Quit gdb: ``quit``
   
#. There are 3 kinds of operations you can choose when
   the program stops at the breakpoint:
   
   - continue – continue executing until the next breakpoint
   - next – execute next line as a single instruction
   - step – same as next, but does not treat function as a single instruction

#. ENTER – Press ENTER key would execute the previous command again
#. help COMMAND – show help of COMMAND 