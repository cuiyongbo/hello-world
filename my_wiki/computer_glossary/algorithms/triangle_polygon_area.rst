****************************
Area of Triangle and Polygon
****************************

Triangle
========

Ancient Triangles
-----------------

Before Pythagoras, the area of the parallelogram (including the rectangle and the square) 
had been known to equal **the product of its base times its height**. Further, two copies 
of the same triangle paste together to form a parallelogram, and thus the area of a triangle 
is half of its base b times its height h. So, for these simple but commonly occurring cases, 
we have:

+--------------------------------------------+---------------------------------------+
| Parallelogram                              | Triangle                              |
+============================================+=======================================+
| .. image:: images/Area_Parallelogram_1.gif | .. image:: images/Area_Triangle_1.gif |
+--------------------------------------------+---------------------------------------+
| :math:`S = bh`                             | :math:`S = \frac{1}{2} bh`            |
+--------------------------------------------+---------------------------------------+

However, except in special situations, finding the height of a triangle at an arbitrary orientation 
usually requires also computing the perpendicular distance of the top vertex from the base.

For example, if one knows the lengths of two sides, a and b, of a triangle and also the angle 
:math:`\theta` between them, then this is enough to determine the triangle and its area. Using 
trigonometry, the height of the triangle over the base b is given by :math:`h = a\sin \theta`, 
and thus the area is:

+----------------------------------------+---------------------------------------+
| :math:`S = \frac{1}{2} ab \sin \theta` | .. image:: images/Area_Triangle_2.gif |
+----------------------------------------+---------------------------------------+

Modern Triangles
----------------

More recently, starting in the 17-th century with *Descartes* and *Fermat*, 
linear algebra produced new simple formulas for area. In 3 dimensional space (3D), 
**the area of a planar parallelogram or triangle can be expressed by the magnitude 
of the cross-product of two edge vectors**, since :math:`\| V \times W \| = \|V\| \|W\| \sin \theta` 
where :math:`\theta` is the angle between the two vectors V and W. Thus for a 3D triangle with 
vertices :math:`V_0V_1V_2` putting :math:`v=V_1-V_0` and :math:`w=V_2-V_0`, one gets

.. sidebar:: Area of a Triangle using cross product

   .. image:: images/Area_Triangle_3.gif 

   .. math::

      S =& \frac{1}{2} \| V \times W \| \\
        =& \frac{1}{2} \|(V_1-V_0) \times (V_2-V_0)\|

**Note** that the signed area will be positive if the vertices :math:`V_0V_1V_2` are oriented counterclockwise 
around the triangle, and will be negative if the triangle is oriented clockwise; and so, **this area computation 
can be used to test for a triangle's orientation.** This signed area can also be used to test whether the point 
:math:`V_2` is to the left (positive) or the right (negative) of the directed line segment :math:`V_0V_1` . 
So this value is a very useful primitive, and it's great to have such an efficient formula for it.


Quadrilaterals
==============

The Greeks singled out certain quadrilaterals (also called quadrangles) for special treatment, 
including the square, the rectangle, the parallelogram, and the trapezium. Then, given an arbitrary 
quadrilateral, they showed how to construct a parallelogram or square with an equal area. And the 
area of the parallelogram was equal to its base times its height. But there was no general formula 
for the quadrilateral's area.

In modern linear algebra, as already noted, the area of a planar parallelogram is the magnitude 
of the cross product of two adjacent edge vectors. So, for any 3D planar parallelogram 
:math:`V_0V_1V_2V_3`, we have:

+--------------------------------------+--------------------------------------------+
| :math:`S=(V_1-V_0) \times (V_3-V_0)` | .. image:: images/Area_Parallelogram_2.gif |
+--------------------------------------+--------------------------------------------+

In 2D, with vertices :math:`Vi=(x_i,y_i)=(x_i,y_i,0) \text{ for } i=0,3,` this becomes:

.. math:: 

   S = \| (x_1-x_0)(y_3-y_0) - (x_3-x_0)(y_1-y_0) \|

which is again a signed area, just as we had for triangles. It also indicates **orientation**.

