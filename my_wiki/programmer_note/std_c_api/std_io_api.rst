*************
Std C I/O API
*************

Input API
=========

**NAME**

   fgetc, fgets, getc, getchar, ungetc - input of characters and strings

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>

      int fgetc(FILE *stream);
      char *fgets(char *s, int size, FILE *stream);
      int getc(FILE *stream);
      int getchar(void);
      int ungetc(int c, FILE *stream);

      /*Windows implementation*/
      #define getc(_stream) fgetc(_stream)
      #define getchar() getc(stdin)

**DESCRIPTION**

   ``fgetc()`` reads the next character from stream and returns it as an
   unsigned char cast to an int, or ``EOF`` on end of file or error.

   ``getc()`` is equivalent to ``fgetc()`` except that it may be
   implemented as a macro which evaluates stream more than once.

   ``getchar()`` is equivalent to ``getc(stdin)``.

   fgets() reads in at most one less than size characters from stream and
   stores them into the buffer pointed to by *s*. Reading stops after an
   ``EOF`` or a newline. If a newline is read, it is stored into the buffer.
   A terminating null byte (``'\0'``) is stored after the last character in
   the buffer.

   ``ungetc()`` pushes *c* back to stream, cast to unsigned char, where it is
   available for subsequent read operations.  Pushed-back characters will
   be returned in reverse order; only one pushback is guaranteed. 
   (**you must not call ungetch() consecutively.**)

   Calls to the functions described here can be mixed with each other and
   with calls to other input functions from the stdio library for the same
   input stream.

   For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.

**RETURN VALUE**

   ``fgetc()``,  ``getc()`` and ``getchar()`` return the character read
   as an unsigned char cast to an int or ``EOF`` on end of file or error.

   ``fgets()`` returns *s* on success, and ``NULL`` on error or when end
   of file occurs while no characters have been read.

   ``ungetc()`` returns *c* on success, or ``EOF`` on error.

**ATTRIBUTES**

   For an explanation of the terms used in this section, see
   :manpage:`attributes(7)`.

   +--------------------------+---------------+---------+
   | Iterface                 | Atrribute     | Value   |
   +==========================+===============+=========+
   | fgetc(), fgets(), getc() | Thread safety | MT-Safe |
   | getchar(), ungetc()      |               |         |
   +--------------------------+---------------+---------+

**SEE ALSO**

   read(2), write(2), ferror(3), fgetwc(3), fgetws(3), fopen(3), fread(3),
   fseek(3),  getline(3), gets(3), getwchar(3), puts(3), scanf(3),
   ungetwc(3), unlocked_stdio(3), feature_test_macros(7)


Input format conversion
=======================

   See :doc:`scanf_info`
   

Output API
==========

**NAME**
   
   fputc, fputs, putc, putchar, puts - output of characters and strings

**SYNOPSIS**
   
   .. code-block:: c

      #include <stdio.h>

      int fputc(int c, FILE *stream);
      int putc(int c, FILE *stream);
      int putchar(int c);
      int puts(const char *s);
      int fputs(const char *s, FILE *stream);

      /*Windows implementation*/
      #define putchar(_c) putc((_c),stdout)

**DESCRIPTION**

   ``fputc()`` writes the character *c*, cast to an unsigned char, to *stream*.

   ``fputs()`` writes the string s to stream, without its terminating
   null byte (``'\0'``).

   ``putc()`` is equivalent to ``fputc()`` except that it may be implemented
   as a macro which evaluates stream more than once.

   ``putchar(c)`` is equivalent to ``putc(c, stdout)``.

   ``puts()`` writes the string *s* and a trailing newline to stdout.

   Calls to the functions described here can be mixed with each other and
   with calls to other output functions from the stdio library for the
   same output stream.

   For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.


**RETURN VALUE**

   ``fputc()``, ``putc()`` and ``putchar()`` return the character written
   as an unsigned char cast to an int or ``EOF`` on error.

   ``puts()`` and ``fputs()`` return a nonnegative number on success,
   or ``EOF`` on error.


**ATTRIBUTES**

   For an explanation of the terms used in this section, see
   :manpage:`attributes(7)`.

   +--------------------------+---------------+---------+
   | Iterface                 | Atrribute     | Value   |
   +==========================+===============+=========+
   | fputc(), fputs(), putc() | Thread safety | MT-Safe |
   | putchar(), puts()        |               |         |
   +--------------------------+---------------+---------+

**SEE ALSO**

   write(2), ferror(3), fgets(3), fopen(3), fputwc(3), fputws(3),
   fseek(3), fwrite(3), putwchar(3), scanf(3), unlocked_stdio(3)

