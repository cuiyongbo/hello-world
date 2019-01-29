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

.. function:: ArgumentParser.add_argument(name or flags...[, action][, nargs][, const][, default][, type][, choices][, required][, help][, metavar][, dest])

    Define how a single command-line argument should be parsed. 
    Each parameter has its own more detailed description below, 
    but in short they are:

    * name or flags - Either a name or a list of option strings.
    * action - The basic type of action to be taken when this argument is encountered at the command line.
    * nargs - The number of command-line arguments that should be consumed.
    * const - A constant value required by some action and nargs selections.
    * default - The value produced if the argument is absent from the command line.
    * type - The type to which the command-line argument should be converted.
    * choices - A container of the allowable values for the argument.
    * required - Whether or not the command-line option may be omitted (optionals only).
    * help - A brief description of what the argument does.
    * metavar - A name for the argument in usage messages.
    * dest - The name of the attribute to be added to the object returned by ``parse_args()``.

.. function:: ArgumentParser.parse_args(args=None, namespace=None)

    Convert argument strings to objects and assign them as attributes of the namespace. 
    Return the populated namespace. Previous calls to ``add_argument()`` determine exactly 
    what objects are created and how they are assigned.

    * args - List of strings to parse. The default is taken from ``sys.argv``.
    * namespace - An object to take the attributes. The default is a new empty Namespace object.

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
    Description of parameters:

    * title - title for the sub-parser group in help output; by default “subcommands” if description is provided, otherwise uses title for positional arguments
    * description - description for the sub-parser group in help output, by default None
    * prog - usage information that will be displayed with sub-command help, by default the name of the program and any positional arguments before the subparser argument
    * parser_class - class which will be used to create sub-parser instances, by default the class of the current parser (e.g. ArgumentParser)
    * action - the basic type of action to be taken when this argument is encountered at the command line
    * dest - name of the attribute under which sub-command name will be stored; by default None and no value is stored
    * help - help for sub-parser group in help output, by default None
    * metavar - string presenting available sub-commands in help; by default it is None and presents sub-commands in form {cmd1, cmd2, ..}

#. get/set/ default argument
   
    * ArgumentParser.get_default(dest)
    * ArgumentParser.set_defaults(\*\*kwargs)
    
    Most of the time, the attributes of the object returned by ``parse_args()`` 
    will be fully determined by inspecting the command-line arguments and the argument actions. 
    ``set_defaults()`` allows some additional attributes that are determined without any inspection 
    of the command line to be added:

        >>> parser = argparse.ArgumentParser()
        >>> parser.add_argument('foo', type=int)
        >>> parser.set_defaults(bar=42, baz='badger')
        >>> parser.parse_args(['736'])
        Namespace(bar=42, baz='badger', foo=736)
    
    **Note** that parser-level defaults always override argument-level defaults::

        >>> parser.add_argument("--light", default="LED")
        >>> parser.set_defaults(light="incandescent light buble")
        >>> parser.parse_args([])
        Namespace(light='incandescent light buble')

    Parser-level defaults can be particularly useful when working with multiple parsers. 
    See the ``add_subparsers()`` method for an example of this type.

    Get the default value for a namespace attribute, as set by either ``add_argument()`` or by ``set_defaults()``:

        >>> parser = argparse.ArgumentParser()
        >>> parser.add_argument('--foo', default='badger')
        >>> parser.get_default('foo')
        'badger'

#. mutually group to add default argument
   

#. custom action

.. code-block:: py

   class ClientAction(argparse.Action):
    def __init__(self, option_strings, dest, nargs=None, **kwargs):
        super(ClientAction, self).__init__(option_strings, dest, nargs=None, **kwargs)

    def __call__(self, parser, namespace, values, option_string=None):
        print("%r %r %r" % (namespace, values, option_string))
        setattr(namespace, self.dest, 'hello')

    if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Get NavInfoIds in a route')
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-i', '--intranet', action='store_true', help="send request to <%s> " % g_server_url_dict['intranet'])
    group.add_argument('-o', '--internet', action='store_true', help="send request to <%s> " % g_server_url_dict['internet'])
    group.add_argument('-l', '--local', action='store_true', help="send request to <%s> " % g_server_url_dict['local'])
    group.add_argument('-n', '--ncbeta', action='store_true', help="send request to <%s> " % g_server_url_dict['ncbeta'])

    #group.add_argument('-i', '--intranet', action=ClientAction, dest='server_type', help="send request to <%s> " % g_server_url_dict['intranet'])
    #group.add_argument('-o', '--internet', action=ClientAction, dest='server_type', help="send request to <%s> " % g_server_url_dict['internet'])
    #group.add_argument('-l', '--local', action=ClientAction, dest='server_type', help="send request to <%s> " % g_server_url_dict['local'])
    #group.add_argument('-n', '--ncbeta', action=ClientAction, dest='server_type', help="send request to <%s> " % g_server_url_dict['ncbeta'])
    #group.set_defaults(server_type='intranet')
    #args = parser.parse_args(['-o',  '(11635660,4001864)', '(11635660,4001864)'])
    #sys.exit(0)

    parser.add_argument('start', help='route start point, e.g. (11635660,4001864)')
    parser.add_argument('end', help='route end point, e.g. (11636104,4000891)')

    args = parser.parse_args()
    #print(args)

    if args.intranet:
        server_type = 'intranet'
    elif args.internet:
        server_type = 'internet'
    elif args.local:
        server_type = 'local'
    elif args.ncbeta:
        server_type = 'ncbeta'