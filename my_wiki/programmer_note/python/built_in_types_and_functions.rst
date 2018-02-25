Built-in Types
==============


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


Built-in Functions
==================


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

+--------------------------+------------------------------------------------------+
| Function                 | Description                                          |
+==========================+======================================================+
| help()                   | Offers interactive help                              |
+--------------------------+------------------------------------------------------+
| str(object)              | Converts a value to string                           |
+--------------------------+------------------------------------------------------+
| int(object)              | Converts a string or number to an integer            |
+--------------------------+------------------------------------------------------+
| long(object)             | Converts a string or number to a long integer        |
+--------------------------+------------------------------------------------------+
| float(object)            | Converts a string or number to a float-point number  |
+--------------------------+------------------------------------------------------+
| repr(object)             | Returns a string representation                      |
+--------------------------+------------------------------------------------------+
| abs(number)              | Returns the absolute value of a number               |
+--------------------------+------------------------------------------------------+
| round(number[, ndigits]) | Rounds a number to a given precision                 |
+--------------------------+------------------------------------------------------+
| cmath.sqrt(number)       | Returns the square root; works with negative numbers |
+--------------------------+------------------------------------------------------+
| math.sqrt(number)        | ditto; but doesn’t work with negative numbers        |
+--------------------------+------------------------------------------------------+
