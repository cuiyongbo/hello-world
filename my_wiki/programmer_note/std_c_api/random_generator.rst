****************
Random generator
****************

**DESCRIPTION**
   
   .. code-block:: c

      #include <stdlib.h>
      int rand(void);
      int rand_r(unsigned *seed);
      void srand(unsigned seed);
      void sranddev(void);

   These interfaces are obsoleted by **arc4random(3).**

   The *rand()* function computes a sequence of pseudo-random integers 
   in the range of 0 to ``RAND_MAX`` (as defined in **stdlib.h**).

   The *srand()* function sets its argument *seed* as the seed 
   for a new sequence of pseudo-random numbers to be returned by *rand()*.
   These sequences are repeatable by calling *srand()* with the same seed value.

   If no seed value is provided, the functions are automatically seeded with a value of 1.

   The *sranddev()* function initializes a seed, using the **random(4)** random number device 
   which returns good random numbers. However, the *rand()* function still remains unsuitable 
   for cryptographic use.

   The *rand_r()* function provides the same functionality as *rand().*  
   A pointer to the *context* value seed must be supplied by the caller.
