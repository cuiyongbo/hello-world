:orphan: 

*******************************
char wchar conversion functions
*******************************

.. contents::
   :local:

wcstombs - convert a wide-character string to a multibyte string
================================================================

**SYNOPSIS**

   .. code-block:: c
   
      #include <stdlib.h>
      size_t wcstombs(char *dest, const wchar_t *src, size_t n);

**DESCRIPTION**

   If *dest* is not a ``NULL`` pointer, the ``wcstombs()`` function converts
   the wide-character string *src* to a multibyte string starting at *dest*. 
   At most *n* bytes are written to *dest*. The conversion starts in the initial
   state. The conversion can stop for three reasons:

      #. A wide character has been encountered that can not be represented
         as a multibyte sequence (according to the current locale). In this
         case ``(size_t) -1`` is returned.

      #. The length limit forces a stop. In this case the number of bytes
         written to *dest* is returned, but the shift state at this point
         is lost.

      #. The wide-character string has been completely converted, including
         the terminating null wide character (L'\0'). In this case the
         conversion ends in the initial state. The number of bytes written
         to *dest*, excluding the terminating null byte ('\0'),  is returned.

   The programmer must ensure that there is room for at least *n* bytes at *dest*.

   If *dest* is ``NULL``, *n* is ignored, and the conversion proceeds as above,
   except that the converted bytes are not written out to memory, and that no
   length limit exists.

   In order to avoid the case 2 above, the programmer should make sure *n* is greater
   or equal to ``wcstombs(NULL,src,0) + 1``.

**RETURN VALUE**

   The ``wcstombs()`` function returns the number of bytes that make up the converted part
   of multibyte sequence, not including the terminating null byte. If a wide character was
   encountered which could not be converted, ``(size_t) -1`` is returned.

**NOTES**

   The behavior of ``wcstombs()`` depends on the ``LC_CTYPE`` category of the current locale.

   The function :manpage:`wcsrtombs(3)` provides a thread safe interface to the same functionality.


wcsrtombs - convert a wide-character string to a multibyte string
=================================================================

**SYNOPSIS**

   .. code-block:: c

      #include <wchar.h>
      size_t wcsrtombs(char *dest, const wchar_t **src, size_t len, mbstate_t *ps);

**DESCRIPTION**

      If *dest* is not a NULL pointer, the ``wcsrtombs()`` function converts the wide-character
      string *\*src* to a multibyte string starting at *dest*. At most *len* bytes are written to
      *dest*. The shift state *\*ps* is updated. The conversion is effectively performed by
      repeatedly calling ``wcrtomb(dest, *src, ps)``, as long as this call succeeds, and then
      incrementing *dest* by the number of bytes written and *\*src* by one. The conversion can
      stop for three reasons:

         #. A wide character has been encountered that can not be represented
            as a multibyte sequence (according to the current locale). In this
            case *\*src* is left pointing to the invalid wide character,
            ``(size_t) -1`` is returned, and *errno* is set to ``EILSEQ``.

         #. The length limit forces a stop. In this case *\*src* is left pointing
            to the next wide character to be converted, and the number of bytes
            written to *dest* is returned.

         #. The wide-character string has been completely converted, including the
            terminating null wide character (L'\0'), which has the side effect of
            bringing back *\*ps* to the initial state. In this case *\*src* is set
            to ``NULL``, and the number of bytes written to *dest*, excluding the 
            terminating null byte ('\0'), is returned.

      If *dest* is ``NULL``, len is ignored, and the conversion proceeds as above, except that
      the converted bytes are not written out to memory, and that no length limit exists.

      In both of the above cases, if *ps* is a ``NULL`` pointer, a static anonymous state known
      only to the ``wcsrtombs()`` function is used instead.

      The programmer must ensure that there is room for at least *len* bytes at *dest*.

**RETURN VALUE**

   The ``wcsrtombs()`` function returns the number of bytes that make up the converted part
   of multibyte sequence, not including the terminating null byte. If a wide character was
   encountered which could not be converted, ``(size_t) -1`` is returned, and *errno* set
   to ``EILSEQ``.

**NOTES**
   
   The behavior of ``wcsrtombs()`` depends on the ``LC_CTYPE`` category of the current locale.
   Passing ``NULL`` as *ps* is not multithread safe.


