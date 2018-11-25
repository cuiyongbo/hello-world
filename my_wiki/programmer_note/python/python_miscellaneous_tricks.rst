***************************
Python Miscellaneous Usages
***************************

#. input vs raw_input

   ``input()`` assumes that what you enter is a valid Python expression (it’s
   more or less the inverse of ``repr``). If you write your name as a string, 
   that’s no problem::
   
      >>> name = input("name:")
      name:'nihao'
   
   However, it’s just a bit too much to ask that users write their name in quotes like this.
   
   .. code-block:: python
   
      >>> name = input("name:")
      name:nihao
      Traceback (most recent call last):
        File "<stdin>", line 1, in <module>
        File "<string>", line 1, in <module>
      NameError: name 'nihao' is not defined
   
   Therefore, we use ``raw_input()``, which treats all input as raw data 
   and puts it into a string::
   
      >>> name = raw_input("name:")
      name:nihao
   
   Unless you have a special need for ``input()``, you should probably use ``raw_input()``.
      
#. Useful Function List

   +------------------------------+------------------------------------------------------------------------+
   | Function                     | Description                                                            |
   +==============================+========================================================================+
   | ``help()``                   | Offers interactive help                                                |
   +------------------------------+------------------------------------------------------------------------+
   | ``str(object)``              | Converts a value to string                                             |
   +------------------------------+------------------------------------------------------------------------+
   | ``int(object)``              | Converts a string or number to an integer                              |
   +------------------------------+------------------------------------------------------------------------+
   | ``long(object)``             | Converts a string or number to a long integer                          |
   +------------------------------+------------------------------------------------------------------------+
   | ``float(object)``            | Converts a string or number to a float-point number                    |
   +------------------------------+------------------------------------------------------------------------+
   | ``repr(object)``             | Returns a string representation                                        |
   +------------------------------+------------------------------------------------------------------------+
   | ``abs(number)``              | Returns the absolute value of a number                                 |
   +------------------------------+------------------------------------------------------------------------+
   | ``round(number[, ndigits])`` | Rounds a number to a given precision                                   |
   +------------------------------+------------------------------------------------------------------------+
   | ``cmath.sqrt(number)``       | Returns the square root; works with negative numbers                   |
   +------------------------------+------------------------------------------------------------------------+
   | ``math.sqrt(number)``        | Ditto; but doesn’t work with negative numbers                          |
   +------------------------------+------------------------------------------------------------------------+
   | ``math.trunc(x)``            | Truncate x to Integral                                                 |
   +------------------------------+------------------------------------------------------------------------+
   | ``bin(number)``              | Return the binary representation of an integer or long integer.        |
   +------------------------------+------------------------------------------------------------------------+
   | ``hex(number)``              | Return the hexadecimal representation of an integer or long integer.   |
   +------------------------------+------------------------------------------------------------------------+
   | ``oct(num)``                 | Return the octal representation of an integer or long integer.         |
   +------------------------------+------------------------------------------------------------------------+
   | ``integer.bit_length()``     | Return the number of bits necessary to represent an integer in binary, |
   |                              | excluding the sign and leading zeros                                   |
   +------------------------------+------------------------------------------------------------------------+
   | ``len(object)``              | Return the number of items of a sequence or collection.                |
   +------------------------------+------------------------------------------------------------------------+


#. Python ByteOrder

   For multibyte data, It follows the architecture of the machine by default. If you need it to work cross-platform, 
   then you'll want to force it. ASCII and UTF-8 are encoded as a single byte per character, so is it affected by 
   the byte ordering? No.
   
   Here is how to pack little ``<`` or big ``>`` endian:
   
   .. code-block:: py
   
      import struct
      
      struct.pack('<L', 1234)
      '\xd2\x04\x00\x00'
      
      struct.pack('>L', 1234)
      '\x00\x00\x04\xd2'
   
   You can also encode strings as big or little endian this way if you are using UTF-16, as an example:
   
   .. code-block:: py
   
      s.encode('utf-16LE')
      s.encode('utf-16BE')
   
   UTF-8, ASCII do not have endianness since it is 1 byte per character.


