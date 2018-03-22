Built-in Functions
==================

Python interpreter has many functions built into it that are always available, They are listed in alphabatical order.

=====================  ===================  ====================  ====================  ======================
..                     ..                   Built-in Functions    ..                    ..                    
=====================  ===================  ====================  ====================  ======================
:func:`abs`            :func:`delattr`      :func:`hash`          |func-memoryview|_    |func-set|_           
:func:`all`            |func-dict|_         :func:`help`          :func:`min`           :func:`setattr`       
:func:`any`            :func:`dir`          :func:`hex`           :func:`next`          :func:`slice`         
:func:`ascii`          :func:`divmod`       :func:`id`            :func:`object`        :func:`sorted`        
:func:`bin`            :func:`enumerate`    :func:`input`         :func:`oct`           :func:`staticmethod`  
:func:`bool`           :func:`eval`         :func:`int`           :func:`open`          |func-str|_           
:func:`breakpoint`     :func:`exec`         :func:`isinstance`    :func:`ord`           :func:`sum`           
|func-bytearray|_      :func:`filter`       :func:`issubclass`    :func:`pow`           :func:`super`         
|func-bytes|_          :func:`float`        :func:`iter`          :func:`print`         |func-tuple|_         
:func:`callable`       :func:`format`       :func:`len`           :func:`property`      :func:`type`          
:func:`chr`            |func-frozenset|_    |func-list|_          |func-range|_         :func:`vars`          
:func:`classmethod`    :func:`getattr`      :func:`locals`        :func:`repr`          :func:`xrange`        
:func:`compile`        :func:`globals`      :func:`map`           :func:`reversed`      :func:`zip`           
:func:`complex`        :func:`hasattr`      :func:`max`           :func:`round`         :func:`__import__`    
=====================  ===================  ====================  ====================  ======================


.. using :func:`dict` would create a link to another page, so local targets are used, with replacement texts to make the output in the table consistent

.. |func-dict| replace:: ``dict()``
.. |func-frozenset| replace:: ``frozenset()``
.. |func-memoryview| replace:: ``memoryview()``
.. |func-set| replace:: ``set()``
.. |func-list| replace:: ``list()``
.. |func-str| replace:: ``str()``
.. |func-tuple| replace:: ``tuple()``
.. |func-range| replace:: ``range()``
.. |func-bytearray| replace:: ``bytearray()``
.. |func-bytes| replace:: ``bytes()``


Basically, they can be classified into distinct groups: container functions, iterator functions, 
numeric types and mathematical functions, string functions, string-int conversion functions,
class utilities, file utilities, miscellaneous utility function.


How to find help
----------------

.. function:: help([object])

   Invoke the built-in help system.  (This function is intended for interactive
   use.)  If no argument is given, the interactive help system starts on the
   interpreter console.  If the argument is a string, then the string is looked up
   as the name of a module, function, class, method, keyword, or documentation
   topic, and a help page is printed on the console.  If the argument is any other
   kind of object, a help page on the object is generated.

   This function is added to the built-in namespace by the :mod:`site` module.


.. function:: dir([object])

   Without arguments, return the list of names in the current local scope.  With an
   argument, attempt to return a list of valid attributes for that object.

   If the object has a method named :meth:`__dir__`, this method will be called and
   must return the list of attributes. This allows objects that implement a custom
   :func:`__getattr__` or :func:`__getattribute__` function to customize the way
   :func:`dir` reports their attributes.

   If the object does not provide :meth:`__dir__`, the function tries its best to
   gather information from the object's :attr:`~object.__dict__` attribute, if defined, and
   from its type object.  The resulting list is not necessarily complete, and may
   be inaccurate when the object has a custom :func:`__getattr__`.

   The default :func:`dir` mechanism behaves differently with different types of
   objects, as it attempts to produce the most relevant, rather than complete,
   information:

   * If the object is a module object, the list contains the names of the module's
     attributes.

   * If the object is a type or class object, the list contains the names of its
     attributes, and recursively of the attributes of its bases.

   * Otherwise, the list contains the object's attributes' names, the names of its
     class's attributes, and recursively of the attributes of its class's base
     classes.

   The resulting list is sorted alphabetically.  For example::

      >>> import struct
      >>> dir()   # show the names in the module namespace  # doctest: +SKIP
      ['__builtins__', '__name__', 'struct']
      >>> dir(struct)   # show the names in the struct module # doctest: +SKIP
      ['Struct', '__all__', '__builtins__', '__cached__', '__doc__', '__file__',
       '__initializing__', '__loader__', '__name__', '__package__',
       '_clearcache', 'calcsize', 'error', 'pack', 'pack_into',
       'unpack', 'unpack_from']
      >>> class Shape:
      ...     def __dir__(self):
      ...         return ['area', 'perimeter', 'location']
      >>> s = Shape()
      >>> dir(s)
      ['area', 'location', 'perimeter']
      >>> dir(Shape)
      ['__dir__', '__doc__', '__module__']

   .. note::

      Because :func:`dir` is supplied primarily as a convenience for use at an
      interactive prompt, it tries to supply an interesting set of names more
      than it tries to supply a rigorously or consistently defined set of names,
      and its detailed behavior may change across releases.  For example,
      metaclass attributes are not in the result list when the argument is a
      class.


Container functions
-------------------

.. _func-set:
.. class:: set([iterable])
   :noindex:

   Return a new :class:`set` object, optionally with elements taken from
   *iterable*.  ``set`` is a built-in class.  See :class:`set` and
   :ref:`types-set` for documentation about this class.

   For other containers see the built-in :class:`frozenset`, :class:`list`,
   :class:`tuple`, and :class:`dict` classes, as well as the :mod:`collections`
   module.


.. _func-frozenset:
.. class:: frozenset([iterable])
   :noindex:

   Return a new :class:`frozenset` object, optionally with elements taken from
   *iterable*.  ``frozenset`` is a built-in class.  See :class:`frozenset` and
   :ref:`types-set` for documentation about this class.

   For other containers see the built-in :class:`set`, :class:`list`,
   :class:`tuple`, and :class:`dict` classes, as well as the :mod:`collections` module.


.. _func-dict:
.. class:: dict(**kwarg)
.. class:: dict(mapping, **kwarg)
.. class:: dict(iterable, **kwarg)
   :noindex:

   Create a new dictionary.  The :class:`dict` object is the dictionary class.
   See :class:`dict` and :ref:`typesmapping` for documentation about this class.

   For other containers see the built-in :class:`list`, :class:`set`, and
   :class:`tuple` classes, as well as the :mod:`collections` module.


.. _func-list:
.. class:: list([iterable])
   :noindex:

   Rather than being a function, :class:`list` is actually a mutable
   sequence type, as documented in :ref:`typesseq-list` and :ref:`typesseq`.


.. _func-tuple:
.. function:: tuple([iterable])
   :noindex:

   Rather than being a function, :class:`tuple` is actually an immutable
   sequence type, as documented in :ref:`typesseq-tuple` and :ref:`typesseq`.


