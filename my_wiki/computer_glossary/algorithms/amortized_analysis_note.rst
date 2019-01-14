******************
Amortized Analysis
******************

#. Aggregate analysis
   
    In aggregate analysis, we show that for all n, a sequence of n operations takes
    worst-case time :math:`T(n)` in total. In the worst case, the average cost, 
    or amortized cost, per operation is therefore :math:`T(n)/n`.

#. Accounting method
   
    In the accounting method of amortized analysis, we assign differing charges to
    different operations, with some operations charged more or less than they actually cost. 
    We call the amount we charge an operation its **amortized cost**. When an operation’s amortized 
    cost exceeds its actual cost, we assign the **difference** to specific objects in the data structure 
    as **credit**. Credit can help pay for later operations whose amortized cost is less than their actual cost.
    Thus, we can view the amortized cost of an operation as being split between its actual cost and credit that
    is either deposited or used up. Different operations may have different amortized costs. This method differs 
    from aggregate analysis, in which all operations have the same amortized cost.

#. Potential method
   
    Instead of representing prepaid work as credit stored with specific objects in the
    data structure, the potential method of amortized analysis represents the prepaid
    work as “potential energy,” or just “potential,” which can be released to pay for
    future operations. We associate the potential with the data structure as a whole
    rather than with specific objects within the data structure.

.. code-block:: none
    :caption: stack operation - multi-pop

    Multi-POP(s, k)
        while not STACK-EMPTY(s) and k > 0
            POP(s)
            k = k-1

.. code-block:: none
    :caption: Incrementing a binary counter
    
    Increment(A)
        i = 0
        while i < A.length and A[i] == 1
            A[i] = 0
            i = i+1
        if i < A.length
            A[i] = 1

.. code-block:: none
    :caption: Dynamic tables analysis

    Table-Insert(T, k)
        if T.size == 0
            allocate T.table with 1 slot
            T.size = 1
        if T.num == T.size
            allocate a new-table with 2*T.size slots
            insert all items in T.table into new-table
            free T.table
            T.size = 2*T.size
            T.table = new-table
        inset k into T.table
        T.num = T.num + 1

    Table-Delete(T, x)
        if T.num == 0
            error("Empty table")
        else
            find the location of x, and mark it as deleted
            T.num = T.num - 1
            if T.num < 0.25 * T.size
                allocate a new-table with 0.5 * T.size
                insert all items in T.table into new-table
                free T.table
                T.table = new-table
                T.size = T.size / 2