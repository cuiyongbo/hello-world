**********
Gdb Tricks
**********

#. select executable file
   
   .. code-block:: sh

      file executableName

   .. note:: 

      :command:`file` without arguments discard symbol table
      of current executable.


#. set / show args
   
   Lauch debugging with multi-arguments: ``gdb --args executable args``.

   Show the arguments to give your program when it is started: ``show args``.

   ``set args argumens`` Specify the *arguments* to be used the next time
   your program is run. If ``set args`` has no *arguments*, run executes your
   program with no arguments. Once you have run your program with arguments,
   using ``set args`` before the next run is the only way to run it again
   without arguments.

   .. code-block:: sh

      (gdb) show convenience # inspect current environment set
      $__ = 4
      $_ = (int32_t *) 0x7fff5fbffa00
      $bpnum = 1
      $_regex = <internal function _regex>
      $_streq = <internal function _streq>
      $_strlen = <internal function _strlen>
      $_memeq = <internal function _memeq>
      $_any_caller_matches = <internal function _any_caller_matches>
      $_any_caller_is = <internal function _any_caller_is>
      $_caller_matches = <internal function _caller_matches>
      $_caller_is = <internal function _caller_is>
      $_as_string = <internal function _as_string>
      $_inferior = 1
      $_isvoid = <internal function _isvoid>
      $_gthread = 3
      $_thread = 3
      $_probe_arg11 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg10 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg9 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg8 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg7 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg6 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg5 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg4 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg3 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg2 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg1 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_arg0 = <error: No probe at PC 0x0000000100000f1a>
      $_probe_argc = <error: No probe at PC 0x0000000100000f1a>
      $_siginfo = void
      $_exception = <error: not stopped at a C++ exception catchpoint>
      $_sdata = void


#. Launch gdb without front materials
   
   .. code-block:: sh

      gdb --silent


#. Execute shell command
   
   .. code-block:: sh

      shell command args

#. show fields of a struct.
 
   .. code-block:: sh
      :caption: Solution

      (gdb) help ptype
      Print definition of type TYPE.
      Usage: ptype[/FLAGS] TYPE | EXPRESSION
      Argument may be any type (for example a type name defined by typedef,
      or "struct STRUCT-TAG" or "class CLASS-NAME" or "union UNION-TAG"
      or "enum ENUM-TAG") or an expression.
      The selected stack frame's lexical context is used to look up the name.
      Contrary to "whatis", "ptype" always unrolls any typedefs.
   
      Available FLAGS are:
        /r    print in "raw" form; do not substitute typedefs
        /m    do not print methods defined in a class
        /M    print methods defined in a class
        /t    do not print typedefs defined in a class
        /T    print typedefs defined in a class
   
      (gdb) ptype object
      type = struct {
          json_t json;
          hashtable_t hashtable;
          int visited;
      } *
   
      (gdb) print object->json
      $3 = {type = JSON_OBJECT, refcount = 1}
      (gdb) ptype json_t
      type = struct json_t {
          json_type type;
          size_t refcount;
      }

#. Force to call a function or return from a function.
   
   .. code-block:: sh

      (gdb) help return
      Make selected stack frame return to its caller.
      Control remains in the debugger, but when you continue
      execution will resume in the frame above the one now selected.
      If an argument is given, it is an expression for the value to return.
   
      (gdb) help call
      Call a function in the program.
      The argument is the function name and arguments, in the notation of the
      current working language.  The result is printed and saved in the value
      history, if it is not void.


