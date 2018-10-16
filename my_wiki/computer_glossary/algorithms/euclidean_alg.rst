*******************
Euclidean Algorithm
*******************

**Introduction**

.. image:: images/Euclid's_algorithm.png

In mathematics, the Euclidean algorithm, is an efficient method for computing the :abbr:`GCD (greatest common divisor)` 
of two numbers, the largest number that divides both of them without leaving a remainder. It is named after the ancient 
Greek mathematician **Euclid,** who first described it in his **Elements** (c. 300 BC). It is an example of an algorithm, 
a step-by-step procedure for performing a calculation according to well-defined rules, and is one of the oldest algorithms 
in common use. It can be used to reduce fractions to their simplest form, and is a part of many other number-theoretic 
and cryptographic calculations.

The Euclidean algorithm is based on the principle that **the greatest common divisor of two numbers does not change 
if the larger number is replaced by its difference with the smaller number.** For example, 21 is the GCD of 252 and 105, 
and the same number 21 is also the GCD of 105 and 252 − 105 = 147. Since this replacement reduces the larger of the 
two numbers, repeating this process gives successively smaller pairs of numbers until the two numbers become equal. 
When that occurs, they are the GCD of the original two numbers. By reversing the steps, the GCD can be expressed as 
a sum of the two original numbers each multiplied by a positive or negative integer, e.g., 21 = 5 × 105 + (−2) × 252. 
The fact that the GCD can always be expressed in this way is known as **Bézout's identity.**

The version of the Euclidean algorithm described above (and by Euclid) can take many **subtraction** steps 
to find the GCD when one of the given numbers is much bigger than the other. A more efficient version of 
the algorithm shortcuts these steps, instead replacing the larger of the two numbers by its **remainder** 
when divided by the smaller of the two (with this version, the algorithm stops when reaching a zero remainder). 
With this improvement, the algorithm never requires more steps than five times the number of digits (base 10) 
of the smaller integer. This was proven by *Gabriel Lamé* in 1844, and marks the beginning of 
**computational complexity theory.** 

The Euclidean algorithm has many theoretical and practical applications. 
It is used for reducing fractions to their simplest form and for performing 
division in modular arithmetic. Computations using this algorithm form part 
of the cryptographic protocols that are used to secure internet communications, 
and in methods for breaking these cryptosystems by factoring large composite numbers. 
The Euclidean algorithm may be used to solve Diophantine equations, such as finding 
numbers that satisfy multiple congruences according to the Chinese remainder theorem, 
to construct continued fractions, and to find accurate rational approximations to real numbers. 
Finally, it can be used as a basic tool for proving theorems in number theory such as Lagrange's 
four-square theorem and the uniqueness of prime factorizations. The original algorithm was described 
only for natural numbers and geometric lengths (real numbers), but the algorithm was generalized in 
the 19th century to other types of numbers, such as Gaussian integers and polynomials of one variable. 
This led to modern abstract algebraic notions such as Euclidean domains.

.. code-block:: none
   :caption: Implementation

   // gcd - greatest common divisor 
   // or
   // gcf - greatest common factor

   gcd-division(a, b)
      while b != 0
         t = b
         b = a mod b
         a = t
      return a

   gcd-recursion(a, b)
      if b == 0
         return a
      else 
         return gcd(b, a mod b)

   gcd-substraction(a, b)
      while a != b
         if a>b
            a = a - b
         else
            b = b - a
      return a
