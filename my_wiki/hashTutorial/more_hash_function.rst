*******************
More Hash Functions
*******************

#. Multiplicative hashing

    Multiplicative hashing is a simple type of hash function often used
    by teachers introducing students to hash tables. Multiplicative hash
    functions are simple and fast, but have higher collision rates in hash
    tables than more sophisticated hash functions. Standard multiplicative
    hashing uses the formula

    .. math:: h_a(x) = [(ax\ mod\ W) / (W / M)]

    which produces a hash value in ``[0, M-1]``. The value *a* is an appropriately
    chosen value that should be relatively prime to *W*. An important practical
    special case occurs when :math:`W = 2^w` and :math:`M = 2^m` are powers of 2
    and *w* is the machine word size. In this case this formula becomes

    .. math:: h_a(x) = [ax\ mod\ 2^w] / 2^{w-m}

    This is special because arithmetic modulo :math:`2^w` is done by default in low-level
    programming languages (ax is an integer between [0, 2^w] because w is the number of bits in an integer)
    and integer division by a power of 2 is simply a right-shift, so, in C, for example, this function becomes::

        unsigned hash(unsigned x
        {
           return (a*x) >> (w-m)
        }

    and (for fixed *m* and *w* this translates into a single integer multiplication and
    right-shift making it one of the fastest hash functions to compute. Furthermore, if
    *a* is a uniformly random odd integer in :math:`\{1, ..., 2^w -1\}` then this hash function
    is nearly universal in the sense that, for any :math:`x \neq y, Pr\{h_a(x) = h_a(y)\} \le 2/m`.

    Refer to :doc:`Integer Hash Function <integer_hash_function>` for more information about how to hash integer keys.

#. Perfect hashing

    A hash function that is injective—that is, maps each valid input to a different hash value—is
    said to be perfect. With such a function one can directly locate the desired entry in a hash
    table, without any additional searching.

    A perfect hash function for *n* keys is said to be **minimal** if its range consists of *n* consecutive
    integers, usually from 0 to n−1. Besides providing single-step lookup, a minimal perfect hash function
    also yields a compact hash table, without any vacant slots. Minimal perfect hash functions are much
    harder to find than perfect ones with a wider range.

    +---------------------------------------+-----------------------------------------------+
    | Perfect Hashing                       | Minimal Perfect Hashing                       |
    +=======================================+===============================================+
    | .. image:: images/perfect_hashing.svg | .. image:: images/minimal_perfect_hashing.svg |
    +---------------------------------------+-----------------------------------------------+

#. Universal hashing

    A universal hashing scheme is a randomized algorithm that selects a hashing function *h* among a family
    of such functions, in such a way that the probability of a collision of any two distinct keys is 1/n,
    where *n* is the number of distinct hash values desired—independently of the two keys. Universal hashing
    ensures (in a probabilistic sense) that the hash function application will behave as well as if it were
    using a random function, for any distribution of the input data. It will, however, have more collisions
    than perfect hashing and may require more operations than a special-purpose hash function.


#. Efficient hashing of strings

    Modern microprocessors will allow for much faster processing, if 8-bit character strings are not hashed by
    processing one character at a time, but by interpreting the string as an array of 32 bit or 64 bit integers
    and hashing/accumulating these "wide word" integer values by means of arithmetic operations (e.g. multiplication
    by constant and bit-shifting). The remaining characters of the string which are smaller than the word length of
    the CPU must be handled differently (e.g. being processed one character at a time). This approach has proven to
    speed up hash code generation by a factor of five or more on modern microprocessors of a word size of 64 bit.

    Another approach is to convert strings to a 32 or 64 bit numeric value and then apply a hash function.
    One method that avoids the problem of strings having great similarity (``"Aaaaaaaaaa"`` and ``"Aaaaaaaaab"``)
    is to use a :abbr:`CRC (Cyclic redundancy check)` of the string to compute a 32- or 64-bit value. While it is
    possible that two different strings will have the same CRC, the likelihood is very small and only requires that
    one check the actual string found to determine whether one has an exact match. CRCs will be different for strings
    such as ``"Aaaaaaaaaa"`` and ``"Aaaaaaaaab"``. Although CRC codes can be used as hash values, they are not
    cryptographically secure, because they are not **collision-resistant**.

    .. note::

       Collision resistance is a property of cryptographic hash functions: a hash function *H*
       is collision resistant if it is hard to find two inputs that hash to the same output.

#. Hashing with cryptographic hash functions

    Some cryptographic hash functions, such as SHA-1, have even stronger uniformity guarantees
    than checksums or fingerprints, and thus can provide very good general-purpose hashing functions.

    In ordinary applications, this advantage may be too small to offset their much higher cost.
    However, this method can provide uniformly distributed hashes even when the keys are chosen
    by a malicious agent. This feature may help to protect services against :abbr:`DoS (denial of service attacks)`.
