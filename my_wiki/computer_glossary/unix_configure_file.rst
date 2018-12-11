*****************
Unix config files
*****************

#. bashrc

   System-wide :file:`.bashrc` file for interactive bash(1) shells lies 
   at :file:`/etc/bashrc`, while user-specific one lies at :file:`$HOME/.bashrc`. 
   
   .. code-block:: sh
      :caption: bashrc sample
   
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
      
      # If set, the pattern "**" used in a pathname expansion context will
      # match all files and zero or more directories and subdirectories.
      #shopt -s globstar
      
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
          PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
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
      
      # some more ls aliases
      alias ll='ls -alF'
      alias la='ls -A'
      alias l='ls -CF'
      
      # Add an "alert" alias for long running commands.  Use like so:
      #   sleep 10; alert
      alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e  '\''s/^\s*[  0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
      
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
      
      export PATH=$PATH:~/workspace/bin
   
#. profile

  System-wide :file:`.profile` file for interactive bash(1) shells lies at :file:`/etc/profile`,
  while user-specific one lies at :file:`$HOME/.profile`. 
  
  .. code-block:: sh
     :caption: profile sample
  
     # ~/.profile: executed by the command interpreter for login shells.
     # This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
     # exists.
     # see /usr/share/doc/bash/examples/startup-files for examples.
     # the files are located in the bash-doc package.
     
     # the default umask is set in /etc/profile; for setting the umask
     # for ssh logins, install and configure the libpam-umask package.
     #umask 022
     
     # if running bash
     if [ -n "$BASH_VERSION" ]; then
         # include .bashrc if it exists
         if [ -f "$HOME/.bashrc" ]; then
        . "$HOME/.bashrc"
         fi
     fi
     
     # set PATH so it includes user's private bin if it exists
     if [ -d "$HOME/bin" ] ; then
         PATH="$HOME/bin:$PATH"
     fi


#. Case Study: Mac OS X does not read **.bashrc** for interactive shell

   Been there, done that. What I came aware of, OS X doesn't read **.bashrc** file on bash start. 
   Instead, it reads the following files (in the following order)::
   
      /etc/profile
      ~/.bash_profile
      ~/.bash_login
      ~/.profile
   
   By default, Terminal starts the shell via **/usr/bin/login**, which makes the shell a login shell. 
   On every platform (not just Mac OS X) bash does not use **.bashrc** for login shells 
   (only **/etc/profile** and the first of **.bash_profile, .bash_login, .profile** that 
   exists and is readable). This is why **put source ~/.bashrc in your .bash_profile** is 
   standard advice.

