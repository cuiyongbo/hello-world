*********
addr2line
*********

**NAME**

   addr2line - convert addresses into file names and line numbers.

**SYNOPSIS**

   .. code-block:: sh

      addr2line [-a|--addresses]
                [-b bfdname|--target=bfdname]
                [-C|--demangle[=style]]
                [-e filename|--exe=filename]
                [-f|--functions] [-s|--basename]
                [-i|--inlines]
                [-p|--pretty-print]
                [-j|--section=name]
                [-H|--help] [-V|--version]
                [addr addr ...]

**DESCRIPTION**

   addr2line translates addresses into file names and line numbers. Given an address in an executable 
   or an offset in a section of a relocatable object, it uses the debugging information to figure out 
   which file name and line number are associated with it.

   The executable or relocatable object to use is specified with the -e option. The default is the file ``a.out.``  
   The section in the relocatable object to use is specified with the -j option.

   addr2line has two modes of operation.

   In the first, hexadecimal addresses are specified on the command line, 
   and addr2line displays the file name and line number for each address.

   In the second, addr2line reads hexadecimal addresses from standard input, 
   and prints the file name and line number for each address on standard output.  
   In this mode, addr2line may be used in a pipe to convert dynamically chosen addresses.

   The format of the output is FILENAME:LINENO. By default each input address generates 
   one line of output.

   If the file name or function name can not be determined, addr2line will print two question 
   marks in their place. If the line number can not be determined, addr2line will print 0.

**OPTIONS**

.. option:: -a, --addresses
           
   Display the address before the function name, file and line number information.  
   The address is printed with a 0x prefix to easily identify it.

.. option:: -e filename, --exe=filename
           
   Specify the name of the executable for which addresses should be translated.  
   The default file is a.out.

.. option:: -f, --functions
   
   Display function names as well as file and line number information.

.. option:: -s, --basenames
           
   Display only the base of each file name.

.. option:: -p, --pretty-print
           
   Make the output more human friendly: each location are printed on one line.  
   If option -i is specified, lines for all enclosing scopes are prefixed with (inlined by).


**EXAMPLE**

.. code-block:: sh

   $ ./a.out 2
   backtrace() returned 7 address(es).
   Frame 0: ./a.out() [0x4007f3]
   Frame 1: ./a.out() [0x4008ad]
   Frame 2: ./a.out() [0x4008d5]
   Frame 3: ./a.out() [0x4008ce]
   Frame 4: ./a.out() [0x40092a]
   Frame 5: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0) [0x7f8ec09cc830]
   Frame 6: ./a.out() [0x400689]

   $ addr2line -f 0x4008d5
   myFunc1
   /home/cherry/program-demo/cpp-demo/backtrace_demo.c:43

   $ addr2line -f -s 0x4008d5
   myFunc1
   backtrace_demo.c:43

   $ addr2line -a -f -s 0x4008d5
   0x00000000004008d5
   myFunc1
   backtrace_demo.c:43

   $ addr2line -a -f -s -p  0x4008d5
   0x00000000004008d5: myFunc1 at backtrace_demo.c:43

