*******************
Mathematics Notes 2
*******************

生而为人，我很抱歉。

-- 太宰治

#. Sums of squares and cubes
   
    .. math::

        \sum_{k=0}^{n} {k^2} &= \frac {n(n+1)(2n+1)}{6} \\
        \sum_{k=0}^{n} {k^3} &= \frac {n^2(n+1)^2}{4} \\
        \sum_{k=0}^{n} {x^k} &= \frac {x^{n+1}-1}{x-1} \\
        \sum_{k=0}^{\infty} {kx^k} &= \frac {x}{(1-x)^2} \text{ for } \lvert x \rvert < 1

#. Identity function
   
    In mathematics, an identity function, also called an identity relation 
    or identity transformation, is a function that always returns the same 
    value that was used as its argument. In equations, the function is 
    given by :math:`f(x) = x`.

#. Idempotence
   
    In mathematics, a number that is idempotent keeps the same value when multiplied by itself, 
    no matter how many times the function is applied. The word idempotent comes from the Latin 
    words idem, which means "the same," and potent, from potentem, which means "power."

#. Radix point
   
    In mathematics and computing, a radix point is the symbol used in numerical representations 
    to separate the integer part of a number from its fractional part. "Radix point" applies to 
    all number bases. In base 10 notation, the radix point is more commonly called the 
    **decimal point,** Similarly, the term **binary point** is used for base 2.
 
#. Tensor
   
    a mathematical object analogous to but more general than a vector, 
    represented by an array of components that are functions of the 
    coordinates of a space.

#. Mathematical induction 

    .. figure:: images/Domino_effect.png

        Domino effect [多米诺骨牌效应]

    Mathematical induction proves that we can climb as high as we like on a ladder, 
    by proving that we can climb onto the bottom rung (the basis) and that from each 
    rung we can climb up to the next one (the step).

    -- Concrete Mathematics, page 3 margins.

    Mathematical induction is a mathematical proof technique. which requires two cases to be proved. 
    The first case, called the base case, proves that the property holds for the number 0. 
    The second case, called the induction step, proves that, if the property holds for one 
    natural number n, then it holds for the next natural number n+1. These two steps establish 
    the property P(n) for every natural number n = 0, 1, 2, 3, ... The base step need not begin with zero. 
    Often it begins with the number one, and it can begin with any natural number, establishing the truth 
    of the property for all natural numbers greater than or equal to the starting number.

#. centroid
   
    centroid: the center of mass of a geometric object of uniform density. [质心，重心]
    incenter: the center of the incircle [内切圆] of a triangle or other figure. [内心]
    orthocenter: the point where all three altitudes [垂线] of the triangle intersect. [垂心]

    .. image:: images/centroid-of-triangles.png

#. manifold
   
    a collection of points forming a certain kind of set, such as those of a topologically 
    closed surface or an analog of this in three or more dimensions.
