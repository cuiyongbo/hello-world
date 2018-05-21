****************
Std C String API
****************

strcpy & strncpy
================

**NAME**

   strcpy, strncpy - copy a string

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>

      char *strcpy(char *dest, const char *src);
      char *strncpy(char *dest, const char *src, size_t n);

**DESCRIPTION**

   The **strcpy()** function copies the string pointed to by *src*, including the terminating null byte (``'\0'``),
   to the buffer pointed to by ``dest``. The strings may not overlap, and the destination string *dest* must be large
   enough to receive the copy.  Beware of buffer overruns!

   The ``strncpy()`` function is similar, except that at most *n* bytes of *src* are copied. 
   Warning: If there is no null byte among the first *n* bytes of *src*, the string placed in *dest*
   will not be null-terminated.

   If the length of *src* is less than *n*, ``strncpy()`` writes additional null bytes to *dest*
   to ensure that a total of *n* bytes are written.

   A simple implementation of ``strncpy()`` might be::

      char* strncpy(char *dest, const char *src, size_t n)
      {
         size_t i;
         for (i = 0; i < n && src[i] != '\0'; i++)
            dest[i] = src[i];
         for ( ; i < n; i++)
            dest[i] = '\0';

         return dest;
      }

**RETURN VALUE**

   The ``strcpy()`` and ``strncpy()`` functions return a pointer to the destination string *dest*.

**NOTES**

   Some programmers consider ``strncpy()`` to be inefficient and error prone. If the programmer knows
   (i.e., includes code to test!) that the size of dest is greater than the length of *src*, then
   ``strcpy()`` can be used.

   One valid (and intended) use of ``strncpy()`` is to copy a C string to a fixed-length buffer
   while ensuring both that the buffer is not overflowed and that unused bytes in the target buffer
   are zeroed out (perhaps to prevent information leaks if the buffer is to be written to media or
   transmitted to another process via an IPC technique).

   If there is no terminating null byte in the first *n* bytes of *src*, ``strncpy()`` produces an
   unterminated string in *dest*. You can force termination using something like the following::

      strncpy(buf, str, n);
      if (n > 0)
         buf[n - 1]= '\0';

   (Of course, the above technique ignores the fact that information contained in *src* is lost
   in the copying to *dest*.)

   Some systems (the BSDs, Solaris, and others) provide the following function::

      size_t strlcpy(char *dest, const char *src, size_t size);

   This function is similar to ``strncpy()``, but it copies at most ``size-1`` bytes to *dest*,
   always adds a terminating null byte, and does not pad the target with (further) null bytes.
   This function fixes some of the problems of ``strcpy()`` and ``strncpy()``, but the caller
   must still handle the possibility of data loss if *size* is too small. The return value of
   the function is the length of *src*, which allows truncation to be easily detected: if the
   return value is greater than or equal to *size*, truncation occurred. If loss of data matters,
   the caller must either check the arguments before the call, or test the function return value.
   ``strlcpy()`` is not present in glibc and is not standardized by POSIX, but is available on Linux
   via the libbsd library.

**BUGS**

   If the destination string of a ``strcpy()`` is not large enough, then anything might happen.
   Overflowing fixed-length string buffers is a favorite cracker technique for taking complete
   control of the machine. Any time a program reads or copies data into a buffer, the program
   first needs to check that there's enough space. This may be unnecessary if you can show that
   overflow is impossible, but be careful: programs can get changed over time, in ways that may
   make the impossible possible.

**SEE ALSO**

   bcopy(3), memccpy(3), memcpy(3), memmove(3), stpcpy(3),
   stpncpy(3), strdup(3), string(3), wcscpy(3), wcsncpy(3)


strcmp & strncmp
================

**NAME**
   
   strcmp, strncmp - compare two strings

**SYNOPSIS**

   .. code-block:: sh

      #include <string.h>
      int strcmp(const char *s1, const char *s2);
      int strncmp(const char *s1, const char *s2, size_t n);

**DESCRIPTION**

   The ``strcmp()`` function compares the two strings *s1* and *s2*. It returns an integer less than, equal to,
   or greater than zero if *s1* is found, respectively, to be less than, to match, or be greater than *s2*.

   The ``strncmp()`` function is similar, except it compares the only first (at most) *n* bytes of *s1* and *s2*.

