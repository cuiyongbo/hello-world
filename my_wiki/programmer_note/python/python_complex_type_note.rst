*******************
Python Complex Note
*******************

.. code-block:: py

   >>> a=1+3j
   >>> type(a)
   <type 'complex'>
   >>> dir(complex)
   ['conjugate', 'imag', 'real']
   >>> a.imag
   3.0
   >>> a.real
   1.0
   >>> a.conjugate()
   (1-3j)
   >>> a.conjugate()*a
   (10+0j)
   >>> abs(a)
   3.1622776601683795   