****************
Python set notes
****************

=========================== ============ =====================================================
Operation                   Equivalent   Result                                               
=========================== ============ =====================================================
len(s)                                   number of elements in set s            
x in s                                   test x for membership in s                           
x not in s                               test x for non-membership in s                       
s.issubset(t)               s <= t       test whether every element in s is in t              
s.issuperset(t)             s >= t       test whether every element in t is in s              
s.union(t)                  s | t        new set with elements from both s and t              
s.intersection(t)           s & t        new set with elements common to s and t              
s.difference(t)             s - t        new set with elements in s but not in t              
s.symmetric_difference(t)   s ^ t        new set with elements in either s or t but not both  
s.copy()                                 new set with a shallow copy of s                     
=========================== ============ =====================================================

.. code-block:: python 

   >>> dir(set)
   ['add', 'clear', 'copy', 'difference', 'difference_update', 'discard', 'intersection', 'intersection_update', 
   'isdisjoint', 'issubset', 'issuperset', 'pop', 'remove', 'symmetric_difference', 'symmetric_difference_update', 
   'union', 'update']

   >>> s3 = s1 | s2
   >>> s1.update(s2) # Update a set with the union of itself and others.
   >>> s1 == s3
   True

   >>> s3 = s1 & s2
   >>> s1.intersection_update(s2) # Update a set with the intersection of itself and another.
   >>> s1==s3
   True

   >>> s3 = s1 - s2
   >>> s1.difference_update(s2) # Update a set with the difference of itself and another.
   >>> s1 == s3
   True

   >>> s3 = s1.symmetric_difference(s2)
   >>> s1.symmetric_difference_update(s2) # Update a set with the symmetric_difference of itself and another.
   >>> s1 == s3
   True

   # isdisjoint(...)
   #     Return True if two sets have a null intersection.

   # remove(...)
   #  Remove an element from a set; it must be a member.
   #  If the element is not a member, raise a KeyError.

   # discard(...)
   #  Remove an element from a set; it must be a member.
   #  If the element is not a member, do nothing.