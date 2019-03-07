******************************
Python Miscellaneous Tricks 03
******************************

#. Python3 install/uninstall

    * Install python3: ``brew install python3``
    * Install packages for python3: ``pip3 install <package>``
    * Uninstall python3: ``brew uninstall python3``

#. set python3 as default python interpreter
   
    Added ``alias python=python3`` in **.bashrc** file.

#. Prohibit generating ``*.pyc`` file

    Add this code in your scripts::
   
        import sys
        sys.dont_write_bytecode = True
   
    The variable must be set **BEFORE** any import.
    and you can add it to your :envvar:`PYTHONSTARTUP`.

    About ``sys.dont_write_bytecode``:
    
    If this is true, Python won’t try to write ``.pyc`` or ``.pyo`` files on the import of source modules. 
    This value is initially set to True or False depending on the ``-B`` command line option and the 
    ``PYTHONDONTWRITEBYTECODE`` environment variable, but you can set it yourself to control bytecode 
    file generation.

    .. note::

        A program doesn’t run any faster when it is read from a ``.pyc`` 
        file than when it is read from a ``.py`` file; the only thing 
        that’s faster about ``.pyc`` files is the speed with which they are loaded.


#. The Interactive Startup File

    When you use Python interactively, it is frequently handy to have some standard commands
    executed every time the interpreter is started. You can do this by setting an environment
    variable named :envvar:`PYTHONSTARTUP` to the name of a file containing your start-up commands.
    This is similar to the :file:`.profile` feature of the Unix shells.
   
    **This file is only read in interactive sessions**, not when Python reads commands from a script,
    and not when :file:`/dev/tty` is given as the explicit source of commands (which otherwise behaves
    like an interactive session). It is executed in the same namespace where interactive commands are executed,
    so that objects that it defines or imports can be used without qualification in the interactive session.
    You can also change the prompts ``sys.ps1`` and ``sys.ps2`` in this file.
   
    If you want to read an additional start-up file from the current directory,
    you can program this in the global start-up file using code like::
   
        if os.path.isfile('.pythonrc.py'):
            exec(open('.pythonrc.py').read())
   
    If you want to use the startup file in a script,
    you must do this explicitly in the script::
   
        import os
        filename = os.environ.get('PYTHONSTARTUP')
        if filename and os.path.isfile(filename):
            with open(filename) as fobj:
                startup_file = fobj.read()
         exec(startup_file)
   
   
    Add follow codes to :file:`.bashrc`::
     
        PYTHONSTARTUP=~/.pythonrc
        export PYTHONSTARTUP
   
    Add command(s) you want to execute in :file:`~/.pythonrc`. like::
   
        import math, time, re
        import os, sys
        from pprint import pprint

    .. note::

        On windows, add an environmental variable named **PYTHONSTARTUP**, 
        and fill its value with the script's full path. (the lettercase doesn't matter)

#. python convert between uid and username
   
    .. code-block:: py

        import pwd, grp
        pprint([p for p in dir(os) if 'uid' in p])
        ['geteuid', 'getuid', 'seteuid', 'setreuid', 'setuid']
        dir(pwd)
        [..., 'getpwall', 'getpwnam', 'getpwuid', 'struct_passwd', 'struct_pwent']

        pwd.getpwuid(os.getuid())
        pwd.struct_passwd(pw_name='cherry', pw_passwd='********', pw_uid=501, pw_gid=20, pw_gecos='cherry', pw_dir='/Users/cherry', pw_shell='/bin/bash')
        pwd.getpwnam('root')
        pwd.struct_passwd(pw_name='root', pw_passwd='********', pw_uid=0, pw_gid=0, pw_gecos='System Administrator', pw_dir='/var/root', pw_shell='/bin/sh')
        pwd.getpwnam('cherry')
        pwd.struct_passwd(pw_name='cherry', pw_passwd='********', pw_uid=501, pw_gid=20, pw_gecos='cherry', pw_dir='/Users/cherry', pw_shell='/bin/bash')

        # another way to get username
        import getpass
        getpass.getuser()
        'cherry'
   
