********************
String format syntax
********************

.. contents::
   :local:

print format syntax
===================

String and Unicode objects have one unique built-in operation: the ``%`` operator (modulo).
(a.k.a string formatting or interpolation operator). Given ``format % values`` ,
``%`` conversion specifications in ``format`` are replaced with zero or more
elements of ``values``. The effect is similar to the using ``sprintf()`` in the C language.
If *format* is a Unicode object, or if any of the objects being converted using
the ``%s`` conversion are Unicode objects, the result will also be a Unicode object.

If *format* requires a single argument, values may be a single non-tuple object.
Otherwise, values must be a tuple with exactly the number of items specified by the format string,
or a single mapping object (for example, a dictionary).

A **conversion specifier** contains two or more characters and has the following components,
which must occur in this order:

   #. The `%` character, which marks the start of the specifier.
     
   #. Mapping key (optional), consisting of a parenthesised
      sequence of characters (for example, (somename)).

   #. Conversion flags (optional), which affect the result of some conversion types.
     
   #. Minimum field width (optional). If specified as an "*" (asterisk),
      the actual width is read from the next element of the tuple in values,
      and the object to convert comes after the minimum field width
      and optional precision.

   #. Precision (optional), given as a "." (dot) followed by the precision.
      If specified as "*" (an asterisk), the actual width is read from the
      next element of the tuple in values, and the value to convert comes
      after the precision.

   #. Length modifier (optional).
  
   #. Conversion type.

When the right argument is a dictionary (or other mapping type), then the formats
in the string must include a parenthesised mapping key into that dictionary
inserted immediately after the "%" character. The mapping key selects the value
to be formatted from the mapping. For example::

   >>> print "%(name)s is a %(sex)s, %(age)2d years old." % \
   ... {"name":"cherry", "sex":"man", "age":25}
   cherry is a man, 25 years old.

   >>> "%s %d" % ("hello world", 6)
   'hello world 6'

The **conversion flag characters** are::

   +------+-----------------------------------------------------------+
   | Flag | Meaning                                                   |
   +======+===========================================================+
   | #    | The value conversion will use the "alternate form".       |
   +------+-----------------------------------------------------------+
   | 0    | The conversion will be zero padded for numeric values.    |
   +------+-----------------------------------------------------------+
   | \+   | A sign character ("+" or "-") will precede the conversion |
   |      | (overrides a "space" flag).                               |
   +------+-----------------------------------------------------------+
   | \-   | The converted value is left adjusted (overrides the "0"   |
   |      | conversion if both are given).                            |
   |      | a space should be left before a positive number           |
   |      | (or empty string) produced by a signed conversion.        |
   +------+-----------------------------------------------------------+

A **length modifier** (h, l, or L) may be present, but is ignored
as it is not necessary for Python.

The **conversion types** are::

   +------------+--------------------------------------------------------------------+-------+
   | Conversion | Meaning                                                            | Notes |
   +============+====================================================================+=======+
   | d          | Signed integer decimal                                             |       |
   +------------+--------------------------------------------------------------------+-------+
   | i          | Signed integer decimal                                             |       |
   +------------+--------------------------------------------------------------------+-------+
   | o          | Unsigned octal                                                     | \(1)  |
   +------------+--------------------------------------------------------------------+-------+
   | u          | Unsigned decimal                                                   |       |
   +------------+--------------------------------------------------------------------+-------+
   | x          | Unsigned hexadecimal (lowercase)                                   | \(2)  |
   +------------+--------------------------------------------------------------------+-------+
   | X          | Unsigned hexadecimal (uppercase)                                   | \(2)  |
   +------------+--------------------------------------------------------------------+-------+
   | e          | Floating point exponential format (lowercase)                      |       |
   +------------+--------------------------------------------------------------------+-------+
   | E          | Floating point exponential format (uppercase)                      |       |
   +------------+--------------------------------------------------------------------+-------+
   | f          | Floating point decimal format                                      |       |
   +------------+--------------------------------------------------------------------+-------+
   | F          | Floating point decimal format                                      |       |
   +------------+--------------------------------------------------------------------+-------+
   | g          | Same as "e" if exponent is greater than -4                         |       |
   |            | or less than precision, "f" otherwise                              |       |
   +------------+--------------------------------------------------------------------+-------+
   | G          | Same as "E" if exponent is greater than -4                         |       |
   |            | or less than precision, "F" otherwise                              |       |
   +------------+--------------------------------------------------------------------+-------+
   | c          | Single character (accepts integer or single character string)      |       |
   +------------+--------------------------------------------------------------------+-------+
   | r          | String (converts any python object using ``repr()``)               |       |
   +------------+--------------------------------------------------------------------+-------+
   | s          | String (converts any python object using ``str()``)                | \(3)  |
   +------------+--------------------------------------------------------------------+-------+
   | %          | No argument is converted, results in a "%" character in the result | \(4)  |
   +------------+--------------------------------------------------------------------+-------+

