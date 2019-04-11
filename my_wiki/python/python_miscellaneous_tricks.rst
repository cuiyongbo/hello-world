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

      # use numpy.unique

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