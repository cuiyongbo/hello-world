**********************
kill & killall Command
**********************

#. kill -- terminate or signal a process

    .. code-block:: sh
        :caption: SYNOPSIS

        kill [-s signal_name] pid ...
        kill -l [exit_status]
        kill -signal_name pid ...
        kill -signal_number pid ...

    The **kill** utility sends a signal to the processes
    specified by the *pid* operands. Only the super-user 
    may send signals to other users' processes.

    .. code-block:: sh

        kill 142 157 # Terminate the processes with PIDs 142 and 157

        kill -s HUP 507 # Send the hangup signal (SIGHUP) to the process with PID 507
        kill -HUP 507 # Ditto
        kill -1 507 #Ditto

        $ kill -l 3
        QUIT
        $ kill -l 15
        TERM

        $ kill -l
         1) SIGHUP      2) SIGINT      3) SIGQUIT     4) SIGILL
         5) SIGTRAP     6) SIGABRT     7) SIGEMT      8) SIGFPE
         9) SIGKILL    10) SIGBUS     11) SIGSEGV    12) SIGSYS
        13) SIGPIPE    14) SIGALRM    15) SIGTERM    16) SIGURG
        17) SIGSTOP    18) SIGTSTP    19) SIGCONT    20) SIGCHLD
        21) SIGTTIN    22) SIGTTOU    23) SIGIO      24) SIGXCPU
        25) SIGXFSZ    26) SIGVTALRM  27) SIGPROF    28) SIGWINCH
        29) SIGINFO    30) SIGUSR1    31) SIGUSR2 


#. killall -- kill processes by name

    .. code-block:: sh
        :caption: SYNOPSIS

        killall [-delmsvz] [-help] [-u user] [-t tty] [-c procname] [-SIGNAL] [procname ...]

    The **killall** utility kills processes selected by name,
    as opposed to the selection by pid as done by :manpage:`kill(1)`.
    By default, it will send a TERM signal to all processes with a
    real UID identical to the caller of **killall** that match
    the name procname. The super-user is allowed to kill any process.

    .. option:: -d          

        Print detailed information about the processes
        matched, but do not send any signal.

    .. option:: -s          

        Show only what would be done, but do not send any signal.

    .. option:: -SIGNAL     

        Send a different signal instead of the default TERM.
        The signal may be specified either as a name (with
        or without a leading SIG), or numerically.

    .. option:: -c procname

        When used with the :option:`-u` or :option:`-t` flags,
        limit potentially matching processes to those matching
        the specified *procname*.

    .. option:: -u user     

        Limit potentially matching processes to those
        belonging to the specified *user*.

    .. option:: -t tty      

        Limit potentially matching processes to those
        running on the specified *tty*.

    .. option::  -z          

        Do not skip zombies. This should not have any effect
        except to print a few error messages if there are
        zombie processes that match the specified pattern.
        See more about :doc:`Zombie Process </programmer_note/linux_system_call/fork_info>`.

    .. code-block:: sh

        $ killall -l
        HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE ALRM TERM URG STOP 
        TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM PROF WINCH INFO USR1 USR2 

        $ killall -s -c Thunder
        kill -TERM 31416
      
        $ killall -d -c Thunder
        uid:501
        nprocs 201
        sig:15, cmd:Thunder, pid:31416, dev:0xffffffff

        $ killall -m Kugou*

