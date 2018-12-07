**************
String Literal
**************

**Syntax**

.. code-block:: none

   " (unescaped_character|escaped_character)* " (1)   
   L " (unescaped_character|escaped_character)* "  (2)   
   u8 " (unescaped_character|escaped_character)* " (3)   (since C++11)
   u " (unescaped_character|escaped_character)* "  (4)   (since C++11)
   U " (unescaped_character|escaped_character)* "  (5)   (since C++11)
   prefix(optional) R "delimiter( raw_characters )delimiter"   (6)   (since C++11)

**Explanation**

.. code-block:: none

   unescaped_character  -  Any valid character except the double-quote ", backslash \, or new-line character
   escaped_character -  See escape sequences
   prefix   -  One of L, u8, u, U
   delimiter   -  A character sequence made of any source character but parentheses, backslash and spaces (can be empty, and at most 16 characters long)
   raw_characters -  Any character sequence, except that it must not contain the closing sequence )delimiter"


1) Narrow multibyte string literal. The type of an unprefixed string literal is ``const char[]``.

2) Wide string literal. The type of a ``L"..."`` string literal is ``const wchar_t[]``.

3) UTF-8 encoded string literal. The type of a ``u8"..."`` string literal is ``const char[]``.

4) UTF-16 encoded string literal. The type of a ``u"..."`` string literal is ``const char16_t[]``.

5) UTF-32 encoded string literal. The type of a ``U"..."`` string literal is ``const char32_t[]``.

6) Raw string literal. Used to avoid escaping of any character. Anything between the delimiters 
   becomes part of the string. *prefix*, if present, has the same meaning as described above.

**Examples**

.. code-block:: cpp

   #include <iostream>
    
   char array1[] = "Foo" "bar";
   // same as
   char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };
    
   const char* s1 = R"foo(
   Hello World
   )foo";
   //same as
   const char* s2 = "\nHello\nWorld\n";
    
   int main()
   {
       std::cout << sizeof("") << ": " << "" << '\n';
       std::cout << sizeof("12345") << ": " << "12345" << '\n';
       std::cout << sizeof(array1) << ": " << array1 << '\n';
       std::cout << sizeof(array2) << ": " << array2 << '\n';
    
       std::cout << s1;
       std::cout << s2;
   }  

#. Difference between ``char* s`` and ``char s[]``
   
   The difference here is that ``char *s = "Hello world";``
   will place ``"Hello world"`` in the read-only parts of the memory, 
   and making s a pointer to that makes any writing operation on this
   memory illegal, generating ``SIGSEGV`` signal.

   While ``char s[] = "Hello world";`` puts the literal string in read-only memory and 
   copies the string to newly allocated memory on the stack. Thus making ``s[0] = 'J';`` legal.

   .. code-block:: c

      #include <stdio.h>
      int main()
      {
          char* s1 = "Hello world";
          char s2[] = "Hello world";
          printf("s1: %p, s2: %p\n", s1, s2);
      
          s1[0] = "s";
          
          return 0;
      }
      
      // Output
      // $ ./a.out 
      // s1: 0x4006a4, s2: 0x7fffaa8fdf90
      // Segmentation fault (core dumped)
      