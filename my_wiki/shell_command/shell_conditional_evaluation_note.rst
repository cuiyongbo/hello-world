**************************
Shell Condition evaluation
**************************

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


#. logic operator

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