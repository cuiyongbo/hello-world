*****************
sys Module Tricks
*****************

+---------------+------------------------------------------------------------------+
| Attribute     | Description                                                      |
+===============+==================================================================+
| argv          | command line arguments; argv[0] is the script pathname if known  |
+---------------+------------------------------------------------------------------+
| modules       | dictionary of loaded modules                                     |
+---------------+------------------------------------------------------------------+
| getsizeof()   | return the size of an object in bytes                            |
+---------------+------------------------------------------------------------------+
| getrefcount() | return the reference count for an object (plus one :-)           |
+---------------+------------------------------------------------------------------+
| gettrace()    | get the global debug tracing function                            |
+---------------+------------------------------------------------------------------+
| platform      | platform identifier                                              |
+---------------+------------------------------------------------------------------+
| executable    | absolute path of the executable binary of the Python interpreter |
+---------------+------------------------------------------------------------------+
| byteorder     | system byteorder                                                 |
+---------------+------------------------------------------------------------------+
   
.. code-block:: py
   
    >>> import sys
    >>> dir(sys)
    ['api_version', 'argv', 'builtin_module_names', 'byteorder', 'call_tracing', 'callstats', 'copyright', 'displayhook', 
    'dont_write_bytecode', 'exc_clear', 'exc_info', 'exc_type', 'excepthook', 'exec_prefix', 'executable', 'exit', 'flags', 
    'float_info', 'float_repr_style', 'getcheckinterval', 'getdefaultencoding', 'getdlopenflags', 'getfilesystemencoding', 
    'getprofile', 'getrecursionlimit', 'getrefcount', 'getsizeof', 'gettrace', 'hexversion', 'long_info', 'maxint', 'maxsize', 
    'maxunicode', 'meta_path', 'modules', 'path', 'path_hooks', 'path_importer_cache', 'platform', 'prefix', 'ps1', 'ps2', 'py3kwarning', 
    'pydebug', 'setcheckinterval', 'setdlopenflags', 'setprofile', 'setrecursionlimit', 'settrace', 'stderr', 'stdin', 'stdout', 
    'subversion', 'version', 'version_info', 'warnoptions']

.. function:: exc_info()

    This function returns a tuple of three values that give information about the
    exception that is currently being handled. The information returned is specific
    both to the current thread and to the current stack frame. If the current stack
    frame is not handling an exception, the information is taken from the calling
    stack frame, or its caller, and so on until a stack frame is found that is
    handling an exception. Here, "handling an exception" is defined as "executing
    or having executed an except clause." For any stack frame, only information
    about the most recently handled exception is accessible.

    If no exception is being handled anywhere on the stack, a tuple containing three
    ``None`` values is returned. Otherwise, the values returned are ``(type, value,
    traceback)``. Their meaning is: *type* gets the exception type of the exception
    being handled (a class object); *value* gets the exception parameter, which is
    always a class instance if the exception type is a class object); *traceback*
    gets a traceback object (see the Reference Manual) which encapsulates the call
    stack at the point where the exception originally occurred.

    If :func:`exc_clear` is called, this function will return three ``None`` values
    until either another exception is raised in the current thread or the execution
    stack returns to a frame where another exception is being handled.

    .. warning::

        Assigning the *traceback* return value to a local variable in a function that is
        handling an exception will cause a circular reference.  This will prevent
        anything referenced by a local variable in the same function or by the traceback
        from being garbage collected.  Since most functions don't need access to the
        traceback, the best solution is to use something like ``exctype, value =
        sys.exc_info()[:2]`` to extract only the exception type and value.  If you do
        need the traceback, make sure to delete it after use (best done with a
        :keyword:`try` ... :keyword:`finally` statement) or to call :func:`exc_info` in
        a function that does not itself handle an exception.

    .. note::

        Beginning with Python 2.2, such cycles are automatically reclaimed when garbage
        collection is enabled and they become unreachable, but it remains more efficient
        to avoid creating cycles.

.. function:: exc_clear()

    This function clears all information relating to the current or last exception
    that occurred in the current thread.  After calling this function,
    :func:`exc_info` will return three ``None`` values until another exception is
    raised in the current thread or the execution stack returns to a frame where
    another exception is being handled.

    This function is only needed in only a few obscure situations.  These include
    logging and error handling systems that report information on the last or
    current exception.  This function can also be used to try to free resources and
    trigger object finalization, though no guarantee is made as to what objects will
    be freed, if any.

    .. versionadded:: 2.3

    .. data:: exc_type
            exc_value
            exc_traceback

    .. deprecated:: 1.5
        Use :func:`exc_info` instead.

    Since they are global variables, they are not specific to the current thread, so
    their use is not safe in a multi-threaded program. When no exception is being
    handled, ``exc_type`` is set to ``None`` and the other two are undefined.
