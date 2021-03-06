*********************************
Section 6.2 Pseudo-random Probing
*********************************

The ideal probe function would select the next position
on the probe sequence at random from among the unvisited
slots; that is, the probe sequence should be a random
permutation of the hash table positions. Unfortunately,
we cannot actually select the next position in the probe
sequence at random, because we would not be able to duplicate
this same probe sequence when searching for the key. However,
we can do something similar called **pseudo-random probing**.
In pseudo-random probing, the :math:`i^{th}` slot in the probe
sequence is :math:`(hash(K) + r_i)%M` where :math:`r_i` is the
:math:`i^{th}` value in a random permutation of the numbers
from 1 to M-1. All insertions and searches use the same sequence
of random numbers. The probe function would be
*probe(K, i) = Perm[i-1]* where *Perm* is an array of length ``M-1``
containing a random permutation of the values from 1 to ``M-1``.
