************************************
gcc - GNU project C and C++ compiler
************************************

**SYNOPSIS**

    .. code-block:: sh

        gcc [-c|-S|-E] [-std=standard]
             [-g] [-pg] [-Olevel]
             [-Wwarn...] [-Wpedantic]
             [-Idir...] [-Ldir...]
             [-Dmacro[=defn]...] [-Umacro]
             [-foption...] [-mmachine-option...]
             [-o outfile] [@file] infile...


**DESCRIPTION**

    When you invoke GCC, it normally does **preprocessing, compilation, assembly and linking.**
    The **overall options** allow you to stop this process at an intermediate stage.
    For example, the -c option says not to run the linker. Then the output consists of object
    files output by the assembler.

**HOT OPTIONS**

.. option:: -c

    Compile or assemble the source files, but do not link.
    The linking stage simply is not done. The ultimate output
    is in the form of an object file for each source file.

    By default, the object file name for a source file is
    made by replacing the suffix .c, .i, .s, etc., with .o.

.. option:: -S

    Stop after the stage of compilation proper; do not assemble.
    The output is in the form of an assembler code file for each
    non-assembler input file specified.

    By default, the assembler file name for a source file is made
    by replacing the suffix .c, .i, etc., with .s.

.. option:: -E

    Stop after the preprocessing stage; do not run the compiler proper.
    The output is in the form of preprocessed source code, which is sent
    to the standard output.

.. option:: -o file

    Place output in file file. This applies to whatever sort of output
    is being produced, whether it be an executable file, an object file,
    an assembler file or preprocessed C code.

.. option:: -static

    Prevent gcc from using shared libraries, force compile to link with static library(*.a).
    By default, gcc link with shared object (*.so).

.. option:: -shared

    Produce a shared object which can then be linked with other objects to form an executable.
    Not all systems support this option. For predictable results, you must also specify the same
    set of options used for compilation (-fpic, -fPIC, or model suboptions) when you specify this
    linker option.

.. option:: -fpic

    Generate position-independent code (PIC) suitable for use in a shared library,
    if supported for the target machine. Such code accesses all constant addresses
    through a global offset table (GOT). The dynamic loader resolves the GOT entries
    when the program starts (the dynamic loader is not part of GCC; it is part of the
    operating system). If the GOT size for the linked executable exceeds a machine-specific
    maximum size, you get an error message from the linker indicating that -fpic does not work;
    in that case, recompile with -fPIC instead.

.. option:: -fPIC

    If supported for the target machine, emit PIC, suitable for dynamic linking and avoiding any
    limit on the size of the global offset table.  This option makes a difference on the m68k,
    PowerPC and SPARC.

.. option:: -fpie, -fPIE

    These options are similar to -fpic and -fPIC, but generated PIC can be only linked into executables.
    Usually these options are used when -pie GCC option is used during linking.

.. option:: -g

    Produce debugging information in the OS's native format (stabs, COFF, XCOFF, or DWARF 2).
    GDB can work with this debugging information.

.. option:: -Wall

    Turns on all optional warnings which are desirable for normal code.

.. option:: -Wextra

    This enables some extra warning flags that are not enabled by -Wall.

.. option:: -Werror

    Make all warnings into hard errors. Source code which triggers warnings will be rejected.

.. option::  -Wpedantic, -pedantic

    Issue all the warnings demanded by strict ISO C and ISO C++; reject all programs that use
    forbidden extensions, and some other programs that do not follow ISO C and ISO C++.

.. option:: -pedantic-errors

    Give an error whenever the base standard (see -Wpedantic) requires a diagnostic.

.. option:: -w

    Suppress all warnings, including those which GNU CPP issues by default.

.. option::  -include file

   Process file as if ``#include "file"`` appeared as
   the first line of the primary source file. However,
   the first directory searched for file is the preprocessor's
   working directory instead of the directory containing the
   main source file. If not found there, it is searched for in
   the remainder of the ``#include "..."`` search chain as normal.

   If multiple -include options are given, the files are included
   in the order they appear on the command line.

.. option:: -imacros file

   Exactly like -include, except that any output produced by scanning
   *file* is thrown away.  Macros it defines remain defined. This allows
   you to acquire all the macros from a header without also processing
   its declarations.

   All files specified by -imacros are processed before all files specified
   by -include.

.. option:: -isystem dir

   Search *dir* for header files, after all directories specified by -I but
   before the standard system directories. Mark it as a system directory,
   so that it gets the same special treatment as is applied to the standard
   system directories. If dir begins with "=", then the "=" will be replaced
   by the sysroot prefix; see --sysroot and -isysroot.

