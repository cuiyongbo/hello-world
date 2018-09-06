*****************
Control Overflows
*****************


``if`` Statements
==================

Perhaps the most well-known statement type is the if statement. For example::

   >>> x = int(input("Please enter an integer: "))
   Please enter an integer: 42
   >>> if x < 0:
   ...     x = 0
   ...     print('Negative changed to zero')
   ... elif x == 0:
   ...     print('Zero')
   ... elif x == 1:
   ...     print('Single')
   ... else:
   ...     print('More')   


``for`` Statements
==================

The ``for`` statement in Python differs a bit from what you may be used to in C or Pascal.
Rather than always iterating over an arithmetic progression of numbers (like in Pascal),
or giving the user the ability to define both the iteration step and halting condition (as C),
Python’s ``for`` statement iterates over the items of any sequence (a list or a string), 
in the order that they appear in the sequence. For example (no pun intended)::
   
   >>> # Measure some strings:
   ... words = ['cat', 'window', 'defenestrate']
   >>> for w in words:
   ...     print(w, len(w))
   ...
   cat 3
   window 6
   defenestrate 12
   
If you need to modify the sequence you are iterating over while inside the loop (for example
to duplicate selected items), it is recommended that you first make a copy. Iterating over a
sequence does not implicitly make a copy. The slice notation makes this especially
convenient::

   >>> for w in words[:]:  # Loop over a slice copy of the entire list.
   ...     if len(w) > 6:
   ...         words.insert(0, w)
   ...
   >>> words
   ['defenestrate', 'cat', 'window', 'defenestrate']

With ``for w in words:``, the example would attempt to create an infinite list, inserting ``defenestrate``
over and over again.

If you do need to iterate over a sequence of numbers, the built-in function ``range()`` comes in handy.
It generates arithmetic progressions::

   >>> for i in range(5):
   ...     print(i)
   ...
   0
   1
   2
   3
   4


``while`` Statement
===================

.. code-block:: python

   while condition:
      # do something


``break`` and ``continue`` Statements, and ``else`` Clauses on Loops
====================================================================

The ``break`` statement, like in C, breaks out of the innermost enclosing ``for`` or ``while`` loop.

Loop statements may have an ``else`` clause; it is executed when the loop terminates through exhaustion
of the list (with ``for``) or when the condition becomes false (with ``while``), but not when the loop is
terminated by a ``break`` statement. This is exemplified by the following loop, which searches for prime
numbers::

   >>> for n in range(2, 10):
   ...     for x in range(2, n):
   ...         if n % x == 0:
   ...             print(n, 'equals', x, '*', n//x)
   ...             break
   ...     else:
   ...         # loop fell through without finding a factor
   ...         print(n, 'is a prime number')
   ...

(Yes, this is the correct code. Look closely: the ``else`` clause belongs to the ``for`` loop,
not the ``if`` statement.)


``pass`` Statements
===================

The ``pass`` statement does nothing. It can be used when a statement is required syntactically
but the program requires no action. For example::

   >>> while True:
   ...     pass  # Busy-wait for keyboard interrupt (Ctrl+C)

Another usage is to create an empty class. For example::

   >>> class EmptyClass:
   ...     pass
