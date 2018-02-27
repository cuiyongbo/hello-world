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
| ``x or y``  | if x is false, then y, else x        | (1)   |
+-------------+--------------------------------------+-------+
| ``x and y`` | if x is false, then x, else y        | (2)   |
+-------------+--------------------------------------+-------+
| ``not x``   | if x is false, then True, else False | (3)   |
+-------------+--------------------------------------+-------+


Notes:

   1. This is a short-circuit operator, so it only evaluates the second argument if the first one is false.
   2. This is a short-circuit operator, so it only evaluates the second argument if the first one is true.
   3. ``not`` has a lower priority than non-Boolean operators, so ``not a == b`` is interpreted as ``not (a == b)``, and ``a == not b`` is a syntax error.


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

All built-in numeric types support the following operations. See The power operator and later sections for the operators’ priorities.


.. note::

   * ``sys.maxint`` is always set to the maximum plain integer value for the current platform, the minimum value is ``-sys.maxint - 1``.
   * information about the precision and internal representation of floating point numbers for the machine on which your program is running is available in ``sys.float_info``.
   * The constructors ``int(), long(), float(), and complex()`` can be used to produce numbers of a specific type.