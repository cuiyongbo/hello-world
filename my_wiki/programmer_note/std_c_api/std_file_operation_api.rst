Std File Operations
===================

.. note:: For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.

#. stream open functions

    .. code-block:: c

        #include <stdio.h>

        FILE *fopen(const char *path, const char *mode);
        FILE *fdopen(int fd, const char *mode);
        FILE *freopen(const char *path, const char *mode, FILE *stream);

    The ``fopen()`` function opens the file whose name is the string
    pointed to by *path* and associates a stream with it.

    The argument *mode* points to a string beginning with one of the following
    sequences::

        r
           Open text file for reading.
           The stream is positioned at the beginning of the file.
        r+
           Open for reading and writing.
           The stream is positioned at the beginning of the file.
        w
           Truncate file to zero length or create text file for writing.
           The stream is positioned at the beginning of the file.
        w+
           Open for reading and writing.
           The file is created if it does not exist, otherwise it is truncated.
           The stream is positioned at the beginning of the file.
        a
           Open for appending (writing at end of file).
           The file is created if it does not exist.
           The stream is positioned at the end of the file.
        a+
           Open for reading and appending (writing at end of file).
           The file is created if it does not exist. The initial file
           position for reading is at the beginning of the file, but
           output is always appended to the end of the file.
           always return EOF when call fread() in Macos.

    Opening a file in append mode causes all subsequent write
    operations to this stream to occur at end-of-file, as if
    preceded the call: ``fseek(stream, 0, SEEK_END);``

    The ``fdopen()`` function associates a stream with the existing file descriptor, *fd*.
    The mode of the stream must be compatible with the mode of the fd.The file position indicator of
    the new stream is set to that belonging to *fd*, and the error and eof indicators are cleared.

    The ``freopen()`` function opens the file whose name is the string pointed to by *path*
    and associates the stream pointed to by *stream* with it. The original stream
    (if it exists) is closed. The *mode* argument is used just as in the ``fopen()`` function.
    The primary use of the ``freopen()`` function is to change the file associated with a
    standard text stream (``stderr``, ``stdin``, or ``stdout``).

#. close a stream

    .. code-block:: c

        #include <stdio.h>
        int fclose(FILE *stream);

    The ``fclose()`` function flushes the stream pointed to by *stream*
    (writing any buffered output data using fflush(3)) and closes
    the underlying file descriptor.

    .. note::

        Note that ``fclose()`` flushes only the user-space buffers provided by the C library.
        To ensure that the data is physically stored on disk the kernel buffers must
        be flushed too, for example, with :manpage:`sync(2)` or :manpage:`fsync(2)`.

#. binary stream input/output

    .. code-block:: c

        #include <stdio.h>
        size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
        size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

    The function ``fread()`` reads *nmemb* items of data, each *size* bytes long,
    from the stream pointed to by *stream*, storing them at
    the location given by *ptr*.

    The function ``fwrite()`` writes *nmemb* items of data, each *size* bytes long,
    to the stream pointed to by *stream*,  obtaining them
    from the location given by *ptr*.

#. check and reset stream status

    .. code-block:: c

        #include <stdio.h>

        int feof(FILE *stream);
        int ferror(FILE *stream);
        int fileno(FILE *stream);
        void clearerr(FILE *stream);

    ``clearerr()`` clears the eof and error indicators
    for the stream pointed to by *stream*.

    ``feof()`` tests the eof indicator for the stream
    pointed to by *stream*, returning nonzero if it is set.

    ``ferror()`` tests the error indicator for the stream pointed
    to by *stream*, returning nonzero if it is set.

    ``fileno()`` examines the argument stream and returns its integer descriptor.

#. reposition a stream

    .. code-block:: c

        #include <stdio.h>

        long ftell(FILE *stream);
        void rewind(FILE *stream);
        int fseek(FILE *stream, long offset, int whence);

    The ``fseek()`` function sets the file position indicator for the stream
    pointed to by *stream*. The new position, measured in bytes, is obtained
    by adding *offset* bytes to the position specified by whence::

        #define SEEK_SET  0  /* Seek from beginning of file.  */
        #define SEEK_CUR  1  /* Seek from current position.  */
        #define SEEK_END  2  /* Seek from end of file.  */

    The ``ftell()`` function obtains the current value of the file position indicator for
    the stream pointed to by *stream*.

    The ``rewind()`` function sets the file position indicator for the stream pointed to
    by *stream* to the beginning of the file. It is equivalent to: ``fseek(stream, 0L, SEEK_SET);``
    except that the error indicator for the stream is also cleared.

#. flush a stream

    .. code-block:: c

        #include <stdio.h>
        int fflush(FILE *stream);

    For output streams, fflush() forces a write of all user-space buffered data
    for the given output or update stream via the stream's underlying write function.

    For input streams associated with seekable files (e.g., disk files, but not pipes
    or terminals), ``fflush()`` discards any buffered data that has been fetched from
    the underlying file, but has not been consumed by the application.
    The open status of the stream is unaffected.

    If the *stream* argument is ``NULL``, ``fflush()`` flushes all open output streams.
