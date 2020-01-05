**********
Radix Tree
**********

In computer science, a **radix tree** is a data structure that represents a space-optimized **trie** (prefix tree)
in which each node is the only child id mergeed with its parents. The result is that the number of child of every
internal node is a most the radix :math:`\gamma`, where :math:`\gamma` is a positive integer and a power of 2.
unlike regular trees, edges can be labeled wiht sequences of elements as well as single emements. This makes
radix trees much more efficient for small sets (especially if the strings are long) and for sets of strings that
share long prefixes.

Radix trees are useful for constructing associative arrays with keys that can be expressed as strings.
They find particular application in the area of IP routing, where the ability to contain large ranges
of values with a few exceptions is particularly suited to the hierarchical organization of IP addresses.

Radix trees support insertion, deletion, and searching operations. Searching operations include (but are
not necessarily limited to) exact lookup, find predecessor, find successor, and find all strings with a prefix.
All of these operations are :math:`O(k)` where k is the maximum length of all strings in the set,
where length is measured in the quantity of bits equal to the radix of the radix trie.
