Built-in Types
==============

The principal built-in types are numerics, sequences, mappings, files, classes, instances and exceptions.


Truth Value Testing
-------------------

* Any object can be tested for truth value, for use in an ``if`` or ``while`` condition or as operand of the Boolean operations below. The following values are considered false:

   * None
   * False
   * zero of any numeric type, for example, 0, 0L, 0.0, 0j.
   * any empty sequence, for example, '', (), [].
   * any empty mapping, for example, {}.
   * instances of user-defined classes, if the class defines a __nonzero__() or __len__() method, when that method returns the integer zero or bool value False.

* All other values are considered true — so objects of many types are always true.

* Operations and built-in functions that have a Boolean result always return 0 or False for false and 1 or True for true, unless otherwise stated. 

.. note::

   **Important exception**: the Boolean operations ``or`` and ``and`` always return one of their operands.

   .. code-block:: python

      >>> 1 and 0
      0
      >>> 1 and False
      False
      >>> 1 or True
      1
      >>> 0  or True
      True
      >>> 0  or 3
      3



Boolean Operations — and, or, not
---------------------------------

These are the Boolean operations, ordered by ascending priority:

+-------------+--------------------------------------+-------+
| Operation   | Result                               | Notes |
+=============+======================================+=======+
| ``x or y``  | if x is false, then y, else x        | \(1)  |
+-------------+--------------------------------------+-------+
| ``x and y`` | if x is false, then x, else y        | \(2)  |
+-------------+--------------------------------------+-------+
| ``not x``   | if x is false, then True, else False | \(3)  |
+-------------+--------------------------------------+-------+


Notes:

(1)
   This is a short-circuit operator, so it only evaluates the second
   argument if the first one is false.

(2)
   This is a short-circuit operator, so it only evaluates the second
   argument if the first one is true.

(3)
   ``not`` has a lower priority than non-Boolean operators, so ``not a == b`` is
   interpreted as ``not (a == b)``, and ``a == not b`` is a syntax error.


Comparisons
-----------

Comparison operations are supported by all objects. They all have the same priority (which is higher than that of the Boolean operations). Comparisons can be chained arbitrarily; for example, ``x < y <= z`` is equivalent to ``x < y and y <= z``, except that y is evaluated only once (but in both cases z is not evaluated at all when ``x < y`` is found to be false).

This table summarizes the comparison operations:

+-----------+-------------------------+
| Operation | Meaning                 |
+===========+=========================+
| <         | strictly less than      |
+-----------+-------------------------+
| <=        | less than or equal      |
+-----------+-------------------------+
| >         | strictly greater than   |
+-----------+-------------------------+
| >=        | greater than or equal   |
+-----------+-------------------------+
| ==        | equal                   |
+-----------+-------------------------+
| !=        | not equal               |
+-----------+-------------------------+
| is        | object identity         |
+-----------+-------------------------+
| is not    | negated object identity |
+-----------+-------------------------+


* Objects of different types, except different numeric types and different string types, never compare equal; such objects are ordered consistently but arbitrarily (so that sorting a heterogeneous array yields a consistent result). Furthermore, some types (for example, file objects) support only a degenerate notion of comparison where any two objects of that type are unequal. Again, such objects are ordered arbitrarily but consistently. 

* The ``<, <=, > and >=`` operators will raise a ``TypeError`` exception when any operand is a complex number.
  
* Non-identical instances of a class normally compare as non-equal unless the class defines the ``__eq__()`` method or the ``__cmp__()`` method.

* Instances of a class cannot be ordered with respect to other instances of the same class, or other types of object, unless the class defines either enough of the rich comparison methods (``__lt__(), __le__(), __gt__(), and __ge__()) or the __cmp__()`` method.
  

Numeric Types — int, float, long, complex
-----------------------------------------

