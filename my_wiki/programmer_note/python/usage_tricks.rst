Built-in Types Tricks
=====================

Long Strings
------------
   
If you want to write a really long string, one that spans several lines, you can use **triple quotes**
instead of ordinary quotes:

.. code-block:: python

   print '''This is a very long string.
      It continues here.
      And it's not over yet.
      "Hello, world!"
      Still here.'''

   this is very long.
   It continues here.
   and it's not over yet.
   "Hello, world!"
   Still here.

You can also use triple double quotes, ``"""like this"""``. 

.. note::

   Note that because of the distinctive enclosing quotes, both single and double quotes are allowed inside, without being backslashescaped. 

Ordinary strings can also span several lines. If the last character on a line is a backslash, the line break itself is “escaped” and ignored. For example:

.. code-block:: python

   >>> print "Hello \
   ... world!"

   Hello world!


Raw Strings
-----------
   
raw strings are prefixed with an ``r``. It would seem that you can put anything
inside a raw string, and that is almost true. Quotes must be escaped as usual, although that
means that you get a backslash in your final string, too:

.. code-block:: python

   >>> print r'let\'s go!'
   let\'s go!

The one thing you can’t have in a raw string is an alone, final backslash. In other words, the
last character in a raw string cannot be a backslash unless you escape it (and then the backslash
you use to escape it will be part of the string, too).

.. code-block:: python

   >>> print r'This is illegal\'
     File "<stdin>", line 1
       print r'This is illegal\'
                               ^
   SyntaxError: EOL while scanning string literal

Okay, so it’s reasonable, but what if you want the last character in your raw string to be a
backslash? (Perhaps it’s the end of a DOS path, for example.) A simple way of doing that is the following:

.. code-block:: python

   >>> print r'C:\VS-Demo\hello-world\my_wiki' '\\'
   C:\VS-Demo\hello-world\my_wiki\

.. note::

   Raw strings can be especially useful when writing regular expressions.


Unicode Strings
---------------
   
Normal strings in Python are stored internally as 8-bit ASCII, while
Unicode strings are stored as 16-bit Unicode. This allows for a more varied set of characters, including special characters from most languages in the world. for example:

.. code-block:: python

   >>> u'Hello world!'
   u'Hello world!'

As you can see, Unicode strings use the prefix ``u``, just as raw strings use the prefix ``r``.

.. note::

   Unicode string or Unicode object—they don’t really belong to the same type as strings. 


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


time Module Tricks
==================

+-------------------------------+------------------------------------------------------------------------------------------+
| Function                      | Description                                                                              |
+===============================+==========================================================================================+
| ``sleep(seconds)``            | Delay execution for a given number of seconds.                                           |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``time()``                    | Return the current time in seconds since the Epoch.                                      |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``clock()``                   | Return the CPU time or real time since the start                                         |
|                               | of the process or since the first call to ``clock()``.                                   |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``gmtime([seconds])``         | Convert seconds since the Epoch to a time tuple expressing UTC(a.k.a. GMT).              |
|                               | When 'seconds' is not passed in, convert the current time instead.                       |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``localtime([seconds])``      | Ditto, but convert to a time tuple expressing local time.                                |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``mktime(tuple)``             | Convert a time tuple in local time to seconds since the Epoch.                           |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``ctime(seconds)``            | Convert a time in seconds since the Epoch to a string in local time.                     |
|                               | This is equivalent to ``asctime(localtime(seconds))``.                                   |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``asctime([tuple])``          | Convert a time tuple to a string. When the time tuple is not present,                    |
|                               | current time as returned by ``localtime()`` is used.                                     |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``strftime(format[, tuple])`` | Convert a time tuple to a string according to a format specification.                    |
|                               | When the time tuple is not present, current time as returned by ``localtime()`` is used. |
+-------------------------------+------------------------------------------------------------------------------------------+
| ``strptime(string, format)``  | Parse a string to a time tuple according to a format specification.                      |
+-------------------------------+------------------------------------------------------------------------------------------+


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


unittest Module Tricks
======================

#. run test cases only interested
   
  .. code-block:: python

    suite = unittest.TestSuite()
    suite.addTest(Test("test_dynamic_adjustment_no_better_route"))
    suite.addTest(Test("test_dynamic_adjustment_new_better_route"))
    result = unittest.TextTestRunner(verbosity=2).run(suite)

