******************
C/C++ Macro Note
******************

#. Predefined Macros

    .. code-block:: c++
        :caption: Codes taken from Jansson

        #define failhdr fprintf(stderr, "%s:%d: ", __FILE__, __LINE__)

#. Variadic Macro

    Variadic macros are function-like macros that contain a variable number of arguments.
   
    To use variadic macros, the ellipsis ``...`` may be specified as the final formal argument
    in a macro definition, and the replacement identifier ``__VA_ARGS__`` may be used in the
    definition to insert the extra arguments. ``__VA_ARGS__`` is replaced by all of the arguments
    that match the ellipsis, including commas between them.
   
    The C Standard specifies that at least one argument must be passed to the ellipsis, to ensure
    that the macro does not resolve to an expression with a trailing comma. The VC++ implementation
    will suppress a trailing comma if no arguments are passed to the ellipsis.

    .. code-block:: c++

        #define eprintf(format, …) fprintf (stderr, format, __VA_ARGS__)
        #define MyLoger(format, ...) fprintf(stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__)