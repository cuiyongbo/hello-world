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

If it's a matter of cleanup that should be run regardless of success or failure, 
then you would do::

   try:
      do_some_stuff()
   finally:
      cleanup_stuff()

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
   
   with open("myfile.txt") as f:
       for line in f:
           print line,  