#. run all tests from a test suite
   
  .. code-block:: python

    suite = unittest.TestLoader().loadTestsFromTestCase(Test)
    result = unittest.TextTestRunner(verbosity=2).run(suite)


String format syntax
====================

print
-----

String and Unicode objects have one unique built-in operation: the ``%`` operator (modulo). (a.k.a string formatting or interpolation operator). Given ``format % values`` , ``%`` conversion specifications in ``format`` are replaced with zero or more elements of ``values``. The effect is similar to the using ``sprintf()`` in the C language. If format is a Unicode object, or if any of the objects being converted using the ``%s`` conversion are Unicode objects, the result will also be a Unicode object.

If format requires a single argument, values may be a single non-tuple object. Otherwise, values must be a tuple with exactly the number of items specified by the format string, or a single mapping object (for example, a dictionary).

A conversion specifier contains two or more characters and has the following components, which must occur in this order:

  #. The "%" character, which marks the start of the specifier.
  #. Mapping key (optional), consisting of a parenthesised sequence of characters (for example, (somename)).
  #. Conversion flags (optional), which affect the result of some conversion types.
  #. Minimum field width (optional). If specified as an "*" (asterisk), the actual width is read from the next element of the tuple in values, and the object to convert comes after the minimum field width and optional precision.
  #. Precision (optional), given as a "." (dot) followed by the precision. If specified as "*" (an asterisk), the actual width is read from the next element of the tuple in values, and the value to convert comes after the precision.
  #. Length modifier (optional).
  #. Conversion type.

When the right argument is a dictionary (or other mapping type), then the formats in the string must include a parenthesised mapping key into that dictionary inserted immediately after the "%" character. The mapping key selects the value to be formatted from the mapping. For example:

.. code-block:: python

  >>> print "%(name)s is a %(sex)s, %(age)2d years old." % \
  ... {"name":"cherry", "sex":"man", "age":25}
  cherry is a man, 25 years old.


The conversion flag characters are:

+------+----------------------------------------------------------------------------------------------------+
| Flag | Meaning                                                                                            |
+======+====================================================================================================+
| #    | The value conversion will use the "alternate form".                                                |
+------+----------------------------------------------------------------------------------------------------+
| 0    | The conversion will be zero padded for numeric values.                                             |
+------+----------------------------------------------------------------------------------------------------+
| \+   | A sign character ("+" or "-") will precede the conversion (overrides a "space" flag).              |
+------+----------------------------------------------------------------------------------------------------+
| \-   | The converted value is left adjusted (overrides the "0" conversion if both are given).             |
|      | a space should be left before a positive number (or empty string) produced by a signed conversion. |
+------+----------------------------------------------------------------------------------------------------+

A length modifier (h, l, or L) may be present, but is ignored as it is not necessary for Python.

The conversion types are:

+------------+----------------------------------------------------------------------------------+-------+
| Conversion | Meaning                                                                          | Notes |
+============+==================================================================================+=======+
| d          | Signed integer decimal                                                           |       |
+------------+----------------------------------------------------------------------------------+-------+
| i          | Signed integer decimal                                                           |       |
+------------+----------------------------------------------------------------------------------+-------+
| o          | Unsigned octal                                                                   | \(1)  |
+------------+----------------------------------------------------------------------------------+-------+
| u          | Unsigned decimal                                                                 |       |
+------------+----------------------------------------------------------------------------------+-------+
| x          | Unsigned hexadecimal (lowercase)                                                 | \(2)  |
+------------+----------------------------------------------------------------------------------+-------+
| X          | Unsigned hexadecimal (uppercase)                                                 | \(2)  |
+------------+----------------------------------------------------------------------------------+-------+
| e          | Floating point exponential format (lowercase)                                    |       |
+------------+----------------------------------------------------------------------------------+-------+
| E          | Floating point exponential format (uppercase)                                    |       |
+------------+----------------------------------------------------------------------------------+-------+
| f          | Floating point decimal format                                                    |       |
+------------+----------------------------------------------------------------------------------+-------+
| F          | Floating point decimal format                                                    |       |
+------------+----------------------------------------------------------------------------------+-------+
| g          | Same as "e" if exponent is greater than -4 or less than precision, "f" otherwise |       |
+------------+----------------------------------------------------------------------------------+-------+
| G          | Same as "E" if exponent is greater than -4 or less than precision, "F" otherwise |       |
+------------+----------------------------------------------------------------------------------+-------+
| c          | Single character (accepts integer or single character string)                    |       |
+------------+----------------------------------------------------------------------------------+-------+
| r          | String (converts any python object using ``repr()``)                             |       |
+------------+----------------------------------------------------------------------------------+-------+
| s          | String (converts any python object using ``str()``)                              | \(3)  |
+------------+----------------------------------------------------------------------------------+-------+
| %          | No argument is converted, results in a "%" character in the result               |       |
+------------+----------------------------------------------------------------------------------+-------+

