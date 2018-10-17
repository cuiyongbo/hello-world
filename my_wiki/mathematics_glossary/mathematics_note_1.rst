*******************
Mathematics Notes 1
*******************

An amateur practices until he can get it right. 
A professional practices until he cannot get it wrong.

#. how to solve quardratic equation :math:`ax^2 + bx + c = 0` (solved)
   
   .. math::

      x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}

#. Combination 
   
   In mathematics, a combination is a selection of items from a collection, 
   such that (unlike permutations) the order of selection does not matter. 
   More formally, a k-combi
   of S. If the set has n elements, the number of k-combinations is equal to 
   the binomial coefficient.

   .. math::

      {\binom {n}{k}} &= {\frac {n(n-1)\dotsb (n-k+1)}{k(k-1)\dotsb 1}} \\
                      &= {\frac {n!}{k!(n-k)!}}

#. k-permutations of n

   A weaker meaning of the term permutation, sometimes used in elementary combinatorics texts, 
   designates those ordered arrangements in which no element occurs more than once, but without 
   the requirement of using all the elements from a given set. These are not permutations except 
   in special cases, but are natural generalizations of the ordered arrangement concept. 
   Indeed, this use often involves considering arrangements of a fixed length k of elements 
   taken from a given set of size n, in other words, these k-permutations of n are the different 
   ordered arrangements of a k-element subset of an n-set. The number of such k-permutations of n 
   is denoted variously by such symbols as :math:`P_{k}^{n}, P_{n,k}, \text{ or } P(n,k)`, and 
   its value is given by the product
   
   .. math::
   
      P(n,k) = \underbrace {n\cdot (n-1)\cdot (n-2)\cdots (n-k+1)} _{k\ \mathrm {factors} }, \\
      \text{ which is 0 when k > n, and otherwise is equal to } {\frac {n!}{(n-k)!}}.
   
   This usage of the term permutation is closely related to the term combination. 
   A k-element combination of an n-set S is a k element subset of S, the elements 
   of which are not ordered. By taking all the k element subsets of S and ordering 
   each of them in all possible ways we obtain all the k-permutations of S. The number 
   of k-combinations of an n-set, :math:`C(n,k),` is therefore related to the number 
   of k-permutations of n by:
   
   .. math:: 
   
      {C(n,k)={\frac {P(n,k)}{P(k,k)}}
            ={\frac {\tfrac {n!}{(n-k)!}}{\tfrac {k!}{0!}}}
            ={\frac {n!}{(n-k)!\,k!}}.}
   
   These numbers are also known as binomial coefficients and denoted :math:`{\binom {n}{k}}.`
   
#. Natural Exponent
   
   The real exponential function :math:`{\exp :\mathbb {R} \to \mathbb {R} }` 
   can be characterized in a variety of equivalent ways. Most commonly, 
   it is defined by the following power series:

   .. math::

      {\exp(x)=\sum_{k=0}^{\infty} {\frac {x^{k}}{k!}}} 

   Since the radius of convergence of this power series is infinite, 
   this definition is, in fact, applicable to all complex numbers :math:`z\in\mathbb{C}`. 
   The constant :math:`e` can then be defined as :math:`{\textstyle e=\exp(1)=\sum_{k=0}^{\infty}(1/k!).}`
   
#. Modular arithmetic
   
   If (a mod n) = (b mod n), we write :math:`a \equiv b \pmod n` 
   and say that a is **equivalent** to b, modulo n. In other words, 
   :math:`a \equiv b \pmod n` if a and b have the same remainder when 
   divided by n. Equivalently, :math:`a \equiv b \pmod n` if and only if 
   n is a divisor of b - a.

#. multiplicative inverse [倒数]

   In mathematics, a **multiplicative inverse** or **reciprocal** for a number x, as
   denoted by :math:`\frac{1}{x}` or :math:`x^{−1}`, is a number which when multiplied
   by x yields the multiplicative identity, 1. The multiplicative inverse of a fraction
   :math:`\frac{a}{b}` is :math:`\frac{b}{a}`. For the multiplicative inverse of a real
   number, divide 1 by the number. The reciprocal function, the function *f(x)* that maps *x* 
   to :math:`\frac{1}{x}`, is one of the simplest examples of a function which is its own inverse
   (an involution).
   
   .. figure:: images/one_over_x.png
   
      The reciprocal function: :math:`y = \frac{1}{x}`. 
      For every x except 0, y represents its multiplicative inverse.

#. Additive inverse [相反数]
 
   In mathematics, the additive inverse of a number *a* is the number that, 
   when added to *a*, yields zero. This number is also known as the opposite (number), 
   sign change, and negation. For a real number, it reverses its sign: the opposite to 
   a positive number is negative, and the opposite to a negative number is positive.

#. Lemma

   In mathematics, a "helping theorem" or lemma (plural lemmata or lemmas) 
   from the Ancient Greek λῆμμα (lemma, "anything which is received, such as 
   a gift, profit, or a bribe”) is a proven proposition which is used as a 
   stepping stone to a larger result rather than as a statement of interest 
   by itself.  

