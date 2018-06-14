************
Shell Script
************

Pipe & Redirect
===============

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

.. code-block:: sh
   :caption: Check if a process is alive

   result=""
   until
      sleep 5 
      result=$(ps aux | grep traffic_data_updater | grep -v grep)
      [ -z "$result" ]
   do :; done


Flow Control: case
==================

**Synposis**

.. code-block:: sh

   case word in
      pattern1)
         Statement(s) to be executed if pattern1 matches
         ;; # similar to break in C/C++
      pattern2)
         Statement(s) to be executed if pattern2 matches
         ;;
      pattern3)
         Statement(s) to be executed if pattern3 matches
         ;;
      *)
        Default condition to be executed
        ;;
   esac

**Example**

.. code-block:: sh
   :caption: case example match specific string

   #!/usr/bin/env sh

   FRUIT="kiwi"
   
   case "$FRUIT" in
      "apple") echo "Apple pie is quite tasty." 
      ;;
      "banana") echo "I like banana nut bread." 
      ;;
      "kiwi") echo "New Zealand is famous for kiwi." 
      ;;
      *) echo "Sorry, I have no idea."
      ;;
   esac

.. code-block:: sh
   :caption: case example prints file information

   #!/bin/sh

   option="${1}" 
   case ${option} in 
      -f) FILE="${2}" 
         echo "File name is $FILE"
         ;; 
      -d) DIR="${2}" 
         echo "Dir name is $DIR"
         ;; 
      *)  
         echo "`basename ${0}`:usage: [-f file] | [-d directory]" 
         exit 1 # Command to come out of the program with status 1
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


Condition evaluation
====================

**Language Support**