There are four distinct numeric types: *plain integers, long integers, floating point numbers, and complex numbers*. In addition, Booleans are a subtype of plain integers. **Plain integers (also just called integers) are implemented using long in C**, which gives them at least 32 bits of precision. Long integers have unlimited precision. **Floating point numbers are usually implemented using double in C**; Complex numbers have a real and imaginary part, which are each a floating point number. To extract these parts from a complex number z, use ``z.real`` and ``z.imag``. 

Numbers are created by numeric literals or as the result of built-in functions and operators. Unadorned integer literals (including binary, hex, and octal numbers) yield plain integers unless the value they denote is too large to be represented as a plain integer, in which case they yield a long integer. Integer literals with an 'L' or 'l' suffix yield long integers (**'L' is preferred because 1l looks too much like eleven!**). Numeric literals containing a decimal point or an exponent sign yield floating point numbers. Appending 'j' or 'J' to a numeric literal yields an imaginary number (a complex number with a zero real part) which you can add to an integer or float to get a complex number with real and imaginary parts.

Python fully supports mixed arithmetic: when a binary arithmetic operator has operands of different numeric types, the operand with the “narrower” type is widened to that of the other, where plain integer is narrower than long integer is narrower than floating point is narrower than complex. Comparisons between numbers of mixed type use the same rule.  

.. note::

   * ``sys.maxint`` is always set to the maximum plain integer value for the current platform, the minimum value is ``-sys.maxint - 1``.
   * information about the precision and internal representation of floating point numbers for the machine on which your program is running is available in ``sys.float_info``.
   * The constructors ``int(), long(), float(), and complex()`` can be used to produce numbers of a specific type.


All built-in numeric types support the following operations. See The power operator and later sections for the operators’ priorities.

+--------------------+-----------------------------------------------------------------------------+-------+
| Operation          | Result                                                                      | Notes |
+====================+=============================================================================+=======+
| ``x + y``          | sum of x and y                                                              |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x - y``          | difference of x and y                                                       |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x * y``          | product of x and y                                                          |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x / y``          | quotient of x and y                                                         | \(1)  |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x // y``         | (floored) quotient of x and y                                               |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x % y``          | remainder of ``x / y``                                                      |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``-x``             | x negated                                                                   |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``+x``             | x unchanged                                                                 |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``abs(x)``         | absolute value or magnitude of x                                            |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``int(x)``         | x converted to integer                                                      | \(2)  |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``long(x)``        | x converted to long integer                                                 | \(2)  |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``float(x)``       | x converted to floating point                                               | \(3)  |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``complex(re,im)`` | a complex number with real part re, imaginary part im. im defaults to zero. |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``c.conjugate()``  | conjugate of the complex number c. (Identity on real numbers)               |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``divmod(x, y)``   | the pair ``(x // y, x % y)``                                                |       |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``pow(x, y)``      | x to the power y                                                            | \(4)  |
+--------------------+-----------------------------------------------------------------------------+-------+
| ``x ** y``         | x to the power y                                                            | \(4)  |
+--------------------+-----------------------------------------------------------------------------+-------+

Notes:

(1)
   Also referred to as integer division.  The resultant value is a whole
   integer, though the result's type is not necessarily int.  The result is
   always rounded towards minus infinity: ``1//2`` is ``0``, ``(-1)//2`` is
   ``-1``, ``1//(-2)`` is ``-1``, and ``(-1)//(-2)`` is ``0``.

(2)
   Conversion from floats using ``int()`` or ``long()`` truncates toward zero like the related function, ``math.trunc()``. 
   Use the function ``math.floor()`` to round downward and ``math.ceil()`` to round upward.

(3)
   float also accepts the strings “nan” and “inf” with an optional prefix “+” or “-” for :abbr:`NaN (Not a Number)` and positive or negative infinity.

(4)
   Python defines ``pow(0, 0)`` and ``0 ** 0`` to be 1, as is common for programming languages.


Bitwise Operations on Integer Type
----------------------------------

Bitwise operations only make sense for integers. Negative numbers are treated as their 2’s complement value (this assumes a sufficiently large number of bits that no overflow occurs during the operation).