Iterator functions
------------------

.. function:: iter(object[, sentinel])

   Return an :term:`iterator` object.  The first argument is interpreted very
   differently depending on the presence of the second argument. Without a
   second argument, *object* must be a collection object which supports the
   iteration protocol (the :meth:`__iter__` method), or it must support the
   sequence protocol (the :meth:`__getitem__` method with integer arguments
   starting at ``0``).  If it does not support either of those protocols,
   :exc:`TypeError` is raised. 

   If the second argument, *sentinel*, is given,
   then *object* must be a callable object.  The iterator created in this case
   will call *object* with no arguments for each call to its
   :meth:`~iterator.__next__` method; if the value returned is equal to
   *sentinel*, :exc:`StopIteration` will be raised, otherwise the value will
   be returned.

   See also :ref:`typeiter`.

   One useful application of the second form of :func:`iter` is to read lines of
   a file until a certain line is reached.  The following example reads a file
   until the :meth:`~io.TextIOBase.readline` method returns an empty string::

      with open('mydata.txt') as fp:
         for line in iter(fp.readline, ''):
            process_line(line)


.. function:: next(iterator[, default])

   Retrieve the next item from the *iterator* by calling its
   :meth:`~iterator.__next__` method.  If *default* is given, it is returned
   if the iterator is exhausted, otherwise :exc:`StopIteration` is raised.

.. function:: reversed(seq)

   Return a reverse :term:`iterator`.  *seq* must be an object which has
   a :meth:`__reversed__` method or supports the sequence protocol (the
   :meth:`__len__` method and the :meth:`__getitem__` method with integer
   arguments starting at ``0``).


.. function:: sorted(iterable, *, key=None, reverse=False)

   Return a new sorted list from the items in *iterable*.

   Has two optional arguments which must be specified as keyword arguments.

   *key* specifies a function of one argument that is used to extract a comparison
   key from each list element: ``key=str.lower``.  The default value is ``None``
   (compare the elements directly).

   *reverse* is a boolean value.  If set to ``True``, then the list elements are
   sorted as if each comparison were reversed.

   Use :func:`functools.cmp_to_key` to convert an old-style *cmp* function to a
   *key* function.

   The built-in :func:`sorted` function is guaranteed to be stable. A sort is
   stable if it guarantees not to change the relative order of elements that
   compare equal --- this is helpful for sorting in multiple passes (for
   example, sort by department, then by salary grade).

   For sorting examples and a brief sorting tutorial, see :ref:`sortinghowto`.


.. class:: slice(stop)
.. class:: slice(start, stop[, step])

   .. index:: single: Numerical Python

   Return a :term:`slice` object representing the set of indices specified by
   ``range(start, stop, step)``.  The *start* and *step* arguments default to ``None``.

   .. note::

      stop is not inclusive.

      .. code-block:: python

         >>> l = range(1, 10)
         >>> len(l)
         9
         >>> l[1:9:2]
         [2, 4, 6, 8]
         >>> l[1:3:1]
         [2, 3]
         >>> l[8:6:-1]
         [9, 8]


.. function:: len(s)

   Return the length (the number of items) of an object.  The argument may be a
   sequence (such as a string, bytes, tuple, list, or range) or a collection
   (such as a dictionary, set, or frozen set).


.. _func-range:
.. function:: range(stop)
.. function:: range(start, stop[, step])
   :noindex:

   Rather than being a function, :class:`range` is actually an immutable
   sequence type, as documented in :ref:`typesseq-range` and :ref:`typesseq`.


