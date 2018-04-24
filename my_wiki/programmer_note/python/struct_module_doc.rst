**********************
struct Module Document
**********************

Brief introduction
==================

**DESCRIPTION**

   Functions to convert between Python values and C structs represented
   as Python strings. It uses format strings (explained below) as compact
   descriptions of the lay-out of the C structs and the intended conversion
   to/from Python values.
    
   The optional first format char indicates byte order, size and alignment::

      @: native order, size & alignment (default)
      =: native order, std. size & alignment
      <: little-endian, std. size & alignment
      >: big-endian, std. size & alignment
      !: same as >
    
   The remaining chars indicate types of args and must match exactly;
   these can be preceded by a decimal repeat count::

      c: char
      x: pad byte (no data)
      ?: _Bool (requires C99; if not available, char is used instead)
      b: signed byte
      B: unsigned byte
      h: short
      H: unsigned short
      i: int
      I: unsigned int
      l: long
      L: unsigned long 
      f: float
      d: double

   Special cases (preceding decimal count indicates length)::

      s: string (array of char)
      p: pascal string (with count byte).
   
   Special case (only available in native format)::
   
      P: an integer type that is wide enough to hold a pointer.
   
   Special case (not in native mode unless 'long long' in platform C)::

      q: long long
      Q: unsigned long long

   Whitespace between formats is ignored.
    
**FUNCTIONS**

   calcsize(...)
      Return size of C struct described by format string *fmt*.
    
   pack(...)
      Return string containing values v1, v2, ... packed according to *fmt*.
    
   pack_into(...)
      Pack the values v1, v2, ... according to *fmt*.
      Write the packed bytes into the writable buffer *buf* starting at *offset*.
    
   unpack(...)
      Unpack the string containing packed C structure data, according to *fmt*.
      Requires ``len(string) == calcsize(fmt)``.
    
   unpack_from(...)
      Unpack the buffer, containing packed C structure data, according to
      *fmt*, starting at *offset*. ``Requires len(buffer[offset:]) >= calcsize(fmt)``.


Further Information
===================

   See :doc:`struct_module_howto`.