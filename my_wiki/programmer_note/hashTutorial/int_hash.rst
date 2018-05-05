Integer Hash Function
=====================

Abstract
--------

An integer hash function accepts an integer hash key, and returns an
integer hash result with **uniform distribution**. In this article, we will
be discussing the construction of integer hash functions.

Introduction
------------

Hash table is an important data structure. All elementary data structure
text books contain some algorithms of hash table. However, all too often
the treatment of hash function is discussed as an after-thought. Thus
examples abound in systems where the poor choice of the hash function
resulted in inferior performance.

Certainly the integer hash function is the most basic form of the hash
function. The integer hash function transforms an integer hash key into
an integer hash result. **For a hash function, the distribution should be
uniform.** This implies when the hash result is used to calculate hash
bucket address, all buckets are equally likely to be picked. In
addition, similar hash keys should be hashed to very different hash
results. Ideally, a single bit change in the hash key should influence
all bits of the hash result.


Hash Function Construction Principles
-------------------------------------

A good mixing function must be reversible. A hash function has form ``h(x)-> y``.
If the input word size and the output word size are identical, and in addition
the operations in ``h()`` are reversible, then the following properties are true.

#. If ``h(x1) == y1``, then there is an inverse function ``h_inverse(y1) == x1``
   
#. Because the inverse function exists, there cannot be a value *x2*
   such that ``x1 != x2``, and ``h(x2) == y1``.

The case of ``h(x1) == y1``, and ``h(x2) == y1`` is called a **collision**.
Using only reversible operations in a hash function makes collisions
impossible. There is an one-to-one mapping between the input and the
output of the mixing function.

Beside reversibility, the operations must use a chain of computations to
achieve **avalanche**. Avalanche means that a single bit of difference in
the input will make about 1/2 of the output bits be different. At a
point in the chain, a new result is obtained by a computation involving
earlier results.

For example, the operation ``a = a + b`` is reversible if we know the value
of *b*, and the after value of *a*. The before value of *a* is obtained
by subtracting the after value of *a* with the value of *b*.


Knuth's Multiplicative Method
-----------------------------

In Knuth's *The Art of Computer Programming*, section 6.4, a
multiplicative hashing scheme is introduced as a way to write hash
function. The key is multiplied by the golden ratio of :math:`2^{32}`
(:math:`2^{31} - 1`) to produce a hash result.

Since :math:`2^{31} - 1` and :math:`2^{32}` has no common factors in
common, the multiplication produces a complete mapping of the key to
hash result with no overlap. This method works pretty well if the keys
have small values. Bad hash results are produced if the keys vary in 
the upper bits. As is true in all multiplications, variations of
upper digits do not influence the lower digits of the multiplication
result.


Robert Jenkins' 96 bit Mix Function
-----------------------------------

Robert Jenkins has developed a hash function based on a sequence
of subtraction, exclusive-or, and bit shift. Click `here`_ to check it.

.. _here: http://www.burtleburtle.net/bob/hash/doobs.html

All the sources in this article are written as Java methods, where the
operator ``>>>`` represents the concept of unsigned right shift. If the
source were to be translated to C, then the Java ``int`` data type should
be replaced with C ``uint32_t`` data type, and the Java ``long`` data type
should be replaced with C ``uint64_t`` data type.

The following source is the mixing part of the hash function::

   int mix(int a, int b, int c)
   {
     a=a-b; a=a-c; a=a^(c >>> 13);
     b=b-c; b=b-a; b=b^(a << 8);
     c=c-a; c=c-b; c=c^(b >>> 13);
     a=a-b; a=a-c; a=a^(c >>> 12);
     b=b-c; b=b-a; b=b^(a << 16);
     c=c-a; c=c-b; c=c^(b >>> 5);
     a=a-b; a=a-c; a=a^(c >>> 3);
     b=b-c; b=b-a; b=b^(a << 10);
     c=c-a; c=c-b; c=c^(b >>> 15);
     return c;
   }

Variable *c* contains the input key. When the mixing is complete,
variable *c* also contains the hash result. Variable *a*, and *b*
contain initialized random bits. Notice the total number of internal
state is 96 bits, much larger than the final output of 32 bits. Also
notice the sequence of subtractions rolls through variable *a* to
variable *c* three times. Each row will act on one variable, mixing in
information from the other two variables, followed by a shift operation.