#. python to add an additional directory to search path
   
    Augment the default search path for module files. The format is the same as the shell’s **PATH**: 
    one or more directory pathnames separated by ``os.pathsep`` (e.g. colons on Unix or semicolons on Windows). 
    Non-existent directories are silently ignored.

    In addition to normal directories, individual **PYTHONPATH** entries may refer to zipfiles containing 
    pure Python modules (in either source or compiled form). Extension modules cannot be imported from zipfiles.

    The default search path is installation dependent, but generally begins with ``prefix/lib/pythonversion``. 
    It is always appended to **PYTHONPATH**.

    The search path can be manipulated from within a Python program as the variable ``sys.path``.

#. sys.path

    A list of strings that specifies the search path for modules. 
    Initialized from the environment variable **PYTHONPATH**, plus an installation-dependent default.

    As initialized upon program startup, the first item of this list, ``path[0]``, is the directory 
    containing the script that was used to invoke the Python interpreter. If the script directory is 
    not available (e.g. if the interpreter is invoked interactively or if the script is read 
    from standard input), ``path[0]`` is the empty string, which directs Python to search modules 
    in the current directory first. Notice that the script directory is inserted before the entries 
    inserted as a result of ``PYTHONPATH``::

        >>> pprint(sys.path)
        ['',
         '/usr/lib/python2.7',
         '/usr/lib/python2.7/plat-x86_64-linux-gnu',
         '/usr/lib/python2.7/lib-tk',
         '/usr/lib/python2.7/lib-old',
         '/usr/lib/python2.7/lib-dynload',
         '/usr/local/lib/python2.7/dist-packages',
         '/usr/lib/python2.7/dist-packages',
         '/usr/lib/python2.7/dist-packages/PILcompat',
         '/usr/lib/python2.7/dist-packages/gtk-2.0',
         '/usr/lib/pymodules/python2.7']
        >>> os.getenv('PYTHONPATH')
        >>> 

    A program is free to modify this list for its own purposes.

#. python convert between gid and group name
   
    .. code-block:: py

        import pwd, grp
        pprint([p for p in dir(os) if 'gid' in p])
        ['getegid', 'getgid', 'getpgid', 'setegid', 'setgid', 'setpgid', 'setregid']
        dir(grp)
        [..., 'getgrall', 'getgrgid', 'getgrnam', 'struct_group']

        # get group information from gid
        grp.getgrgid(os.getgid())
        grp.struct_group(gr_name='staff', gr_passwd='*', gr_gid=20, gr_mem=['root', 'cherry'])

        # get group information from groupname
        grp.getgrnam('staff')
        grp.struct_group(gr_name='staff', gr_passwd='*', gr_gid=20, gr_mem=['root', 'cherry'])

#. python to list all submodules in a module
   
    .. code-block:: py

        >>> import types
        >>> for key, obj in sp.__dict__.items():
        ...     if type(obj) is types.ModuleType:
        ...         print(key)
        ... 
        char
        math
        ...
        fftpack
        ndimage
        signal

#. python to check if an array is sorted
   
    Solution: ``all([l[i] <= l[i+1] for i in xrange(len(l)-1)])``.

#. python namedtuple
   
    .. code-block:: sh

        from colllectins import namedtuple

        help(namedtuple)
            namedtuple(typename, field_names, verbose=False, rename=False)
            Returns a new subclass of tuple with named fields.
    
        >>> Point = namedtuple('Point', ['x', 'y'])
        >>> Point.__doc__                   # docstring for the new class
        'Point(x, y)'
        >>> p = Point(11, y=22)             # instantiate with positional args or keywords
        >>> p[0] + p[1]                     # indexable like a plain tuple
        33
        >>> x, y = p                        # unpack like a regular tuple
        >>> x, y
        (11, 22)
        >>> p.x + p.y                       # fields also accessable by name
        33
        >>> d = p._asdict()                 # convert to a dictionary
        >>> d['x']
        11
        >>> Point(**d)                      # convert from a dictionary
        Point(x=11, y=22)
        >>> p._replace(x=100)               # _replace() is like str.replace() but targets named fields
        Point(x=100, y=22)

#. python to print without newline

    From Python2.6 you can import the print function from Python3: ``from __future__ import`` 
    This allows you to use the Python3's `print` function. In Python3, the `print` statement 
    has been changed into a function. In Python 3, you can instead do: ``print('.', end='')``. 
    If you are having trouble with buffering, you can flush the output by adding ``flush=True`` keyword argument.
