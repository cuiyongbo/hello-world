*************
Python String
*************

.. toctree::
   
   python_string_method_note
   python_string_format_syntax

.. contents::
   :local:

String type
===========

#. Long Strings
   
   If you want to write a really long string, one that spans several lines, 
   you can use **triple quotes** instead of ordinary quotes::
   
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
   
   **Note** that because of the distinctive enclosing quotes, 
   both single and double quotes are allowed inside, without 
   being backslash-escaped. 
   
   Ordinary strings can also span several lines. If the last character 
   on a line is a backslash, the line break itself is “escaped” and 
   ignored. For example::
   
      >>> print "Hello \
      ... world!"
   
      Hello world!
   
#. Raw Strings
   
   raw strings are prefixed with an ``r``. It would seem that you can put anything
   inside a raw string, and that is almost true. Quotes must be escaped as usual, 
   although that means that you get a backslash in your final string, too::
   
      >>> print r'let\'s go!'
      let\'s go!
   
   The one thing you can’t have in a raw string is an alone, final backslash. 
   In other words, the last character in a raw string can't be a backslash 
   unless you escape it::
   
      >>> print r'This is illegal\'
        File "<stdin>", line 1
          print r'This is illegal\'
                                  ^
      SyntaxError: EOL while scanning string literal
   
   Okay, so it’s reasonable, but what if you want the last character in your raw 
   string to be a backslash? (Perhaps it’s the end of a DOS path, for example.) 
   A simple way of doing that is the following::
   
      >>> print r'C:\VS-Demo\hello-world\my_wiki' '\\'
      C:\VS-Demo\hello-world\my_wiki\


#. Unicode Strings
   
Normal strings in Python are stored internally as 8-bit ASCII, while
Unicode strings are stored as 16-bit Unicode. This allows for a more 
varied set of characters, including special characters from most languages 
in the world. for example::

   >>> u'Hello world!'
   u'Hello world!'

As you can see, Unicode strings use the prefix ``u``, just as raw strings 
use the prefix ``r``.

**Note** that Unicode string or Unicode object—they don’t really belong 
to the same type as strings. 


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