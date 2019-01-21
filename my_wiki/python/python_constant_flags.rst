*********************
Python Constant Flags
*********************

#. signal - mechanisms to use signal handlers in Python
    
    .. code-block:: py
        :caption: get signal name from signal number

        # in python2
        import signal
        >>> g_signal_num_2_name=dict((getattr(signal, n),n) for n in dir(signal) \
                                      if n.startswith("SIG") and '_' not in n)
        >>> g_signal_num_2_name
        {1: 'SIGHUP', 2: 'SIGINT', 3: 'SIGQUIT', 4: 'SIGILL', 5: 'SIGTRAP', 6: 'SIGIOT', 
        7: 'SIGEMT', 8: 'SIGFPE', 9: 'SIGKILL', 10: 'SIGBUS', 11: 'SIGSEGV', 12: 'SIGSYS', 
        13: 'SIGPIPE', 14: 'SIGALRM', 15: 'SIGTERM', 16: 'SIGURG', 17: 'SIGSTOP', 18: 'SIGTSTP', 
        19: 'SIGCONT', 20: 'SIGCHLD', 21: 'SIGTTIN', 22: 'SIGTTOU', 23: 'SIGIO', 24: 'SIGXCPU', 
        25: 'SIGXFSZ', 26: 'SIGVTALRM', 27: 'SIGPROF', 28: 'SIGWINCH', 29: 'SIGINFO', 
        30: 'SIGUSR1', 31: 'SIGUSR2'}

        # but in python3, things go simple
        >>> signal.SIGABRT
        <Signals.SIGABRT: 6>
        >>> type(signal.SIGABRT)
        <enum 'Signals'>
        >>> signal.SIGABRT.name
        'SIGABRT'
        >>> signal.SIGABRT.value
        6

#. stat - Constants/functions for interpreting results of ``os.stat()`` and ``os.lstat()``

    The following flags can also be used in the mode argument of ``os.chmod()``::
    
        stat.S_ISUID
        Set UID bit (short for "set user ID upon execution").
    
        stat.S_ISGID
        S_ISGIDet-group-ID bit (short for "set group ID upon execution"). 
        This bit has several special uses. 
        For a directory it indicates that BSD semantics is to be used 
        for that directory: files created there inherit their gid from 
        the directory, not from the effective gid of the creating process, 
        and directories created there will also get the S_ISGID bit set. 
        For a file that does not have the group execution bit (S_IXGRP) set, 
        the set-group-ID bit indicates mandatory file/record locking.
    
        stat.S_ISVTX
        Sticky bit. When this bit is set on a directory it means that 
        a file in that directory can be renamed or deleted only by the 
        owner of the file, by the owner of the directory, or by a privileged process.

        stat.S_ENFMT
        stat.S_IREAD
        stat.S_IWRITE
        stat.S_IEXEC
        stat.S_IRWXU
        stat.S_IRUSR
        stat.S_IWUSR
        stat.S_IXUSR
        stat.S_IRWXG
        stat.S_IRGRP
        stat.S_IWGRP
        stat.S_IXGRP
        stat.S_IRWXO
        stat.S_IROTH
        stat.S_IWOTH
        stat.S_IXOTH

    .. Note:: 

        While the setuid feature is very useful in many cases, 
        its improper use can pose a security risk if the setuid attribute 
        is assigned to executable programs that are not carefully designed. 
        Due to potential security issues, **many OS ignore the setuid attribute 
        when applied to executable shell scripts**.