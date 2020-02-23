*****************************
Section 6.3 Quadratic Probing
*****************************

Another probe function that eliminates **primary clustering** is called quadratic probing.
Here the probe function is some quadratic function :math:`probe(K, i) = c_1 i^2 + c_2 i + c_3`
for some choice of constants :math:`c_1, c_2, c_3`.

The simplest variation is :math:`probe(K, i) = i^2 (i.e., c_1 = 1, c_2 = 0, c_3 = 0)`.
Then the :math:`i^{th}` value in the probe sequence would be :math:`(hash(K) + i^2) % M`.
Under quadratic probing, two keys with different home positions will have diverging probe
sequences.

Unfortunately, quadratic probing has the disadvantage that typically not all hash table slots
will be on the probe sequence. Using :math:`probe(K, i) = i^2` gives particularly inconsistent
results. For many hash table sizes, this probe function will cycle through a relatively small
number of slots. If all slots on that cycle happen to be full, this means that the record cannot
be inserted at all! For example A table with 105 slots. The probe sequence starting
from any given slot will only visit 23 other slots in the table. If all 24 of these slots should
happen to be full, even if other slots in the table are empty, then the record cannot be inserted
because the probe sequence will continually hit only those same 24 slots.

.. code-block:: py

    m = 105
    for i in range(m):
        s = set(); j=1
        while True:
                k = i + j**2
                if k%m == i: break
                s.add(k%m)
                j += 1
        print(len(s))

Fortunately, it is possible to get good results from quadratic probing at low cost. The right
combination of probe function and table size will visit many slots in the table. In particular,
if the hash table size is a prime number and the probe function is :math:`probe(K, i) = i^2`,
then at least half the slots in the table will be visited. Thus, if the table is less than half
full, we can be certain that a free slot will be found. Alternatively, if the hash table size is
a power of two and the probe function is :math:`probe(K, i) = (i^2 + i)/2` then every slot in
the table will be visited by the probe function.
