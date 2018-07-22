***************
Makefile Basics
***************

**For me, everything is over.**

#. constants in Makefile
   
   +-----------+---------------------------------------------------------+
   | Constants | Meaning                                                 |
   +===========+=========================================================+
   | $@        | Name of current target                                  |
   +-----------+---------------------------------------------------------+
   | $<        | Name of the first prerequisite in depency               |
   +-----------+---------------------------------------------------------+
   | $^        | Names of all prerequisites in depency                   |
   +-----------+---------------------------------------------------------+
   | $?        | Names of all prerequisites newer than target in depency |
   +-----------+---------------------------------------------------------+
   | $+        | Same as '$^', but removes the repeated ones             |
   +-----------+---------------------------------------------------------+

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

#. Change directory
  
   .. code-block:: sh

      # Wrong
      $ make test
      cd ~
      pwd   
      /Users/cherry/Development-note/scaffold
   
      # Right
      $ make test
      cd ~; pwd   
      /Users/cherry
   
      # Also right, but there must be some insight, 
      # because cd ~ return 0 on success.
      $ make test
      cd ~ && pwd 
      /Users/cherry

#. Variable definition and assignment
   
   .. code-block:: sh

      # := makes x's definition invisible to the previously definied y. 
      y := $(x) bar
      x := foo
      
      variable_1:
          @echo $(y)  
        
      q = xxx  
      p = $(q) bar
      q = foo
      variable_2:
          @echo $(p)

      # ?= assigns the value to the variable if the variable is undefined.
      k ?= xxx 
      j = ddd 
      j ?= xxx 
      variable_3:
          @echo $(k)
          @echo $(j)

      # += appends the value to the variable.
      x += bar
      y := $(y) xxx
      variable_4:
          @echo $(x)
          @echo $(y)

      OBJS_1 = *.o
      OBJS_2 = $(wildcard *.o)
      variable_5:
          @echo $(OBJS_1)
          @echo $(OBJS_2)

   Output::

      $ make variable_1
      bar
      $ make variable_2
      foo bar
      $ make variable_3
      xxx
      ddd
      $ make variable_4
      foo bar
      bar xxx
      $ make variable_5
      echo *.o # OBJS_1 won't expand.
      main.o math.o util.o
      echo main.o math.o util.o 
      main.o math.o util.o

#. Function call
   
   .. code-block:: sh
      :caption: Syntax

      $(<function> <arguments>)
      # or
      ${<function> <arguments>}

      # e.g.
      $(subst a,b,$(x))

   .. code-block:: sh
      :caption: Hot functions

      $(subst <from>, <to>, <text>)
      $(patsubst <pat>, <replacement>, <text>)
      $(dir, <names...>)
      $(notdir, <names...>)
      $(suffix <names...>)
      $(basename <names...>)
      $(addsuffix <names...>)
      $(addprefix <names...>)
      $(join <list1>, <list2>)

      # e.g.
      SRCS := $(wildcard *.cpp)
      names := /Users/cherry/Development-note/my_wiki/index.rst hello.c makefile
      names_2 := $(basename $(names))
      scripts := $(shell echo *.py *.sh)
      func:
          @echo $(subst world, make, hello world)
          @echo $(patsubst %.cpp, %.o, $(SRCS))
          @echo $(dir $(names))
          @echo $(notdir $(names))
          @echo $(suffix $(names))    
          @echo $(basename $(names))
          @echo $(addsuffix .o, $(names_2))
          @echo $(addprefix /home/, $(names_2))
          @echo $(join hello world, .c .o)
          @echo $(scripts)

   Output::
      
      $ make func
      hello make
      comp_test.o
      /Users/cherry/Development-note/my_wiki/ ./ ./
      index.rst hello.c makefile
      .rst .c
      /Users/cherry/Development-note/my_wiki/index hello makefile
      /Users/cherry/Development-note/my_wiki/index.o hello.o makefile.o
      /home//Users/cherry/Development-note/my_wiki/index /home/hello /home/makefile
      hello.c world.o
      unittest_demo.py test.sh

#. Implicit rules
   
   .. code-block:: sh

      %.o: %.c
         $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