Next, for an **arbitrary quadrilateral**, one can compute its area using a parallelogram 
discovered by *Pierre Varignon* (first published in 1731). It is amazing that the Greeks 
missed Varignon's simple result which was discovered 2000 years after Euclid! Given any 
quadrilateral, one can take the midpoints of its 4 edges to get 4 vertices which form a 
new quadrilateral. It is then easy to show that this midpoint quadrilateral is always a 
parallelogram, called the **Varignon parallelogram**, and that **its area is exactly one-half 
the area of the original quadrilateral**. To see this, for any quadrilateral :math:`S_{V_0V_1V_2V_3}`, 
let the midpoint vertices be :math:`S_{M_0M_1M_2M_3}` as shown in the diagram:

.. image:: images/Area_Parallelogram_3.gif

The area relation is also easy to demonstrate. And we can then compute the area as:

.. math:: 

   S_{V_0V_1V_2V_3} =& 2 S_{M_0M_1M_2M_3} \\
                    =& 2 \| (M_1 - M_0) \times (M_3 - M_0) \| \\
                    =& 2 \| \left(\frac{V_1+V_2}{2} - \frac{V_1+V_0}{2} \right) 
                                 \times \left(\frac{V_3+V_0}{2} - \frac{V_1+V_0}{2}\right) \| \\
                    =& \frac{1}{2} \| (V_2 - V_0) \times (V_3 - V_1) \|

which is one-half the magnitude of the cross-product of the two diagonals of the quadrilateral.
For simple quadrilaterals, the area is positive when the vertices are oriented counterclockwise, 
and negative when they are clockwise. However, it also works for nonsimple quadrilaterals and is 
equal to the difference in area of the two regions the quadrilateral bounds. For example, in the 
following diagram where **I** is the self-intersection point of a nonsimple quadrilateral 
:math:`V_0V_1V_2V_3`, we have:

.. sidebar:: Nonsimple polygon

   .. image:: images/Area_Parallelogram_4.gif

.. math::
   
   S_{V_0V_1V_2V_3} =& S_{V_0V_1I} + S_{IV_2V_3} \\
                    =& S_{V_0V_1I} - S_{IV_3V_2}



Polygon
=======

2D polygon
----------

A 2D polygon can be decomposed into triangles. For computing area, there is a very easy decomposition 
method for simple polygons (i.e. ones without self intersections). Let a polygon :math:`\Omega` be defined 
by its vertices :math:`Vi=(xi,yi) \text{ for i=0,n with } V_n=V_0`. Also, let **P** be any point; and for each 
edge :math:`e_i=V_iV_{i+1} \text{ of } \Omega`, form :math:`\triangle{PV_iV_{i+1}}`. Then, the area of :math:`\Omega` 
is equal to the sum of the signed areas of all the triangles; and we have:

+-----------------------------------------------------+---------------------------------+
| :math:`S_{\Omega} = \sum_{i=0}^{n} S_{PV_iV_{i+1}}` | .. image:: images/Polygon_1.gif |
+-----------------------------------------------------+---------------------------------+

Notice that, for a counterclockwise oriented polygon, when the point P is on the "inside" left side of an edge 
:math:`V_iV_{i+1}`, then the area is positive; otherwise negative. If instead the polygon is oriented clockwise, 
then the signs are reversed, and inside triangles become negative.

One can make the formula more explicit by picking a specific point **P** and expanding the terms. 
By selecting **P=(0,0)**, the area formula of each triangle reduces to 
:math:`2S{\triangle_i}=(x_iy_{i+1}-x_{i+1}y_i)`. This yields:

.. sidebar:: 2D Polygon Area Deduction

   .. image:: images/Polygon_2.gif

.. math:: 

   \begin{align}
      2S_{\Omega} &= \sum_{i=0}^{n-1} {(x_iy_{i+1}-x_{i+1}y_i)} \\
                  &= \sum_{i=0}^{n-1} {(x_i + x_{i+1})(y_{i+1} - y_i)} \\
                  &= \sum_{i=1}^{n} {x_i (y_{i+1} - y_{i-1})} \\
   \end{align} \\
   \text{where } V_i=(x_i, y_i) \text{, with i mod n}

This computation gives a signed area for a polygon; and, similar to the signed area of a triangle, 
is positive when the vertices are oriented counterclockwise around the polygon, and negative when 
oriented clockwise. So, this computation can be used to test for a polygon's **global orientation**. 
However, there are other more efficient algorithms for determining polygon orientation. The easiest 
is to find the rightmost lowest vertex of the polygon, and then test the orientation of the entering 
and leaving edges at this vertex. This test can be made by checking if the end vertex of the leaving 
edge is to the left of the entering edge, which means that the orientation is counterclockwise, otherwise 
it is clockwise.