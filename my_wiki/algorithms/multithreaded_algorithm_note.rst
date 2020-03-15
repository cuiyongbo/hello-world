****************************
Multithreaded Algorithm Note
****************************

不要把自己当成一块砖而随波逐流，失去方向，丧失进取心，正是平庸的标志。

.. code-block:: none

    // serialization
    Fibnacci(n)
        if n <= 1
            return n
        else
            x = Fibnacci(n-1)
            y = Fibnacci(n-2)
            return x+y

    // add concurrency
    P-Fibnacci(n)
        if n <= 1
            return n
        else
            x = spawn P-Fibnacci(n-1)
            y = P-Fibnacci(n-2)
            sync
            return x+y