#. sys Module Tricks

   +---------------+------------------------------------------------------------------+
   | Attribute     | Description                                                      |
   +===============+==================================================================+
   | argv          | command line arguments; argv[0] is the script pathname if known  |
   +---------------+------------------------------------------------------------------+
   | modules       | dictionary of loaded modules                                     |
   +---------------+------------------------------------------------------------------+
   | getsizeof()   | return the size of an object in bytes                            |
   +---------------+------------------------------------------------------------------+
   | getrefcount() | return the reference count for an object (plus one :-)           |
   +---------------+------------------------------------------------------------------+
   | gettrace()    | get the global debug tracing function                            |
   +---------------+------------------------------------------------------------------+
   | platform      | platform identifier                                              |
   +---------------+------------------------------------------------------------------+
   | executable    | absolute path of the executable binary of the Python interpreter |
   +---------------+------------------------------------------------------------------+
   | byteorder     | system byteorder                                                 |
   +---------------+------------------------------------------------------------------+
   
   .. code-block:: py
   
      >>> import sys
      >>> dir(sys)
      ['api_version', 'argv', 'builtin_module_names', 'byteorder', 'call_tracing', 'callstats', 'copyright', 'displayhook', 
      'dont_write_bytecode', 'exc_clear', 'exc_info', 'exc_type', 'excepthook', 'exec_prefix', 'executable', 'exit', 'flags', 
      'float_info', 'float_repr_style', 'getcheckinterval', 'getdefaultencoding', 'getdlopenflags', 'getfilesystemencoding', 
      'getprofile', 'getrecursionlimit', 'getrefcount', 'getsizeof', 'gettrace', 'hexversion', 'long_info', 'maxint', 'maxsize', 
      'maxunicode', 'meta_path', 'modules', 'path', 'path_hooks', 'path_importer_cache', 'platform', 'prefix', 'ps1', 'ps2', 'py3kwarning', 
      'pydebug', 'setcheckinterval', 'setdlopenflags', 'setprofile', 'setrecursionlimit', 'settrace', 'stderr', 'stdin', 'stdout', 
      'subversion', 'version', 'version_info', 'warnoptions']
      >>> sys.version
      '2.7.6 (default, Oct 26 2016, 20:30:19) \n[GCC 4.8.4]'
      >>> sys.version_info
      sys.version_info(major=2, minor=7, micro=6, releaselevel='final', serial=0)


#. Executable Python Scripts

   On BSD’ish Unix systems, Python scripts can be made directly executable,
   like shell scripts, by putting the line
   
   .. code-block:: sh
   
      #!/usr/bin/env python
      # coding: utf-8 # source code encoding
   
   (assuming that the interpreter is on the user’s :envvar:`PATH`) at the beginning of the script
   and giving the file an executable mode. The ``#!`` must be the first two characters of the file.
   On some platforms, this first line must end with a Unix-style line ending ('\n'),
   not a Windows ('\r\n') line ending. Note that the hash, or pound, character,
   ``'#'``, is used to start a comment in Python.
   
   The script can be given an executable mode, or permission,
   using the :command:`chmod` command.
   
   .. code-block:: sh
   
      $ chmod +x myscript.py
   
   On Windows systems, there is no notion of an “executable mode”.
   The Python installer automatically associates ``.py`` files with :command:`python.exe`
   so that a double-click on a Python file will run it as a script. The extension can also be ``.pyw``,
   in that case, the console window that normally appears is suppressed.


#. Source Code Encoding

   By default, Python source files are treated as encoded in ASCII. 
   To declare an encoding other than the default one, a special comment 
   line should be added as the first line of the file. The syntax is 
   as follows ``#coding: encoding`` where *encoding* is one of the 
   valid codecs supported by Python.
   
   For example, to declare that Windows-1252 encoding is to be used, the 
   first line of your source code file should be ``#coding: cp1252.``
   
   One exception to the first line rule is when the source code starts with 
   a UNIX “shebang” line. In this case, the encoding declaration should be 
   added as the second line of the file. For example::
   
      #!/usr/bin/env python
      #coding: cp1252


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

      On windows, add an environmental variable named **PYTHONSTARTUP**, and fill its value
      with the script's full path. (the lettercase doesn't matter)

