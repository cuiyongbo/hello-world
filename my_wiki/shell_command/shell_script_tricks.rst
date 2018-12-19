************
Shell Script
************

.. toctree::

   shell_flow_control_note
   shell_conditional_evaluation_note

.. contents::
  :local:

#. Pipe & Redirect

   .. code-block:: sh
   
      $ more < main.cpp # redirect input
      $ kill -HUP 1234 >killout.txt 2>killerr.txt # redirect stdout to killout.txt and stderr to killerr.txt
      $ kill -1 1234 >/dev/null 2>&1 # discard all output
      $ ls -lh >>directoryEntries.txt # redirect stdout to directoryEntries.txt in append mode
      $ ps | sort -h
   
   .. note::
      
      * 0 - stdin
      * 1 - stdout
      * 2 - stderr
        
      the "&" in "2>&1" cannot be omitted, otherwise the command will be interpreted as
      "redirect stderr to a file named 1." "&" indicates that what follows is a file 
      descriptor and not a filename.  

#. use "-" in operand
   
   .. code-block:: sh

      rm -- -bar

#. Command line arguments

   .. code-block:: sh
   
      $0  # script name.
      $$  # script process PID.
      $n  # the nth argument of script.
      $#  # the number of arguments. NOT include $0
      $*  # all the arguments
      $@  # all the arguments
      $?  # return code of last command, return 0 on success.
   
   .. note::
   
      The difference between ``$*`` and ``$@``: ``"$*"`` creates one
      argument separated by the :envvar:`IFS` variable, while ``"$@"``
      will expand into separate arguments. Use ``"`` instead of ``'``.
   
   Example::
   
      #!/usr/bin/env sh
   
      echo "Program name: $0"
      echo "PID: $$"
      echo "Parameter count: $#"
      if [ $# -ne 0 ] # space cannot be ommited.
      then
         for i in "$@"; do echo "@ '$i'"; done
         for i in "$*"; do echo "* '$i'"; done
      fi

#. Increment variable value by 1

   .. code-block:: sh
   
      i=0
      i=$((i+1))
   
      ((i++))
   
      echo $i

#. Assign bash command output to a variable

   Try: ``"pwd=`pwd`"`` or ``pwd=$(pwd)``.
   
   .. note:: 
   
      Notice no spaces after the equals sign. and you don't assign to ``$pwd``,
      you assign to ``pwd``.


#. exit arbitrarily

   Use ``exit`` in your scripts.

#. subshell

   Running a shell script launches another instance of the command processor.
   Just as your commands are interpreted at the command line prompt, similarly
   does a script batch process a list of commands in a file. Each shell script
   running is, in effect, a subprocess of the parent shell, the one that gives
   you the prompt at the console or in an xterm window.
   
   A shell script can also launch subprocesses. These subshells let the script
   do parallel processing, in effect executing multiple subtasks simultaneously.
   
   A command list embedded between parentheses runs as a subshell::
   
      ( command1; command2; command3; ... )
   
   Variables in a subshell are not visible outside the block of code in the subshell.
   They are not accessible to the parent process, to the shell that launched the subshell.\
   These are, in effect, local variables.
   
   Processes may execute in parallel within different subshells.
   This permits breaking a complex task into subcomponents processed concurrently.
   
   .. code-block:: sh
      :caption: Variable scope in a subshell
   
      #!/bin/bash
      # subshell.sh
      
      echo
      
      echo "Subshell level OUTSIDE subshell = $BASH_SUBSHELL"
      # Bash, version 3, adds the new         $BASH_SUBSHELL variable.
      echo
      
      outer_variable=Outer
      
      (
      echo "Subshell level INSIDE subshell = $BASH_SUBSHELL"
      inner_variable=Inner
      
      echo "From subshell, \"inner_variable\" = $inner_variable"
      echo "From subshell, \"outer\" = $outer_variable"
      )
      
      echo
      echo "Subshell level OUTSIDE subshell = $BASH_SUBSHELL"
      echo
      
      if [ -z "$inner_variable" ]
      then
        echo "inner_variable undefined in main body of shell"
      else
        echo "inner_variable defined in main body of shell"
      fi
      
      echo "From main body of shell, \"inner_variable\" = $inner_variable"
      #  $inner_variable will show as uninitialized
      #+ because variables defined in a subshell are "local variables".
      #  Is there any remedy for this?
      
      echo
      
      exit 0
   
   .. code-block:: sh
      :caption: Running parallel processes in subshells
   
      (cat list1 list2 list3 | sort | uniq > list123) &
      (cat list4 list5 list6 | sort | uniq > list456) &
      # Merges and sorts both sets of lists simultaneously.
      # Running in background ensures parallel execution.
      #
      # Same effect as
      #   cat list1 list2 list3 | sort | uniq > list123 &
      #   cat list4 list5 list6 | sort | uniq > list456 &
      
      wait   # Don't execute the next command until subshells finish.
      
      diff list123 list456


#. loop through array of strings in Bash
   
   .. code-block:: sh

      ## declare an array variable
      declare -a arr=("element1" 
                "element2" "element3"
                "element4"
                )
      
      ## now loop through the above array
      for i in "${arr[@]}"
      do
         echo "$i"
         # or do whatever with individual element of the array
      done

#. concate string in Bash
   
   .. code-block:: sh

      # there is no space between variable and operator

      $ foo="hello"
      $ foo="$foo world"
      $ echo $foo
      hello world
      $ foo+=" nice to meet you"
      $ echo $foo
      hello world nice to meet you

#. comparison with ``test "x$SHELL_VAR" = "xyes"``
   
   If you're using a shell that does simple substitution and the ``SHELL_VAR`` variable 
   does not exist (or is blank), then you need to watch out for the **edge cases**. 
   The following translations will happen::

      if test $SHELL_VAR = yes; then        -->  if test = yes; then
      if test x$SHELL_VAR = xyes; then      -->  if test x = xyes; then

   The first of these will generate an error since the fist argument to **test** 
   has gone missing. The second does not have that problem.

   Your case translates as follows::

      if test "x$SHELL_VAR" = "xyes"; then  -->  if test "x" = "xyes"; then

   It may seem a bit redundant since it has both the quotes and the ``x`` 
   but it will also handle a variable with spaces in it.

   The other reason (other than empty variables) has to do with option processing. 
   If you write ``if test "$1" = "abc" ; then ...`` and ``$1`` has the value ``-n`` 
   or ``-z`` or any other valid options to the ``test`` command, the syntax is ambiguous. 
   The ``x`` at the front prevents a leading dash from being picked up as an option to ``test``.

#. split string by space
   
   .. code-block:: sh

      $ cat test.sh
      #!/usr/bin/env bash
      
      if [ $# -ne 1 ]; then
              echo "Usage: $0 proc"
              exit 1
      fi
      
      proc_info=`ps -ef | grep -i $1 | grep -v grep`
      if [ -z '${proc_info}' ]; then
              echo "$1 is not running"
              exit 2
      fi
      info_array=(${proc_info})
      echo "$1's PID: ${info_array[1]}"

#. Space in variable assignment
   
   ``var=23`` assigns ``23`` to the variable ``var``.

   ``var =23`` tries to run command (or alias, or function) var with argument ``=23``

   ``var = 23`` ditto, but arguments ``=`` and ``23``

   ``var= 23`` sets ``var`` to blank string, then runs command ``23``

   **Note:** In comparison, ``[ (/usr/bin/[)`` is the command and it requires 
   ``var1, != and var2`` to be 3 separate arguments. ``var1!=var2`` is a single argument

#. Extract file path
   
   .. code-block:: sh

      $ readlink -f start.sh | xargs -0 dirname
      /etc/ncserver/traffic-data-updater
      $ readlink -f start.sh 
      /etc/ncserver/traffic-data-updater/start.sh
      $ dirname start.sh
      .
      $ dirname /etc/ncserver/start.sh
      /etc/ncserver