mbstowcs - convert a multibyte string to a wide-character string
================================================================

**SYNOPSIS**

   .. code-block:: c

      #include <stdlib.h>
      size_t mbstowcs(wchar_t *dest, const char *src, size_t n);

**DESCRIPTION**

   If *dest* is not a ``NULL`` pointer, the ``mbstowcs()`` function converts
   the multibyte string *src* to a wide-character string starting at *dest*.
   At most *n* wide characters are written to *dest*. The conversion starts
   in the initial state. The conversion can stop for three reasons:

      #. An invalid multibyte sequence has been encountered.
         In this case ``(size_t) -1`` is returned.

      #. n non-L'\0' wide characters have been stored at *dest*.
         In this case the number of wide characters written to *dest*
         is returned, but the shift state at this point is lost.

      #. The multibyte string has been completely converted, including
         the terminating null wide character ('\0'). In this case the
         number of wide characters written to *dest*, excluding the
         terminating null wide character, is returned.

   The programmer must ensure that there is room for at least *n* wide characters at *dest*.

   If dest is ``NULL``, *n* is ignored, and the conversion proceeds as above, except that the
   converted wide characters are not written out to memory, and that no length limit exists.

   In order to avoid the case 2 above, the programmer should make sure *n* is greater or
   equal to ``mbstowcs(NULL,src,0) + 1``.

**RETURN VALUE**

   The ``mbstowcs()`` function returns the number of wide characters that make up the converted
   part of the wide-character string, not including the terminating null wide character. If an
   invalid multibyte sequence was encountered, ``(size_t) -1`` is returned.

**NOTES**

   The behavior of ``mbstowcs()`` depends on the **LC_CTYPE** category of the current locale.
   The function :manpage:`mbsrtowcs(3)` provides a better interface to the same functionality.
   

mbsrtowcs - convert a multibyte string to a wide-character string
=================================================================

**SYNOPSIS**

   .. code-block:: c

      #include <wchar.h>
      size_t mbsrtowcs(wchar_t *dest, const char **src, size_t len, mbstate_t *ps);

**DESCRIPTION**

   If *dest* is not a *NULL* pointer, the ``mbsrtowcs()`` function converts the multibyte string *\*src*
   to a wide-character string starting at *dest*. At most *len* wide characters are written to *dest*. 
   The shift state *\*ps* is updated. The conversion is effectively performed by repeatedly calling
   ``mbrtowc(dest, *src, n, ps)`` where *n* is some positive number, as long as this call succeeds, and
   then incrementing *dest* by one and *\*src* by the number of bytes consumed. The conversion can stop
   for three reasons:

      #. An invalid multibyte sequence has been encountered. In this case *\*src*
         is left pointing to the invalid multibyte sequence, ``(size_t) -1`` is
         returned, and *errno* is set to **EILSEQ**.

      #. *len* non-L'\0' wide characters have been stored at *dest*. In this case *\*src*
         is left pointing to the next multibyte sequence to be converted, and the number
         of wide characters written to *dest* is returned.

      #. The multibyte string has been completely converted, including the terminating null
         wide character ('\0'), which has the side effect of bringing back *\*ps* to the
         initial state.  In this case *\*src* is set to ``NULL``, and the number of wide
         characters written to *dest*, excluding the terminating null wide character, is
         returned.

   If *dest* is ``NULL``, len is ignored, and the conversion proceeds as above, except that the converted wide characters
   are not written out to memory, and that no length limit exists.

   In both of the above cases, if *ps* is a ``NULL`` pointer, a static anonymous state known only to the ``mbsrtowcs()``
   function is used instead.

   The programmer must ensure that there is room for at least *len* wide characters at ``dest``.

**RETURN VALUE**

   The ``mbsrtowcs()`` function returns the number of wide characters that make up
   the converted part of the wide-character string, not including the terminating
   null wide character. If an invalid multibyte sequence was encountered, 
   ``(size_t) -1`` is returned, and *errno* set to **EILSEQ**.


**NOTES**

   The behavior of ``mbsrtowcs()`` depends on the **LC_CTYPE** category of the current locale.
   Passing ``NULL`` as *ps* is not multithread safe.