#. Python3 install/uninstall

   Install python3::
   
      $ brew install python3
   
   Install packages for python3::
   
      $ pip3 install <package>
   
   Uninstall python3::
   
      $ brew uninstall python3


#. Prohibit generating ``*.pyc`` file

   Add this code in your scripts::
   
      import sys
      sys.dont_write_bytecode = True
   
   The variable must be set **BEFORE** any import.
   you can add it to your :envvar:`PYTHONSTARTUP`.

   To speed up loading modules, Python caches the compiled version 
   of each module in the __pycache__ directory under the name 
   ``module.version.pyc,`` where the version encodes the format 
   of the compiled file; it generally contains the Python version 
   number. This naming convention allows compiled modules from 
   different releases and different versions of Python to coexist.

   .. note::

      A program doesn’t run any faster when it is read from a ``.pyc`` 
      file than when it is read from a ``.py`` file; the only thing 
      that’s faster about ``.pyc`` files is the speed with which they are loaded.


#. Convert uncode string to Chinese characters

   .. code-block:: python
   
      >>> print '\u5f53\u524d\u9053\u8def\u56e0\u9053\u8def\u65bd\u5de5\u7981\u6b62\u901a\u884c'.decode('unicode-escape')
      当前道路因道路施工禁止通行


#. Binary to Decimal

   .. code-block:: py
   
      >>> int("1111", 2)
      15
      
      >>> def get_int_big_endian(data):
      ...     return int(data.encode('hex'), 16)
      ...
      >>> def get_int_little_endian(data):
      ...     return int(data[::-1].encode('hex'), 16)


#. Save Chinese characters to file

   .. code-block:: py

      #!/usr/bin/env python
      #coding: utf-8
      
      import codecs, json, sys
      
      def get_interested_events(src, linkId):
         results = []
         result_obj = {}
         root = json.load(src)
         events = root["result"]["events"]
         for event in events:
            if linkId in event["niLinkIds"]:
               results.append(event)
         results.sort(key=lambda event: event["niLinkIds"])
         result_obj["interested_events"] = results
         return result_obj
   
      with open("./event.json") as f:
         result = get_interested_events(f, sys.argv[1])
         format = codecs.open("./interested_event.json", "w", encoding='utf-8') # Basically open result file with utf-8 encoding
         json.dump(result, format, ensure_ascii=False, indent=1, separators=(",", ":"))
         format.close()
         f.close()

#. Python list unique
   
   .. code-block:: py

      mylist = [u'nowplaying', u'PBS', u'PBS', u'nowplaying', u'job', u'debate', u'thenandnow']
      myset = set(mylist)
      print myset

      # or

      >>> ll = [1,2,3,4,5,4,3,21,4]
      >>> ll = list(set(ll))
      >>> ll
      [1, 2, 3, 4, 5, 21]

#. Force stdout to be unbuffered
   
   .. code-block:: py

      import sys, os
      
      # Solution one
      sys.stdout = os.fdopen(sys.stdout, "w", 0)

      #fdopen(fd [, mode='r' [, bufsize]]) -> file_object
      #Return an open file object connected to a file descriptor.

      # Solution two
      class Unbuffered(object):
         def __init__(self, stream):
             self.stream = stream
         def write(self, data):
             self.stream.write(data)
             self.stream.flush()
         def writelines(self, datas):
             self.stream.writelines(datas)
             self.stream.flush()
         def __getattr__(self, attr):
             return getattr(self.stream, attr)

      sys.stdout = Unbuffered(sys.stdout)

#. difference between ``/`` and ``//.`` 
     
   In Python 3.0, 5 / 2 will return 2.5 and 5 // 2 will return 2. 
   The former is floating point division, and the latter is floor 
   division, sometimes also called integer division.

   In Python 2.2 or later in the 2.x line, there is no difference for integers 
   unless you perform a ``from __future__ import division,`` which causes 
   Python 2.x to adopt the behavior of 3.0

   Refer to 
   `PEP 238: Changing the Division Operator <https://docs.python.org/whatsnew/2.2.html#pep-238-changing-the-division-operator>`_
   for more information.

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