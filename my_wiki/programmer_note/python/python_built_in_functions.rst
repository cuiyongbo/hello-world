Built-in Functions
==================


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
:func:`classmethod`    :func:`getattr`      :func:`locals`        :func:`repr`          :func:`zip`           
:func:`compile`        :func:`globals`      :func:`map`           :func:`reversed`      :func:`__import__`    
:func:`complex`        :func:`hasattr`      :func:`max`           :func:`round`       
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


.. function:: abs(x)

   Return the absolute value of a number.  The argument may be an
   integer or a floating point number.  If the argument is a complex number, its
   magnitude is returned.


.. function:: all(iterable)

   Return ``True`` if all elements of the iterable are true (or if the iterable is empty). Equivalent to::
   
      def all(iterable):
         for element in iterable:
            if not element:
               return False
         return True
   

.. function:: any(iterable)

   Return ``True`` if all elements of the iterable are true (or if the iterable is empty). Equivalent to::
   
      def all(iterable):
         for element in iterable:
            if not element:
               return False
         return True


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

.. _func-str:
.. class:: class str(object='')

   Return a string containing a nicely printable representation of an object. 
   For strings, this returns the string itself. 
   The difference with ``repr(object)`` is that ``str(object)`` does not always 
   attempt to return a string that is acceptable to ``eval()``; 
   its goal is to return a printable string. If no argument is given, returns the empty string, ''.


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


.. function:: oct(x)

   Convert an integer number (of any size) to an octal string. The result is a valid Python expression.


.. function:: hex(x)

   Convert an integer number (of any size) to a lowercase hexadecimal string prefixed with “0x”


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


.. function:: map(function, iterable, ...)

   Return an iterator that applies *function* to every item of *iterable*,
   yielding the results.  If additional *iterable* arguments are passed,
   *function* must take that many arguments and is applied to the items from all
   iterables in parallel.  With multiple iterables, the iterator stops when the
   shortest iterable is exhausted.  For cases where the function inputs are
   already arranged into argument tuples, see :func:`itertools.starmap`\.


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

