**************
String methods
**************

Strings also support two styles of string formatting, one providing a large
degree of flexibility and customization (see :meth:`str.format`,
:ref:`formatstrings` and :ref:`string-formatting`) and the other based on C
``printf`` style formatting that handles a narrower range of types and is
slightly harder to use correctly, but is often faster for the cases it can
handle (:ref:`old-string-formatting`).

.. method:: str.decode([encoding[, errors]])

   Decodes the string using the codec registered for *encoding*. *encoding* defaults to
   the default string encoding. errors may be given to set a different error handling scheme.
   The default is '``strict'``, meaning that encoding errors raise :exc:`UnicodeError`.
   Other possible values are ``'ignore'``, ``'replace'`` and any other name registered
   via :func:`codecs.register_error`, see section Codec Base Classes.

   .. versionadded:: 2.2

.. method:: str.encode([encoding[, errors]])

   Return an encoded version of the string. Default encoding is the current default string encoding.
   errors may be given to set a different error handling scheme. Same as :func:`str.decode`.

.. method:: str.startswith(prefix[, start[, end]])
.. method:: str.endswith(suffix[, start[, end]])

   *prefix*, or *suffix* can also be a tuple of suffixes to look for. With 
   optional *start*, test beginning at that position. With optional *end*, 
   stop comparing at that position.

   .. versionadded:: 2.5
      Accept tuples as suffix.

.. method:: str.count(sub[, start[, end]])

   Return the number of non-overlapping occurrences of substring *sub* in
   the range ``[start, end]``.

.. method:: str.find(sub[, start[, end]])
.. method:: str.rfind(sub[, start[, end]])

   Return the lowest/highest index in the string where substring *sub* is found 
   within the slice ``s[start:end]``. Return ``-1`` if *sub* is not found.

.. note::

   Note The ``find()`` method should be used only if you need to know the position of *sub*.
   To check if *sub* is a substring or not, use the ``in`` operator::

      >>> 'Py' in 'Python'
      True

.. method:: str.index(sub[, start[, end]])
.. method:: str.rindex(sub[, start[, end]])

   Like :meth:`find`, but raise :exc:`ValueError` when the substring is not found.

.. method:: str.replace(old, new[, count])

   Return a copy of the string with all occurrences of substring
   *old* replaced by *new*. If the optional argument *count* is given,
   only the first count occurrences are replaced.

.. method:: str.join(iterable)

   Return a string which is the concatenation of the strings in iterable.
   A :exc:`TypeError` will be raised if there are any non-string or non :class:`Unicode` object
   values in iterable. The separator between elements is the string providing this method.

.. method:: str.split([sep[, maxsplit]])

   Return a list of the words in the string, using *sep* as the delimiter string.
   If *maxsplit* is given, at most *maxsplit* splits are done (thus, the list will
   have at most ``maxsplit+1`` elements). If *maxsplit* is not specified or ``-1``,
   then there is no limit on the number of splits::

      >>> "1,,2".split(",")
      ['1', '', '2']
      >>> "1<>2<>3".split("<>")
      ['1', '2', '3']
      >>> ' 1    2 3 '.split()
      ['1', '2', '3']

.. method:: str.splitlines([keepends])

   Return a list of the lines in the string, breaking at line boundaries.
   Line breaks are not included in the resulting list unless *keepends*
   is given and true.

   Python recognizes ``"\r"``, ``"\n"``, and ``"\r\n"`` as line boundaries
   for 8-bit strings.

   For example::

      >>> 'ab c\n\nde fg\rkl\r\n'.splitlines()
      ['ab c', '', 'de fg', 'kl']
      >>> 'ab c\n\nde fg\rkl\r\n'.splitlines(True)
      ['ab c\n', '\n', 'de fg\r', 'kl\r\n']

      >>> ''.splitlines()
      []
      >>> "One line\n".splitlines()
      ['One line']

      >>> ''.split('\n')
      ['']
      >>> 'Two lines\n'.split('\n')
      ['Two lines', '']

.. method:: str.strip([chars])
.. method:: str.lstrip([chars])
.. method:: str.rstrip([chars])

   Return a copy of the string with the leading and trailing characters removed.
   The *chars* argument is a string specifying the set of characters to be removed.
   If omitted or ``None``, the chars argument defaults to removing whitespace.
   The *chars* argument is not a prefix or suffix; rather,
   all combinations of its values are stripped::

      >>> s1 = '  spacious   '
      >>> s1.strip()
      'spacious'
      >>> s1.lstrip()
      'spacious   '
      >>> s1.rstrip()
      '  spacious'
      >>> chars = 'cmowz.'
      >>> s2 = 'www.example.com'
      >>> s2.strip(chars)
      'example'
      >>> s2.lstrip(chars)
      'example.com'
      >>> s2.rstrip(chars)
      'www.example'

.. method:: str.center(width[, fillchar])
.. method:: str.ljust(width[, fillchar])
.. method:: str.rjust(width[, fillchar])

   Return the string center / left / right justified in a string of length width.
   Padding is done using the specified *fillchar* (default is a space).
   The original string is returned if *width* is less than or equal to ``len(s)``.

.. versionchanged:: 2.4
   Support for the fillchar argument.

.. code-block:: python

   >>> s = "Hello world"
   >>> s.center(20, '-')
   '----Hello world-----'
   >>> s.ljust(20)
   'Hello world         '
   >>> s.rjust(20, '>')
   '>>>>>>>>>Hello world'

.. method:: str.zfill(width)

   Return the numeric string left filled with zeros in a string of length *width*.
   A sign prefix is handled correctly. The original string is returned if *width*
   is less than or equal to ``len(s)``.

   .. versionadded:: 2.2.2

.. method:: str.lower()
.. method:: str.upper()
.. method:: str.swapcase()

   Return a copy of the string with all the cased characters
   converted to lowercase / uppercase.

.. method:: str.isalnum()
.. method:: str.isalpha()
.. method:: str.isdigit()
.. method:: str.islower()
.. method:: str.isupper()
.. method:: str.isspace()