Here is a list of the conditions that test can evaluate.
Since test is a shell builtin, use ``help test`` to see
a complete list::

   $ help test
   test: test [expr]
      Evaluate conditional expression.
   
      Exits with a status of 0 (true) or 1 (false) depending on
      the evaluation of EXPR. Expressions may be unary or binary. Unary
      expressions are often used to examine the status of a file. There
      are string operators and numeric comparison operators as well.
   
      The behavior of test depends on the number of arguments. Read the
      bash manual page for the complete specification.
   
      File operators:
   
         -a FILE        True if file exists.
         -b FILE        True if file is block special.
         -c FILE        True if file is character special.
         -d FILE        True if file is a directory.
         -e FILE        True if file exists.
         -f FILE        True if file exists and is a regular file.
         -g FILE        True if file is set-group-id.
         -h FILE        True if file is a symbolic link.
         -L FILE        True if file is a symbolic link.
         -k FILE        True if file has its `sticky' bit set.
         -p FILE        True if file is a named pipe.
         -r FILE        True if file is readable by you.
         -s FILE        True if file exists and is not empty.
         -S FILE        True if file is a socket.
         -t FD          True if FD is opened on a terminal.
         -u FILE        True if the file is set-user-id.
         -w FILE        True if the file is writable by you.
         -x FILE        True if the file is executable by you.
         -O FILE        True if the file is effectively owned by you.
         -G FILE        True if the file is effectively owned by your group.
         -N FILE        True if the file has been modified since it was last read.
   
         FILE1 -nt FILE2  True if file1 is newer than file2 (according to
                          modification date).
   
         FILE1 -ot FILE2  True if file1 is older than file2.
   
         FILE1 -ef FILE2  True if file1 is a hard link to file2.
   
      String operators:
   
         -z STRING      True if string is empty.
   
         -n STRING
            STRING      True if string is not empty.
   
         STRING1 = STRING2
                        True if the strings are equal.
        
         STRING1 != STRING2
                        True if the strings are not equal.
        
         STRING1 < STRING2
                        True if STRING1 sorts before STRING2 lexicographically.
        
         STRING1 > STRING2
                        True if STRING1 sorts after STRING2 lexicographically.
   
      Other operators:
   
         -o OPTION      True if the shell option OPTION is enabled.
         -v VAR     True if the shell variable VAR is set
         -R VAR     True if the shell variable VAR is set and is a name reference.
         ! EXPR         True if expr is false.
         EXPR1 -a EXPR2 True if both expr1 AND expr2 are true.
         EXPR1 -o EXPR2 True if either expr1 OR expr2 is true.
   
         arg1 OP arg2   Arithmetic tests. OP is one of -eq, -ne,
                        -lt, -le, -gt, or -ge.
   
      Arithmetic binary operators return true if ARG1 is equal, not-equal,
      less-than, less-than-or-equal, greater-than, or greater-than-or-equal
      than ARG2.
   
      Exit Status:
      Returns success if EXPR evaluates to true; fails if EXPR evaluates to
      false or an invalid argument is given.

**Example**

.. code-block:: sh
   :caption: Linux .bashrc

   # ~/.bashrc: executed by bash(1) for non-login shells.
   # see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
   # for examples
   
   # If not running interactively, don't do anything
   case $- in
       *i*) ;;
         *) return;;
   esac
   
   # don't put duplicate lines or lines starting with space in the history.
   # See bash(1) for more options
   HISTCONTROL=ignoreboth
   
   # append to the history file, don't overwrite it
   shopt -s histappend
   
   # for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
   HISTSIZE=1000
   HISTFILESIZE=2000
   
   # check the window size after each command and, if necessary,
   # update the values of LINES and COLUMNS.
   shopt -s checkwinsize
   
   # If set, the pattern "**" used in a pathname expansion context will
   # match all files and zero or more directories and subdirectories.
   #shopt -s globstar
   
   # make less more friendly for non-text input files, see lesspipe(1)
   [ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"
   
   # set variable identifying the chroot you work in (used in the prompt below)
   if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
       debian_chroot=$(cat /etc/debian_chroot)
   fi
   
   # set a fancy prompt (non-color, unless we know we "want" color)
   case "$TERM" in
       xterm-color) color_prompt=yes;;
   esac
   
   # uncomment for a colored prompt, if the terminal has the capability; turned
   # off by default to not distract the user: the focus in a terminal window
   # should be on the output of commands, not on the prompt
   #force_color_prompt=yes
   
   if [ -n "$force_color_prompt" ]; then
       if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
      # We have color support; assume it's compliant with Ecma-48
      # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
      # a case would tend to support setf rather than setaf.)
      color_prompt=yes
       else
      color_prompt=
       fi
   fi
   
   if [ "$color_prompt" = yes ]; then
       PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
   else
       PS1='${debian_chroot:+($debian_chroot)}\u@\h:\W\$ '
       #PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
   fi
   unset color_prompt force_color_prompt
   
   # If this is an xterm set the title to user@host:dir
   case "$TERM" in
   xterm*|rxvt*)
       PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
       ;;
   *)
       ;;
   esac
   
   # enable color support of ls and also add handy aliases
   if [ -x /usr/bin/dircolors ]; then
       test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
       alias ls='ls --color=auto'
       #alias dir='dir --color=auto'
       #alias vdir='vdir --color=auto'
   
       alias grep='grep --color=auto'
       alias fgrep='fgrep --color=auto'
       alias egrep='egrep --color=auto'
   fi
   
   # some more ls aliases
   alias ll='ls -alF'
   alias la='ls -A'
   alias l='ls -CF'
   
   # Add an "alert" alias for long running commands.  Use like so:
   #   sleep 10; alert
   alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
   
   # Alias definitions.
   # You may want to put all your additions into a separate file like
   # ~/.bash_aliases, instead of adding them here directly.
   # See /usr/share/doc/bash-doc/examples in the bash-doc package.
   
   if [ -f ~/.bash_aliases ]; then
       . ~/.bash_aliases
   fi
   
   # enable programmable completion features (you don't need to enable
   # this, if it's already enabled in /etc/bash.bashrc and /etc/profile
   # sources /etc/bash.bashrc).
   if ! shopt -oq posix; then
     if [ -f /usr/share/bash-completion/bash_completion ]; then
       . /usr/share/bash-completion/bash_completion
     elif [ -f /etc/bash_completion ]; then
       . /etc/bash_completion
     fi
   fi
   
   export PYTHONPATH=$PYTHONPATH:~/workspace/bin
