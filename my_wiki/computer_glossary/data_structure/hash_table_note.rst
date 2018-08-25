**********
Hash Table
**********

.. code-block:: none
   :caption: Taken from *Introduction to algorithms*
   
   Chained-Hash-Insert(T, x)
      insert x at the head of list T[h(x.key)]

   Chained-Hash-Search(T, k)
      search for an element with key k in list T[h(k)]

   Chained-Hash-Delete(T, x)
      delete x from the list T[h(x.key)]

   # A prime not too cose to an exact power of 2 is often a good choice form m.
   Hash-byDivision(k)
      return k mod m

   # 0 < A < 1
   # A = (sqrt(5) - 1)/2 as suggested by Knuth
   Hash-byMultiplication(k)
      return floor(m(kA - floor(kA)))

