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

LSD radix sorts typically use the following sorting order: short keys come before longer keys, 
and then keys of the same length are sorted lexicographically. This coincides with the **normal order** 
of integer representations, such as the sequence ``1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11.``

MSD radix sorts use lexicographic order, which is suitable for sorting strings, such as words, 
or fixed-length integer representations. A sequence such as ``b, c, d, e, f, g, h, i, j, ba`` 
would be lexicographically sorted as ``b, ba, c, d, e, f, g, h, i, j.`` If lexicographic ordering 
is used to sort variable-length integer representations, then the representations of the numbers 
from 1 to 10 would be output as ``1, 10, 2, 3, 4, 5, 6, 7, 8, 9,`` as if the shorter keys were 
left-justified and padded on the right with blank characters to make the shorter keys as long as 
the longest key for the purpose of determining sorted order.

.. code-block:: py
   :caption: A python LSD implementation

   #!/usr/bin/env python
   import random
   
   def list_to_buckets(array, base, iteration):
       buckets = [[] for x in range(base)]
       for number in array:
           # Isolate the base-digit from the number
           digit = (number // (base ** iteration)) % base
           # Drop the number into the correct bucket
           buckets[digit].append(number)
       return buckets
   
   def buckets_to_list(buckets):
       numbers = []
       for bucket in buckets:
           # append the numbers in a bucket
           # sequentially to the returned array
           for number in bucket:
               numbers.append(number)
       return numbers
   
   def radix_sort(array, base=10):
       maxval = max(array)
       it = 0
       # Iterate, sorting the array by each base-digit
       while base ** it <= maxval:
           array = buckets_to_list(list_to_buckets(array, base, it))
           it += 1
       return array
   
   array = random.sample(xrange(1, 1000), 20)
   print "Before sorting: ", array
   sorted_array = radix_sort(array)
   print "After sorting: ", sorted_array