#. print and x command
   
   .. code-block:: sh

      (gdb) help print
      Print value of expression EXP.
      Variables accessible are those of the lexical environment of the selected
      stack frame, plus all those whose scope is global or an entire file.
      
      $NUM gets previous value number NUM.  $ and $$ are the last two values.
      $$NUM refers to NUM'th value back from the last one.
      Names starting with $ refer to registers (with the values they would have
      if the program were to return to the stack frame now selected, restoring
      all registers saved by frames farther in) or else to debugger
      "convenience" variables (any such name not a known register).
      Use assignment expressions to give values to convenience variables.
      
      {TYPE}ADREXP refers to a datum of data type TYPE, located at address ADREXP.
      @ is a binary operator for treating consecutive data objects
      anywhere in memory as an array.  FOO@NUM gives an array whose first
      element is FOO, whose second element is stored in the space following
      where FOO is stored, etc.  FOO must be an expression whose value
      resides in memory.
      
      EXP may be preceded with /FMT, where FMT is a format letter
      but no count or size letter (see "x" command).

      print can also midify value of a variable.

      (gdb) help x
      Examine memory: x/FMT ADDRESS.
      ADDRESS is an expression for the memory address to examine.
      FMT is a repeat count followed by a format letter and a size letter.
      Format letters are o(octal), x(hex), d(decimal), u(unsigned decimal),
        t(binary), f(float), a(address), i(instruction), c(char), s(string)
        and z(hex, zero padded on the left).
      Size letters are b(byte), h(halfword, 2 bytes), w(word, 4 bytes), 
      g(giant, 8 bytes).The specified number of objects of the specified 
      size are printed according to the format.  If a negative number is 
      specified, memory is examined backward from the address.
      
      Defaults for format and size letters are those previously used.
      Default count is 1.  Default address is following last thing printed
      with this command or "print".

   .. code-block:: sh

      (gdb) print /x input
      $1 = 0x4d2
      (gdb) p a@4
      $4 = {{0, 1, 2, 3, 4}, {32767, -1685651237, 1511422820, 1606416928, 32767}, {-1042042315, 32767, 0, 0, 1}, {0, 1606417272, 32767, 0, 0}}
      (gdb) p {int}a@4
      $5 = {0, 1, 2, 3}
      (gdb) p {int}a@5
      $6 = {0, 1, 2, 3, 4}
      (gdb) x/5dw a # display 5 words in decimal from a
      0x7fff5fbff9f0:   0  1  2  3
      0x7fff5fbffa00:   4

      (gdb) l
      8     scanf("%d", &input);
      9     printf("You input %d.\n", input);
      10 
      11    int a[5];
      12    int i=0;
      13    for(; i<5; i++)
      14       a[i] = i;
      15 
      16    return 0;
      17 }

      (gdb) print input
      $7 = 1234
      (gdb) print input= 9
      $8 = 9
      (gdb) print input
      $9 = 9
      
      # view struct
         
      (gdb) ptype p
      type = struct Node {
          int data;
          struct Node *next;
      } *
      (gdb) print p
      $6 = (Node *) 0x100200240
      (gdb) print {Node}p
      $7 = {data = 35, next = 0x0}

      # view simple array

      (gdb) l
      1  #include <stdio.h>
      2  #include <stdlib.h>
      3  #include <string.h>
      4  
      5  int main()
      6  {
      7      const int n = 5;
      8      int b[] = {1,2,3,4};
      9      int* a = (int*)malloc(sizeof(int)*n);
      10     int i;
      11     for(i=0; i<n; i++)
      12         a[i] = i;
      13     free(a);
      14     return 0;
      15 }
      16 
      (gdb) b 13
      Breakpoint 1 at 0x4005eb: file test.c, line 13.
      (gdb) r
      13     free(a);
      (gdb) ptype a
      type = int *
      (gdb) pt b
      type = int [4]
      (gdb) p b
      $2 = {1, 2, 3, 4}
      (gdb) p a
      $3 = (int *) 0x602010
      (gdb) p *a@n
      $4 = {0, 1, 2, 3, 4}

      # view struct array
      
      (gdb) l
      5  typedef struct Node
      6  {
      7      int key;
      8      int value;
      9  } Node;
      10 
      11 
      12 int main()
      13 {
      14     const int n = 5;
      15     Node* nodes = (Node*)malloc(n*sizeof(Node));
      16     int i;
      17     for(i=0; i<n; i++)
      18     {
      19         nodes[i].key = i;
      20         nodes[i].value = i*10;
      21     }
      22     free(nodes);
      23     return 0;
      24 }
      (gdb) b 22
      Breakpoint 1 at 0x4005f3: file test.c, line 22.
      (gdb) r
      22     free(nodes);
      (gdb) p {Node}nodes@5
      $2 = {{key = 0, value = 0}, {key = 1, value = 10}, {key = 2, value = 20}, {key = 3, value = 30}, {key = 4, value = 40}}
      (gdb) set $i=0
      (gdb) p nodes[$i++].key
      $3 = 0
      (gdb) 
      $4 = 1
      (gdb) 
      $5 = 2
      (gdb) 
      $6 = 3
      (gdb) 
      $7 = 4


#. list command
   
   .. code-block:: sh

      (gdb) help list
      List specified function or line.
      With no argument, lists ten more lines after or around previous listing.
      "list -" lists the ten lines before a previous ten-line listing.
      "list +" lists the ten lines after a previous ten-line listing.
      One argument specifies a line, and ten lines are listed around that line.
      Two arguments with comma between specify starting and ending lines to list.
      Lines can be specified in these ways:
        LINENUM, to list around that line in current file,
        FILE:LINENUM, to list around that line in that file,
        FUNCTION, to list around beginning of that function,
        FILE:FUNCTION, to distinguish among like-named static functions.
        *ADDRESS, to list around the line containing that address.
      With two args, if one is empty, it stands for ten lines away from
      the other arg.
   
      By default, when a single location is given, display ten lines.
      This can be changed using "set listsize", and the current value
      can be shown using "show listsize".

      (gdb) show listsize
      Number of source lines gdb will list by default is 10.
      (gdb) set listsize 5
      (gdb) show listsize
      Number of source lines gdb will list by default is 5.
      (gdb) l 5
      3  
      4  int main()
      5  {
      6     int input = 0;
      7     printf("Enter an integer: ");