.. class:: xrange(stop)
.. class:: xrange(start, stop[, step])

   This function is very similar to :func:`range`, but returns an :class:`xrange object` instead of a list. 
   This is an opaque sequence type which yields the same values as the corresponding list, 
   without actually storing them all simultaneously. The advantage of :func:`xrange` over :func:`range` is 
   minimal (since :func:`xrange` still has to create the values when asked for them) except 
   when a very large range is used on a memory-starved machine or when all of the range’s elements 
   are never used (such as when the loop is usually terminated with ``break``). 

   .. note:: 

      :func:`xrange` is intended to be simple and fast. Implementations may impose restrictions to achieve this. 
      The C implementation of Python restricts all arguments to native C longs (“short” Python integers), 
      and also requires that the number of elements fit in a native C long. 
      If a larger range is needed, an alternate version can be crafted using 
      the :mod:`itertools` module: ``islice(count(start, step), (stop-start+step-1+2*(step<0))//step)``.


.. function:: enumerate(iterable, start=0)

   Return an enumerate object. *iterable* must be a sequence, an
   :term:`iterator`, or some other object which supports iteration.
   The :meth:`~iterator.__next__` method of the iterator returned by
   :func:`enumerate` returns a tuple containing a count (from *start* which
   defaults to 0) and the values obtained from iterating over *iterable*.

      >>> seasons = ['Spring', 'Summer', 'Fall', 'Winter']
      >>> list(enumerate(seasons))
      [(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
      >>> list(enumerate(seasons, start=1))
      [(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]

   Equivalent to::

      def enumerate(sequence, start=0):
          n = start
          for elem in sequence:
              yield n, elem
              n += 1


.. function:: filter(function, iterable)

   Construct an iterator from those elements of *iterable* for which *function*
   returns true.  *iterable* may be either a sequence, a container which
   supports iteration, or an iterator.  If *function* is ``None``, the identity
   function is assumed, that is, all elements of *iterable* that are false are
   removed.

   Note that ``filter(function, iterable)`` is equivalent to the generator
   expression ``(item for item in iterable if function(item))`` if function is
   not ``None`` and ``(item for item in iterable if item)`` if function is
   ``None``. for example::

      >>> se = range(1,10)
      >>> filter((lambda x: x%2), se)
      [1, 3, 5, 7, 9]
      >>> filter(lambda x: x%2, se)
      [1, 3, 5, 7, 9]

   See :func:`itertools.filterfalse` for the complementary function that returns
   elements of *iterable* for which *function* returns false.


Numeric functions
-----------------

.. class:: class complex([real[, imag]])

   Return a complex number with the value real + imag*1j or convert a string or number to a complex number. 
   If the first parameter is a string, it will be interpreted as a complex number and the function must be called without a second parameter. 
   The second parameter can never be a string. Each argument may be any numeric type (including complex). 
   If imag is omitted, it defaults to zero and the function serves as a numeric conversion function like ``int()``, ``long()`` and ``float()``. 
   If both arguments are omitted, returns ``0j``.

   .. note::
   
      Note When converting from a string, the string must not contain whitespace around the central ``+`` or ``-`` operator. 
      For example, ``complex('1+2j')`` is fine, but ``complex('1 + 2j')`` raises ``ValueError``.


.. class:: class float([x])

   Return a floating point number constructed from a number or string x.

   If the argument is a string, it must contain a possibly signed decimal or floating point number, possibly embedded in whitespace. 
   The argument may also be [+|-]nan or [+|-]inf. Otherwise, the argument may be a plain or long integer or a floating point number, 
   and a floating point number with the same value (within Python’s floating point precision) is returned. 
   If no argument is given, returns ``0.0``.

   .. note:: 

      Note When passing in a string, values for NaN and Infinity may be returned, depending on the underlying C library. 
      Float accepts the strings nan, inf and -inf for NaN and positive or negative infinity. 
      The case and a leading + are ignored as well as a leading - is ignored for NaN. 
      Float always represents NaN and infinity as nan, inf or -inf.


.. class:: int(x=0)
.. class:: int(x, base=10)

   Return an integer object constructed from a number or string *x*, or return
   ``0`` if no arguments are given.  If *x* is a number, return
   :meth:`x.__int__() <object.__int__>`.  For floating point numbers, this
   truncates towards zero.

   If *x* is not a number or if *base* is given, then *x* must be a string,
   :class:`bytes`, or :class:`bytearray` instance representing an :ref:`integer
   literal <integers>` in radix *base*.  Optionally, the literal can be
   preceded by ``+`` or ``-`` (with no space in between) and surrounded by
   whitespace.  A base-n literal consists of the digits 0 to n-1, with ``a``
   to ``z`` (or ``A`` to ``Z``) having values 10 to 35. 

   The default *base* is 10. The allowed values are 0 and 2--36. 
   Base-2, -8, and -16 literals can be optionally prefixed with ``0b``/``0B``,
   ``0o``/``0O``, or ``0x``/``0X``, as with integer literals in code.  Base 0
   means to interpret exactly as a code literal, so that the actual base is 2,
   8, 10, or 16, and so that ``int('010', 0)`` is not legal, while
   ``int('010')`` is, as well as ``int('010', 8)``.


.. function:: class long(x=0)
.. function:: class long(x, base=10)

   Return a long integer object constructed from a string or number ``x``. 
   If the argument is a string, it must contain a possibly signed number of arbitrary size, possibly embedded in whitespace. 
   The ``base`` argument is interpreted in the same way as for ``int()``, and may only be given when x is a string.
   Otherwise, the argument may be a plain or long integer or a floating point number, and a long integer with the same value is returned. 
   Conversion of floating point numbers to integers truncates (towards zero). If no arguments are given, returns ``0L``.


Boolean functions
-----------------

.. class:: bool([x])

   Return a Boolean value, i.e. one of ``True`` or ``False``. 
   *x* is converted using the standard truth testing procedure. 
   If x is false or omitted, this returns ``False``; otherwise it returns ``True``. 
   bool is also a class, which is a subclass of int. Class bool cannot be subclassed further. 
   Its only instances are ``False`` and ``True``.


.. function:: all(iterable)

   Return ``True`` if all elements of the iterable are true (or if the iterable is empty). 
   Equivalent to::
   
      def all(iterable):
         for element in iterable:
            if not element:
               return False
         return True
   

.. function:: any(iterable)

   Return ``True`` if all elements of the iterable are true (or if the iterable is empty). 
   Equivalent to::
   
      def any(iterable):
         for element in iterable:
            if element:
               return True
         return False


Mathematical functions
----------------------

.. function:: abs(x)

   Return the absolute value of a number.  The argument may be an
   integer or a floating point number.  If the argument is a complex number, its
   magnitude is returned.


.. function:: divmod(a, b)

   Take two (non complex) numbers as arguments and return a pair of numbers
   consisting of their quotient and remainder when using integer division.  With
   mixed operand types, the rules for binary arithmetic operators apply.  For
   integers, the result is the same as ``(a // b, a % b)``. For floating point
   numbers the result is ``(q, a % b)``, where *q* is usually ``math.floor(a /
   b)`` but may be 1 less than that.  In any case ``q * b + a % b`` is very
   close to *a*, if ``a % b`` is non-zero it has the same sign as *b*, and ``0
   <= abs(a % b) < abs(b)``.


.. function:: max(iterable, *[, key, default])
.. function:: max(arg1, arg2, *args[, key])

   Return the largest item in an iterable or the largest of two or more arguments.

   If one positional argument is provided, it should be an :term:`iterable`.
   The largest item in the iterable is returned.  If two or more positional
   arguments are provided, the largest of the positional arguments is returned.

   There are two optional keyword-only arguments. The *key* argument specifies
   a one-argument ordering function like that used for :meth:`list.sort`. The
   *default* argument specifies an object to return if the provided iterable is empty.
   If the iterable is empty and *default* is not provided, a :exc:`ValueError` is raised.

   If multiple items are maximal, the function returns the first one encountered.
   This is consistent with other sort-stability preserving tools such as 
   ``sorted(iterable, key=keyfunc, reverse=True)[0]`` and
   ``heapq.nlargest(1, iterable, key=keyfunc)``.


.. function:: min(iterable, *[, key, default])
.. function:: min(arg1, arg2, *args[, key])

   Return the smallest item in an iterable or the smallest of two or more
   arguments.

   If one positional argument is provided, it should be an :term:`iterable`.
   The smallest item in the iterable is returned.  If two or more positional
   arguments are provided, the smallest of the positional arguments is returned.

   There are two optional keyword-only arguments. The *key* argument specifies
   a one-argument ordering function like that used for :meth:`list.sort`. The
   *default* argument specifies an object to return if the provided iterable is empty.
   If the iterable is empty and *default* is not provided, a :exc:`ValueError` is raised.

   If multiple items are minimal, the function returns the first one encountered.
   This is consistent with other sort-stability preserving tools such as 
   ``sorted(iterable, key=keyfunc)[0]`` and ``heapq.nsmallest(1, iterable, key=keyfunc)``.


.. function:: pow(x, y[, z])

   Return *x* to the power *y*; if *z* is present, return *x* to the power *y*,
   modulo *z* (computed more efficiently than ``pow(x, y) % z``). The two-argument
   form ``pow(x, y)`` is equivalent to using the power operator: ``x**y``.

   The arguments must have numeric types.  With mixed operand types, the
   coercion rules for binary arithmetic operators apply.  For :class:`int`
   operands, the result has the same type as the operands (after coercion)
   unless the second argument is negative; in that case, all arguments are
   converted to float and a float result is delivered.  For example, ``10**2``
   returns ``100``, but ``10**-2`` returns ``0.01``.  If the second argument is
   negative, the third argument must be omitted.  If *z* is present, *x* and *y*
   must be of integer types, and *y* must be non-negative.


.. function:: round(number[, ndigits])

   Return *number* rounded to *ndigits* precision after the decimal point.
   If *ndigits* is omitted or is ``None``, it returns the nearest integer to its input.

   For the built-in types supporting :func:`round`, values are rounded to the
   closest multiple of 10 to the power minus *ndigits*; if two multiples are
   equally close, rounding is done toward the even choice (so, for example,
   both ``round(0.5)`` and ``round(-0.5)`` are ``0``, and ``round(1.5)`` is
   ``2``).  Any integer value is valid for *ndigits* (positive, zero, or
   negative).  The return value is an integer if called with one argument,
   otherwise of the same type as *number*.

   For a general Python object ``number``, ``round(number, ndigits)`` delegates to
   ``number.__round__(ndigits)``.

   .. note::

      The behavior of :func:`round` for floats can be surprising: for example,
      ``round(2.675, 2)`` gives ``2.67`` instead of the expected ``2.68``.
      This is not a bug: it's a result of the fact that most decimal fractions
      can't be represented exactly as a float.  See :ref:`tut-fp-issues` for
      more information.


.. function:: sum(iterable[, start])

   Sums *start* and the items of an *iterable* from left to right and returns the total.
   *start* defaults to ``0``. The *iterable*'s items are normally numbers,
   and the start value is not allowed to be a string.

   For some use cases, there are good alternatives to :func:`sum`.
   The preferred, fast way to concatenate a sequence of strings is by calling
   ``''.join(sequence)``.  To add floating point values with extended precision,
   see :func:`math.fsum`\.  To concatenate a series of iterables, consider using
   :func:`itertools.chain`.


String functions
----------------

.. _func-str:
.. class:: class str(object='')

   Return a string containing a nicely printable representation of an object. 
   For strings, this returns the string itself. 
   The difference with ``repr(object)`` is that ``str(object)`` does not always 
   attempt to return a string that is acceptable to ``eval()``; 
   its goal is to return a printable string. If no argument is given, returns the empty string, ''.


.. _func-bytearray:
.. class:: bytearray([source[, encoding[, errors]]])
   :noindex:

   Return a new array of bytes.  The :class:`bytearray` class is a mutable
   sequence of integers in the range 0 <= x < 256.  It has most of the usual
   methods of mutable sequences, described in :ref:`typesseq-mutable`, as well
   as most methods that the :class:`bytes` type has, see :ref:`bytes-methods`.

   The optional *source* parameter can be used to initialize the array in a few
   different ways:

   * If it is a *string*, you must also give the *encoding* (and optionally,
     *errors*) parameters; :func:`bytearray` then converts the string to
     bytes using :meth:`str.encode`.

   * If it is an *integer*, the array will have that size and will be
     initialized with null bytes.

   * If it is an object conforming to the *buffer* interface, a read-only buffer
     of the object will be used to initialize the bytes array.

   * If it is an *iterable*, it must be an iterable of integers in the range
     ``0 <= x < 256``, which are used as the initial contents of the array.

   Without an argument, an array of size 0 is created.

   See also :ref:`binaryseq` and :ref:`typebytearray`.


.. _func-bytes:
.. class:: bytes([source[, encoding[, errors]]])
   :noindex:

   Return a new "bytes" object, which is an immutable sequence of integers in
   the range ``0 <= x < 256``.  :class:`bytes` is an immutable version of
   :class:`bytearray` -- it has the same non-mutating methods and the same
   indexing and slicing behavior.

   Accordingly, constructor arguments are interpreted as for :func:`bytearray`.

   Bytes objects can also be created with literals, see :ref:`strings`.

   See also :ref:`binaryseq`, :ref:`typebytes`, and :ref:`bytes-methods`.


str-int conversion functions
----------------------------

.. function:: bin(x)

   Convert an integer number to a binary string. The result is a valid Python expression. 
   If x is not a Python :class:`int` object, it has to define an :meth:`__index__` method 
   that returns an integer. some examples::

      >>> bin(14)
      '0b1110'
      >>> bin(-14)
      '-0b1110'

   If prefix "0b" is desired or not, you can use either of the following ways::

      >>> format(14, '#b'), format(14, 'b')
      ('0b1110', '1110')

  See also :func:`format` for more information.


.. function:: oct(x)

   Convert an integer number (of any size) to an octal string. The result is a valid Python expression.


.. function:: hex(x)

   Convert an integer number (of any size) to a lowercase hexadecimal string prefixed with “0x”


.. function:: ascii(object)

   As :func:`repr`, return a string containing a printable representation of an
   object, but escape the non-ASCII characters in the string returned by
   :func:`repr` using ``\x``, ``\u`` or ``\U`` escapes. 


.. function:: chr(i)

   Return a string of one character whose ASCII code is the integer ``i``. This is the inverse of :func:`ord`. 
   The argument must be in the range [0..255]; ``ValueError`` will be raised if i is outside that range. 
   See also :func:`unichr`.
   
   .. code-block:: python
   
      >>> chr(97)
      'a'


.. function:: unichr(i)

   Return the Unicode string of one character whose Unicode code is the integer ``i``.This is the inverse of :func:`ord` for Unicode strings. 
   The valid range for the argument depends how Python was configured – it may be either UCS2 [0..0xFFFF] or UCS4 [0..0x10FFFF]. 
   ``ValueError`` is raised otherwise. For ASCII and 8-bit strings see :func:`chr`.
   
   .. code-block:: python
   
      >>> unichr(97)
      u'a'


.. function:: ord(c)

   Given a string of length one, return an integer representing the Unicode code point of the character when the argument is a unicode object, 
   or the value of the byte when the argument is an 8-bit string. This is the inverse of :func:`chr` for 8-bit strings and of :func:`unichr` for unicode objects. 
   If a unicode argument is given and Python was built with UCS2 Unicode, then the character’s code point must be in the range [0..65535]; 
   otherwise the string length is two, and a ``TypeError`` will be raised.
   
   .. code-block:: python
   
      >>> ord('a')
      97
      >>> ord(u'\u2020')
      8224
      >>> int('0x2020', 16)
      8224


File Utilities
--------------

.. class:: file(name[, mode[, buffering]])

   Constructor function for the file type, described further in section File Objects. 
   The constructor’s arguments are the same as those of the :func:`open` built-in function described below.

   When opening a file, it’s preferable to use :func:`open` instead of invoking this constructor directly. 
   file is more suited to type testing (for example, writing ``isinstance(f, file)``).

   .. versionadded::
      2.2


.. function:: open(name[, mode[, buffering]])

   Open a file, returning an object of the file type described in section File Objects.
   If the file cannot be opened, :exc:`IOError` is raised. When opening a file,
   it’s preferable to use :func:`open` instead of invoking the file constructor directly.

   The first two arguments are the same as for stdio’s ``fopen()``:
   *name* is the file name to be opened, and *mode* is a string indicating how the file is to be opened.


      ===========  =================================================================
      Character    Meaning                                                          
      ===========  =================================================================
      ``'r'``      open for reading (default)                                       
      ``'w'``      open for writing, truncating the file first                      
      ``'x'``      open for exclusive creation, failing if the file already exists  
      ``'a'``      open for writing, appending to the end of the file if it exists  
      ``'b'``      binary mode                                                      
      ``'t'``      text mode (default)                                              
      ``'+'``      open a disk file for updating (reading and writing)              
      ===========  =================================================================

   The optional *buffering* argument specifies the file’s desired buffer size:

      =======  ======================
      Value    Meaning               
      =======  ======================
      <0       system default        
      0        unbuffered            
      1        line buffered         
      >1       buffer size in bytes  
      =======  ======================

   If omitted, the system default is used, which is usually line buffered for tty devices 
   and fully buffered for other files. 


Class utilities
---------------

.. class:: object()

   Return a new featureless object.  :class:`object` is a base for all classes.
   It has the methods that are common to all instances of Python classes.
   This function does not accept any arguments.

   .. code-block:: python

      >>> help(object)
      Help on class object in module __builtin__:
      
      class object
       |  The most base type

   .. note::

      :class:`object` does *not* have a :attr:`~object.__dict__`, so you can't
      assign arbitrary attributes to an instance of the :class:`object` class.


.. function:: super([type[, object-or-type]])

   Return a proxy object that delegates method calls to a parent or sibling
   class of *type*.  This is useful for accessing inherited methods that have
   been overridden in a class. The search order is same as that used by
   :func:`getattr` except that the *type* itself is skipped.

   The :attr:`~class.__mro__` attribute of the *type* lists the method
   resolution search order used by both :func:`getattr` and :func:`super`.  The
   attribute is dynamic and can change whenever the inheritance hierarchy is
   updated.

   If the second argument is omitted, the super object returned is unbound.  If
   the second argument is an object, ``isinstance(obj, type)`` must be true.  If
   the second argument is a type, ``issubclass(type2, type)`` must be true (this
   is useful for classmethods).

   There are two typical use cases for *super*.  In a class hierarchy with
   single inheritance, *super* can be used to refer to parent classes without
   naming them explicitly, thus making the code more maintainable.  This use
   closely parallels the use of *super* in other programming languages.

   The second use case is to support cooperative multiple inheritance in a
   dynamic execution environment.  This use case is unique to Python and is
   not found in statically compiled languages or languages that only support
   single inheritance.  This makes it possible to implement "diamond diagrams"
   where multiple base classes implement the same method.  Good design dictates
   that this method have the same calling signature in every case (because the
   order of calls is determined at runtime, because that order adapts
   to changes in the class hierarchy, and because that order can include
   sibling classes that are unknown prior to runtime).

   For both use cases, a typical superclass call looks like this::

      class C(B):
          def method(self, arg):
              super().method(arg)    # This does the same thing as:
                                     # super(C, self).method(arg)

   Note that :func:`super` is implemented as part of the binding process for
   explicit dotted attribute lookups such as ``super().__getitem__(name)``.
   It does so by implementing its own :meth:`__getattribute__` method for searching
   classes in a predictable order that supports cooperative multiple inheritance.
   Accordingly, :func:`super` is undefined for implicit lookups using statements or
   operators such as ``super()[name]``.

   Also note that, aside from the zero argument form, :func:`super` is not
   limited to use inside methods.  The two argument form specifies the
   arguments exactly and makes the appropriate references.  The zero
   argument form only works inside a class definition, as the compiler fills
   in the necessary details to correctly retrieve the class being defined,
   as well as accessing the current instance for ordinary methods.

   For practical suggestions on how to design cooperative classes using
   :func:`super`, see `guide to using super()
   <https://rhettinger.wordpress.com/2011/05/26/super-considered-super/>`_.


.. class:: type(object)
.. class:: type(name, bases, dict)

   .. index:: object: type

   With one argument, return the type of an *object*.  The return value is a
   type object and generally the same object as returned by
   :attr:`object.__class__ <instance.__class__>`.

   The :func:`isinstance` built-in function is recommended for testing the type
   of an object, because it takes subclasses into account.

   With three arguments, return a new type object.  This is essentially a
   dynamic form of the :keyword:`class` statement. The *name* string is the
   class name and becomes the :attr:`~definition.__name__` attribute; the *bases*
   tuple itemizes the base classes and becomes the :attr:`~class.__bases__`
   attribute; and the *dict* dictionary is the namespace containing definitions
   for class body and is copied to a standard dictionary to become the
   :attr:`~object.__dict__` attribute.  For example, the following two
   statements create identical :class:`type` objects::

      >>> class X:
      ...     a = 1
      ...
      >>> X = type('X', (object,), dict(a=1))


.. function:: isinstance(object, classinfo)

   Return true if the *object* argument is an instance of the *classinfo* argument, or of a (direct, indirect or virtual) subclass thereof. 
   Also return true if *classinfo* is a type object (new-style class) and *object* is an object of that type or of a (direct, indirect or virtual) subclass thereof. 
   If *object* is not a class instance or an object of the given type, the function always returns false. 
   If *classinfo* is a tuple of class or type objects (or recursively, other such tuples), return true if object is an instance of any of the classes or types. 
   If *classinfo* is not a class, type, or tuple of classes, types, and such tuples, a ``TypeError`` exception is raised.


.. function:: issubclass(class, classinfo)

   Return true if ``class`` is a subclass (direct, indirect or virtual) of ``classinfo``. 
   A class is considered a subclass of itself. ``classinfo`` may be a tuple of class objects, 
   in which case every entry in ``classinfo`` will be checked. In any other case, a ``TypeError`` exception is raised.


.. function:: hasattr(object, name)

   The arguments are an object and a string.  The result is ``True`` if the
   string is the name of one of the object's attributes, ``False`` if not. (This
   is implemented by calling ``getattr(object, name)`` and seeing whether it
   raises an :exc:`AttributeError` or not.)


.. function:: getattr(object, name[, default])

   Return the value of the named attribute of *object*.  *name* must be a string.
   If the string is the name of one of the object's attributes, the result is the
   value of that attribute.  For example, ``getattr(x, 'foobar')`` is equivalent to
   ``x.foobar``.  If the named attribute does not exist, *default* is returned if
   provided, otherwise :exc:`AttributeError` is raised.


.. function:: setattr(object, name, value)
  
   This is the counterpart of :func:`getattr`.  The arguments are an object, a
   string and an arbitrary value.  The string may name an existing attribute or a
   new attribute.  The function assigns the value to the attribute, provided the
   object allows it.  For example, ``setattr(x, 'foobar', 123)`` is equivalent to
   ``x.foobar = 123``.


.. function:: delattr(object, name)

   This is a relative of ``setattr()``. The arguments are an object and a string. 
   The string must be the name of one of the object’s attributes. The function deletes the named attribute, provided the object allows it. 
   For example, delattr(x, 'foobar') is equivalent to del x.foobar.


.. function:: callable(object)

   Return :const:`True` if the *object* argument appears callable,
   :const:`False` if not.  If this returns true, it is still possible that a
   call fails, but if it is false, calling *object* will never succeed.
   Note that classes are callable (calling a class returns a new instance);
   instances are callable if their class has a :meth:`__call__` method.


.. decorator:: classmethod

   Transform a method into a class method.

   A class method receives the class as implicit first argument, just like an
   instance method receives the instance. To declare a class method, use this
   idiom::

      class C:
          @classmethod
          def f(cls, arg1, arg2, ...): ...

   The ``@classmethod`` form is a function :term:`decorator` -- see the description
   of function definitions in :ref:`function` for details.

   It can be called either on the class (such as ``C.f()``) or on an instance (such
   as ``C().f()``).  The instance is ignored except for its class. If a class
   method is called for a derived class, the derived class object is passed as the
   implied first argument.

   Class methods are different than C++ or Java static methods. If you want those,
   see :func:`staticmethod` in this section.

   For more information on class methods, consult the documentation on the standard
   type hierarchy in :ref:`types`.


.. decorator:: staticmethod

   Transform a method into a static method.

   A static method does not receive an implicit first argument. To declare a static
   method, use this idiom::

      class C:
          @staticmethod
          def f(arg1, arg2, ...): ...

   The ``@staticmethod`` form is a function :term:`decorator` -- see the
   description of function definitions in :ref:`function` for details.

   It can be called either on the class (such as ``C.f()``) or on an instance (such
   as ``C().f()``).  The instance is ignored except for its class.

   Static methods in Python are similar to those found in Java or C++. Also see
   :func:`classmethod` for a variant that is useful for creating alternate class
   constructors.

   Like all decorators, it is also possible to call ``staticmethod`` as
   a regular function and do something with its result.  This is needed
   in some cases where you need a reference to a function from a class
   body and you want to avoid the automatic transformation to instance
   method.  For these cases, use this idiom::

      class C:
          builtin_open = staticmethod(open)

   For more information on static methods, consult the documentation on the
   standard type hierarchy in :ref:`types`.


Miscellaneous utilities
-----------------------

.. function:: input([prompt])

   Equivalent to ``eval(raw_input(prompt))``.

   This function does not catch user errors. If the input is not syntactically valid, a :exc:`SyntaxError` will be raised. 
   Other exceptions may be raised if there is an error during evaluation.

   If the :mod:`readline` module was loaded, then :func:`input` will use it to provide elaborate line editing and history features.

   Consider using the :func:`raw_input` function for general input from users.


.. function:: raw_input([prompt])

   If the prompt argument is present, it is written to standard output without a trailing newline.
   The function then reads a line from input, converts it to a string (stripping a trailing newline),
   and returns that. When ``EOF`` is read, :exc:`EOFError` is raised. Example::

      >>> input("-->")
      -->nihao
      Traceback (most recent call last):
        File "<stdin>", line 1, in <module>
        File "<string>", line 1, in <module>
      NameError: name 'nihao' is not defined
      >>> s = input("-->")
      -->"ni hao"
      >>> s
      'ni hao'
      >>> s = raw_input("-->")
      -->Hello world
      >>> s
      'Hello world'


.. function:: id(object)

   Return the "identity" of an object.  This is an integer which
   is guaranteed to be unique and constant for this object during its lifetime.
   Two objects with non-overlapping lifetimes may have the same :func:`id`
   value.

   .. note::

      This is the address of the object in memory.


.. function:: hash(object)

   Return the hash value of the object (if it has one).  Hash values are
   integers.  They are used to quickly compare dictionary keys during a
   dictionary lookup.  Numeric values that compare equal have the same hash
   value (even if they are of different types, as is the case for 1 and 1.0).

  .. note::

    For objects with custom :meth:`__hash__` methods, note that :func:`hash`
    truncates the return value based on the bit width of the host machine.
    See :meth:`__hash__` for details.


.. function:: locals()

   Update and return a dictionary representing the current local symbol table.
   Free variables are returned by :func:`locals` when it is called in function
   blocks, but not in class blocks.

   .. note::
      The contents of this dictionary should not be modified; changes may not
      affect the values of local and free variables used by the interpreter.


.. function:: globals()

   Return a dictionary representing the current global symbol table. This is always
   the dictionary of the current module (inside a function or method, this is the
   module where it is defined, not the module from which it is called).


.. function:: vars([object])

   Return the :attr:`~object.__dict__` attribute for a module, class, instance,
   or any other object with a :attr:`~object.__dict__` attribute.

   Objects such as modules and instances have an updateable :attr:`~object.__dict__`
   attribute; however, other objects may have write restrictions on their
   :attr:`~object.__dict__` attributes (for example, classes use a
   :class:`types.MappingProxyType` to prevent direct dictionary updates).

   Without an argument, :func:`vars` acts like :func:`locals`.  Note, the
   locals dictionary is only useful for reads since updates to the locals
   dictionary are ignored.

   .. code-block:: python

      >>> os.__dict__ == vars(os)
      True
      >>> vars() == locals()
      True


.. function:: map(function, iterable, ...)

   Return an iterator that applies *function* to every item of *iterable*,
   yielding the results.  If additional *iterable* arguments are passed,
   *function* must take that many arguments and is applied to the items from all
   iterables in parallel.  With multiple iterables, the iterator stops when the
   shortest iterable is exhausted.  For cases where the function inputs are
   already arranged into argument tuples, see :func:`itertools.starmap`.

.. function:: reduce(function, iterable[, initializer])

   Apply function of two arguments cumulatively to the items of iterable, from left to right, so as to reduce the iterable to a single value.
   For example, ``reduce(lambda x, y: x+y, [1, 2, 3, 4, 5])`` calculates ``((((1+2)+3)+4)+5)``.
   The left argument *x*, is the accumulated value and the right argument *y*, is the update value from the iterable.
   If the optional *initializer* is present, it is placed before the items of the iterable in the calculation,
   and serves as a default when the iterable is empty. If *initializer* is not given and iterable contains only one item,
   the first item is returned. Roughly equivalent to::

      def reduce(function, iterable, initializer=None):
         it = iter(iterable)
         if initializer is None:
            initializer = next(it)
         except StopIteration:
            raise TypeError('reduce() of empty sequence with no initial value')
         result = initializer
         for x in it:
            result = function(result, x)
         return result

   for example::

      >>> reduce(lambda:0, [])
      Traceback (most recent call last):
        File "<stdin>", line 1, in <module>
      TypeError: reduce() of empty sequence with no initial value
      >>> nums
      [1, 2, 3, 4, 5, 6, 7, 8, 9]
      >>> reduce(lambda x,y:x+y, nums)
      45
      >>> reduce(lambda x,y:x+y, nums, 10)
      55
      >>> sum(nums, 10)
      55


.. function:: zip([iterable, ...])

   This function returns a list of tuples, where the i-th tuple contains the i-th element from each of the argument sequences or iterables. 
   The returned list is truncated in length to the length of the shortest argument sequence. 
   When there are multiple arguments which are all of the same length, ``zip()`` is similar to ``map()`` with an initial argument of ``None``. 
   With a single sequence argument, it returns a list of 1-tuples. With no arguments, it returns an empty list.
   
   The left-to-right evaluation order of the iterables is guaranteed. This makes possible an idiom for clustering a data series into n-length groups using ``zip(*[iter(s)]*n)``.
   
   ``zip()`` in conjunction with the ``*`` operator can be used to unzip a list::

      >>> x = [1,2,3]
      >>> y = [4,5,6]
      >>> zipped = zip(x, y)
      >>> x1, y1 = zip(*zipped)
      >>> x == list(x1) and y == list(y1)
      True 


.. function:: repr(object)

   Return a string containing a printable representation of an object.  For many
   types, this function makes an attempt to return a string that would yield an
   object with the same value when passed to :func:`eval`, otherwise the
   representation is a string enclosed in angle brackets that contains the name
   of the type of the object together with additional information often
   including the name and address of the object.  A class can control what this
   function returns for its instances by defining a :meth:`__repr__` method.


.. index::
   single: __format__
   single: string; format() (built-in function)

.. function:: format(value[, format_spec])

   Convert a *value* to a "formatted" representation, as controlled by
   *format_spec*.  The interpretation of *format_spec* will depend on the type
   of the *value* argument, however there is a standard formatting syntax that
   is used by most built-in types: :ref:`formatspec`.

   The default *format_spec* is an empty string which usually gives the same
   effect as calling :func:`str(value) <str>`.

   A call to ``format(value, format_spec)`` is translated to
   ``type(value).__format__(value, format_spec)`` which bypasses the instance
   dictionary when searching for the value's :meth:`__format__` method.  A
   :exc:`TypeError` exception is raised if the method search reaches
   :mod:`object` and the *format_spec* is non-empty, or if either the
   *format_spec* or the return value are not strings.


.. function:: print(*objects, sep=' ', end='\\n', file=sys.stdout, flush=False)

   Print *objects* to the text stream *file*, separated by *sep* and followed
   by *end*.  *sep*, *end*, *file* and *flush*, if present, must be given as keyword
   arguments.

   All non-keyword arguments are converted to strings like :func:`str` does and
   written to the stream, separated by *sep* and followed by *end*.  Both *sep*
   and *end* must be strings; they can also be ``None``, which means to use the
   default values.  If no *objects* are given, :func:`print` will just write
   *end*.

   The *file* argument must be an object with a ``write(string)`` method; if it
   is not present or ``None``, :data:`sys.stdout` will be used.  Since printed
   arguments are converted to text strings, :func:`print` cannot be used with
   binary mode file objects.  For these, use ``file.write(...)`` instead.

   Whether output is buffered is usually determined by *file*, but if the
   *flush* keyword argument is true, the stream is forcibly flushed.


.. function:: eval(expression, globals=None, locals=None)

   The arguments are a string and optional globals and locals.  If provided,
   *globals* must be a dictionary.  If provided, *locals* can be any mapping
   object.

   The *expression* argument is parsed and evaluated as a Python expression
   (technically speaking, a condition list) using the *globals* and *locals*
   dictionaries as global and local namespace.  If the *globals* dictionary is
   present and lacks ``__builtins__``, the current globals are copied into *globals*
   before *expression* is parsed.  This means that *expression* normally has full
   access to the standard :mod:`builtins` module and restricted environments are
   propagated.  If the *locals* dictionary is omitted it defaults to the *globals*
   dictionary.  If both dictionaries are omitted, the expression is executed in the
   environment where :func:`eval` is called.  The return value is the result of
   the evaluated expression. Syntax errors are reported as exceptions.  Example:

      >>> x = 1
      >>> eval('x+1')
      2

   This function can also be used to execute arbitrary code objects (such as
   those created by :func:`compile`).  In this case pass a code object instead
   of a string.  If the code object has been compiled with ``'exec'`` as the
   *mode* argument, :func:`eval`\'s return value will be ``None``.

   .. note::

      Hints: dynamic execution of statements is supported by the :func:`exec`
      function.  The :func:`globals` and :func:`locals` functions
      returns the current global and local dictionary, respectively, which may be
      useful to pass around for use by :func:`eval` or :func:`exec`.


.. function:: breakpoint(*args, **kws)

   This function drops you into the debugger at the call site.  Specifically,
   it calls :func:`sys.breakpointhook`, passing ``args`` and ``kws`` straight
   through.  By default, ``sys.breakpointhook()`` calls
   :func:`pdb.set_trace()` expecting no arguments.  In this case, it is
   purely a convenience function so you don't have to explicitly import
   :mod:`pdb` or type as much code to enter the debugger.  However,
   :func:`sys.breakpointhook` can be set to some other function and
   :func:`breakpoint` will automatically call that, allowing you to drop into
   the debugger of choice.


.. function:: compile(source, filename, mode, flags=0, dont_inherit=False, optimize=-1)

   Compile the *source* into a code or AST object.  Code objects can be executed
   by :func:`exec` or :func:`eval`.  *source* can either be a normal string, a
   byte string, or an AST object.  Refer to the :mod:`ast` module documentation
   for information on how to work with AST objects.

   The *filename* argument should give the file from which the code was read;
   pass some recognizable value if it wasn't read from a file (``'<string>'`` is
   commonly used).

   The *mode* argument specifies what kind of code must be compiled; it can be
   ``'exec'`` if *source* consists of a sequence of statements, ``'eval'`` if it
   consists of a single expression, or ``'single'`` if it consists of a single
   interactive statement (in the latter case, expression statements that
   evaluate to something other than ``None`` will be printed).

   The optional arguments *flags* and *dont_inherit* control which future
   statements (see :pep:`236`) affect the compilation of *source*.  If neither
   is present (or both are zero) the code is compiled with those future
   statements that are in effect in the code that is calling :func:`compile`.  If the
   *flags* argument is given and *dont_inherit* is not (or is zero) then the
   future statements specified by the *flags* argument are used in addition to
   those that would be used anyway. If *dont_inherit* is a non-zero integer then
   the *flags* argument is it -- the future statements in effect around the call
   to compile are ignored.

   Future statements are specified by bits which can be bitwise ORed together to
   specify multiple statements.  The bitfield required to specify a given feature
   can be found as the :attr:`~__future__._Feature.compiler_flag` attribute on
   the :class:`~__future__._Feature` instance in the :mod:`__future__` module.

   The argument *optimize* specifies the optimization level of the compiler; the
   default value of ``-1`` selects the optimization level of the interpreter as
   given by :option:`-O` options.  Explicit levels are ``0`` (no optimization;
   ``__debug__`` is true), ``1`` (asserts are removed, ``__debug__`` is false)
   or ``2`` (docstrings are removed too).

   This function raises :exc:`SyntaxError` if the compiled source is invalid,
   and :exc:`ValueError` if the source contains null bytes.

   If you want to parse Python code into its AST representation, see
   :func:`ast.parse`.

   .. note::

      When compiling a string with multi-line code in ``'single'`` or
      ``'eval'`` mode, input must be terminated by at least one newline
      character.  This is to facilitate detection of incomplete and complete
      statements in the :mod:`code` module.

   .. versionchanged:: 3.2
      Allowed use of Windows and Mac newlines.  Also input in ``'exec'`` mode
      does not have to end in a newline anymore.  Added the *optimize* parameter.

   .. versionchanged:: 3.5
      Previously, :exc:`TypeError` was raised when null bytes were encountered
      in *source*.


.. _func-memoryview:
.. function:: memoryview(obj)
   :noindex:

   Return a "memory view" object created from the given argument.  See
   :ref:`typememoryview` for more information.


.. class:: property(fget=None, fset=None, fdel=None, doc=None)

   Return a property attribute.

   *fget* is a function for getting an attribute value.  *fset* is a function
   for setting an attribute value. *fdel* is a function for deleting an attribute
   value.  And *doc* creates a docstring for the attribute.

   A typical use is to define a managed attribute ``x``::

      class C:
          def __init__(self):
              self._x = None

          def getx(self):
              return self._x

          def setx(self, value):
              self._x = value

          def delx(self):
              del self._x

          x = property(C.getx, C.setx, C.delx, "I'm x")

   If *c* is an instance of *C*, ``c.x`` will invoke the getter,
   ``c.x = value`` will invoke the setter and ``del c.x`` the deleter.

   If given, *doc* will be the docstring of the property attribute. Otherwise, the
   property will copy *fget*'s docstring (if it exists).  This makes it possible to
   create read-only properties easily using :func:`property` as a :term:`decorator`::

      class Parrot:
          def __init__(self):
              self._voltage = 100000

          @property
          def voltage(self):
              """Get the current voltage."""
              return self._voltage

   The ``@property`` decorator turns the :meth:`voltage` method into a "getter"
   for a read-only attribute with the same name, and it sets the docstring for
   *voltage* to "Get the current voltage."

   A property object has :attr:`~property.getter`, :attr:`~property.setter`,
   and :attr:`~property.deleter` methods usable as decorators that create a
   copy of the property with the corresponding accessor function set to the
   decorated function.  This is best explained with an example::

      class C:
          def __init__(self):
              self._x = None

          @property
          def x(self):
              """I'm the 'x' property."""
              return self._x

          @x.setter
          def x(self, value):
              self._x = value

          @x.deleter
          def x(self):
              del self._x

   This code is exactly equivalent to the first example.  Be sure to give the
   additional functions the same name as the original property (``x`` in this
   case.)

   The returned property object also has the attributes ``fget``, ``fset``, and
   ``fdel`` corresponding to the constructor arguments.

   .. versionchanged:: 3.5
      The docstrings of property objects are now writeable.


.. function:: __import__(name, globals=None, locals=None, fromlist=(), level=0)

   .. index::
      statement: import
      module: imp

   .. note::

      This is an advanced function that is not needed in everyday Python
      programming, unlike :func:`importlib.import_module`.

   This function is invoked by the :keyword:`import` statement.  It can be
   replaced (by importing the :mod:`builtins` module and assigning to
   ``builtins.__import__``) in order to change semantics of the
   :keyword:`import` statement, but doing so is **strongly** discouraged as it
   is usually simpler to use import hooks (see :pep:`302`) to attain the same
   goals and does not cause issues with code which assumes the default import
   implementation is in use.  Direct use of :func:`__import__` is also
   discouraged in favor of :func:`importlib.import_module`.

   The function imports the module *name*, potentially using the given *globals*
   and *locals* to determine how to interpret the name in a package context.
   The *fromlist* gives the names of objects or submodules that should be
   imported from the module given by *name*.  The standard implementation does
   not use its *locals* argument at all, and uses its *globals* only to
   determine the package context of the :keyword:`import` statement.

   *level* specifies whether to use absolute or relative imports. ``0`` (the
   default) means only perform absolute imports.  Positive values for
   *level* indicate the number of parent directories to search relative to the
   directory of the module calling :func:`__import__` (see :pep:`328` for the
   details).

   When the *name* variable is of the form ``package.module``, normally, the
   top-level package (the name up till the first dot) is returned, *not* the
   module named by *name*. However, when a non-empty *fromlist* argument is
   given, the module named by *name* is returned.

   For example, the statement ``import spam`` results in bytecode resembling the
   following code::

      spam = __import__('spam', globals(), locals(), [], 0)

   The statement ``import spam.ham`` results in this call::

      spam = __import__('spam.ham', globals(), locals(), [], 0)

   Note how :func:`__import__` returns the toplevel module here because this is
   the object that is bound to a name by the :keyword:`import` statement.

   On the other hand, the statement ``from spam.ham import eggs, sausage as
   saus`` results in ::

      _temp = __import__('spam.ham', globals(), locals(), ['eggs', 'sausage'], 0)
      eggs = _temp.eggs
      saus = _temp.sausage

   Here, the ``spam.ham`` module is returned from :func:`__import__`.  From this
   object, the names to import are retrieved and assigned to their respective names.

   If you simply want to import a module (potentially within a package) by name,
   use :func:`importlib.import_module`.

   .. versionchanged:: 3.3
      Negative values for *level* are no longer supported (which also changes
      the default value to 0).


.. function:: reload(module)

   Reload a previously imported module. The argument must be a module object,
   so it must have been successfully imported before. This is useful if you
   have edited the module source file using an external editor and want to try out
   the new version without leaving the Python interpreter. The return value is the
   module object (the same as the module argument).

   When reload(module) is executed:

   * Python modules’ code is recompiled and the module-level code reexecuted, defining a new set of objects which are bound to names in the module’s dictionary. The :meth:`init` function of extension modules is not called a second time.

   * As with all other objects in Python the old objects are only reclaimed after their reference counts drop to zero.

   * The names in the module namespace are updated to point to any new or changed objects.
     
   * Other references to the old objects (such as names external to the module) are not rebound to refer to the new objects and must be updated in each namespace where they occur if that is desired.

There are a number of other caveats:

When a module is reloaded, its dictionary (containing the module’s global variables) is retained.
Redefinitions of names will override the old definitions, so this is generally not a problem.
If the new version of a module does not define a name that was defined by the old version,
the old definition remains. This feature can be used to the module’s advantage if it maintains
a global table or cache of objects — with a ``try`` statement it can test for the table’s presence
and skip its initialization if desired::

   try:
       cache
   except NameError:
       cache = {}

It is generally not very useful to reload built-in or dynamically loaded modules.
Reloading :mod:`sys`, :mod:`__main__`, :mod:`builtins` and other key modules is not recommended.
In many cases extension modules are not designed to be initialized more than once,
and may fail in arbitrary ways when reloaded.

If a module imports objects from another module using ``from … import …``,
calling :func:`reload` for the other module does not redefine the objects
imported from it — one way around this is to re-execute the from statement,
another is to use import and qualified names (module.*name*) instead.

If a module instantiates instances of a class, reloading the module that defines
the class does not affect the method definitions of the instances — they continue to
use the old class definition. The same is true for derived classes.

