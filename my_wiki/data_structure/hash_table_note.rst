**********
Hash Table
**********

.. code-block:: none

    Direct-Address-Search(T, k)
        return T[k]

    Direct-Address-Insert(T, x)
        T[x.key] = x

    Direct-Address-Delete(T, x)
        T[x.key] = NIL

.. code-block:: none
    :caption: Taken from *Introduction to algorithms*
   
    Chained-Hash-Insert(T, x)
        insert x at the head of list T[h(x.key)]

    Chained-Hash-Search(T, k)
        search for an element with key k in list T[h(k)]

    Chained-Hash-Delete(T, x)
        delete x from the list T[h(x.key)]

    # A prime not too close to an exact power of 2 is often a good choice form m.
    Hash-byDivision(k)
        return k % m

    # 0 < A < 1
    # A = (sqrt(5) - 1)/2 as suggested by Knuth
    Hash-byMultiplication(k)
        return floor(m(kA - floor(kA)))

    # Assume to use open addressing as collision resolution
    Hash-Insert(T, k)
        i=0
        repeat 
            j=h(k,i)
            if T[j] == NIL or T[j] == DELETED
                T[j] = k
                return j
            else i = i + 1
        until i==m
        error "hash table overflow"

    Hash-Search(T, k)
        i = 0
        repeat
            j = h(k,i)
            if T[j] != DELETED and T[j] == k
                return j
            i = i + 1
        until T[j] == NIL or i == m
        return NIL

    Hash-Delete(T, k)
        i = 0
        repeat
            j = h(k,i)
            if T[j] == k
                T[k] = DELETED
                return k
            i = i + 1
        until T[j] == NIL or i == m
        error "not found"


    // collision resolution
    
    // primary clustering
    Hash-linearProbing(k, i)
        return (auxillary_hash_func(k) + i) mod m

    // secondary clustering
    Hash-quadraticProbing(k, i)
        return (auxillary_hash_func(k) + c_1 * i + c_2 * i * i) mod m

    Hash-doubleHashing(k, i)
        return (auxillary_hash_func_1(k) + i * auxillary_hash_func_2(k) ) mod m



