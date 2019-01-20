*********
os Module
*********


.. code-block:: none
    :caption: Hot Methods

    # os.getcwd()
    # os.chdir(path)
    # os.listdir(path) # just names, with no path components
    # os.path.exists(path)
    # os.path.getsize(path)
    # os.path.isabs(path)
    # os.path.isfile(path) # check if path is a regular file
    # os.path.isdir(path)
    # os.path.islink(path)
    # os.path.normpath(path) # only combine consective forward slashes

    >>> os.path.getsize("conf.py")
    6655
    >>> os.path.getsize("languages") # directory
    952
    >>> os.path.normpath('/ljklfs//sdf//sdf////sdf')
    '/ljklfs/sdf/sdf/sdf'
    >>> os.path.normpath('/ljklfs//sdf\\\sdf\\\sdf')
    '/ljklfs/sdf\\\\sdf\\\\sdf'


.. method:: os.walk(top, topdown=True, onerror=None, followlinks=False)
  
    Directory tree generator.

    For each directory in the directory tree rooted at top (including top itself, 
    but excluding ``'.'`` and ``'..'``), yields a 3-tuple ``(dirpath, dirnames, filenames)``. 

    *dirpath* is a string, the path to the directory. *dirnames* is a list of the names of 
    the subdirectories in *dirpath* (excluding ``'.'`` and ``'..'``). *filenames* is a 
    list of the names of the non-directory files in *dirpath*. **Note** that the names in the
    lists are just names, with no path components. To get a full path (which begins with top) 
    to a file or directory in *dirpath*, do ``os.path.join(dirpath, name)``.

    If optional arg *topdown* is true or not specified, the triple for a
    directory is generated before the triples for any of its subdirectories.  
    Otherwise, the triple for a directory is generated after the triples for 
    all of its subdirectories (directories are generated bottom up).

    When *topdown* is true, the caller can modify the *dirnames* list in-place
    (e.g., via del or slice assignment), and walk will only recurse into the
    subdirectories whose names remain in *dirnames*; this can be used to prune the
    search, or to impose a specific order of visiting. 
    No matter the value of *topdown*, the list of subdirectories is retrieved 
    before the tuples for the directory and its subdirectories are generated.

    By default errors from the ``os.listdir()`` call are ignored.  If
    optional arg *onerror* is specified, it should be a function; it
    will be called with one argument, an ``os.error`` instance.  It can
    report the error to continue with the walk, or raise the exception
    to abort the walk. Note that the filename is available as the
    filename attribute of the exception object.

    **Caution**:  if you pass a relative pathname for top, don't change the
    current working directory between resumptions of walk. walk never
    changes the current directory, and assumes that the client doesn't either.

    Example::

        import os
        from os.path import join, getsize
        for root, dirs, files in os.walk('python/Lib/email'):
            print root, "consumes",
            print sum([getsize(join(root, name)) for name in files]),
            print "bytes in", len(files), "non-directory files"
            if 'CVS' in dirs:
                dirs.remove('CVS')  # don't visit CVS directories

.. method:: os.path.walk(top, func, arg)

    For each directory in the directory tree rooted at top
    (including top itself, but excluding ``'.'`` and ``'..'``), 
    call ``func(arg, dirname, fnames)``. *dirname* is the name of the directory,
    and *fnames* a list of the names of the files and subdirectories in *dirname*
    (excluding ``'.'`` and ``'..'``).  *func* may modify the *fnames* list in-place
    (e.g. via del or slice assignment), and walk will only recurse into the
    subdirectories whose names remain in *fnames*; this can be used to implement
    a filter, or to impose a specific order of visiting. No semantics are defined
    for, or required of, *arg*, beyond that *arg* is always passed to *func*.
    It can be used, e.g., to pass a filename pattern, or a mutable object
    designed to accumulate statistics. Passing ``None`` for *arg* is common.

.. method:: os.path.join(path, *paths)

    Join one or more path components intelligently.
    The return value is the concatenation of path and
    any members of *paths* with exactly one directory separator
    (``os.sep``) following each non-empty part except the last,
    meaning that the result will only end in a separator if the
    last part is empty. If a component is an absolute path,
    all previous components are thrown away and joining continues
    from the absolute path component.

    On Windows, the drive letter is not reset when an absolute path
    component (e.g., ``r'\foo'``) is encountered. If a component
    contains a drive letter, all previous components are thrown away
    and the drive letter is reset. Note that since there is a current
    directory for each drive, ``os.path.join("c:", "foo")`` represents
    a path relative to the current directory on drive
    ``C: (c:foo)``, not ``c:\foo``.  

.. function:: os.urandom(n)
    
    Return n random bytes suitable for cryptographic use.
    On a UNIX-like system this will query ``/dev/urandom``, 
    and on Windows it will use ``CryptGenRandom()``. If a randomness 
    source is not found, ``NotImplementedError`` will be raised.

.. method:: os.times()
    
    Return a 5-tuple (``(utime, stime, cutime, cstime, elapsed_time)``) 
    of floating point numbers indicating accumulated (processor or other) times, in seconds. 
    The items are: **user time, system time, children’s user time, children’s system time, 
    and elapsed real time** since a fixed point in the past, in that order::

        >>> os.times()
        (1.84, 2.47, 0.07, 0.03, 1547864527.64)
        >>> time.ctime(1547864527.64)
        'Sat Jan 19 10:22:07 2019'

.. method:: os.utime(path, times)

    Set the access and modified times of the file specified by path. 
    If times is None, then the file’s access and modified times are set to 
    the current time. (The effect is similar to running the Unix program **touch** 
    on the path.) Otherwise, times must be a 2-tuple of numbers, of the form ``(atime, mtime)`` 
    which is used to set the access and modified times, respectively. 

#. Python to traverse a directory

   .. code-block:: python
     
        # Traversing directory using ``os.listdir()``
        files = os.listdir(".")
        for file in files:
            doWork(file)
   
        # Traversing directory using ``os.path.walk()``
        # It will walk subdirectories recursively
        def printFile(arg, dirname, fnames):
            print arg
            print dirname
            print fnames
        os.path.walk(".", printFile, None)

#. Get/set environment variable
 
    .. code-block:: py
    
        # to view current environment variables, execute `env` in terminal
        >>> [p for p in dir(os) if 'env' in p]
        ['environ', 'getenv', 'putenv', 'unsetenv']

        >>> os.getenv("SHELL")
        '/bin/bash'

        # putenv doesn't work as expected
        >>> os.environ["MASTER"] = 'cyb'
        >>> os.getenv('MASTER')
        'cyb'
