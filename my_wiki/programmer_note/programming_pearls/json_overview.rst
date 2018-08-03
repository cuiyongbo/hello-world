*************
Json Overview
*************

.. sidebar:: JSON Structures

   |   object
   |      {}
   |      { members }
   |   members
   |      pair
   |      pair , members
   |   pair
   |      string : value
   |   array
   |      []
   |      [ elements ]
   |   elements
   |      value 
   |      value , elements
   |   value
   |      string
   |      number
   |      object
   |      array
   |      true
   |      false
   |      null
   |   string
   |      ""
   |      " chars "
   |   chars
   |      char
   |      char chars
   |   char
   |      any-Unicode-character-except
   |      -"-or-\-or-control-character
   |      \\"
   |      \\
   |      \/
   |      \b
   |      \f
   |      \n
   |      \r
   |      \t
   |      \u four-hex-digits
   |   number
   |      int
   |      int frac
   |      int exp
   |      int frac exp
   |      int
   |      digit
   |      digit1-9 digits 
   |      - digit
   |      - digit1-9 digits
   |   frac
   |      . digits
   |   exp
   |      e digits
   |   digits
   |      digit
   |      digit digits
   |   e
   |      e
   |      e+
   |      e-
   |      E
   |      E+
   |      E-

:abbr:`JSON (JavaScript Object Notation)` is a lightweight data-interchange format. 
It is easy for humans to read and write. It is easy for machines to parse and generate. 
It is based on a subset of the JavaScript Programming Language, **JSON is a text format** 
that is completely language independent but uses conventions that are familiar to programmers 
of the C-family of languages, including C, C++, C#, Java, JavaScript, Perl, Python, and many others. 
These properties make JSON an ideal data-interchange language.

JSON is built on two structures:

   * A collection of name/value pairs. In various languages, this is realized as 
     an object, record, struct, dictionary, hash table, keyed list, or associative array.

   * An ordered list of values. In most languages, this is realized as an array, vector, list, or sequence.

These are universal data structures. Virtually all modern programming languages support them in one form or another. 
It makes sense that a data format that is interchangeable with programming languages also be based on these structures.

.. image:: images/json_object.gif
.. image:: images/json_array.gif
.. image:: images/json_value.gif
.. image:: images/json_string.gif
.. image:: images/json_number.gif





