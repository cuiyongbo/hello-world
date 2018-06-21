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

+------------------------------------------+---------------------------------------+
| Parallelogram                            | Triangle                              |
+==========================================+=======================================+
| .. image:: images/Area_Parallelogram.gif | .. image:: images/Area_Triangle_1.gif |
+------------------------------------------+---------------------------------------+
| :math:`S = bh`                           | :math:`S = \frac{1}{2} bh`            |
+------------------------------------------+---------------------------------------+

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