**RETURN VALUE**

   The ``strcmp()`` and ``strncmp()`` functions return an integer less than, equal to, or greater than zero
   if *s1* (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater
   than *s2*.


memcpy & memmove
================

**NAME**

   memcpy, memmove - copy memory area

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>

      void *memcpy(void *dest, const void *src, size_t n);
      void *memmove(void *dest, const void *src, size_t n);

**DESCRIPTION**

   The ``memcpy()`` function copies *n* bytes from memory area *src* to memory area *dest*.
   The memory areas must not overlap. Use ``memmove()`` if the memory areas do overlap.

   The ``memmove()`` function does the same job as ``memcpy()``, except that the memory areas
   may overlap: copying takes place as though the bytes in *src* are first copied into a
   temporary array that does not overlap *src* or *dest*, and the bytes are then copied from
   the temporary array to *dest*. Possible implementation::

      void *memmove(void *dest, const void *src, size_t n)
      {
         if (dest <= src) {
            for (size_t i=0; i != n; i++)
               dest[i] = src[i];
         }
         else
         {
            for (size_t i= n-1; i != 0; i--)
               dest[i] = src[i];

            dest[0] = src[0];
         }

         return dest;
      }

   Note that the implementation skips necessary error checkings, which must be done
   in production code.

**RETURN VALUE**
   
   Return a pointer to *dest*.


memcmp
======

**NAME**
   
   memcmp - compare memory areas

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>
      int memcmp(const void *s1, const void *s2, size_t n);

**DESCRIPTION**

   The ``memcmp()`` function compares the first *n* bytes (each interpreted as unsigned char)
   of the memory areas *s1* and *s2*. Possible implementation::

      int memcmp(const void *s1, const void *s2, size_t n)
      {
         unsigned char* p1 = (char*)s1;
         unsigned char* p2 = (char*)s2;
         
         size_t i;
         for (i=0; i != n-1; i++)
            if(p1[i] != p2[i])
               break;

         return p1[i]-p2[i];
      }

   Note that the implementation skips necessary error checkings, which must be done
   in production code.

**RETURN VALUE**

   The ``memcmp()`` function returns an integer less than, equal to, or greater than zero
   if the first *n* bytes of *s1* is found, respectively, to be less than, to match, or
   be greater than the first *n* bytes of *s2*.

   For a nonzero return value, the sign is determined by the sign of the difference between
   the first pair of bytes (interpreted as unsigned char) that differ in *s1* and *s2*.


char wchar conversion functions
===============================

See :doc:`char_wchar_conversion`.


strtok & strtok_r
=================

**NAME**
   
   strtok, strtok_r - extract tokens from strings

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>
      char *strtok(char *str, const char *delim);
      char *strtok_r(char *str, const char *delim, char **saveptr);

**DESCRIPTION**

   The ``strtok()`` function breaks a string into a sequence of zero or more nonempty tokens.
   On the first call to ``strtok()`` the string to be parsed should be specified in *str*.
   In each subsequent call that should parse the same string, *str* must be NULL.

   The *delim* argument specifies a set of bytes that delimit the tokens in the parsed string.
   The caller may specify different strings in *delim* in successive calls that parse the same string.

   Each call to ``strtok()`` returns a pointer to a null-terminated string containing the next token.
   This string does not include the delimiting byte.  If no more tokens are found, ``strtok()`` returns ``NULL``.

   A sequence of calls to ``strtok()`` that operate on the same string maintains a pointer
   that determines the point from which to start searching for the next token. The first
   call to ``strtok()`` sets this pointer to point to the first byte of the string. The
   start of the next token is determined by scanning forward for the next nondelimiter byte
   in *str*. If such a byte is found, it is taken as the start of the next token. If no such
   byte is found, then there are no more tokens, and ``strtok()`` returns ``NULL``. (A string
   that is empty or that contains only delimiters will thus cause ``strtok()`` to return ``NULL``
   on the first call.)

   The end of each token is found by scanning forward until either the next delimiter byte is found
   or until the terminating null byte ('\0') is encountered. If a delimiter byte is found, it is
   overwritten with a null byte to terminate the current token, and ``strtok()`` saves a pointer
   to the following byte, which will be used as the starting point when searching for the
   next token. In this case, ``strtok()`` returns a pointer to the start of the found token.

   From the above description, it follows that a sequence of two or more contiguous delimiter bytes
   in the parsed string is considered to be a single delimiter, and that delimiter bytes at the start
   or end of the string are ignored. Put another way: the tokens returned by ``strtok()`` are always
   nonempty strings. Thus, for example, given the string ``"aaa;;bbb,"``, successive calls to ``strtok()``
   that specify the delimiter string ``";,"`` would return the strings ``"aaa"`` and ``"bbb"``,
   and then a ``NULL`` pointer.

   The ``strtok_r()`` function is a reentrant version ``strtok()``.  The *saveptr* argument is a
   pointer to a ``char*`` variable that is used internally by ``strtok_r()`` in order to maintain
   context between successive calls that parse the same string.

   On the first call to ``strtok_r()``, *str* should point to the string to be parsed, and the value
   of *saveptr* is ignored. In subsequent calls, *str* should be ``NULL``, and *saveptr* should be
   unchanged since the previous call.

   Different strings may be parsed concurrently using sequences of calls to ``strtok_r()`` that specify
   different *saveptr* arguments.

**RETURN VALUE**

   The ``strtok()`` and ``strtok_r()`` functions return a pointer to the next token,
   or ``NULL`` if there are no more tokens.

**ATTRIBUTES**

   The ``strtok()`` function is not thread-safe.
   The ``strtok_r()`` function is thread-safe.

**BUGS**

   Be cautious when using these functions. If you do use them, note that:

      * These functions modify their first argument.
      * These functions cannot be used on constant strings.
      * The identity of the delimiting byte is lost.
      * The ``strtok()`` function uses a static buffer while parsing,
        so it's not thread safe. Use ``strtok_r()`` if this matters to you.

**EXAMPLE**

   The program below uses nested loops that employ ``strtok_r()`` to break a string into
   a two-level hierarchy of tokens. The first command-line argument specifies the string
   to be parsed. The second argument specifies the delimiter byte(s) to be used to separate
   that string into "major" tokens. The third argument specifies the delimiter byte(s) to be
   used to separate the "major" tokens into subtokens.

   An example of the output produced by this program is the following::

      $ ./a.out "fsdfs,sdf,sdf,fs;dfsdf;sfd,dfas,sdf,sdf;" ";" ","
      1: fsdfs,sdf,sdf,fs
       --> fsdfs
       --> sdf
       --> sdf
       --> fs
      2: dfsdf
       --> dfsdf
      3: sfd,dfas,sdf,sdf
       --> sfd
       --> dfas
       --> sdf
       --> sdf

   Program source::

      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>

      int main(int argc, char *argv[])
      {
         char *str1, *str2, *token, *subtoken;
         char *saveptr1, *saveptr2;
         int j;

         if (argc != 4) 
         {
            fprintf(stderr, "Usage: %s string delim subdelim\n", argv[0]);
            exit(EXIT_FAILURE);
         }

         for (j = 1, str1 = argv[1]; ; j++, str1 = NULL)
         {
            token = strtok_r(str1, argv[2], &saveptr1);
            if (token == NULL)
               break;

            printf("%d: %s\n", j, token);

            for (str2 = token; ; str2 = NULL)
            {
               subtoken = strtok_r(str2, argv[3], &saveptr2);
               if (subtoken == NULL)
                  break;
               printf(" --> %s\n", subtoken);
            }
         }

         exit(EXIT_SUCCESS);
      }

   Another example program using ``strtok()`` can be found in :manpage:`getaddrinfo_a(3)`.

**SEE ALSO**
      
   index(3), memchr(3), rindex(3), strchr(3), string(3), strpbrk(3),
   strsep(3), strspn(3), strstr(3), wcstok(3)


Duplicate a string
==================

**NAME**
   
   strdup, strndup, strdupa, strndupa - duplicate a string

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>
      char *strdup(const char *s);
      char *strndup(const char *s, size_t n);
      char *strdupa(const char *s);
      char *strndupa(const char *s, size_t n);

**DESCRIPTION**

   The ``strdup()`` function returns a pointer to a new string which is a duplicate of the string *s*.
   Memory for the new string is obtained with :manpage:`malloc(3)`, and can be freed with :manpage:`free(3)`.

   The ``strndup()`` function is similar, but copies at most *n* bytes.  If *s* is longer than *n*, only *n*
   bytes are copied, and a terminating null byte ('\0') is added.

   ``strdupa()`` and ``strndupa()`` are similar, but use :manpage:`alloca(3)` to allocate the buffer.
   They are available only when using the GNU GCC suite, and suffer from the same limitations described
   in :manpage:`alloca(3)`.

**RETURN VALUE**

   On success, the **strdup()** function returns a pointer to the duplicated string.
   It returns ``NULL`` if insufficient memory was available, with *errno* set to
   indicate the cause of the error.

**ERRORS**

   ENOMEM 
      Insufficient memory available to allocate duplicate string.


**SEE ALSO**

   alloca(3), calloc(3), free(3), malloc(3),
   realloc(3), string(3), wcsdup(3)
