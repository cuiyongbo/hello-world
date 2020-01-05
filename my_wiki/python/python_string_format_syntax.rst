********************
String format syntax
********************

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
