***********************************
Section 6.1 Linear Probing by Steps
***********************************

How can we avoid **primary clustering?** One possible improvement might be to use linear
probing, but to skip slots by some constant *c* other than 1. This would make the probe
function *probe(K, i) = ci*, and so the :math:`i^{th}` slot in the probe sequence will
be ``(hash(K) + ic)%M``. In this way, records with adjacent home positions will not
follow the same probe sequence.

One quality of a good probe sequence is that it will cycle through all slots in the
hash table before returning to the home position. Clearly linear probing (which
"skips" slots by one each time) does this. Unfortunately, not all values for *c*
will make this happen. For example, if ``c = 2`` and the table contains an even
number of slots, then any key whose home position is in an even slot will have
a probe sequence that cycles through only the even slots. Likewise, the probe
sequence for a key whose home position is in an odd slot will cycle through the
odd slots. Thus, this combination of table size and linear probing constant
effectively divides the records into two sets stored in two disjoint sections
of the hash table. So long as both sections of the table contain the same number
of records, this is not really important. However, just from chance it is likely
that one section will become fuller than the other, leading to more collisions and
poorer performance for those records. The other section would have fewer records,
and thus better performance. But the overall system performance will be degraded,
as the additional cost to the side that is more full outweighs the improved
performance of the less-full side.

**Constant c must be relatively prime to M to generate a linear probing sequence
that visits all slots in the table (that is, c and M must share no factors).**
For a hash table of size ``M = 10``, if *c* is any one of 1, 3, 7, or 9, then the
probe sequence will visit all slots for any key. When ``M = 11``, any value for
*c* between 1 and 10 generates a probe sequence that visits all slots for every key.

Consider the situation where ``c = 2`` and we wish to insert a record with key *k1*
such that ``h(k1) = 3``. The probe sequence for *k1* is 3, 5, 7, 9, and so on.
If another key *k2* has home position at slot 5, then its probe sequence will be
5, 7, 9, and so on. The probe sequences of *k1* and *k2* are linked together
in a manner that contributes to clustering. In other words, linear probing with a
value of ``c > 1`` does not solve the problem of primary clustering. We would like
to find a probe function that does not link keys together in this way. We would prefer
that the probe sequence for *k1* after the first step on the sequence should not be
identical to the probe sequence of *k2*. Instead, their probe sequences should diverge.
