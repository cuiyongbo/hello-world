:orphan:

************
Shell Script
************

Command line arguments
======================

.. code-block:: sh

   $0  # script name.
   $$  # script process PID.
   $n  # the nth argument of script.
   $#  # the number of arguments.
   $*  # all the arguments
   $@  # all the arguments
   $?  # return code of last command, return 0 on success.

.. note::

   The difference is subtle; ``"$*"`` creates one argument
   separated by the :envvar:`IFS` variable, while ``"$@"`` will
   expand into separate arguments. 
   Use ``"`` instead of ``'``.

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


Flow Control : if
=================

**Synposis**

.. code-block:: sh

   if condition_1
      then
      # commands
   elif condition_2
      then
      # commands
   else
      # commands
   fi

**Example**

.. code-block:: sh
   :caption: Check if str is empty

   str="Hello World"
   str2=" "
   str3=""
   
   # You need a space on either side of the !=.
   # spaces between "[", "]" cannot be omitted.

   if [ ! -z "$str" -a "$str" != " " ]; then
           echo "Str is not null or space"
   fi
   
   if [ ! -z "$str2" -a "$str2" != " " ]; then
           echo "Str2 is not null or space"
   fi
   
   if [ ! -z "$str3" -a "$str3" != " " ]; then
           echo "Str3 is not null or space"
   fi


Flow Control : while/until
==========================

**Synposis**

.. code-block:: sh

   while / until condition
   do
      # commands
   done

``until`` excute the loop when the condition is false.

Variant ``do ... while/until`` syntax::

   while/until 
         Commands ...
   do :; done

**Example**

.. code-block:: sh

   i=16
   while
         echo "this command is executed at least once $i"
         : ${start=$i}              # capture the starting value of i
         # some other commands      # needed for the loop
         i="$((i+1))"               # increment the variable of the loop.
         [ "$i" -lt 20 ]            # test the limit of the loop.
         # (( ++i < 20 ))
   do :;  done
   echo "Final value of $i///$start"
   echo "The loop was executed $(( i - start )) times "


Flow Control: case
==================

.. code-block:: sh

   case var in
   mode1)
      命令序列1
   ;; #類似 break
   mode2)
      命令序列2
   ;;
   …
   *) #類似 default
      命令序列 n
   ;;
   esac



Increment variable value by 1
=============================

.. code-block:: sh

   i=0
   i=$((i+1))

   ((i++))

   echo $i


Assign bash command output to a variable
========================================

Try: ``"pwd=`pwd`"`` or ``pwd=$(pwd)``.

.. note:: 

   Notice no spaces after the equals sign. and you don't assign to ``$pwd``,
   you assign to ``pwd``.


exit arbitrarily
================

Use ``exit`` in your scripts.


logic operator
==============

Rule of thumb: Use ``-a`` and ``-o`` inside square brackets, ``&&`` and ``||`` outside.

It's important to understand the difference between shell syntax and the syntax of the ``[`` command:

   * ``&&`` and ``||`` are shell operators. They are used to combine the results of two commands.
     Because they are shell syntax, they have special syntactical significance and cannot be used
     as arguments to commands.

   * ``[`` is not special syntax. It's actually a command with the name ``[``, also known as test.
     Since ``[`` is just a regular command, it uses ``-a`` and ``-o`` for its and and or operators.
     It can't use ``&&`` and ``||`` because those are shell syntax that commands don't get to see.

But wait! Bash has a fancier test syntax in the form of ``[[ ]]``. If you use double square brackets,
you get access to things like regexes and wildcards. You can also use shell operators like ``&&``, ``||``,
``<``, and ``>`` freely inside the brackets because, unlike ``[``, the double bracketed form is special
shell syntax. Bash parses ``[[`` itself so you can write things like ``[[ $foo == 5 && $bar == 6 ]]``.

For example::

   [ "$1" = "yes" ] && [ -r $2.txt ]
   [ "$1" = "yes" -a $2 -lt 3 ]


subshell
========

**Synposis**

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


**Example**

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