Notes:

\(1)
   The alternate form causes a leading zero ("0") to be inserted between left-hand padding
   and the formatting of the number if the leading character of the result is not already a zero.

\(2)
   The alternate form causes a leading ``'0x' or '0X'`` (depending on whether the ``"x" or "X"`` 
   format was used) to be inserted  between left-hand padding and the formatting of the number
   if the leading character of the result is not already a zero.

\(3)
   If the object or format provided is a unicode string, the resulting string will also be unicode.

\(4) 
   If you want a ``"%"`` character in the result, use ``"%%"`` in the format.

Since Python strings have an explicit length, ``%s`` conversions do not assume that ``'\0'`` is
the end of the string.

For safety reasons, floating point precisions are clipped to ``50``; 
``%f`` conversions for numbers whose absolute value is over ``1e25`` 
are replaced by ``%g`` conversions. All other errors raise exceptions.

.. code-block:: cpp
   :caption: printf using '/r'

   typedef long long int64;
   typedef unsigned long long uint64;
   
   uint64 loaded, total;
   printf("Loaded: %9llu, total: %9llu\r", loaded, total)


Built-in string: str
====================

Grammer
-------

Format strings contain “replacement fields” surrounded by curly braces ``{}``. 
Anything that is not contained in braces is considered literal text,
which is copied unchanged to the output. 

Grammer for a replacement field as follow::

   replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"
   field_name        ::=  arg_name ("." attribute_name | "[" element_index "]")*
   arg_name          ::=  [identifier | integer]
   attribute_name    ::=  identifier
   element_index     ::=  integer | index_string
   index_string      ::=  <any source character except "]"> +
   conversion        ::=  "r" | "s"
   format_spec       ::=  <described in the next section>

