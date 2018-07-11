***************
Function Basics
***************

Defining Functions
==================

We can create a function that writes the Fibonacci series to an 
arbitrary boundary::

   def fib(n):
      """print a Fibonacci series up to n."""
      a, b = 0, 1
      while a<n :
         print a, 
         a, b = b, b+a

   >>> fib(2000)
   0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597

The keyword ``def`` introduces a function definition. It must be followed by 
the function name and the parenthesized list of formal parameters. The 
statements that form the body of the function start at the next line, 
and **MUST** be indented.

The first statement of the function body can optionally be a string literal; 
this string literal is the function’s documentation string, or **docstring**. 
it’s good practice to include docstrings in code that you write, so make a 
habit of it.

The execution of a function introduces a new symbol table used for the local 
variables of the function. More precisely, all variable assignments in a function 
store the value in the local symbol table; whereas variable references first look 
in the local symbol table, then in the local symbol tables of enclosing functions, 
then in the global symbol table, and finally in the table of built-in names. Thus, 
global variables cannot be directly assigned a value within a function (unless named 
in a ``global`` statement), although they may be referenced.

The actual parameters (arguments) to a function call are introduced in the local symbol 
table of the called function when it is called; thus, arguments are passed using call **by value** 
(where the value is always an object reference, not the value of the object). When a function calls 
another function, a new local symbol table is created for that call.

A function definition introduces the function name in the current symbol table. The value 
of the function name has a type that is recognized by the interpreter as a user-defined 
function. This value can be assigned to another name which can then also be used as a 
function. This serves as a general renaming mechanism::

   >>> fib
   <function fib at 0x02C69930>
   >>> f = fib
   >>> f(100)
   0 1 1 2 3 5 8 13 21 34 55 89

Coming from other languages, you might object that *fib* is not a function but a procedure 
since it doesn’t return a value. In fact, even functions without a ``return`` statement do 
return a value, albeit a rather boring one. This value is called ``None`` (it’s a built-in name).
Writing the value None is normally suppressed by the interpreter if it would be the only value 
written. You can see it if you really want to using ``print`` ::

   >>> fib(0)
   >>> print fib(0)
   None

The ``return`` statement returns with a value from a function. ``return`` without an expression 
argument returns ``None``. It is simple to write a function that returns a list of the numbers 
of the Fibonacci series, instead of printing it::

   def fib2(n):
      """Return a list containing the Fibonacci series up to n."""
      result = []
      a, b = 0, 1
      while a<n:
         result.append(a)
         a, b = b, b+a
      return result
   
   >>> f100 = fib2(100)
   >>> f100
   [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]


Default Argument Values
=======================

.. code-block:: python

   def ask_ok(prompt, retries=4, complaint="Yes or no, please!"):
      while True:
         ok = raw_input(prompt + " ")
         if ok.lower() in ('y', 'ye', 'yes'):
            return True
         elif ok.lower() in ('n', 'no', 'nop', 'nope'):
            return False
         else:
            retries = retries - 1
            if retries < 0:
               raise IOError('refused')
            print complaint   

This function can be called in several ways:

   - giving only the mandatory argument: ``ask_ok('Do you really want to quit?')``
   - giving one of the optional arguments: ``ask_ok('OK to overwrite the file?', 2)``
   - or even giving all arguments: ``ask_ok('OK to overwrite the file?', 2, 'Come on, only yes or no!')``

The default values are evaluated at the point of function definition in the defining scope, 
so that

.. code-block:: python

   i = 5
   def f(arg=i):
       print arg
   
   i = 6
   f()

will print 5.

**Important warning**: The default value is evaluated only once. This makes a difference when 
the default is a mutable object such as a list, dictionary, or instances of most classes. 
For example, the following function accumulates the arguments passed to it on subsequent 
calls::

   def f(a, L=[]):
      L.append(a)
      return L
   
   >>> f(1)
   [1]
   >>> f(2)
   [1, 2]
   >>> f(3)
   [1, 2, 3]


If you don't want the default to be shared between subsequent calls, you can write the function like
this instead::

   def f(a, L=None):
      if L is None:
         L = []
      L.append(a)
      return L
   
   >>> f(1)
   [1]
   >>> f(2)
   [2]
   >>> f(3)
   

Keyword Arguments
=================

Functions can also be called using keyword arguments of the form ``kwarg=value``. 
For instance, the following function:

   def parrot(voltage, state='a stiff', action='voom', type='Norwegian Blue'):
       print "-- This parrot wouldn't", action,
       print "if you put", voltage, "volts through it."
       print "-- Lovely plumage, the", type
       print "-- It's", state, "!"