Subtraction is similar to multiplication in that changes in upper bits
of the key do not influence lower bits of the addition. The 9 bit shift
operations in Robert Jenkins' mixing algorithm shifts the key to the
right 61 bits in total, and shifts the key to the left 34 bits in total.
As the calculation is chained, each exclusive-or doubles the number of
states. There are at least :math:`2^9` different combined versions of the
original key, shifted by various amounts. That is why a single bit
change in the key can influence widely apart bits in the hash result.

The uniform distribution of the hash function can be determined from the
nature of the subtraction operation. Look at a single bit subtraction
operation between a key, and a random bit. If the random bit is 0, then
the key remains unchanged. If the random bit is 1, then the key will be
flipped. A carry will occur in the case where both the key bit and the
random bit are 1. Subtracting the random bits will cause about half of
the key bits to be flipped. So even if the key is not uniform,
subtracting the random bits will result in uniform distribution.


32 bit Mix Functions
--------------------

Based on an original suggestion on Robert Jenkin's part in 1997, I have
done some research for a version of the integer hash function. This is
my latest version as of January 2007. The specific value of the bit
shifts are obtained from running the accompanied search program::

   public int hash32shift(int key)
   {
      key = ~key + (key << 15); // key = (key << 15) - key - 1;
      key = key ^ (key >>> 12);
      key = key + (key << 2);
      key = key ^ (key >>> 4);
      key = key * 2057; // key = (key + (key << 3)) + (key << 11);
      key = key ^ (key >>> 16);
      return key;
   }

``(~x) + y`` is equivalent to ``y - x - 1`` in two's complement representation.

By taking advantages of the native instructions such as 'add
complement', and 'shift & add', the above hash function runs in 11
machine cycles on HP 9000 workstations.

Having more rounds will strengthen the hash function by making the
result more random looking, but performance will be slowed down
accordingly. Simulation seems to prefer small shift amounts for inner
rounds, and large shift amounts for outer rounds.


Robert Jenkins' 32 bit integer hash function
--------------------------------------------

.. code-block:: java

   uint32_t hash( uint32_t a)
   {
      a = (a+0x7ed55d16) + (a<<12);
      a = (a^0xc761c23c) ^ (a>>19);
      a = (a+0x165667b1) + (a<<5);
      a = (a+0xd3a2646c) ^ (a<<9);
      a = (a+0xfd7046c5) + (a<<3);
      a = (a^0xb55a4f09) ^ (a>>16);
      return a;
   }

This version of integer hash function uses operations with integer
constants to help producing a hash value. I suspect the actual values of
the magic constants are not very important. Even using 16 bit constants
may still work pretty well.

These magic constants open up the construction of perfect integer hash
functions. A test program can vary the magic constants until a set of
perfect hashes are found.


Using Multiplication for Hashing
--------------------------------

Using multiplication requires a mechanism to transport changes from high
bit positions to low bit positions. Bit reversal is best, but is slow to
implement. A viable alternative is left shifts.

Using multiplication presents some sort of dilemma. Certain machine
platforms supports integer multiplication in hardware, and an integer
multiplication can be completed in 4 or less cycles. But on some other
platforms an integer multiplication could take 8 or more cycles to
complete. On the other hand, integer hash functions implemented with bit
shifts perform equally well on all platforms.

A compromise is to multiply the key with a 'sparse' bit pattern, where
on machines without fast integer multiplier they can be replaced with a
'shift & add' sequence. An example is to multiply the key with ``(4096 + 8 + 1)``,
with an equivalent expression of ``(key + (key << 3) + (key << 12))``.

On most machines a bit shift of 3 bits or less, following by an addition
can be performed in one cycle. For example, Pentium's ``lea`` instruction
can be used to good effect to compute a 'shift & add' in one cycle.

Function ``hash32shiftmult()`` uses a combination of bit shifts and integer
multiplication to hash the input key::

   public int hash32shiftmult(int key)
   {
     int c2=0x27d4eb2d; // a prime or an odd constant
     key = (key ^ 61) ^ (key >>> 16);
     key = key + (key << 3);
     key = key ^ (key >>> 4);
     key = key * c2;
     key = key ^ (key >>> 15);
     return key;
   }


