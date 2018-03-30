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

.. method:: str.capitalize()

   Return a copy of the string with its first character capitalized and the
   rest lowercased.

.. method:: str.center(width[, fillchar])

   Return centered in a string of length *width*. Padding is done using the 
   specified *fillchar* (default is a space). For example::

      >>> s = "Hello World"
      >>> s.center(20, '-')
      '----Hello World-----'

   .. versionchanged:: 2.4
      Support for the fillchar argument.

.. method:: str.count(sub[, start[, end]])

   Return the number of non-overlapping occurrences of substring *sub* in
   the range ``[start, end]``. Optional arguments *start* and *end* are
   interpreted as in slice notation.

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

.. method:: str.endswith(suffix[, start[, end]])

   Return ``True`` if the string ends with the specified *suffix*, otherwise return ``False``.
   *suffix* can also be a tuple of suffixes to look for. With optional *start*, test beginning
   at that position. With optional *end*, stop comparing at that position.

   .. versionadded:: 2.5
      Accept tuples as suffix.