.. option:: --sysroot=dir

   Use *dir* as the logical root directory for headers and libraries. For example,
   if the compiler normally searches for headers in :file:`/usr/include` and libraries
   in :file:`/usr/lib`, it instead searches :file:`dir/usr/include` and :file:`dir/usr/lib`.

   If you use both this option and the -isysroot option, then the --sysroot option applies to
   libraries, but the -isysroot option applies to header files.

   The GNU linker (beginning with version 2.16) has the necessary support for this option.
   f your linker does not support this option, the header file aspect of --sysroot still
   works, but the library aspect does not.

.. option:: -isysroot dir

   This option is like the --sysroot option, but applies only to header files (except for
   Darwin targets, where it applies to both header files and libraries).

.. option:: -I dir

   Add the directory *dir* to the list of directories to be searched for header files.
   Directories named by -I are searched before the standard system include directories.
   If the directory *dir* is a standard system include directory, the option is ignored
   to ensure that the default search order for system directories and the special
   treatment of system headers are not defeated.

.. option:: -Ldir

   Add directory *dir* to the list of directories to be searched for -l.

.. option:: -llibrary, -l library

   Search the library named *library* when linking. (The second alternative with the library
   as a separate argument is only for POSIX compliance and is not recommended.)

   It makes a difference where in the command you write this option; the linker searches and
   processes libraries and object files in the order they are specified. Thus, ``foo.o -lz bar.o``
   searches library *z* after file *foo.o* but before *bar.o*. If *bar.o* refers to functions
   in *z*, those functions may not be loaded.

   The linker searches a standard list of directories for the library, which is actually a file
   named ``liblibrary.a``. The linker then uses this file as if it had been specified precisely
   by name. The directories searched include several standard system directories plus any that
   you specify with -L.

   Normally the files found this way are library files---archive files whose members are object
   files. The linker handles an archive file by scanning through it for members which define
   symbols that have so far been referenced but not defined.  But if the file that is found is
   an ordinary object file, it is linked in the usual fashion. The only difference between using
   an -l option and specifying a file name is that -l surrounds library with lib and .a and
   searches several directories.

.. option:: -Dname, -D name=definition

   With the first format, predefine *name* as a macro, with definition 1.

   As with the second format, The contents of definition are tokenized
   and processed as if they appeared during translation phase three in
   a ``#define`` directive. In particular, the *definition* will be
   truncated by embedded newline characters.

   If you are invoking the preprocessor from a shell or shell-like
   program you may need to use the shell's quoting syntax to protect
   characters such as spaces that have a meaning in the shell syntax.

   If you wish to define a function-like macro on the command line,
   write its argument list with surrounding parentheses before the
   equals sign (if any). Parentheses are meaningful to most shells,
   so you will need to quote the option.
   With sh and csh, ``-D'name(args...)=definition'`` works.

   -D and -U options are processed in the order they are given on
   the command line.  All -imacros file and -include file options
   are processed after all -D and -U options.

.. option:: -U name

   Cancel any previous definition of name, either built in or provided with a -D option.

.. option:: -M

   Instead of outputting the result of preprocessing, output a rule suitable for make
   describing the dependencies of the main source file. The preprocessor outputs one
   make rule containing the object file name for that source file, a colon, and the
   names of all the included files, including those coming from -include or -imacros
   command-line options.

.. option:: -MM

   -MM Like -M but do not mention header files that are found in system header directories,
   nor header files that are included, directly or indirectly, from such a header.

.. option:: -MF file

   When used with -M or -MM, specifies a file to write the dependencies to.
   If no -MF switch is given the preprocessor sends the rules to the same
   place it would have sent preprocessed output.

.. option:: -MD

   -MD is equivalent to ``-M -MF file``, except that -E is not implied.

.. option:: -MMD

   Like -MD except mention only user header files, not system header files.

.. option:: -MG

   In conjunction with an option such as -M requesting dependency generation,
   -MG assumes missing header files are generated files and adds them to the
   dependency list without raising an error. The dependency filename is taken
   directly from the ``#include`` directive without prepending any path.

   -MG also suppresses preprocessed output, as a missing header file renders
   this useless.

   This feature is used in automatic updating of makefiles.

.. option:: -MP

   This option instructs CPP to add a phony target for each dependency other
   than the main file, causing each to depend on nothing. These dummy rules
   work around errors make gives if you remove header files without updating
   then :file:`Makefile` to match.

   This is typical output::

      test.o: test.c test.h
      test.h:

