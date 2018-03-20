Built-in Functions
==================

zip
---

zip(...)
    zip(seq1 [, seq2 [...]]) -> [(seq1[0], seq2[0] ...), (...)]
    
    Return a list of tuples, where each tuple contains the i-th element
    from each of the argument sequences.  The returned list is truncated
    in length to the length of the shortest argument sequence.


all(iterable)
-------------

Return ``True`` if all elements of the iterable are true (or if the iterable is empty). Equivalent to:

.. code-block:: python

   def all(iterable):
      for element in iterable:
         if not element:
            return False
      return True


any(iterable)
-------------

Return ``True`` if any element of the iterable is true. If the iterable is empty, return ``False``. Equivalent to:

.. code-block:: python

   def any(iterable):
      for element in iterable:
         if element:
            return True
      return False


.. _chr:

chr(i)
------

Return a string of one character whose ASCII code is the integer ``i``. This is the inverse of :ref:`ord`. 
The argument must be in the range [0..255], inclusive; ``ValueError`` will be raised if i is outside that range. See also :ref:`unichr`.

.. code-block:: python

   >>> chr(97)
   'a'


.. _ord:

ord(c)
------

Given a string of length one, return an integer representing the Unicode code point of the character when the argument is a unicode object, 
or the value of the byte when the argument is an 8-bit string. This is the inverse of :ref:`chr` for 8-bit strings and of :ref:`unichr` for unicode objects. 
If a unicode argument is given and Python was built with UCS2 Unicode, then the character’s code point must be in the range [0..65535] inclusive; 
otherwise the string length is two, and a ``TypeError`` will be raised.

.. code-block:: python

   >>> ord('a')
   97
   >>> ord(u'\u2020')
   8224
   >>> int('0x2020', 16)
   8224


.. _unichr:

unichr(i)
---------

Return the Unicode string of one character whose Unicode code is the integer ``i``.This is the inverse of :ref:`ord` for Unicode strings. 
The valid range for the argument depends how Python was configured – it may be either UCS2 [0..0xFFFF] or UCS4 [0..0x10FFFF]. 
``ValueError`` is raised otherwise. For ASCII and 8-bit strings see :ref:`chr`.

.. code-block:: python

   >>> unichr(97)
   u'a'

