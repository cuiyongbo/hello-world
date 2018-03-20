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


.. using :func:`dict` would create a link to another page, so local targets are
   used, with replacement texts to make the output in the table consistent

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


.. function:: chr(i)

   Return a string of one character whose ASCII code is the integer ``i``. This is the inverse of :func:`ord`. 
   The argument must be in the range [0..255]; ``ValueError`` will be raised if i is outside that range. 
   See also :func:`unichr`.
   
   .. code-block:: python
   
      >>> chr(97)
      'a'


.. function:: isinstance(object, classinfo)

   Return true if the *object* argument is an instance of the *classinfo* argument, or of a (direct, indirect or virtual) subclass thereof. 
   Also return true if *classinfo* is a type object (new-style class) and *object* is an object of that type or of a (direct, indirect or virtual) subclass thereof. 
   If *object* is not a class instance or an object of the given type, the function always returns false. 
   If *classinfo* is a tuple of class or type objects (or recursively, other such tuples), return true if object is an instance of any of the classes or types. 
   If *classinfo* is not a class, type, or tuple of classes, types, and such tuples, a ``TypeError`` exception is raised.


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


.. function:: unichr(i)

   Return the Unicode string of one character whose Unicode code is the integer ``i``.This is the inverse of :func:`ord` for Unicode strings. 
   The valid range for the argument depends how Python was configured – it may be either UCS2 [0..0xFFFF] or UCS4 [0..0x10FFFF]. 
   ``ValueError`` is raised otherwise. For ASCII and 8-bit strings see :func:`chr`.
   
   .. code-block:: python
   
      >>> unichr(97)
      u'a'


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