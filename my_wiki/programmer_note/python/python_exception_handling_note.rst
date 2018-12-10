*************************
Python Exception Handling
*************************

.. code-block:: py
   :caption: Syntax 1

   try:
      You do your operations here;
      ......................
   except ExceptionI:
      If there is ExceptionI, then execute this block.
      ......................
   except (ExceptionII, ExceptionIII, ExceptionIV):
      If there is ExceptionII, ExceptionIII or ExceptionIV, then execute this block.
      ......................
   else:
      If there is no exception then execute this block. 
   finally:
      cleanup_stuff() # execute always no matter whether there is an exception or not

.. code-block:: py
   :caption: Example 1

   #!/usr/bin/python

   try:
      fh = open("testfile", "w")
      fh.write("This is my test file for exception handling!!")
   except IOError:
      print "Error: can\'t find file or read data"
   else:
      print "Written content in the file successfully"
      fh.close()

.. code-block:: py
   :caption: Example 2 - use the Exception object

   (x,y) = (5,0)
   try:
     z = x/y
   except ZeroDivisionError as e:
     z = e # representation: "<exceptions.ZeroDivisionError instance at 0x817426c>"
   print z # output: "integer division or modulo by zero"

.. code-block:: py
   :caption: Example 3

   import sys
   try:
     untrusted.execute()
   except: # catch *all* exceptions
     e = sys.exc_info()[0]
     write_to_page( "<p>Error: %s</p>" % e )

.. code-block:: py
   :caption: Example 4

   #!/usr/bin/env python
   import sys, subprocess

   if __name__ == "__main__":
       if(len(sys.argv) < 2):
           print "Usage: %s file1 file2 ...", sys.argv[0]
           exit(1)
   
       for i in range(1, len(sys.argv)):
           try:
               s = subprocess.check_output(["lsof", sys.argv[i]], stderr=subprocess.STDOUT)
               print s
           except subprocess.CalledProcessError as e:
               print e.returncode, ": ", e.output
               print "%s: not in use" % sys.argv[i]

.. code-block:: py
   :caption: More examples

   import sys

   try:
       f = open('myfile.txt')
       s = f.readline()
       i = int(s.strip())
   except IOError as e:
       print "I/O error({0}): {1}".format(e.errno, e.strerror)
   except ValueError:
       print "Could not convert data to an integer."
   except:
       print "Unexpected error:", sys.exc_info()[0]
       raise 

   for arg in sys.argv[1:]:
       try:
           f = open(arg, 'r')
       except IOError:
           print 'cannot open', arg
       else:
           print arg, 'has', len(f.readlines()), 'lines'
           f.close()
   
   >>> try:
   ...     raise Exception('spam', 'eggs')
   ... except Exception as inst:
   ...     print type(inst)     # the exception instance
   ...     print inst.args      # arguments stored in .args
   ...     print inst           # __str__ allows args to be printed directly
   ...     x, y = inst.args
   ...     print 'x =', x
   ...     print 'y =', y
   ...
   <type 'exceptions.Exception'>
   ('spam', 'eggs')
   ('spam', 'eggs')
   x = spam
   y = eggs

   >>> def f():
   ...     1/0
   ... 
   >>> try:
   ...     f()
   ... except ZeroDivisionError as detail:
   ...     print "Run-time error: ", detail
   ... 
   Run-time error:  integer division or modulo by zero
   
   >>> try:
   ...     raise NameError('HiThere')
   ... except NameError:
   ...     print 'An exception flew by!'
   ...     raise
   ...
   An exception flew by!
   Traceback (most recent call last):
     File "<stdin>", line 2, in <module>
   NameError: HiThere

   >>> class CSError(Exception):
   ...     def __init__(self, value):
   ...             self.value = value
   ...     def __str__(self):
   ...             return repr(self.value)
   ... 
   >>> try:
   ...     raise CSError(2*2)
   ... except CSError as e:
   ...     print "My exception occurred, value: ", e.value
   ... 
   My exception occurred, value:  4
   >>> raise CSError("Opps")
   Traceback (most recent call last):
     File "<stdin>", line 1, in <module>
   __main__.CSError: 'Opps'

   class Error(Exception):
       """Base class for exceptions in this module."""
       pass
   
   class InputError(Error):
       """Exception raised for errors in the input.
   
       Attributes:
           expr -- input expression in which the error occurred
           msg  -- explanation of the error
       """
   
       def __init__(self, expr, msg):
           self.expr = expr
           self.msg = msg
   
   class TransitionError(Error):
       """Raised when an operation attempts a state transition that's not
       allowed.
   
       Attributes:
           prev -- state at beginning of transition
           next -- attempted new state
           msg  -- explanation of why the specific transition is not allowed
       """
   
       def __init__(self, prev, next, msg):
           self.prev = prev
           self.next = next
           self.msg = msg
   
   >>> def divide(x, y):
   ...     try:
   ...             result=x/y
   ...     except ZeroDivisionError:
   ...             print "division by zero"
   ...     else:
   ...             print "result: ", result
   ...     finally:
   ...             print "Goodbye"
   ... 
   >>> divide(2,1)
   result:  2
   Goodbye
   >>> divide(2,0)
   division by zero
   Goodbye
   >>> divide("2","0")
   Goodbye
   Traceback (most recent call last):
     File "<stdin>", line 1, in <module>
     File "<stdin>", line 3, in divide
   TypeError: unsupported operand type(s) for /: 'str' and 'str'
   

When the ``with`` statement is executed, Python evaluates the expression, 
calls the ``__enter__`` method on the resulting value (which is called a “context guard”), 
and assigns whatever ``__enter__`` returns to the variable given by ``as``. Python will then 
execute the code body, and no matter what happens in that code, call the guard 
object’s ``__exit__`` method.

As an extra bonus, the ``__exit__`` method can look at the exception, 
if any, and suppress it or act on it as necessary. To suppress the exception, 
just return a true value. For example, the following ``__exit__`` method 
swallows any ``TypeError``, but lets all other exceptions through::

    def __exit__(self, type, value, traceback):
        return isinstance(value, TypeError)

In Python 2.5, the file object has been equipped with ``__enter__`` and ``__exit__`` methods; 
the former simply returns the file object itself, and the latter closes the file::

    >>> f = open("x.txt")
    >>> f
    <open file 'x.txt', mode 'r' at 0x00AE82F0>
    >>> f.__enter__()
    <open file 'x.txt', mode 'r' at 0x00AE82F0>
    >>> f.read(1)
    'X'
    >>> f.__exit__(None, None, None)
    >>> f.read(1)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    ValueError: I/O operation on closed file

so to open a file, process its contents, and make sure to close it, 
you can simply do::

   with open("myfile.txt") as f:
       for line in f:
           print line,  

