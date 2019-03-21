**********
Radix sort
**********

In computer science, radix sort is a **non-comparative integer sorting algorithm** 
that sorts data with integer keys by grouping keys by the individual digits which 
share the same significant position and value. A positional notation is required, 
but because integers can represent strings of characters (e.g., names or dates) and 
specially formatted floating point numbers, **radix sort is not limited to integers.** 
Radix sort dates back as far as 1887 to the work of Herman Hollerith on tabulating machines.

Most digital computers internally represent all of their data as electronic representations 
of binary numbers, so processing the digits of integer representations by groups of binary 
digit representations is most convenient. Radix sorts can be implemented to start at either 
the :abbr:`MSD (most significant digit)` or :abbr:`LSD (least significant digit).` 

A LSD radix sort example: ``1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11``

A MSD radix sort example: ``1, 10, 2, 3, 4, 5, 6, 7, 8, 9``

Another MSD radix sort example: ``b, ba, c, d, e, f, g, h, i, j.``

.. code-block:: none
    :caption: Taken from **Introduction to algorithm**

    Radix-Sort(A, d)
        for i=1 to d
            use a stable sort to sort array A on i_th digit