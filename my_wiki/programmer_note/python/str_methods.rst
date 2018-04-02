String methods
==============

.. index::
   module: re

Strings implement all of the :ref:`common <typesseq-common>` sequence
operations, along with the additional methods described below.

Strings also support two styles of string formatting, one providing a large
degree of flexibility and customization (see :meth:`str.format`,
:ref:`formatstrings` and :ref:`string-formatting`) and the other based on C
``printf`` style formatting that handles a narrower range of types and is
slightly harder to use correctly, but is often faster for the cases it can
handle (:ref:`old-string-formatting`).

The :ref:`textservices` section of the standard library covers a number of
other modules that provide various text related utilities (including regular
expression support in the :mod:`re` module).

.. method:: str.decode([encoding[, errors]])

   Decodes the string using the codec registered for *encoding*. *encoding* defaults to
   the default string encoding. errors may be given to set a different error handling scheme.
   The default is '``strict'``, meaning that encoding errors raise :exc:`UnicodeError`.
   Other possible values are ``'ignore'``, ``'replace'`` and any other name registered
   via :func:`codecs.register_error`, see section Codec Base Classes.

   .. versionadded:: 2.2

.. method:: str.encode([encoding[, errors]])

   Return an encoded version of the string. Default encoding is the current default string encoding.
   errors may be given to set a different error handling scheme. The default for *errors* is ``'strict'``,
   meaning that encoding errors raise a :exc:`UnicodeError`. Other possible values are ``'ignore'``, ``'replace'``,
   ``'xmlcharrefreplace'``, '``backslashreplace'`` and any other name registered via :func:`codecs.register_error`,
   see section Codec Base Classes. For a list of possible encodings, see section Standard Encodings.

.. method:: str.startswith(prefix[, start[, end]])
.. method:: str.endswith(suffix[, start[, end]])

   Return ``True`` if the string starts or ends with the specified *suffix*, otherwise return ``False``.
   *suffix* can also be a tuple of suffixes to look for. With optional *start*, test beginning
   at that position. With optional *end*, stop comparing at that position.

   .. versionadded:: 2.5
      Accept tuples as suffix.

.. method:: str.count(sub[, start[, end]])

   Return the number of non-overlapping occurrences of substring *sub* in
   the range ``[start, end]``. Optional arguments *start* and *end* are
   interpreted as in slice notation.

.. method:: str.find(sub[, start[, end]])
.. method:: str.rfind(sub[, start[, end]])

   Return the lowest index in the string where substring *sub* is found within the slice
   ``s[start:end]``. Optional arguments *start* and *end* are interpreted as in slice notation.
   Return ``-1`` if *sub* is not found.

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
   If there is any :class:`Unicode` object in iterable, return a :class:`Unicode` instead.
   A :exc:`TypeError` will be raised if there are any non-string or non :class:`Unicode` object
   values in iterable. The separator between elements is the string providing this method.

.. method:: str.split([sep[, maxsplit]])

   Return a list of the words in the string, using *sep* as the delimiter string.
   If *maxsplit* is given, at most *maxsplit* splits are done (thus, the list will
   have at most ``maxsplit+1`` elements). If *maxsplit* is not specified or ``-1``,
   then there is no limit on the number of splits (all possible splits are made).

   If *sep* is given, consecutive delimiters are not grouped together and are deemed to delimit empty strings
   (for example, ``'1,,2'.split(',')`` returns ``['1', '', '2']``). The ``sep`` argument may consist of multiple
   characters (for example, ``'1<>2<>3'.split('<>')`` returns ``['1', '2', '3']``). Splitting an empty string with
   a specified separator returns ``['']``.

   If *sep* is not specified or is ``None``, a different splitting algorithm is applied:
   runs of consecutive whitespace are regarded as a single separator, and the result will
   contain no empty strings at the start or end if the string has leading or trailing whitespace.
   Consequently, splitting an empty string or a string consisting of just whitespace with
   a ``None`` separator returns ``[]``.

   For example, ``' 1  2   3  '.split()`` returns ``['1', '2', '3']``, and
   ``'  1  2   3  '.split(None, 1)`` returns ``['1', '2   3  ']``.

.. method:: str.splitlines([keepends])

   Return a list of the lines in the string, breaking at line boundaries.
   This method uses the universal newlines approach to splitting lines.
   Line breaks are not included in the resulting list unless *keepends*
   is given and true.

   Python recognizes ``"\r"``, ``"\n"``, and ``"\r\n"`` as line boundaries
   for 8-bit strings.

   For example::

      >>> 'ab c\n\nde fg\rkl\r\n'.splitlines()
      ['ab c', '', 'de fg', 'kl']
      >>> 'ab c\n\nde fg\rkl\r\n'.splitlines(True)
      ['ab c\n', '\n', 'de fg\r', 'kl\r\n']
      

   Unlike ``split()`` when a delimiter string *sep* is given, this method
   returns an empty list for the empty string, and a terminal line break
   does not result in an extra line::

      >>> "".splitlines()
      []
      >>> "One line\n".splitlines()
      ['One line']

   For comparison, split('\n') gives::
      
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
      >>> s2 = 'www.example.com'
      >>> chars = 'cmowz.'
      >>> s1.strip()
      'spacious'
      >>> s1.lstrip()
      'spacious   '
      >>> s1.rstrip()
      '  spacious'
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

.. note:: 

   For 8-bit strings, the folllowing methods are locale-dependent.

.. method:: str.isalnum()

   Return true if all characters in the string are alphanumeric
   and there is at least one character, false otherwise.

.. method:: str.isalpha()

   Return true if all characters in the string are alphabetic
   and there is at least one character, false otherwise.

.. method:: str.isdigit()
   
   Return true if all characters in the string are digits
   and there is at least one character, false otherwise.

.. method:: str.islower()

   Return true if all cased characters in the string are lowercase
   and there is at least one cased character, false otherwise.

.. method:: str.isupper()

   Return true if all cased characters in the string are uppercase
   and there is at least one cased character, false otherwise.

.. method:: str.isspace()

   Return true if there are only whitespace characters in the string
   and there is at least one character, false otherwise.

.. method:: str.istitle()

   Return true if the string is a titlecased string and there is at
   least one character, for example uppercase characters may only follow
   uncased characters and lowercase characters only cased ones. Return false otherwise.

.. method:: str.lower()
.. method:: str.upper()
.. method:: str.swapcase()

   Return a copy of the string with all the cased characters
   converted to lowercase / uppercase.

.. method:: str.capitalize()

   Return a copy of the string with its first character capitalized
   and the rest lowercased.

   .. code-block:: python

      >>> s3 = "they're bill's friends from the UK"
      >>> s3.capitalize()
      "They're bill's friends from the uk"

.. method:: str.title()

   Return a titlecased version of the string where words start with
   an uppercase character and the remaining characters are lowercase.

   The algorithm uses a simple language-independent definition of a word
   as groups of consecutive letters. The definition works in many contexts
   but it means that apostrophes in contractions and possessives form word
   boundaries, which may not be the desired result::

      >>> "they're bill's friends from the UK".title()
      "They'Re Bill'S Friends From The Uk"

   A workaround for apostrophes can be constructed
   using regular expressions::

      >>> def titlecase(s):
      ...     return re.sub(r"[a-zA-Z]+('[a-zA-Z]+)?",
      ...             lambda mo: mo.group(0)[0].upper() +
      ...                    mo.group(0)[1:].lower(), s)
      ...
      >>> titlecase("they're bill's friends from the UK")
      "They're Bill's Friends From The Uk"
