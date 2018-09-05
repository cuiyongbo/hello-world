***************
File Operations
***************

fopen, fdopen, freopen - stream open functions
==============================================

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>

      FILE *fopen(const char *path, const char *mode);
      FILE *fdopen(int fd, const char *mode);
      FILE *freopen(const char *path, const char *mode, FILE *stream);


**DESCRIPTION**

   The ``fopen()`` function opens the file whose name is the string
   pointed to by *path* and associates a stream with it.

   The argument *mode* points to a string beginning with one of the following
   sequences (possibly followed by additional characters, as described below)::

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

   The *mode* string can also include the letter ``'b'`` either as a last character
   or as a character between the characters in any of the two-character strings described above.
   This is strictly for compatibility with C89 and has no effect; the ``'b'`` is ignored on all
   POSIX conforming systems, including Linux. (Other systems may treat text files and binary 
   files differently, and adding the ``'b'`` may be a good idea if you do I/O to a binary file
   and expect that your program may be ported to non-UNIX environments.)

   Reads and writes may be intermixed on read/write streams in any order.
   Note that ANSI C requires that a file positioning function intervene
   between output and input, unless an input operation encounters end-of-file.
   (If this condition is not met, then a read is allowed to return the result
   of writes other than the most recent.) Therefore it is good practice (and
   indeed sometimes necessary under Linux) to put an :manpage:`fseek(3)` or :manpage:`fgetpos(3)`
   operation between write and read operations on such a stream. This operation may be an apparent
   no-op (as in ``fseek(...,  0L,  SEEK_CUR)`` called for its synchronizing side effect).

   Opening a file  in append mode (a as the first character of mode) causes all subsequent write
   operations to this stream to occur at end-of-file, as if preceded the call::

      fseek(stream, 0, SEEK_END);

   The ``fdopen()`` function associates a stream with the existing file descriptor, *fd*.
   The mode of the stream (one of the  values "r",  "r+",  "w",  "w+", "a", "a+") must be
   compatible with the mode of the file descriptor. The file position indicator of
   the new stream is set to that belonging to *fd*, and the error and end-of-file indicators
   are cleared. Modes "w" or "w+" do not cause truncation of the file.  The file descriptor
   is not duplicated, and will be closed when the stream created by ``fdopen()`` is closed.
   The result of applying ``fdopen()`` to a shared memory object is undefined.

   The ``freopen()`` function opens the file whose name is the string pointed to by *path*
   and associates the stream pointed to by *stream* with it. The original stream
   (if it exists) is closed. The *mode* argument is used just as in the ``fopen()`` function.
   The primary use of the ``freopen()`` function is to change the file associated with a
   standard text stream (``stderr``, ``stdin``, or ``stdout``).


**RETURN VALUE**

   Upon successful completion ``fopen()``, ``fdopen()`` and ``freopen()``
   return a ``FILE`` pointer. Otherwise, ``NULL`` is returned and ``errno``
   is set to indicate the error.


**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +------------------------------+---------------+---------+
   | Interface                    | Attribute     | Value   |
   +==============================+===============+=========+
   | fopen(), fdopen(), freopen() | Thread safety | MT-Safe |
   +------------------------------+---------------+---------+


fclose - close a stream
=======================

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>
      int fclose(FILE *stream);

**DESCRIPTION**

   The ``fclose()`` function flushes the stream pointed to by *stream*
   (writing any buffered output data using fflush(3)) and closes
   the underlying file descriptor.

   The behaviour of ``fclose()`` is undefined if the *stream* parameter
   is an illegal pointer, or is a descriptor already passed to a
   previous invocation of ``fclose()``.

**RETURN VALUE**

   Upon successful completion ``0`` is returned.
   Otherwise, ``EOF`` is returned and *errno* is set to indicate the error. 
   In either case any further access (including another call to ``fclose()``)
   to the *stream* results in undefined behavior.

**ERRORS**

   EBADF
      The file descriptor underlying stream is not valid.

   The ``fclose()`` function may also fail and set *errno*
   for any of the errors specified for the routines
   :manpage:`close(2)`, :manpage:`write(2)` or :manpage:`fflush(3)`.

**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +-----------+---------------+---------+
   | Interface | Attribute     | Value   |
   +===========+===============+=========+
   | fclose()  | Thread safety | MT-Safe |
   +-----------+---------------+---------+

**NOTES**
   
   Note that ``fclose()`` flushes only the user-space buffers provided by the C library. 
   To ensure that the data is physically stored on disk the kernel buffers must
   be flushed too, for example, with :manpage:`sync(2)` or :manpage:`fsync(2)`.


fread, fwrite - binary stream input/output
==========================================

**SYNOPSIS**
   
   .. code-block:: c

      #include <stdio.h>

      size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
      size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

**DESCRIPTION**

   The function ``fread()`` reads *nmemb* items of data, each *size* bytes long,
   from the stream pointed to by *stream*, storing them at
   the location given by *ptr*.

   The function ``fwrite()`` writes *nmemb* items of data, each *size* bytes long,
   to the stream pointed to by *stream*,  obtaining them
   from the location given by *ptr*.

   For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.

**RETURN VALUE**

   On success, ``fread()`` and ``fwrite()`` return the number of items read or written.
   This number equals the number of bytes transferred only when size is 1. 
   If an error occurs, or the end of the file is reached,
   the return value is a shorter item count (or zero).

   ``fread()`` does not distinguish between end-of-file and error, and callers must
   use :manpage:`feof(3)` and :manpage:`ferror(3)` to determine which occurred.