.. option:: -MT target

   Change the target of the rule emitted by dependency generation.
   By default CPP takes the name of the main input file, deletes
   any directory components and any file suffix such as .c, and
   appends the platform's usual object suffix. The result is the
   target.

   For example, ``-MT '$(objpfx)foo.o'`` might give::

      $(objpfx)foo.o: foo.c

.. option:: -MQ target

   Same as -MT, but it quotes any characters which are special to Make.

.. option:: -std=standard, -ansi

   Specify the standard to which the code should conform.
   Currently CPP knows about C and C++ standards; others
   may be added in the future.

   Usual standards::

      "c90"
         The -ansi option is equivalent to -std=c90.

      "gnu++98"
         The same as -std=c++98 plus GNU extensions.
         This is the default for C++ code.

      c++11

.. option:: -rdynamic

   Pass the flag ``-export-dynamic`` to the ELF linker, on targets that support it.
   This instructs the linker to add all symbols, not only used ones, to the dynamic
   symbol table. This option is needed for some uses of "dlopen" or to allow obtaining
   backtraces from within a program.

.. option:: -s

   Remove all symbol table and relocation information from the executable.

.. option:: -pthread / -pthreads

   Adds support for multithreading with the pthreads library. This option
   sets flags for both the preprocessor and linker.

.. option:: -Olevel

   set code optimization level, -O2 is usual.
   Note: don't turn on this optimization when you are programming,
   debugging, or with limited resources such as on embedded devices.

.. option:: -pipe

   Use pipes rather than temporary files for communication between the various stages of
   compilation. This fails to work on some systems where the assembler is unable to read
   from a pipe; but the GNU assembler has no trouble.

   **Note:** this option can speed up compilation when building a huge project, but will
   consume more memory in return.

.. option:: -fkeep-inline-functions

   In C, emit "static" functions that are declared "inline" into the object file, even if the
   function has been inlined into all of its callers. This switch does not affect functions using
   the "extern inline" extension in GNU C90. In C++, emit any and all inline functions into the object file.

.. option:: -fpermissive

   Downgrade some diagnostics about nonconformant code from errors to warnings.
   Thus, using ``-fpermissive`` allows some nonconforming code to compile.


**TRICKS**

#. Set -std default to c99

    For bash only, add ``alias gcc='gcc -Wall -std=c99'`` to **.bashrc** in HOME directory.
    To check the shell you currently use, type ``echo $SHELL``.

#. Using g++ with template class

    **Solution one:** It's possible to put all the code in the class declaration, in essence making all member functions inline.
    Inline functions don't cause conflicts with multiple definitions when linking. This is the solution used in the ``std::vector.``

    **Solution two:** when the declaration and definition are separated in two files, just #include the source code/implementation/definition
    of the templated class. although some compiler may complain about multiple definitions of the same functions.

#. check the builtin library search paths

    .. code-block:: sh

        $ gcc --print-search-dirs
        install: /usr/lib/gcc/x86_64-linux-gnu/4.8/
        programs: =/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/4.8/:
        : ...
        :/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../:/lib/:/usr/lib/

#. disable certain compiler warnings

    .. code-block:: c

        #if defined(__clang__)
        // disable warning about "this != NULL"
        #  pragma clang diagnostic ignored "-Wtautological-undefined-compare"
        // disabled warning "delete called on non-final 'XXX' that has virtual functions but non-virtual destructor [-Wdelete-non-virtual-dtor]"
        #  pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
        #elif defined(__GNUC__)
        #  pragma GCC diagnostic ignored "-Wunknown-pragmas"
        #endif
        #if defined(_MSC_VER)
        #  pragma warning(disable: 4068)
        #endif

#. pass macro to make

    Solution: ``make CFLAGS=-DNDEBUG test``

#. linux system header and library search path environment variables

    .. code-block:: sh

        export THIRD_PARTY_REPO=/home/cuiyb/workSpace/projects/third-party-repo
        export LIBEVENT_DIR=$THIRD_PARTY_REPO/libevent

        export C_INCLUDE_PATH=$C_INCLUDE_PATH:$LIBEVENT_DIR/include
        export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$THIRD_PARTY_REPO:$LIBEVENT_DIR/include
        export LIBRARY_PATH=$LIBRARY_PATH:$THIRD_PARTY_REPO:$LIBEVENT_DIR/lib