Notes:

(1)
  The alternate form causes a leading zero ("0") to be inserted between left-hand padding and the formatting of the number 
  if the leading character of the result is not already a zero.

(2)
  The alternate form causes a leading ``'0x' or '0X'`` (depending on whether the ``"x" or "X"`` format was used) to be inserted 
  between left-hand padding and the formatting of the number if the leading character of the result is not already a zero.

(3)
  If the object or format provided is a unicode string, the resulting string will also be unicode.

(4) 
  If you want a ``"%"`` character in the result, use ``"%%"`` in the format.

Since Python strings have an explicit length, ``%s`` conversions do not assume that ``'\0'`` is the end of the string.

For safety reasons, floating point precisions are clipped to 50; 
``%f`` conversions for numbers whose absolute value is over 1e25 are replaced by ``%g`` conversions. 
All other errors raise exceptions.


Built-in string: str
--------------------

Grammer
^^^^^^^

Format strings contain “replacement fields” surrounded by curly braces ``{}``. 
Anything that is not contained in braces is considered literal text, which is copied unchanged to the output. 

Grammer for a replacement field as follow::

  replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"
  field_name        ::=  arg_name ("." attribute_name | "[" element_index "]")*
  arg_name          ::=  [identifier | integer]
  attribute_name    ::=  identifier
  element_index     ::=  integer | index_string
  index_string      ::=  <any source character except "]"> +
  conversion        ::=  "r" | "s"
  format_spec       ::=  <described in the next section>

