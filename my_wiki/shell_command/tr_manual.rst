*********
tr Manual
*********

**DESCRIPTION**

   .. code-block:: sh

      tr [OPTION]... SET1 [SET2]

   Translate, squeeze, and/or delete characters from standard input, writing to standard output.

      .. option:: -c, -C, --complement
              
         use the complement of SET1

      .. option:: -d, --delete
         
         delete characters in SET1, do not translate

      .. option:: -s, --squeeze-repeats
              
         replace each sequence of a repeated character that is listed 
         in the last specified SET, with a single occurrence of that character.

       -t, --truncate-set1
              first truncate SET1 to length of SET2

   SETs are specified as strings of characters. Most represent themselves.  
   Interpreted sequences are::

      \NNN   character with octal value NNN (1 to 3 octal digits)
      \\     backslash
      \a     audible BEL
      \b     backspace
      \f     form feed
      \n     new line
      \r     return
      \t     horizontal tab
      \v     vertical tab
      [:alnum:] all letters and digits
      [:alpha:] all letters
      [:digit:] all digits
      [:xdigit:] all hexadecimal digits
      [:lower:] all lower case letters
      [:upper:] all upper case letters
      [:blank:] all horizontal whitespace
      [:space:] all horizontal or vertical whitespace

   Translation occurs if -d is not given and both SET1 and SET2 appear.  
   -t may be used only when translating. SET2 is extended to length of SET1 
   by repeating its last character as necessary. Excess characters of SET2 
   are ignored. -s uses the last specified SET, and occurs after translation or deletion.


.. code-block:: sh
   :caption: Examples
   
   $ echo "wwwwwwwwweeeeeeee" | tr -s "we"
   we
   $ echo "This is this" | tr " " "\n"
   This
   is
   this

