***********************************
random - Random variable generators
***********************************

**Overview**

   .. code-block:: none
      
      integers
      --------
         uniform within range
   
      sequences
      ---------
         pick random element
         pick random sample
         generate random permutation
   
      distributions on the real line:
      ------------------------------
         uniform
         triangular
         normal (Gaussian)
         lognormal
         negative exponential
         gamma
         beta
         pareto
         Weibull
    
      distributions on the circle (angles 0 to 2pi)
      ---------------------------------------------
         circular uniform
         von Mises
 
   General notes on the underlying Mersenne Twister core generator:
    
      * The period is ``2**19937-1.``
      
      * Without a direct way to compute N steps forward, the semantics of
        jumpahead(n) are weakened to simply jump to another distant state 
        and rely on the large period to avoid overlapping sequences.

      * The random() method is implemented in C, executes in a single 
        Python step, and is, therefore, threadsafe.        

**Examples**

#. return a number in a certain list
 
   .. code-block:: py
   
      >>> random.randint(1, 1000)
      618
      
      # randint(self, a, b)
      #  Return random integer in range [a, b], including both end points.

#. return a random member from a sequence
   
   .. code-block:: py

      >>> random.choice(xrange(1, 100))
      60
      >>> random.choice("hello world")
      'o'
      
      # choice(self, seq)
      #  Return a random element from the non-empty sequence seq. 
      #  If seq is empty, raises IndexError.

#. generate a list in a certain range
   
   .. code-block:: py

      >>> random.sample(xrange(1, 100), 5)
      [31, 73, 15, 43, 74]

   # sample(self, population, k) 
   #  Chooses k unique random elements from a population sequence.
   #  
   #  Returns a new list containing elements from the population while
   #  leaving the original population unchanged. 
   #  
   #  Members of the population need not be hashable or unique. If the
   #  population contains repeats, then each occurrence is a possible
   #  selection in the sample.
   #  
   #  To choose a sample in a range of integers, use xrange as an argument.
   #  This is especially fast and space efficient for sampling from a
   #  large population:  sample(xrange(10000000), 60)

#. shuffle a sequence
   
   .. code-block:: py

      >>> a = range(1,10)
      >>> random.shuffle(a)
      >>> a
      [6, 4, 2, 9, 8, 7, 3, 5, 1]

      # shuffle(self, x[, random])   
      #  Shuffle the sequence x in place. The optional argument random is 
      #  a 0-argument function returning a random float in [0.0, 1.0); 
      #  by default, this is the function random().

   .. note::

      Note that for even rather small len(x), the total number of permutations 
      of x is larger than the period of most random number generators; 
      this implies that most permutations of a long sequence can never be generated.
