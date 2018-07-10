Built-in Functions Tricks
=========================

input vs. raw_input
-------------------

``input`` assumes that what you enter is a valid Python expression (it’s
more or less the inverse of ``repr``). If you write your name as a string, that’s no problem:

.. code-block:: python

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

Therefore, we use ``raw_input``, which treats all input as raw data and puts it into a string:

.. code-block:: python

   >>> name = raw_input("name:")
   name:nihao

Unless you have a special need for ``input``, you should probably use ``raw_input``.


floor vs ceil
=============

.. code-block:: python

   >>> help(math.floor)
   Help on built-in function floor in module math
   
   floor(...)
       floor(x)
   
       Return the floor of x as a float.
       This is the largest integral value <= x.
   
   >>> help(math.ceil)
   Help on built-in function ceil in module math:
   
   ceil(...)
       ceil(x)
   
       Return the ceiling of x as a float.
       This is the smallest integral value >= x.
   

Useful Function List
====================

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
| ``integer.bit_length()``     | Return the number of bits necessary to represent an integer in binary, |
|                              | excluding the sign and leading zeros                                   |
+------------------------------+------------------------------------------------------------------------+
| ``len(object)``              | Return the number of items of a sequence or collection.                |
+------------------------------+------------------------------------------------------------------------+
   
    
Binary to Decimal
=================

.. code-block:: python

  >>> int("1111", 2)
  15


Python ByteOrder
================


For multibyte data, It follows the architecture of the machine by default. If you need it to work cross-platform, then you'll want to force it.

ASCII and UTF-8 are encoded as a single byte per character, so is it affected by the byte ordering? No.

Here is how to pack little ``<`` or big ``>`` endian:

.. code-block:: python

  import struct
  
  struct.pack('<L', 1234)
  '\xd2\x04\x00\x00'
  
  struct.pack('>L', 1234)
  '\x00\x00\x04\xd2'

You can also encode strings as big or little endian this way if you are using UTF-16, as an example:

.. code-block:: python

  s.encode('utf-16LE')
  s.encode('utf-16BE')

UTF-8, ASCII do not have endianness since it is 1 byte per character.


sys Module Tricks
=================

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


json Module Tricks
==================

==============  =============
json type       python type  
==============  =============
json array      list         
json object     dict         
json string     str          
json integer    int, float   
json true       True         
json fase       False        
json null       None         
==============  =============

.. note:: 
  
   Locate module::

      >>> json.__file__
      '/usr/lib/python2.7/json/__init__.pyc'


string Module Tricks
====================

Public module variables::

   whitespace -- a string containing all characters considered whitespace
   lowercase -- a string containing all characters considered lowercase letters
   uppercase -- a string containing all characters considered uppercase letters
   letters -- a string containing all characters considered letters
   digits -- a string containing all characters considered decimal digits
   hexdigits -- a string containing all characters considered hexadecimal digits
   octdigits -- a string containing all characters considered octal digits
   punctuation -- a string containing all characters considered punctuation
   printable -- a string containing all characters considered printable

.. code-block:: python

   >>> import string
   >>> string.whitespace
   '\t\n\x0b\x0c\r '
   >>> string.punctuation
   '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
   >>> string.lowercase
   'abcdefghijklmnopqrstuvwxyz'
   >>> string.uppercase
   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
   >>> string.letters
   'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
   >>> string.digits
   '0123456789'
   >>> string.octdigits
   '01234567'
   >>> string.hexdigits
   '0123456789abcdefABCDEF'
   >>> string.printable
   '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c'


Executable Python Scripts
=========================

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


The Interactive Startup File
============================

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

Python3
=======

Install python3::

   $ brew install python3

Install packages for python3::

   $ pip3 install <package>

Uninstall python3::

   $ brew uninstall python3


Prohibit generating ``*.pyc`` file
==================================

add this code in your scripts::

   import sys
   sys.dont_write_bytecode = True

The variable must be set before any import.
you can add it to your :envvar:`PYTHONSTARTUP`.


Convert uncode string to Chinese characters
===========================================

.. code-block:: python

   >>> print '\u5f53\u524d\u9053\u8def\u56e0\u9053\u8def\u65bd\u5de5\u7981\u6b62\u901a\u884c'.decode('unicode-escape')
   当前道路因道路施工禁止通行


Source Code Encoding
====================

By default, Python source files are treated as encoded in ASCII. 
To declare an encoding other than the default one, a special comment 
line should be added as the first line of the file. The syntax is 
as follows ``#coding: encoding``　where *encoding* is one of the 
valid codecs supported by Python.

For example, to declare that Windows-1252 encoding is to be used, the 
first line of your source code file should be::

   #coding: cp1252

One exception to the first line rule is when the source code starts with 
a UNIX “shebang” line. In this case, the encoding declaration should be 
added as the second line of the file. For example::

   #!/usr/bin/env python
   #coding: cp1252
