***********************
C++ operator precedence
***********************

.. code-block:: none

    +------------+-----------------+---------------------------------------------+---------------+
    | Precedence | Operator        | Name                                        | Associativity |
    +============+=================+=============================================+===============+
    | 1          | ::              | Scope resolution                            |               |
    +------------+-----------------+---------------------------------------------+ Left-to-right +
    | 2          | a++ a--         | Postfix increment / decrement               |               |
    |            | type() type{}   | Functional cast                             |               |
    |            | a()             | Function call                               |               |
    |            | a[]             | Subscript                                   |               |
    |            | . ->            | Member access                               |               |
    +------------+-----------------+---------------------------------------------+---------------+
    | 3          | ++a --a         | Prefix increment / decrement                | Right-to-left |
    |            | +a -a           | Unary plus / minus                          |               |
    |            | ! ~             | Logical NOT and bitwise NOT                 |               |
    |            | (type)          | C-style cast                                |               |
    |            | *a              | Deference                                   |               |
    |            | &a              | Address-of                                  |               |
    |            | sizeof          | Size-of                                     |               |
    |            | new new[]       | Dynamic memory allocation                   |               |
    |            | delete delete[] | Dynamic memory deallocation                 |               |
    +------------+-----------------+---------------------------------------------+---------------+
    | 4          | .* ->*          | Pointer-to-member                           |               |
    +------------+-----------------+---------------------------------------------+ Left-to-right +
    | 5          | a*b a/b a%b     | Multiplication, division, and remainder     |               |
    +------------+-----------------+---------------------------------------------+               +
    | 6          | a+b a-b         | addition, subtraction                       |               |
    +------------+-----------------+---------------------------------------------+               +
    | 7          | << >>           | Bitwise left-shift and right-shift          |               |
    +------------+-----------------+---------------------------------------------+               +
    | 8          | <=>             | Three-way comparison operator (since c++20) |               |
    +------------+-----------------+---------------------------------------------+               +
    | 9          | < <=            |                                             |               |
    |            | > >=            |                                             |               |
    +------------+-----------------+---------------------------------------------+               +
    | 10         | == !=           |                                             |               |
    +------------+-----------------+---------------------------------------------+               +
    | 11         | &               | Bitwise AND                                 |               |
    +------------+-----------------+---------------------------------------------+               +
    | 12         | ^               | Bitwise XOR (exclusive OR)                  |               |
    +------------+-----------------+---------------------------------------------+               +
    | 13         | |               | Bitwise OR                                  |               |
    +------------+-----------------+---------------------------------------------+               +
    | 14         | &&              | Logical AND                                 |               |
    +------------+-----------------+---------------------------------------------+               +
    | 15         | ||              | Logical OR                                  |               |
    +------------+-----------------+---------------------------------------------+---------------+
    | 16         | a?b:c           | Ternary conditional                         | Right-to-left |
    |            | throw           | Throw operator                              |               |
    |            | =               | Directional assignment                      |               |
    |            | += -=           |                                             |               |
    |            | *= /= %=        |                                             |               |
    |            | <<= >>=         |                                             |               |
    |            | &= |= ^=        |                                             |               |
    +------------+-----------------+---------------------------------------------+---------------+
    | 17         | ,               | Comma                                       | Left-to-right |
    +------------+-----------------+---------------------------------------------+---------------+
   

#. Calling Conventions
   
    A calling convention specifies precisely **how the stack should be maintained**, 
    and whether the caller or callee is responsible for popping the arguments off the stack.

    For example, in the ``stdcall`` calling convention the callee is responsible for restoring 
    the stack pointer before the function returns. In the ``cdecl`` calling convention, 
    the caller is responsible.

    It should be obvious that mixing calling conventions is bad! If the caller is using ``stdcall``, 
    it's expecting the callee to maintain the stack. If the callee is using ``cdecl``, it's expecting 
    the caller to maintain the stack. End result: no one is maintaining the stack! 