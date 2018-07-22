***********
Make Manual
***********

**NAME**

   make - GNU make utility to maintain groups of programs

**SYNOPSIS**

   make [OPTION]... [TARGET]...

**DESCRIPTION**

   The make utility will determine automatically which pieces of a large program 
   need to be recompiled, and issue the commands to recompile them. The manual 
   describes the GNU implementation of make. Our examples show C programs, since 
   they are very common, but you can use make with any programming language whose 
   compiler can be run with a shell command.  In fact, make is not limited to programs.  
   You can use it to describe any task where some files must be updated automatically 
   from others whenever the others change. e.g. sphinx rst documents.

   To prepare to use make, you must write a file called the **makefile** that describes 
   the relationships among files in your program, and the states the commands for updating 
   each file. In a program, typically the executable file is updated from object files, 
   which are in turn made by compiling source files.

   Once a suitable makefile exists, each time you change some source files, 
   this simple shell command: ``make.``

   suffices to perform all necessary recompilations. The make program uses the makefile description 
   and the last-modification times of the files to decide which of the files need to be updated.
   For each of those files, it issues the commands recorded in the makefile.

   make executes commands in the makefile to update one or more target names, where name is typically 
   a program. If no ``-f`` option is present, make will look for the makefiles GNUmakefile, makefile, 
   and Makefile, in that order.

   Normally you should call your makefile either makefile or Makefile. (We recommend Makefile because 
   it appears prominently near the beginning of a directory listing, right near other important files 
   such as README.)  The first name checked, GNUmakefile, is not recommended for most makefiles. You 
   should use this name if you have a makefile that is specific to GNU  make, and will not be understood 
   by other versions of make.  If makefile is '-', the standard input is read.

   make updates a target if it depends on prerequisite files that have been modified since the target was 
   last modified, or if the target does not exist.

**Hot Options**

   .. option:: -f file, --file=file, --makefile=FILE
      
      Use *file* as a makefile.

   .. option:: -i, --ignore-errors
      
      Ignore all errors in commands executed to remake files.

   .. option:: -I dir, --include-dir=dir
            
      Specifies a directory *dir* to search for included makefiles. 
      If several -I options are used to specify several directories, 
      the directories are searched in the order specified. Unlike
      the arguments to other flags of make, directories given with -I flags 
      may come directly after the flag: ``-Idir`` is allowed, as well as ``-I dir.`` 
      This syntax is allowed for compatibility with the C preprocessor's -I flag.

   .. option:: -k, --keep-going
            
      Continue as much as possible after an error. While the target that failed, 
      and those that depend on it, cannot be remade, the other dependencies of 
      these targets can be processed all the same.

   .. option:: -s, --silent, --quiet
            
      Silent operation; do not print the commands as they are executed.

   .. option:: -S, --no-keep-going, --stop
      
      Cancel the effect of the -k option. This is never necessary except 
      in a recursive make where -k might be inherited from the top-level 
      make via MAKEFLAGS or if you set -k in MAKEFLAGS in your environment.

   .. option:: -t, --touch
            
      Touch files (mark them up to date without really changing them) 
      instead of running their commands.  This is used to pretend that 
      the commands were done, in order to fool future invocations of make.