accepts one mandatory argument (``voltage``) and three optional arguments 
(``state``, ``action``, and ``type``). This function can be called in any 
of the following ways::

   parrot(1000)                                          # 1 positional argument
   parrot(voltage=1000)                                  # 1 keyword argument
   parrot(voltage=1000000, action='VOOOOOM')             # 2 keyword arguments
   parrot(action='VOOOOOM', voltage=1000000)             # 2 keyword arguments
   parrot('a million', 'bereft of life', 'jump')         # 3 positional arguments
   parrot('a thousand', state='pushing up the daisies')  # 1 positional, 1 keyword

but all the following calls would be invalid::

   parrot()                     # required argument missing
   parrot(voltage=5.0, 'dead')  # non-keyword argument after a keyword argument
   parrot(110, voltage=220)     # duplicate value for the same argument
   parrot(actor='John Cleese')  # unknown keyword argument

In a function call, keyword arguments **MUST** follow positional arguments. 
All the keyword arguments passed must match one of the arguments accepted 
by the function (e.g. ``actor`` is not a valid argument for the ``parrot`` function), 
and their order is not important. 

When a final formal parameter of the form ``**name`` is present, it receives a dictionary 
containing all keyword arguments except for those corresponding to a formal parameter. 
This may be combined with a formal parameter of the form ``*name`` which receives a tuple 
containing the positional arguments beyond the formal parameter list. (``*name`` MUST occur 
before ``**name``.) For example, if we define a function like this::

   def cheeseshop(kind, *arguments, **keywords):
       print "-- Do you have any", kind, "?"
       print "-- I'm sorry, we're all out of", kind
       for arg in arguments:
           print arg
       print "-" * 40
       keys = sorted(keywords.keys())
       for kw in keys:
           print kw, ":", keywords[kw]

Make a call::

   >>> cheeseshop('chocolate', "strawbery", "apple", "pear",
   ... producer="sihua", address="china", date="2018")
   -- Do you have any chocolate ?
   -- I'm sorry, we're all out of chocolate
   strawbery
   apple
   pear
   ----------------------------------------
   address : china
   date : 2018
   producer : sihua

Note that the list of keyword argument names is created by sorting the result of the 
``keywords`` dictionary’s ``keys()`` method before printing its contents; if this is 
not done, the order in which the arguments are printed is undefined.


Arbitrary Argument Lists
========================

Finally, the least frequently used option is to specify that a function can be called with 
an arbitrary number of arguments. These arguments will be wrapped up in a tuple. Before 
the variable number of arguments, zero or more normal arguments may occur::

   def write_multiple_items(file, separator, *args):
       file.write(separator.join(args))


Unpacking Argument Lists
========================

The reverse situation occurs when the arguments are already in a list or tuple 
but need to be unpacked for a function call requiring separate positional arguments. 
For instance, the built-in ``range()`` function expects separate ``start`` and ``stop`` arguments. 
If they are not available separately, write the function call with the ``*``-operator to unpack the 
arguments out of a list or tuple::

   >>> range(3,6)
   [3, 4, 5]
   >>> arg=[3,6]
   >>> range(*arg)
   [3, 4, 5]

In the same fashion, dictionaries can deliver keyword arguments with the ``**``-operator::

   >>> def parrot(voltage, state='a stiff', action='voom'):
   ...     print "-- This parrot wouldn't", action,
   ...     print "if you put", voltage, "volts through it.",
   ...     print "E's", state, "!"
   ...
   >>> d = {"voltage": "four million", "state": "bleedin' demised", "action": "VOOM"}
   >>> parrot(**d)
   -- This parrot wouldn't VOOM if you put four million volts through it. E's bleedin' demised !


Lambda Expressions
==================

Small anonymous functions can be created with the ``lambda`` keyword. This function returns the sum 
of its two arguments: ``lambda a, b: a+b``. Lambda functions can be used wherever function objects 
are required. They are syntactically restricted to a single expression. Semantically, they are just 
syntactic sugar for a normal function definition. Like nested function definitions, lambda functions 
can reference variables from the containing scope::

   >>> def make_incrementor(n):
   ...     return lambda x: x + n
   ...
   >>> f = make_incrementor(42)
   >>> f(0)
   42
   >>> f(1)
   43

The above example uses a lambda expression to return a function. Another use is to pass a small function 
as an argument::

   >>> pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
   >>> pairs.sort(key=lambda pair: pair[1])
   >>> pairs
   [(4, 'four'), (1, 'one'), (3, 'three'), (2, 'two')]