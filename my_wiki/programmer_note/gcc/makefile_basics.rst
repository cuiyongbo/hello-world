***************
Makefile Basics
***************

Symbols
=======

#. constants in Makefile
   
   +-----------+-------------------------------------------+
   | Constants | Meaning                                   |
   +===========+===========================================+
   | $@        | Name of current target                    |
   +-----------+-------------------------------------------+
   | $<        | Name of the first prerequisite in depency |
   +-----------+-------------------------------------------+
   | $^        | Names of all prerequisites in depency     |
   +-----------+-------------------------------------------+

#. Compiler flags in make
   
   +----------+---------------------------------------------------------+
   | Flags    | Meaning                                                 |
   +==========+=========================================================+
   | CFLAGS   | Extra flags to give to the C compiler.                  |
   +----------+---------------------------------------------------------+
   | CXXFLAGS | Extra flags to give to the C++ compiler.                |
   +----------+---------------------------------------------------------+
   | CPPFLAGS | Extra flags to give to the C preprocessor               |
   |          | and programs that use it (the C and Fortran compilers). |
   +----------+---------------------------------------------------------+