standard **format specifier**::

   format_spec ::=  [[fill]align][sign][#][0][width][,][.precision][type]
   fill        ::=  <any character>
   align       ::=  "<" | ">" | "=" | "^"
   sign        ::=  "+" | "-" | " "
   width       ::=  integer
   precision   ::=  integer
   type        ::=  "b" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" | "n" | "o" | "s" | "x" | "X" | "%"

.. note::

   If you need to include a brace character in the literal text,
   it can be escaped by doubling: `{{` and `}}`.

The meaning of the various **alignment options** is as follows::

   +--------+--------------------------------------------------------------------------------+
   | Option | Meaning                                                                        |
   +========+================================================================================+
   | '<'    | Forces the field to be left-aligned within the available space                 |
   |        | (this is the default for most objects).                                        |
   +--------+--------------------------------------------------------------------------------+
   | '>'    | Forces the field to be right-aligned within the available space                |
   |        | (this is the default for numbers).                                             |
   +--------+--------------------------------------------------------------------------------+
   | '^'    | Forces the field to be centered within the available space.                    |
   +--------+--------------------------------------------------------------------------------+
   | '='    | Forces the padding to be placed after the sign (if any) but before the digits. |
   |        | This is used for printing fields in the form ``‘+000000120’``. This alignment  |
   |        | option is only valid for numeric types. It becomes the default when ‘0’        |
   |        | immediately precedes the field width.                                          |
   +--------+--------------------------------------------------------------------------------+

Note that unless a minimum field width is defined, the field width will always be the same size
as the data to fill it, so that the alignment option has no meaning in this case.

The **sign option** is only valid for number types, and can be one of the following::

   +--------+-----------------------------------------------------------+
   | Option | Meaning                                                   |
   +========+===========================================================+
   | '+'    | indicates that a sign should be used for                  |
   |        | both positive as well as negative numbers.                |
   +--------+-----------------------------------------------------------+
   | '-'    | indicates that a sign should be used                      |
   |        | only for negative numbers (this is the default behavior). |
   +--------+-----------------------------------------------------------+
   | space  | indicates that a leading space should be used on          |
   |        | positive numbers, and a minus sign on negative numbers.   |
   +--------+-----------------------------------------------------------+

The `#` option causes the “alternate form” to be used for the conversion.
**This option is only valid for integer, float, complex and Decimal types**.
For integers, when binary, octal, or hexadecimal output is used, this option
adds the prefix respective `0b`, `0o`, or `0x` to the output value.
For floats, complex and Decimal the alternate form causes the result of the
conversion to always contain a decimal-point character, even if no digits follow it.
In addition, for ``'g'`` and ``'G'`` conversions, trailing zeros are not removed from the result.

The `,` option signals the use of a comma for a thousands separator.
For a locale aware separator, use the `n` integer presentation type instead.

**width** is a decimal integer defining the minimum field width.
If not specified, then the field width will be determined by the content.

When no explicit alignment is given, preceding the width field by
a zero ('0') character enables sign-aware zero-padding for numeric types.
This is equivalent to a fill character of ``'0'`` with an alignment type of ``'='``.

The **precision** is a decimal number indicating how many digits should be
displayed after the decimal point for a floating point value formatted
with ``'f'`` and ``'F'``, or before and after the decimal point for a
floating point value formatted with ``'g'`` or ``'G'``. For non-number
types the field indicates the maximum field size - in other words,
how many characters will be used from the field content.
The precision is not allowed for integer values.

Finally, the **type** determines how the data should be presented.

Examples
--------

Accessing arguments by position::
  
   >>> "{}, {}, {}".format('a', 'b', 'c')
   'a, b, c'
   >>> "{0}, {1}, {2}".format('a', 'b', 'c')
   'a, b, c'
   >>> "{2}, {1}, {0}".format('a', 'b', 'c')
   'c, b, a'
   >>> "{2}, {1}, {1}".format('a', 'b', 'c')
   'c, b, b' # arguments' indices can be repeated
   >>> "{2}, {1}, {1}".format(*"abc")
   'c, b, b' # unpacking argument sequence
   >>> "{2}, {1}, {1}".format(*("I", "love", "you"))
   'you, love, love'

Accessing arguments by name::

   >>> 'Coordinates: {latitude}, {longitude}'.format(latitude='37.24N', longitude='112.81E') 
   'Coordinates: 37.24N, 112.81E'
   >>> coord = {'latitude':'37.24N', 'longitude':'112.81E'}
   >>> 'Coordinates: {latitude}, {longitude}'.format(**coord)
   'Coordinates: 37.24N, 112.81E'

Accessing arguments' item::

   >>> coord=(3,5)
   >>> 'x:{0[0]}; y:{0[1]}'.format(coord)
   'x:3; y:5'

Accessing arguments' attribute::

   >>> c = 3-5j
   >>> ('Complex number: {0}, real part: {0.real}, imaginary part: {0.imag}').format(c)
   'Complex number: (3-5j), real part: 3.0, imaginary part: -5.0'
   >>> class Point:
   ...     def __init__(self, x, y):
   ...             self.x, self.y = x, y
   ...     def __str__(self):
   ...             return "Point({self.x}, {self.y})".format(self=self)
   ... 
   >>> str(Point(2,4))
   'Point(2, 4)'

Replacing ``%s`` with ``%r``::

   >>> "repr() shows quotes: {!r}; str() doesn't: {!s}".format('test1', 'test2')
   "repr() shows quotes: 'test1'; str() doesn't: test2"

Aligning the text with field width::

   >>> '{:<30}'.format('left aligned')
   'left aligned                  '
   >>> '{:>30}'.format('right aligned')
   '                 right aligned'
   >>> '{:^30}'.format('centered')
   '           centered           '
   >>> '{:*^30}'.format('centered') # using '*' as a fill char
   '***********centered***********'
   >>> '{0:=+030}'.format(67817638)
   '+00000000000000000000067817638'

Numberic format specificer::

   >>> '{:+f} {:+f}'.format(3.14, -3.14)
   '+3.140000 -3.140000'
   >>> '{:-f} {:-f}'.format(3.14, -3.14)
   '3.140000 -3.140000'
   >>> '{: f} {: f}'.format(3.14, -3.14)
   ' 3.140000 -3.140000'

   >>> 'int: {0:d}, hex: {0:x}, oct: {0:o}, bin: {0:b}'.format(42)
   'int: 42, hex: 2a, oct: 52, bin: 101010'
   >>> 'int: {0:d}, hex: {0:#x}, oct: {0:#o}, bin: {0:#b}'.format(42)
   'int: 42, hex: 0x2a, oct: 0o52, bin: 0b101010'

   >>> '{:,}'.format(1234567890)
   '1,234,567,890'

   >>> 'Correct answers: {:.2%}'.format(19.5/22)
   'Correct answers: 88.64%'

Nested ones::

   >>> for align, text in zip('<^>', ['left', 'center', 'right']):
   ...     '{0:{fill}{align}16}'.format(text, fill=align, align=align)
   ... 
   'left<<<<<<<<<<<<'
   '^^^^^center^^^^^'
   '>>>>>>>>>>>right'

   >>> for num in xrange(5, 12):
   ...     for base in 'dXob':
   ...             print '{0:{width}{base}}'.format(num, base=base, width=5),
   ...     print
   ... 
       5     5     5   101
       6     6     6   110
       7     7     7   111
       8     8    10  1000
       9     9    11  1001
      10     A    12  1010
      11     B    13  1011


Template strings
================

Templates provide simpler string substitutions as described in PEP 292. 
Instead of the normal %-based substitutions, Templates support $-based
substitutions, using the following rules:

   #. ``$$`` is an escape; it is replaced with a single ``$``.
      
   #. ``$identifier`` names a substitution placeholder matching a mapping key of "identifier".
      By default, "identifier" must spell a Python identifier. The first non-identifier character
      after the ``$`` character terminates this placeholder specification. 
   #. ``${identifier}`` is equivalent to ``$identifier``. It is required when valid identifier
      characters follow the placeholder but are not part of the placeholder, such as ``${noun}ification``.  

Any other appearance of ``$`` in the string will result in a ``ValueError`` being raised.

The string module provides a Template class that implements these rules. The methods of Template are::

   >>> from string import Template
   >>> s = Template("$who likes $what")
   >>> s.substitute(who='Jim', what='programming')
   'Jim likes programming'
   >>> d = dict(who='Jim')
   >>> s.substitute(d)
   Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/string.py", line 176, in substitute
        return self.pattern.sub(convert, self.template)
      File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/string.py", line 166, in convert
        val = mapping[named]
   KeyError: 'what'
   >>> s.safe_substitute(d)
   'Jim likes $what'