*The priorities of the binary bitwise operations are all lower than the numeric operations and higher than the comparisons; the unary operation ~ has the same priority as the other unary numeric operations (+ and -).*

This table lists the bitwise operations sorted in ascending priority:

+------------+---------------------------------+----------+
| Operation  | Result                          | Notes    |
+============+=================================+==========+
| ``x | y``  | bitwise or of x and y           |          |
+------------+---------------------------------+----------+
| ``x ^ y``  | bitwise exclusive or of x and y |          |
+------------+---------------------------------+----------+
| ``x & y``  | bitwise and of x and y          |          |
+------------+---------------------------------+----------+
| ``x << n`` | x shifted left by n bits        | \(1)\(2) |
+------------+---------------------------------+----------+
| ``x >> n`` | x shifted right by n bits       | \(1)\(3) |
+------------+---------------------------------+----------+
| ``~x``     | the bits of x inverted          |          |
+------------+---------------------------------+----------+


Notes:

(1)
   Negative shift counts are illegal and cause a ``ValueError`` to be raised.

(2)
   A left shift by n bits is equivalent to multiplication by ``pow(2, n)``. 
   A long integer is returned if the result exceeds the range of plain integers.

(3)
   A right shift by n bits is equivalent to division by ``pow(2, n)``.


Additional Methods on Float
---------------------------


The float type implements the :class:`numbers.Real` :term:`abstract base
class`. float also has the following additional methods.

.. method:: float.as_integer_ratio()

   Return a pair of integers whose ratio is exactly equal to the
   original float and with a positive denominator.  Raises
   :exc:`OverflowError` on infinities and a :exc:`ValueError` on
   NaNs.

.. method:: float.is_integer()

   Return ``True`` if the float instance is finite with integral value, and ``False`` otherwise::

      >>> (-2.0).is_integer()
      True
      >>> (3.2).is_integer()
      False

Two methods support conversion to and from hexadecimal strings.  
Since Python's floats are stored internally as binary numbers, 
converting a float to or from a *decimal* string usually involves a small rounding error.  
In contrast, hexadecimal strings allow exact representation and specification of floating-point numbers.  
This can be useful when debugging, and in numerical work:

   * float.hex()
   * float.fromhex
   
   .. code-block:: python
   
      >>> float.hex(3740.0)
      '0x1.d380000000000p+11'
      >>> float.fromhex('0x3.a7p10')
      3740.0


Iterator Types
--------------


Python supports a concept of iteration over containers. This is implemented using two distinct methods; these are used to allow user-defined classes to support iteration. Sequences, described below in more detail, always support the iteration methods.

One method needs to be defined for container objects to provide iteration support:

.. method:: container.__iter__()

   Return an iterator object. 
   The object is required to support the iterator protocol described below. 
   If a container supports different types of iteration, additional methods can be provided to specifically 
   request iterators for those iteration types. (An example of an object supporting multiple forms of iteration 
   would be a tree structure which supports both breadth-first and depth-first traversal.) 
   This method corresponds to the :class:`tp_iter` slot of the type structure for Python objects in the Python/C API.

The iterator objects themselves are required to support the following two methods, which together form the iterator protocol:

.. method:: iterator.__iter__()

   Return the iterator object itself. 
   This is required to allow both containers and iterators to be used with the ``for`` and ``in`` statements. 
   This method corresponds to the :class:`tp_iter` slot of the type structure for Python objects in the Python/C API.

.. method:: iterator.next()

   Return the next item from the container. 
   If there are no further items, raise the ``StopIteration`` exception. 
   This method corresponds to the :class:`tp_iternext` slot of the type structure for Python objects in the Python/C API.

Python defines several iterator objects to support iteration over general and specific sequence types, dictionaries, and other more specialized forms. 
The specific types are not important beyond their implementation of the iterator protocol.

The intention of the protocol is that once an iterator’s ``next()`` method raises ``StopIteration``, it will continue to do so on subsequent calls. 