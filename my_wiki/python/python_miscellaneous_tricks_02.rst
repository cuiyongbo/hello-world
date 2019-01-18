******************************
Python Miscellaneous Tricks 02
******************************

#. python interpreter to suppress startup message.
   
    For python 2.x, you can do around with ``python -ic ""``.
    But with python 3.x, ``python3 -q`` would suffice.

    Note::

        -c command
        Specify the command to execute. This terminates the option list, 
        following options are passed as arguments to the command.

        -i     
        When a script is passed as first argument or the -c option is used, 
        enter interactive mode after executing the script or the  command.  
        It does not read the $PYTHONSTARTUP file. This can be useful to 
        inspect global variables or a stack trace when a script raises an exception.

#. python assert usage
   
    Syntax: ``assert Expression[, Arguments]``
   
    If the assertion fails, Python uses *ArgumentExpression* as the argument for the *AssertionError*,
    which can be caught and handled like any other exception using the try-except statement, 
    but if not handled, they will terminate the program and produce a traceback. for example::

        def max_heapify_siftdown(array, i):
            assert (i < len(array)),"index out of range"
            # ...

#. python to collect code running time
   
    .. code-block:: py

        >>> import timeit

        # timeit.timeit(stmt='pass', setup='pass', 
        #   timer=<default timer>, number=1000000)
        #
        # Create a Timer instance with the given statement, 
        # setup code and timer function and run its timeit() 
        # method with number executions.
      
        >>> timeit.timeit('"-".join(map(str, range(100)))', number=10000)
        0.14010405540466309
        >>> timeit.timeit('"-".join(map(str, range(100)))', number=1000)
        0.016650915145874023
        >>> timeit.timeit('"-".join(map(str, range(100)))', number=100)
        0.0018639564514160156

        # from command-line
        $ python -m timeit '"-".join(map(str, range(100)))'
        100000 loops, best of 3: 12.2 usec per loop

    Refer to `timeit docs <https://docs.python.org/2/library/timeit.html>`_ for further information.

#. difference between ``/`` and ``//.`` 
     
    In Python 3.0, ``5 / 2`` will return 2.5 and ``5 // 2`` will return 2. 
    The former is floating point division, and the latter is floor 
    division, sometimes also called integer division.

    In Python 2.2 or later in the 2.x line, there is no difference for integers 
    unless you perform a ``from __future__ import division,`` which causes 
    Python 2.x to adopt the behavior of 3.0.

    Refer to 
    `PEP 238: Changing the Division Operator <https://docs.python.org/whatsnew/2.2.html#pep-238-changing-the-division-operator>`_
    for more information.

#. python to see imported modules
   
    .. code-block:: py

        >>> pprint(globals())
        {'__builtins__': <module '__builtin__' (built-in)>,
         '__doc__': None,
         '__name__': '__main__',
         '__package__': None,
         'json': <module 'json' from '/usr/lib/python2.7/json/__init__.pyc'>,
         'math': <module 'math' (built-in)>,
         'os': <module 'os' from '/usr/lib/python2.7/os.pyc'>,
         'pprint': <function pprint at 0x7fe3efc669b0>,
         'random': <module 'random' from '/usr/lib/python2.7/random.pyc'>,
         're': <module 're' from '/usr/lib/python2.7/re.pyc'>,
         'sys': <module 'sys' (built-in)>,
         'time': <module 'time' (built-in)>}
   
#. python get signal name from signal num
   
    .. code-block:: py

        >>> g_signal_num_2_name=dict((getattr(signal, n),n) for n in dir(signal) \
                                      if n.startswith("SIG") and '_' not in n)
        >>> pprint(g_signal_num_2_name)
        {1: 'SIGHUP',
         2: 'SIGINT',
         3: 'SIGQUIT',
         4: 'SIGILL',
         5: 'SIGTRAP',
         6: 'SIGIOT',
         7: 'SIGBUS',
         8: 'SIGFPE',
         9: 'SIGKILL',
         10: 'SIGUSR1',
         11: 'SIGSEGV',
         12: 'SIGUSR2',
         13: 'SIGPIPE',
         14: 'SIGALRM',
         15: 'SIGTERM',
         17: 'SIGCLD',
         18: 'SIGCONT',
         19: 'SIGSTOP',
         20: 'SIGTSTP',
         21: 'SIGTTIN',
         22: 'SIGTTOU',
         23: 'SIGURG',
         24: 'SIGXCPU',
         25: 'SIGXFSZ',
         26: 'SIGVTALRM',
         27: 'SIGPROF',
         28: 'SIGWINCH',
         29: 'SIGPOLL',
         30: 'SIGPWR',
         31: 'SIGSYS',
         34: 'SIGRTMIN',
         64: 'SIGRTMAX'}

