**********
dict notes
**********

================ ===========================================================
Operation        Result                                               
================ ===========================================================
len(d)           number of elements in dict d            
key (not) in d   test whether key in dict d or not, shortcut for has_key() 
d[key] = values  
del d[key]       remove key from dict d
iter(d)          return an iterator over keys of d, shortcut for iterkeys() 
d.copy()         new set with a shallow copy of d                     
================ ===========================================================

.. code-block:: py

   >>> dir(dict)
   ['clear', 'copy', 'fromkeys', 'get', 'has_key', 'items', 'iteritems', 
   'iterkeys', 'itervalues', 'keys', 'pop', 'popitem', 'setdefault', 'update', 
   'values', 'viewitems', 'viewkeys', 'viewvalues']

   >>> a = dict(one=1, two=2, three=3)
   >>> b = {'one':1, "two":2, "three":3}
   >>> c = dict(zip(['one', 'two', 'three'], [1,2,3]))
   >>> d = dict([("one", 1), ("two", 2), ('three', 3)])
   >>> a == b == c == d
   True

   >>> for item in a.items():
   ...     print "key: ", item[0], " value: ", item[1]
   ... 
   key:  three  value:  3
   key:  two  value:  2
   key:  one  value:  1
   >>> for k in iter(a):
   ...     print "key: ", k, " value: ", a[k]
   ... 
   key:  three  value:  3 
   key:  two  value:  2 
   key:  one  value:  1

   >>> e = {"four": 4}
   >>> a.update(e)
   >>> a
   {'four': 4, 'three': 3, 'two': 2, 'one': 1}
   >>> e["four"] = 40
   >>> a.update(e)
   >>> a
   {'four': 40, 'three': 3, 'two': 2, 'one': 1}

   >>> del e['four']
   >>> e.fromkeys(["1", "2", "3"], [1,2,3])
   {'1': [1, 2, 3], '3': [1, 2, 3], '2': [1, 2, 3]}