standard format specifier::

  format_spec ::=  [[fill]align][sign][#][0][width][,][.precision][type]
  fill        ::=  <any character>
  align       ::=  "<" | ">" | "=" | "^"
  sign        ::=  "+" | "-" | " "
  width       ::=  integer
  precision   ::=  integer
  type        ::=  "b" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" | "n" | "o" | "s" | "x" | "X" | "%"

.. note::

  If you need to include a brace character in the literal text, it can be escaped by doubling: ``{{`` and ``}}``.


Examples
^^^^^^^^

Accessing arguments by position::
  
  >>> "{}, {}, {}".format('a', 'b', 'c')
  'a, b, c'
  >>> "{0}, {1}, {2}".format('a', 'b', 'c')
  'a, b, c'
  >>> "{2}, {1}, {0}".format('a', 'b', 'c')
  'c, b, a'
  >>> "{2}, {1}, {1}".format('a', 'b', 'c')
  'c, b, b' # arguments' indices can be repeated
  >>> "{2}, {1}, {1}".format(*"abc")
  'c, b, b' # unpacking argument sequence
  >>> "{2}, {1}, {1}".format(*("I", "love", "you"))
  'you, love, love'

Accessing arguments by name::

  >>> 'Coordinates: {latitude}, {longitude}'.format(latitude='37.24N', longitude='112.81E') 
  'Coordinates: 37.24N, 112.81E'
  >>> coord = {'latitude':'37.24N', 'longitude':'112.81E'}
  >>> 'Coordinates: {latitude}, {longitude}'.format(**coord)
  'Coordinates: 37.24N, 112.81E'

Accessing arguments' item::

  >>> coord=(3,5)
  >>> 'x:{0[0]}; y:{0[1]}'.format(coord)
  'x:3; y:5'

Accessing arguments' attribute::

  >>> c = 3-5j
  >>> ('Complex number: {0}, real part: {0.real}, imaginary part: {0.imag}').format(c)
  'Complex number: (3-5j), real part: 3.0, imaginary part: -5.0'
  >>> class Point:
  ...     def __init__(self, x, y):
  ...             self.x, self.y = x, y
  ...     def __str__(self):
  ...             return "Point({self.x}, {self.y})".format(self=self)
  ... 
  >>> str(Point(2,4))
  'Point(2, 4)'

Replacing ``%s`` with ``%r``::

  >>> "repr() shows quotes: {!r}; str() doesn't: {!s}".format('test1', 'test2')
  "repr() shows quotes: 'test1'; str() doesn't: test2"

Aligning the text with field width::

  >>> '{:<30}'.format('left aligned')
  'left aligned                  '
  >>> '{:>30}'.format('right aligned')
  '                 right aligned'
  >>> '{:^30}'.format('centered')
  '           centered           '
  >>> '{:*^30}'.format('centered') # using '*' as a fill char
  '***********centered***********'

Numberic format specificer::

  >>> '{:+f} {:+f}'.format(3.14, -3.14)
  '+3.140000 -3.140000'
  >>> '{:-f} {:-f}'.format(3.14, -3.14)
  '3.140000 -3.140000'
  >>> '{: f} {: f}'.format(3.14, -3.14)
  ' 3.140000 -3.140000'

  >>> 'int: {0:d}, hex: {0:x}, oct: {0:o}, bin: {0:b}'.format(42)
  'int: 42, hex: 2a, oct: 52, bin: 101010'
  >>> 'int: {0:d}, hex: {0:#x}, oct: {0:#o}, bin: {0:#b}'.format(42)
  'int: 42, hex: 0x2a, oct: 0o52, bin: 0b101010'

  >>> '{:,}'.format(1234567890)
  '1,234,567,890'

  >>> 'Correct answers: {:.2%}'.format(19.5/22)
  'Correct answers: 88.64%'

Nested ones::

  >>> for align, text in zip('<^>', ['left', 'center', 'right']):
  ...     '{0:{fill}{align}16}'.format(text, fill=align, align=align)
  ... 
  'left<<<<<<<<<<<<'
  '^^^^^center^^^^^'
  '>>>>>>>>>>>right'

  >>> for num in xrange(5, 12):
  ...     for base in 'dXob':
  ...             print '{0:{width}{base}}'.format(num, base=base, width=5),
  ...     print
  ... 
      5     5     5   101
      6     6     6   110
      7     7     7   111
      8     8    10  1000
      9     9    11  1001
     10     A    12  1010
     11     B    13  1011


Template strings
----------------

Templates provide simpler string substitutions as described in PEP 292. 
Instead of the normal %-based substitutions, Templates support $-based substitutions, 
using the following rules:

  #. ``$$`` is an escape; it is replaced with a single ``$``.
  #. ``$identifier`` names a substitution placeholder matching a mapping key of "identifier". By default, "identifier" must spell a Python identifier. The first non-identifier character after the ``$`` character terminates this placeholder specification.
  #. ``${identifier}`` is equivalent to ``$identifier``. It is required when valid identifier characters follow the placeholder but are not part of the placeholder, such as ``${noun}ification``.

Any other appearance of ``$`` in the string will result in a ``ValueError`` being raised.

The string module provides a Template class that implements these rules. The methods of Template are::

  >>> from string import Template
  >>> s = Template("$who likes $what")
  >>> s.substitute(who='Jim', what='programming')
  'Jim likes programming'
  >>> d = dict(who='Jim')
  >>> s.substitute(d)
  Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
    File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/string.py", line 176, in substitute
      return self.pattern.sub(convert, self.template)
    File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/string.py", line 166, in convert
      val = mapping[named]
  KeyError: 'what'
  >>> s.safe_substitute(d)
  'Jim likes $what'

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


Executable Python Scripts
=========================

On BSD’ish Unix systems, Python scripts can be made directly executable,
like shell scripts, by putting the line

.. code-block:: python

   #!/usr/bin/env python

(assuming that the interpreter is on the user’s :envvar:`PATH`) at the beginning of the script
and giving the file an executable mode. The ``#!`` must be the first two characters of the file.
On some platforms, this first line must end with a Unix-style line ending ('\n'),
not a Windows ('\r\n') line ending. Note that the hash, or pound, character,
``'#'``, is used to start a comment in Python.

The script can be given an executable mode, or permission,
using the :command:`chmod` command.

.. code-block:: python

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

This file is only read in interactive sessions, not when Python reads commands from a script,
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