64 bit Mix Functions
--------------------

.. code-block:: java

   public long hash64shift(long key)
   {
     key = (~key) + (key << 21); // key = (key << 21) - key - 1;
     key = key ^ (key >>> 24);
     key = key + (key << 3) + (key << 8); // key * 265
     key = key ^ (key >>> 14);
     key = key + (key << 2) + (key << 4); // key * 21
     key = key ^ (key >>> 28);
     key = key + (key << 31);
     return key;
   }

The longer width of 64 bits require more mixing than the 32 bit version.


64 bit to 32 bit Hash Functions
-------------------------------

One such use for this kind of hash function is to hash a 64 bit virtual
address to a hash table index. Because the output of the hash function
is narrower than the input, the result is no longer one-to-one.

Another usage is to hash two 32 bit integers into one hash value::

   public int hash6432shift(long key)
   {
      key = (~key) + (key << 18); // key = (key << 18) - key - 1;
      key = key ^ (key >>> 31);
      key = key + (key << 2) + (key << 4); // key = key * 21;
      key = key ^ (key >>> 11);
      key = key + (key << 6);
      key = key ^ (key >>> 22);
      return (int) key;
   }


Parallel Operations
-------------------

If a CPU can dispatch multiple instructions in the same clock cycle, one
can consider adding more parallelism in the formula.

For example, for the following formula, the two shift operations can be
performed in parallel. On certain platforms where there are multiple
ALUs but a single shifter unit, this idea does not offer a speed
increase::

   key ^= (key << 17) | (key >>> 16);

For 32 bit word operations, only certain pairs of shift amounts will be
reversible. The valid pairs include: (17,16) (16,17) (14,19) (19,14)
(13,20) (20,13) (10,23) (23,10) (8,25) (25,8)

Multiplication can be computed in parallel. Any multiplication with odd
number is reversible::

   key += (key << 3) + (key << 9); // key = key * (1 + 8 + 512)

On certain machines, bit rotation can be performed in one cycle. Any odd
number bits rotation can be made reversible when exclusive-or is applied
to the un-rotated key with one particular bit set to 1 or 0::

   key = (key | 64) ^ ((key >>> 15) | (key << 17));

However, on certain machine and compiler combinations, this code
sequence can run as slow as 4 cycles. 2 cycles: a win, 3 cycles: tie,
more than 3 cycles: a loss.


Pseudo Random Usages
--------------------

There has been queries whether these mix functions can be used for
pseudo random purposes. Although the out does look random to the naked
eye, the official recommendation is to use a real pseudo random number
generator instead, such as the `Mercenne Twister`_.

.. _Mercenne Twister: http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html

The hash functions listed in this article were only tested for hashing
purpose. No tests of randomness were performed.


Test Program
------------

This is a `test program`_ testing the choices of the shift amounts with
regard to the resulting avalanche property. The program detects if a
certain bit position has both changes and no changes, based on a single
bit flip. Promising candidates are further tested to verify the percentage
chance of bit flip is sufficiently close to 50% for all input and output
bit pairs.

The test program prints out the name of the algorithm under test,
followed by the list of shift amounts that pass the avalanche test.

.. _test program: http://www.concentric.net/~Ttwang/tech/testchange.java


Power of 2 Hash Table Size
--------------------------

Programmer uses hash table size that is power of 2 because address
calculation can be performed very quickly. The integer hash function can
be used to post condition the output of a marginal quality hash function
before the final address calculation is done::

   addr = inthash(marginal_hash_value) & (tablesize - 1);
   // addr = inthash(marginal_hash_value) % tablesize;

Using the inlined version of the integer hash function is faster than
doing a remaindering operation with a prime number! An integer remainder
operation may take up to 18 cycles or longer to complete, depending on
machine architecture.


Conclusions
-----------

In this article, we have examined a number of hash function construction
algorithms. Knuth's multiplicative method is the simplest, but has some
known defects. Robert Jenkins' 96 bit mix function can be used as an
integer hash function, but is more suitable for hashing long keys. A
dedicated hash function is well suited for hashing an integer number.

We have also presented an application of the integer hash function to
improve the quality of a hash value.
