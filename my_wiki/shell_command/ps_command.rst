********************
ps -- process status
********************

**DESCRIPTION**

   .. code-block:: none
      :caption: SYNOPSIS

      ps [-AaCcEefhjlMmrSTvwXx] [-O fmt | -o fmt] [-G gid[,gid...]]
         [-g grp[,grp...]] [-u uid[,uid...]] [-p pid[,pid...]] [-t tty[,tty...]]
         [-U user[,user...]]
      ps [-L]

   The :command:`ps` utility displays a header line, followed by lines containing
   information about all of your processes that have controlling terminals.

   A different set of processes can be selected for display by using any combination
   of the :option:`-a`, :option:`-G`, :option:`-g`, :option:`-p`, :option:`-T`,
   :option:`-t`, :option:`-U`, and :option:`-u` options.  If more than one of
   these options are given, then ps will select all processes which are matched
   by at least one of the given options.

   For the processes which have been selected for display, :command:`ps` will usually
   display one line per process.  The :option:`-M` option may result in multiple output
   lines (one line per thread) for some processes.  By default all of these output
   lines are sorted first by controlling terminal, then by process ID. The :option:`-m`,
   :option:`-r`, and :option:`-v` options will change the sort order. If more than one
   sorting option was given, then the selected processes will be sorted by the last
   sorting option which was specified.

   For the processes which have been selected for display, the information to
   display is selected based on a set of keywords (see the :option:`-L`, :option:`-O`,
   and :option:`-o` options). The default output format includes, for each process,
   the process'ID, controlling terminal, CPU time (including both user and system time),
   state, and associated command.


**OPTIONS**

   .. option:: -h

      Repeat the information header as often as necessary to
      guarantee one header per page of information.

   .. option:: -H

      Show process hierarchy (forest).

   .. option:: -M

      Print the threads corresponding to each task.

   .. option::  -T

      Show threads, possibly with SPID column.

   .. option:: -A / -e

      Display information about other users' processes,
      including those without controlling terminals.

   .. option:: -d

      Like :option:`-A`, but excludes session leaders.

   .. option:: -a

      Display information about other users' processes as well as your
      own. This will skip any processes which do not have a controlling
      terminal, unless the :option:`-x` option is also specified.

   .. option:: -p

      Display information about processes which match the specified process IDs.

   .. option: -q pidlist

      Select by PID (quick mode). This selects the processes
      whose process ID numbers appear in pidlist. With this
      option ps reads the necessary info only for the pids
      listed in the pidlist and doesn't apply additional
      filtering rules. The order of pids is unsorted and
      preserved. No additional selection options, sorting
      and forest type listings are allowed in this mode.
      Identical to q and --quick-pid.

   .. option:: -G

      Display information about processes which are running with the specified real group IDs.

   .. option:: -g

      Display information about processes with the specified process group leaders.

   .. option:: -U

      Display the processes belonging to the specified real user IDs.

   .. option:: -u

      Display the processes belonging to the specified usernames.

   .. option:: -c

      Change the "command" column output to just contain the executable name,
      rather than the full command line.

   .. option:: -E

      Display the environment as well. This does not reflect changes
      in the environment after process launch.
      Don't mix it with :option:`-c`.

   .. option:: -C cmdlist

      Select by command name. This selects the processes
      whose executable name is given in cmdlist.

   .. option:: -f

      Display the uid, pid, parent pid, recent CPU usage, process start time,
      controlling tty, elapsed CPU usage, and the associated command.
      If the :option:`-u` option is also used, display the user name
      rather then the numeric uid.

   .. option:: -j

      Print information associated with the following keywords:
      **user, pid, ppid, pgid, sess, jobc, state,
      tt, time, and command**.

   .. option:: -l

      Display information associated with the following keywords:
      **uid, pid, ppid, flags, cpu, pri, nice, vsz=SZ, rss, wchan,
      state=S, paddr=ADDR, tty, time, and command=CMD**.

   .. option:: -v

      Display information associated with the following keywords:
      **pid, state, time, sl, re, pagein, vsz, rss, lim, tsiz,
      %cpu, %mem, and command**.
      The :option:`-v` option implies the :option:`-m` option.

   .. option:: -O

      Add the information associated with the space or comma separated list of keywords specified,
      after the process ID, in the default information display. Keywords may be appended with an
      equals ('=') sign and a string. This causes the printed header to use the specified string
      instead of the standard header.

   .. option:: -o

      Display information associated with the space or comma separated list of keywords specified.
      Multiple keywords may also be given in the form of more than one :option:`-o` option.
      Keywords may be appended with an equals ('=') sign and a string. This causes the printed header
      to use the specified string instead of the standard header. If all keywords have empty header
      texts, no header line is written.

   .. option:: -r

      Sort by current CPU usage.

   .. option:: -m

      Sort by memory usage.