**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +-------------------+---------------+---------+
   | Interface         | Attribute     | Value   |
   +===================+===============+=========+
   | fread(), fwrite() | Thread safety | MT-Safe |
   +-------------------+---------------+---------+


clearerr, feof, ferror, fileno - check and reset stream status
==============================================================

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>

      int feof(FILE *stream);
      int ferror(FILE *stream);
      int fileno(FILE *stream);
      void clearerr(FILE *stream);

**DESCRIPTION**

   The function ``clearerr()`` clears the end-of-file and error indicators
   for the stream pointed to by *stream*.

   The function ``feof()`` tests the end-of-file indicator for the stream
   pointed to by *stream*, returning nonzero if it is set. The end-of-file
   indicator can be cleared only by the function ``clearerr()``.

   The function ``ferror()`` tests the error indicator for the stream pointed
   to by *stream*, returning nonzero if it is set. The error indicator can be
   reset only by the ``clearerr()`` function.

   The function ``fileno()`` examines the argument stream and
   returns its integer descriptor.

   For nonlocking counterparts, see :manpage:`unlocked_stdio(3)`.

**ERRORS**

   These functions should not fail and do not set the external variable *errno*.
   (However, in case ``fileno()`` detects that its argument is not a valid stream,
   it must return ``-1`` and set *errno* to ``EBADF``.)

**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +----------------------+---------------+---------+
   | Interface            | Attribute     | Value   |
   +======================+===============+=========+
   | feof(), ferror()     | Thread safety | MT-Safe |
   | fileno(), clearerr() |               |         |
   +----------------------+---------------+---------+


fgetpos, fseek, fsetpos, ftell, rewind - reposition a stream
============================================================

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>

      long ftell(FILE *stream);
      void rewind(FILE *stream);
      int fseek(FILE *stream, long offset, int whence);

      int fgetpos(FILE *stream, fpos_t *pos);
      int fsetpos(FILE *stream, const fpos_t *pos);

**DESCRIPTION**

   The ``fseek()`` function sets the file position indicator for the stream
   pointed to by *stream*. The new position, measured in bytes, is obtained
   by adding *offset* bytes to the position specified by *whence*. If *whence*
   is set to ``SEEK_SET``, ``SEEK_CUR``, or ``SEEK_END``, the *offset* is relative
   to the start of the file, the current position indicator, or end-of-file, respectively. 
   A successful call to the ``fseek()`` function clears the end-of-file indicator for the
   stream and undoes any effects of the :manpage:`ungetc(3)` function on the same stream.

   The ``ftell()`` function obtains the current value of the file position indicator for
   the stream pointed to by *stream*.

   The ``rewind()`` function sets the file position indicator for the stream pointed to
   by *stream* to the beginning of the file. It is equivalent to::

      (void) fseek(stream, 0L, SEEK_SET)

   except that the error indicator for the stream is also cleared.

   The ``fgetpos()`` and ``fsetpos()`` functions are alternate interfaces equivalent to
   ``ftell()`` and ``fseek()`` (with *whence* set to ``SEEK_SET``), setting and storing
   the current value of the file offset into or from the object referenced by *pos*. On
   some non-UNIX systems, an ``fpos_t`` object may be a complex object and these routines
   may be the only way to portably reposition a text stream.

**RETURN VALUE**

   The ``rewind()`` function returns no value. Upon successful completion,
   ``fgetpos()``, ``fseek()``, ``fsetpos()`` return ``0``, and ``ftell()``
   returns the current offset. Otherwise, ``-1`` is returned and *errno*
   is set to indicate the error.

**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +----------------------------+---------------+---------+
   | Interface                  | Attribute     | Value   |
   +============================+===============+=========+
   | ftell(), fseek(), rewind() | Thread safety | MT-Safe |
   | fsetpos(), fgetpos()       |               |         |
   +----------------------------+---------------+---------+


fflush - flush a stream
=======================

**SYNOPSIS**

   .. code-block:: c

      #include <stdio.h>
      int fflush(FILE *stream);

**DESCRIPTION**

   For output streams, fflush() forces a write of all user-space buffered data
   for the given output or update stream via the stream's underlying write function.

   For input streams associated with seekable files (e.g., disk files, but not pipes
   or terminals), ``fflush()`` discards any buffered data that has been fetched from
   the underlying file, but has not been consumed by the application.
   The open status of the stream is unaffected.

   If the *stream* argument is ``NULL``, ``fflush()`` flushes all open output streams.

   For a nonlocking counterpart, see :manpage:`unlocked_stdio(3)`.

**RETURN VALUE**

   Upon successful completion 0 is returned.  
   Otherwise, EOF is returned and errno is set to indicate the error.

**ATTRIBUTES**

   For an explanation of the terms used in this section, 
   see :manpage:`attributes(7)`.

   +-----------+---------------+---------+
   | Interface | Attribute     | Value   |
   +===========+===============+=========+
   | fflush()  | Thread safety | MT-Safe |
   +-----------+---------------+---------+

**NOTES**
   
   Note that ``fclose()`` flushes only the user-space buffers provided by the C library. 
   To ensure that the data is physically stored on disk the kernel buffers must
   be flushed too, for example, with :manpage:`sync(2)` or :manpage:`fsync(2)`.

