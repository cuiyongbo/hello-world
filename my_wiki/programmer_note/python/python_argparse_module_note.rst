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

.. code-block:: py

   #!/usr/bin/env python
   import argparse, sys
   
   parser = argparse.ArgumentParser(description="Management of TrafficDataUpdater")
   subparsers = parser.add_subparsers(dest='subcommand_name')
   subparsers.add_parser("start")
   subparsers.add_parser("stop")
   subparsers.add_parser("reload")
   
   try:
       args = parser.parse_args()
   except:
       parser.print_usage()
       sys.exit(1)
   
   if args.subcommand_name == "start":
       pass
   elif args.subcommand_name == "stop":
       pass
   elif args.subcommand_name == "reload":
       pass

.. function:: ArgumentParser.add_mutually_exclusive_group(required=False)

   Create a mutually exclusive group. argparse will make sure that only one 
   of the arguments in the mutually exclusive group was present on the 
   command line::

      >>> parser = argparse.ArgumentParser(prog='PROG')
      >>> group = parser.add_mutually_exclusive_group()
      >>> group.add_argument('--foo', action='store_true')
      >>> group.add_argument('--bar', action='store_false')
      >>> parser.parse_args(['--foo'])
      Namespace(bar=True, foo=True)
      >>> parser.parse_args(['--bar'])
      Namespace(bar=False, foo=False)
      >>> parser.parse_args(['--foo', '--bar'])
      usage: PROG [-h] [--foo | --bar]
      PROG: error: argument --bar: not allowed with argument --foo

   The ``add_mutually_exclusive_group()`` method also accepts a required argument, 
   to indicate that at least one of the mutually exclusive arguments is required:

      >>> parser = argparse.ArgumentParser(prog='PROG')
      >>> group = parser.add_mutually_exclusive_group(required=True)
      >>> group.add_argument('--foo', action='store_true')
      >>> group.add_argument('--bar', action='store_false')
      >>> parser.parse_args([])
      usage: PROG [-h] (--foo | --bar)
      PROG: error: one of the arguments --foo --bar is required

.. function:: ArgumentParser.add_subparsers([title][, description][, prog][, parser_class][, action][, option_string][, dest][, help][, metavar])

   Many programs split up their functionality into a number of sub-commands, 
   for example, the git program can invoke sub-commands like git checkout, git push, 
   and git commit. Splitting up functionality this way can be a particularly good idea 
   when a program performs several different functions which require different kinds 
   of command-line arguments. ArgumentParser supports the creation of such sub-commands 
   with the ``add_subparsers()`` method, which is normally called with no arguments and 
   returns a special action object. This object has a single method, ``add_parser()``, 
   which takes a command name and any ArgumentParser constructor arguments, and returns 
   an ArgumentParser object that can be modified as usual.
