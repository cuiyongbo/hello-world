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
   except ExceptionII:
      If there is ExceptionII, then execute this block.
      ......................
   except ExceptionIII, ExceptionIV:
      If there is ExceptionIII or ExceptionIV, then execute this block.
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
