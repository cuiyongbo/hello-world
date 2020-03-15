************************
Python File module notes
************************

#. File Object

    .. code-block:: python

        >>> dir(file)
        ['close', 'closed', 'encoding', 'errors', 'fileno', 'flush', 'isatty', 'mode', 'name',
        'newlines', 'next', 'read', 'readinto', 'readline', 'readlines', 'seek', 'softspace',
        'tell', 'truncate', 'write', 'writelines', 'xreadlines']

#. open(name[, mode[, buffering]])

    Open a file, returning an object of the file type described in section File Objects.
    If the file cannot be opened, ``IOError`` is raised. When opening a file, it’s preferable
    to use *open()*  instead of invoking the file constructor directly.

    The first two arguments are the same as for stdio’s ``fopen().``

    The most commonly-used values of *mode* are 'r' for reading, 'w' for writing (truncating the file if it already exists),
    and 'a' for appending (which on some Unix systems means that all writes append to the end of the file regardless of the
    current seek position). **If mode is omitted, it defaults to 'r'. The default is to use text mode,** which may convert '\n'
    characters to a platform-specific representation on writing and back on reading. Thus, **when opening a binary file,
    you should append 'b' to the mode value to open the file in binary mode,** which will improve portability.

    The optional *buffering* argument specifies the file’s desired buffer size: 0 means unbuffered, 1 means line buffered, any other
    positive value means use a buffer of (approximately) that size (in bytes). A negative buffering means to use the system default,
    which is usually line buffered for tty devices and fully buffered for other files. If omitted, the system default is used.

    Modes 'r+', 'w+' and 'a+' open the file for updating (reading and writing); note that 'w+' truncates the file.

#. os.fdopen(fd [, mode='r' [, bufsize]])

    Return an open file object connected to a file descriptor fd. mode and bufsize is of the same meaning as in builtin ``open().``

#. codecs.open(filename, mode='rb', encoding=None, errors='strict', buffering=1)

    Similar to ``open`` except that the caller can specify the encoding used for the file.

#. Get file size

    .. code-block:: py

        >>> os.path.getsize("/tmp/realtime/realtime.data")
        5000920

#. Traverse a file

    .. code-block:: py

        >>> f.seek(0,0)
        >>> for line in f:
        ...     if(len(line.strip(' \r\n\t'))):
        ...             print line,
        ...
        *************
        Pending tasks
        *************
        #. speed up ti tile compilation
           - extract PointMap building
           - Grid splitting

#. ``file.read()`` return less data than it have read

    .. code-block:: py

        # Problem
        >>> f = open('traffic_info.nkvds.bak')
        >>> f.tell()
        0L
        >>> data = f.read(64)
        >>> f.tell()
        4096L

        # Solution
        >>> f = open(f.name, "rb")
        >>> f.tell()
        0L
        >>> data = f.read(64)
        >>> f.tell()
        64L

        # Indeed, append "b" to mode when you open a binary file.

#. check if a file exists

    .. code-block:: py

        os.path.isfile(path)
        os.path.ispath(path) # check if directory exists
        os.path.exists(path) # file + directory

#. python to implement unix touch

    .. code-block:: py

        import os
        def touch(fname, times=None):
            with open(fname, 'a'):
                os.utime(fname, times)

#. manipulate file path

    .. code-block:: py

        >>> abs_path = '/Users/cherry/Downloads/Comics/test.html'
        >>> os.path.dirname(abs_path)
        '/Users/cherry/Downloads/Comics'
        >>> fn = os.path.basename(abs_path)
        >>> fn
        'test.html'
        >>> os.path.splitext(fn)
        ('test', '.html')

#. move/copy/delete files, delete directory

    .. code-block:: py

        import shutil
        shutil.copyfile
        shutil.rmtree
        os.rename
        os.remove