**PROCESS STATE CODES**

   Here are the different values that the s, stat and state output specifiers (header "STAT" or "S")
   will display to describe the state of a process::

      D    uninterruptible sleep (usually IO)
      R    running or runnable (on run queue)
      S    interruptible sleep (waiting for an event to complete)
      T    stopped by job control signal
      t    stopped by debugger during the tracing
      W    paging (not valid since the 2.6.xx kernel)
      X    dead (should never be seen)
      Z    defunct ("zombie") process, terminated but not reaped by its parent

   For BSD formats and when the stat keyword is used, additional characters may be displayed::

      <    high-priority (not nice to other users)
      N    low-priority (nice to other users)
      L    has pages locked into memory (for real-time and custom IO)
      s    is a session leader
      l    is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
      +    is in the foreground process group


**EXAMPLE**

.. code-block:: sh

   ps -e -U "$(who am i | cut –f1 -d " ")"
   ps aux | grep -i thunder | grep -v grep (忽略 grep 匹配行)
   ps aux | grep -i word | grep -v grep | awk '{print $2}'(提取PID)
   ps  u -p 72 (查询 PID 为72的进程)

   $ ps -o 'pid %cpu %mem state'
   PID  %CPU %MEM STAT
   435   0.0  0.0 S

   $ ps -O '%cpu %mem state'
   PID  %CPU %MEM STAT   TT  STAT      TIME COMMAND
   435   0.0  0.0 S    s000  S      0:00.86 -bash

   $ ps -fc
   UID   PID  PPID   C STIME   TTY           TIME CMD
   501   435   433   0 24Mar18 ttys000    0:00.88 -bash

   # To see every process on the system using standard syntax:
   ps -e
   ps -ef
   ps -eF
   ps -ely

   # To see every process on the system using BSD syntax:
   ps ax
   ps axu

   # To print a process tree:
   ps -ejH
   ps axjf

   $ ps -ejH | grep a.out
   16225 16225 15569 pts/2    00:00:00           a.out
   16226 16225 15569 pts/2    00:00:00             a.out

   # To get info about threads:
   ps -eLf
   ps axms

   # threads in a process
   $ ps -T -p16206
     PID  SPID TTY          TIME CMD
   16206 16206 pts/2    00:00:00 a.out
   16206 16208 pts/2    00:00:00 a.out
   16206 16209 pts/2    00:00:00 a.out
   16206 16210 pts/2    00:00:00 a.out


   # To get security info:
   ps -eo euser,ruser,suser,fuser,f,comm,label
   ps axZ
   ps -eM

   # To see every process running as root (real & effective ID) in user format:
   ps -U root -u root u

   # To see every process with a user-defined format:
   ps -eo pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:14,comm
   ps axo stat,euid,ruid,tty,tpgid,sess,pgrp,ppid,pid,pcpu,comm
   ps -Ao pid,tt,user,fname,tmout,f,wchan

   # Print only the process IDs of syslogd:
   ps -C syslogd -o pid=

   # Print only the name of PID 42:
   ps -q 42 -o comm=

   $ ps -a -C httpd -o pid=
     564
   29647
   29659
   $ ps -a -C httpd -o pid
     PID
     600
   29647
   29659
   $ ps -q 1 -o comm
   COMMAND
   systemd
   $ ps -q 1 -o comm=
   systemd
   $ ps -a -C pager -o user,pid
   USER       PID
   cherry    1360
   cherry   29647
   cherry   29659
