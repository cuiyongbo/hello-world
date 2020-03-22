*************
Std C I/O API
*************

.. toctree::

   scanf_info

.. note:: For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.

#. Input API

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

    ``fgetc()`` reads the next character from stream and returns it as an
    unsigned char cast to an int, or ``EOF`` on end of file or error.

    ``fgets()`` reads in at most one less than *size* characters from *stream*
    and stores them into the buffer pointed to by *s*. Reading stops after an
    ``EOF`` or a newline. If a newline is read, it is stored into the buffer.
    A terminating null byte (``'\0'``) is stored after the last character in the buffer.

    ``ungetc()`` pushes *c* back to stream, cast to unsigned char, where it is
    available for subsequent read operations. Pushed-back characters will
    be returned in reverse order; only one pushback is guaranteed.
    (**you must not call ungetch() consecutively.**)

#. Output API

    .. code-block:: c

        #include <stdio.h>

        int fputc(int c, FILE *stream);
        int putc(int c, FILE *stream);
        int putchar(int c);
        int puts(const char *s);
        int fputs(const char *s, FILE *stream);

        /*Windows implementation*/
        #define putchar(_c) putc((_c),stdout)

    ``fputc()`` writes the character *c*, cast to an unsigned char, to *stream*.

    ``fputs()`` writes the string s to stream, without its terminating null byte (``'\0'``).

    ``putc()`` is equivalent to ``fputc()`` except that it may be implemented
    as a macro which evaluates stream more than once.

    ``puts()`` writes the string *s* and a trailing newline to ``stdout``.

#. Buffer Control

    .. code-block:: cpp

        #include <stdio.h>
        void setbuf(FILE *stream, char *buf);
        void setbuffer(FILE *stream, char *buf, size_t size);
        void setlinebuf(FILE *stream);
        int setvbuf( std::FILE* stream, char* buffer, int mode, std::size_t size );

    Changes the the buffering mode of the given file stream ``stream`` as indicated by
    the argument ``mode``. In addition,

       * If ``buffer`` is a null pointer, resizes the internal buffer to *size*.

       * If ``buffer`` is not a null pointer, instructs the ``stream`` to use the
         user-provided buffer of size ``size`` beginning at *buffer*.

    .. warning:: the lifetime of buffer must persist until the end of program.

    ``mode`` can be one of the following values:

        +--------+----------------+
        | _IOFBF | full buffering |
        +--------+----------------+
        | _IOLBF | line buffering |
        +--------+----------------+
        | _IONBF | no buffering   |
        +--------+----------------+

    The other three calls are, in effect, simply aliases for calls to ``setvbuf()``.
    ``setbuf()`` is equivalent to the call: ``setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);``

    ``setbuffer()`` is the same, except that the size of the buffer is up to the caller,
    rather than being determined by the default ``BUFSIZ``.

    ``setlinebuf()`` is equivalent to the call: ``setvbuf(stream, NULL, _IOLBF, 0);``

#. set ``stdout`` to no buffer mode

    .. code-block:: sh

        std::setbuf(stdout, NULL);

        // equivalent to
        // std::setvbuf(stream, NULL, _IONBF, 0);

