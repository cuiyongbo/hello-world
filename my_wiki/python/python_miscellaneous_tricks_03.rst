******************************
Python Miscellaneous Tricks 03
******************************

#. Python3 install/uninstall

    * Install python3: ``brew install python3``
    * Install packages for python3: ``pip3 install <package>``
    * Uninstall python3: ``brew uninstall python3``

#. set python3 as default python interpreter
   
    Added ``alias python=python3`` in .**bashrc** file.

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