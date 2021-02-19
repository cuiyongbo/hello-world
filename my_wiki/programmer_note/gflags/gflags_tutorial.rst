How To Use gflags
=================

.. contents::
    :local:

Define: Defining Flags
----------------------

Defining a flag is easy: just use the appropriate macro for the type you want the flag to be, as defined at the bottom of ``gflags/gflags.h``,
for instance:

.. code-block:: cpp


    #include <gflags/gflags.h>

    DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
    DEFINE_string(languages, "english,french,german",
                    "comma-separated list of languages to offer in the 'lang' menu");

``DEFINE_bool`` defines a boolean flag. Here are the types supported:

* DEFINE_bool: boolean
* DEFINE_int32: 32-bit integer
* DEFINE_int64: 64-bit integer
* DEFINE_uint64: unsigned 64-bit integer
* DEFINE_double: double
* DEFINE_string: C++ string

All DEFINE macros take the same three arguments: the name of the flag, its default value, and a 'help' string that describes its use. 
The 'help' string is displayed when the user runs the application with the ``--help`` flag.

You can define a flag in any source-code file in your executable. Only define a flag once! 
If you want to access a flag in more than one source file, DEFINE it in one file, and DECLARE it in the others. 
Even better, DEFINE it in foo.cc and DECLARE it in foo.h; then everyone who ``#includes "foo.h"`` can use the flag.

Accessing the Flag
------------------

All defined flags are available to the program as just a normal variable, with the prefix ``FLAGS_`` prepended. 
In the above example, the macros define two variables, ``FLAGS_big_menu`` (a bool), and ``FLAGS_languages`` (a C++ string).

DECLARE: Using the Flag in a Different File
-------------------------------------------

Accessing a flag in the manner of the previous section only works if the flag was DEFINE-ed at the top of the file. 
If it wasn't, you'll get an 'unknown variable' error.

The DECLARE_type macro is available when you want to use a flag that's defined in another file. 
For instance, if I were writing bar.cc but wanted to access the big_menu, flag, 
I would put this near the top of bar.cc: ``DECLARE_bool(big_menu);``

This is functionally equivalent to saying ``extern FLAGS_big_menu``.

RegisterFlagValidator: Sanity-checking Flag Values
--------------------------------------------------

After DEFINE-ing a flag, you may optionally register a validator function with the flag. If you do this, 
after the flag is parsed from the commandline, and whenever its value is changed via a call to ``SetCommandLineOption``, 
the validator function is called with the new value as an argument. The validator function should return true if the flag value is valid, 
and false otherwise. If the function returns false for the new setting of the flag, the flag will retain its current value. 
If it returns false for the default value, ``ParseCommandLineFlags`` will die.

Here is an example use of this functionality:

.. code-block:: cpp

    static bool ValidatePort(const char* flagname, int32 value) {
    if (value > 0 && value < 32768)   // value is ok
        return true;
    printf("Invalid value for --%s: %d\n", flagname, (int)value);
    return false;
    }
    DEFINE_int32(port, 0, "What port to listen on");
    DEFINE_validator(port, &ValidatePort);

By doing the registration at global initialization time (right after the ``DEFINE_int32``), 
we ensure that the registration happens before the commandline is parsed at the beginning of ``main()``.

Putting It Together: How to Set Up Flags
----------------------------------------

The final piece is the one that tells the executable to process the commandline flags, and set the ``FLAGS_*`` variables to the appropriate, 
non-default value based on what is seen on the commandline. This is equivalent to the ``getopt()`` call in the getopt library, but has much less overhead to use. 
In fact, it's just a single function call: ``gflags::ParseCommandLineFlags(&argc, &argv, true);``

Usually, this code is at the beginning of ``main()``. ``argc`` and ``argv`` are exactly as passed in to ``main()``. 
This routine might modify them, which is why pointers to them are passed in.

The last argument is called "remove_flags". If true, then ``ParseCommandLineFlags`` removes the flags and their arguments from argv, 
and modifies ``argc`` appropriately. In this case, after the function call, ``argv`` will hold only commandline arguments, and not commandline flags.

If, on the other hand, remove_flags is false, then ``ParseCommandLineFlags`` will leave ``argc`` unchanged, but will rearrange the arguments in ``argv`` 
so that the flags are all at the beginning. For example, if the input is ``/bin/foo arg1 -q arg2`` (which is legal but weird), 
the function will rearrange argv so it reads ``/bin/foo arg1 -q arg2``. In this case, ``ParseCommandLineFlags`` returns the index into ``argv`` 
that holds the first commandline argument: that is, the index past the last flag. (In this example, it would return 2, since ``argv[2]`` points to arg1.)

Changing the Default Flag Value
-------------------------------

Sometimes a flag is defined in a library, and you want to change its default value in one application but not others. 
It's simple to do this: just assign a new value to the flag in ``main()``, before calling ``ParseCommandLineFlags()``:

.. code-block:: cpp

    DECLARE_bool(lib_verbose);   // mylib has a lib_verbose flag, default is false
    int main(int argc, char** argv) {
        FLAGS_lib_verbose = true;  // in my app, I want a verbose lib by default
        ParseCommandLineFlags(...);
    }

For this application, users can still set the flag value on the commandline, but if they do not, the flag's value will default to true.

Other API
---------

.. code-block:: cpp

    // Set the "usage" message for this program.  For example:
    //   string usage("This program does nothing.  Sample usage:\n");
    //   usage += argv[0] + " <uselessarg1> <uselessarg2>";
    //   SetUsageMessage(usage);
    // Do not include commandline flags in the usage: we do that for you!
    // Thread-hostile; meant to be called before any threads are spawned.
    extern GFLAGS_DLL_DECL void SetUsageMessage(const std::string& usage);

    // Sets the version string, which is emitted with --version.
    // For instance: SetVersionString("1.3");
    // Thread-hostile; meant to be called before any threads are spawned.
    extern GFLAGS_DLL_DECL void SetVersionString(const std::string& version);

    // Looks for flags in argv and parses them.  Rearranges argv to put
    // flags first, or removes them entirely if remove_flags is true.
    // If a flag is defined more than once in the command line or flag
    // file, the last definition is used.  Returns the index (into argv)
    // of the first non-flag argument.
    // See top-of-file for more details on this function.
    #ifndef SWIG   // In swig, use ParseCommandLineFlagsScript() instead.
    extern GFLAGS_DLL_DECL uint32 ParseCommandLineFlags(int *argc, char*** argv, bool remove_flags);
    #endif

Reference
---------

.. rubric:: Footnotes

.. [#] `How To Use gflags <https://gflags.github.io/gflags/>`_