#. Homotopy

   A continuous transformation from one function to another. 
   A homotopy between two functions **f** and **g** from a space **X** to a space **Y** 
   is a continuous map **G** from :math:`X \times [0,1]| \mapsto Y` such that **G(x,0)=f(x)** 
   and **G(x,1)=g(x)**, where :math:`\times` denotes set pairing. Another way of saying this 
   is that a homotopy is a path in the mapping space **Map(X,Y)** from the first function to 
   the second.
   
   Two mathematical objects are said to be homotopic if one can be continuously deformed 
   into the other. The concept of homotopy was first formulated by *Poincaré* around 1900. 

#. Bisection
   
   In geometry, bisection is the division of something into two equal or congruent parts, 
   usually by a line, which is then called a bisector. The most often considered types 
   of bisectors are the segment bisector (a line that passes through the midpoint of 
   a given segment) and the angle bisector (a line that passes through the apex of an 
   angle, that divides it into two equal angles).

   In three-dimensional space, bisection is usually done by a plane, 
   also called the bisector or bisecting plane.

   .. figure:: images/Bisectors.svg

      Bisection

      Line DE bisects line AB at D, 
      line EF is a perpendicular bisector 
      of segment AD at C, and line EF is 
      the interior bisector of right angle AED

#. Bisection method
   
   The bisection method in mathematics is a *root-finding method* 
   that repeatedly bisects an interval and then selects a subinterval 
   in which a root must lie for further processing. It is a very simple 
   and robust method, but it is also relatively slow. Because of this, 
   it is often used to obtain a rough approximation to a solution 
   which is then used as a starting point for more rapidly converging methods. 
   The method is also called the interval halving method, the binary search method,
   or the dichotomy method.

   .. figure:: images/Bisection_method.svg

      Bisection method

      A few steps of the bisection method applied over 
      the starting range :math:`[a_1, b_1].` 
      The bigger red dot is the root of the function.

#. Matrix multiplication
   
   if :math:`A=(a_{ij})` and :math:`B=(b_{ij})` are square :math:`n \times n` matrices,
   then :math:`C = A \cdot B,` we define the entry :math:`c_{ij}, \text{ for } i,j = 1,2, \ldots, n,`

   .. math::

      c_{ij} = \sum_{k=1}^{n} a_{ik} \cdot b_{kj}

#. Fibonacci series

   We define the **Fibonacci numbers** by the following recurrence:

   .. math::

      F_0 &= 0, \\
      F_1 &= 1, \\
      F_i &= F_{i-1} + F_{i-2}

   
   .. code-block:: python
   
      # exponential complexity O(2^n)
      def recursive_fibnacci(n):
         """return the nth element in fibonacci series."""
         if n < 2:
            return n
         else:
            return fibnacci_1(n-1) + fibnacci_1(n-2) 
   
      # linear complexity O(n)
      def iterative_fibonacci(n):
         """Return a list containing the Fibonacci series up to n."""
         result = []
         a, b = 0, 1
         while a<n:
            result.append(a)
            a, b = b, b+a
         return result

      def trick_fibonacci(n)
         a = math.sqrt(5)
         phy = (1 + a)/2 // called golden ratio
         result = []
         for i in range(n)
            result.append(math.floor(phy**i + 0.5))
         return return

#. Geometric series [等比数列]
   
   .. image:: images/GeometricSquares.svg.png

   In mathematics, a geometric series is a series with a constant ratio 
   between successive terms. For example, the series

   .. math::

      {\frac {1}{2}}\,+\,{\frac {1}{4}}\,+\,{\frac {1}{8}}\,+\,{\frac {1}{16}}\,+\,\cdots 

   is geometric, because each successive term can be obtained by multiplying the previous term by 1/2.

   Geometric series are among the simplest examples of infinite series with finite sums, 
   although not all of them have this property. Historically, geometric series played an 
   important role in the early development of calculus, and they continue to be central 
   in the study of convergence of series. Geometric series are used throughout mathematics, 
   and they have important applications in physics, engineering, biology, economics, 
   computer science, queueing theory, and finance. 
   specifically, when the coefficient q < 1, then

   .. math::

      \lim \limits_{i \to \infty} {\sum_{i=0}^{n} q^n} = \frac {a_0}{1-q}

#. Caculus [微积分]
   
   .. image:: images/Integral_as_region_under_curve.svg

   the branch of mathematics that deals with the finding and properties of derivatives 
   and integrals of functions, by methods originally based on the summation of 
   infinitesimal differences. The two main types are differential calculus and integral calculus.

   .. figure:: images/Gottfried_Wilhelm_Leibniz.jpg

      Gottfried Wilhelm Leibniz was the first to state clearly the rules of calculus.

   .. figure:: images/IsaacNewton.jpg

      Isaac Newton developed the use of calculus in his laws of motion and gravitation.