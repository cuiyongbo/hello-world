********************
Python argparse note
********************




**EXAMPLES**

.. code-block:: py

   #!/usr/bin/env python
   import argparse
   parser = argparse.ArgumentParser()
   parser.add_argument("square", type = int, help = "display the square of the input number") 
   parser.add_argument("-v", "--verbosity", action = "store_true", help = "increase output verbosity")
   args = parser.parse_args()
   answer = args.square**2
   if args.verbosity:
       print "%d^2 = %d" % (args.square, answer)
   else:
       print answer

.. code-block:: py

   #!/usr/bin/env python
   import argparse
   parser = argparse.ArgumentParser()
   parser.add_argument("square", type = int, help = "display the square of the input number") 
   parser.add_argument("-v", "--verbosity", type = int, choices = [0, 1, 2], help = "increase output verbosity")
   args = parser.parse_args()
   answer = args.square**2
   if args.verbosity == 1:
       print "%d^2 = %d" % (args.square, answer)
   if args.verbosity == 2:
       print "the square of %d equals %d" % (args.square, answer)
   else:
       print answer
   
.. code-block:: py

   #!/usr/bin/env python
   import argparse
   parser = argparse.ArgumentParser()
   parser.add_argument("square", type = int, help = "display the square of the input number") 
   parser.add_argument("-v", "--verbosity", action="count", default = 0,
                                        help = "increase output verbosity")
   args = parser.parse_args()
   answer = args.square**2
   if args.verbosity >= 2:
       print "the square of %d equals %d" % (args.square, answer)
   elif args.verbosity >= 1:
       print "%d^2 = %d" % (args.square, answer)
   else:
       print answer

.. code-block:: py

   #!/usr/bin/env python
   import argparse
   parser = argparse.ArgumentParser()
   parser.add_argument("x", type = int, help = "the base") 
   parser.add_argument("y", type = int, help = "the exponent") 
   parser.add_argument("-v", "--verbosity", action="count", default = 0)
   args = parser.parse_args()
   answer = args.x ** args.y
   if args.verbosity >= 2:
       print "Running %s" % __file__
       print "%d to the power %d equals %d" % (args.x, args.y, answer)
   elif args.verbosity >= 1:
       print "%d^%d = %d" % (args.x, args.y, answer)
   else:
       print answer

.. code-block:: py

   #!/usr/bin/env python
   import argparse
   parser = argparse.ArgumentParser(description = "calculate X to the power of Y")
   group = parser.add_mutually_exclusive_group()
   group.add_argument("-v", "--verbosity", action="store_true")
   group.add_argument("-q", "--quite", action="store_true")
   parser.add_argument("x", type = int, help = "the base") 
   parser.add_argument("y", type = int, help = "the exponent") 
   args = parser.parse_args()
   answer = args.x ** args.y
   if args.quite:
       print answer
   elif args.verbosity:
       print "%d to the power of %d equals %d" % (args.x, args.y, answer)
   else:
       print "%d^%d = %d" % (args.x, args.y, answer)

