*************
Std C I/O API
*************

.. contents::
   :local:


Input API
=========

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

   ``fgets()`` reads in at most one less than *size* characters from *stream* 
   and stores them into the buffer pointed to by *s*. Reading stops after an
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

   +---------------+---------+
   | Atrribute     | Value   |
   +===============+=========+
   | Thread safety | MT-Safe |
   |               |         |
   +---------------+---------+


Input format conversion
=======================

   See :doc:`scanf_info`
   

Output API
==========

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

   ``puts()`` writes the string *s* and a trailing newline to ``stdout``.

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

   +---------------+---------+
   | Atrribute     | Value   |
   +===============+=========+
   | Thread safety | MT-Safe |
   |               |         |
   +---------------+---------+


Buffer Control
==============

.. code-block:: c++

   #include <stdio.h>

   int setvbuf( std::FILE* stream, char* buffer, int mode, std::size_t size );

Changes the the buffering mode of the given file stream *stream* as indicated by 
the argument *mode*. In addition,

   * If *buffer* is a null pointer, resizes the internal buffer to *size*.

   * If buffer is not a null pointer, instructs the *stream* to use the 
     user-provided buffer of size *size* beginning at *buffer*. 

The *stream* must be closed (with fclose) before the lifetime of the array pointed to by *buffer* ends. 
The contents of the array after a successful call to *setvbuf* are indeterminate and any attempt to use 
it is undefined behavior.

*mode* can be one of the following values:

   +--------+----------------+
   | _IOFBF | full buffering |
   +--------+----------------+
   | _IOLBF | line buffering |
   +--------+----------------+
   | _IONBF | no buffering   |
   +--------+----------------+

**Return value**

​  0​ on success or nonzero on failure.

**Notes**

This function may only be used after *stream* has been associated with an open file, 
but before any other operation (other than a failed call to ``std::setbuf/std::setvbuf``).

Not all *size* bytes will necessarily be used for buffering: the actual buffer size is usually 
rounded down to a multiple of 2, a multiple of page size, etc.

On many implementations, line buffering is only available for terminal input streams.

A common error is setting the buffer of *stdin* or *stdout* to an array whose lifetime ends 
before the program terminates::

   FILE * open_data(void)
   {
       FILE    *fp;
       char    databuf[BUFSIZ];  /* setvbuf makes this the stdio buffer */
       if ((fp = fopen("datafile", "r")) == NULL)
           return(NULL);
       if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
           return(NULL);
       return(fp);     /* error */
   }

The default buffer size *BUFSIZ* is expected to be the most efficient buffer size for file I/O 
on the implementation, but POSIX *fstat* often provides a better estimate.

**Example**

.. code-block:: sh

   #include <iostream>
   #include <cstdio>
   #include <stdlib.h>
   #include <sys/stat.h>
    
   int main()
   {
       std::FILE* fp = std::fopen("test.txt", "r");
       if(!fp) {
          std::perror("fopen"); return 1;
       }
    
       struct stat stats;
       if(fstat(fileno(fp), &stats) == -1) { // POSIX only
           std::perror("fstat"); return 1;
       }
    
       std::cout << "BUFSIZ is " << BUFSIZ << ", but optimal block size is "
                 << stats.st_blksize << '\n';
       if(std::setvbuf(fp, NULL, _IOFBF, stats.st_blksize) != 0) {
          perror("setvbuf"); // POSIX version sets errno
          return 1;
       }
    
       int ch;
       while((ch=std::fgetc(fp)) != EOF); // read entire file: use truss/strace to
                                          // observe the read(2) syscalls used
       std::fclose(fp);
   }