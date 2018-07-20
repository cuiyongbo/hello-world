************************
C++ Operator overloading
************************

.. contents::
   :local:

Stream extraction and insertion
===============================

The overloads of ``operator>>`` and ``operator<<`` that take a ``std::istream&`` or ``std::ostream&`` 
as the left hand argument are known as insertion and extraction operators. Since they take the user-defined 
type as the right argument (``b in a@b``), they must be implemented as non-members.

.. code-block:: cpp

   std::ostream& operator<<(std::ostream& os, const T& obj)
   {
       // write obj to stream
       return os;
   }
   std::istream& operator>>(std::istream& is, T& obj)
   {
       // read obj from stream
       if( /* T could not be constructed */ )
           is.setstate(std::ios::failbit);
       return is;
   }