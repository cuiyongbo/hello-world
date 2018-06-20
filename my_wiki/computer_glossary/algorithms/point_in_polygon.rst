****************
Point in Polygon
****************

Overview
========

In computational geometry, the :abbr:`PIP (point-in-polygon)` problem asks whether a given point 
in the plane lies inside, outside, or on the boundary of a polygon. It is a special case of point 
location problems and finds applications in areas that deal with processing geometrical data, 
such as computer graphics, computer vision, :abbr:`GIS (geographical information systems)`, motion 
planning, and CAD.

An early description of the problem in computer graphics shows two common approaches (*ray casting 
and angle summation*) in use as early as 1974.

An attempt of computer graphics veterans to trace the history of the problem and some tricks for its 
solution can be found in an issue of the Ray Tracing News.


Ray casting algorithm
=====================

.. sidebar:: Ray casting algorithm

   .. image:: images/RecursiveEvenPolygon.svg.png

   The number of intersections for a ray passing from the exterior of the polygon 
   to any point; if odd, it shows that the point lies inside the polygon. If it is 
   even, the point lies outside the polygon; this test also works in three dimensions.

One simple way of finding whether the point is inside or outside a simple polygon is 
to test how many times a ray, starting from the point and going in any fixed direction, 
intersects the edges of the polygon. If the point is on the outside of the polygon the ray 
will intersect its edge an even number of times. If the point is on the inside of the polygon 
then it will intersect the edge an odd number of times. Unfortunately, this method won't work 
if the point is on the edge of the polygon.

This algorithm is sometimes also known as the crossing number algorithm or the even–odd rule algorithm, 
and is known as early as 1962. The algorithm is based on a simple observation that if a point moves along 
a ray from infinity to the probe point and if it crosses the boundary of a polygon, possibly several times, 
then it alternately goes from the outside to inside, then from the inside to the outside, etc. As a result, 
after every two "border crossings" the moving point goes outside. This observation may be mathematically 
proved using the **Jordan curve theorem**.

If implemented on a computer with finite precision arithmetics, the results may be incorrect if the point 
lies very close to that boundary, because of rounding errors. This is not normally a concern, as speed is 
much more important than complete accuracy in most applications of computer graphics. However, for a formally 
correct computer program, one would have to introduce a numerical tolerance :math:`\epsilon` and test in line 
whether P (the point) lies within :math:`\epsilon` of L (the Line), in which case the algorithm should stop 
and report "P lies very close to the boundary."


Winding number algorithm
========================

Another algorithm is to compute the given point's winding number with respect to the polygon. 
If the winding number is non-zero, the point lies inside the polygon. One way to compute the 
winding number is to sum up the angles subtended by each side of the polygon. However, this 
involves costly inverse trigonometric functions, which generally makes this algorithm slower 
than the ray casting algorithm. Luckily, these inverse trigonometric functions do not need to 
be computed. Since the result, the sum of all angles, can add up to 0 or :math:`2\pi` (or multiples 
of :math:`2\pi`) only, it is sufficient to track through which quadrants the polygon winds, as 
it turns around the test point, which makes the winding number algorithm comparable in speed to 
counting the boundary crossings.

There is a significant speed-up (known since 2001) of the winding number algorithm. It uses signed 
crossings, based on whether each crossing is left-to-right or right-to-left. Details and C++ code 
are given at `here <http://geomalgorithms.com/a03-_inclusion.html>`_. Angles are not used, and no 
trigonometry is involved. The code is as fast as the simple boundary crossing algorithm. Further, 
it gives the correct answer for nonsimple polygons, whereas the boundary crossing algorithm fails 
in this case.


Comparison
==========

For simple polygons, both algorithms will always give the same results for all points. 
However, for complex polygons, the algorithms may give different results for points in 
the regions where the polygon intersects itself, where the polygon does not have a clearly 
defined inside and outside. In this case, the former algorithm is called the even-odd rule. 
One solution is to transform (complex) polygons in simpler, but even-odd-equivalent ones 
before the intersection check. This, however, is computationally expensive. It is better 
to use the fast "signed crossings" winding number algorithm which gives the correct result, 
even when the polygon overlaps itself. The point is then inside the polygon whenever the 
winding number is nonzero.


Implementation Example
======================

.. code-block:: c
   :caption: Sample taken from apache project [*httpd-2.4.33/modules/mappers/mod_imagemap.c*]

   static int pointinrect(const double point[2], double coords[MAXVERTS][2])
   {
       double max[2], min[2];
       if (coords[0][X] > coords[1][X]) {
           max[0] = coords[0][X];
           min[0] = coords[1][X];
       }
       else {
           max[0] = coords[1][X];
           min[0] = coords[0][X];
       }
   
       if (coords[0][Y] > coords[1][Y]) {
           max[1] = coords[0][Y];
           min[1] = coords[1][Y];
       }
       else {
           max[1] = coords[1][Y];
           min[1] = coords[0][Y];
       }
   
       return ((point[X] >= min[0] && point[X] <= max[0]) &&
               (point[Y] >= min[1] && point[Y] <= max[1]));
   }
   
   static int pointincircle(const double point[2], double coords[MAXVERTS][2])
   {
       double radius1, radius2;
   
       radius1 = ((coords[0][Y] - coords[1][Y]) * (coords[0][Y] - coords[1][Y]))
           + ((coords[0][X] - coords[1][X]) * (coords[0][X] - coords[1][X]));
   
       radius2 = ((coords[0][Y] - point[Y]) * (coords[0][Y] - point[Y]))
           + ((coords[0][X] - point[X]) * (coords[0][X] - point[X]));
   
       return (radius2 <= radius1);
   }
   
   #define X 0
   #define Y 1
   #define fmin(a,b) (((a)>(b))?(b):(a))
   #define fmax(a,b) (((a)>(b))?(a):(b))
   
   static int pointinpoly(const double point[2], double pgon[MAXVERTS][2])
   {
       int i, numverts, crossings = 0;
       double x = point[X], y = point[Y];
   
       double maxX, minX, maxY, minY.
       maxX = minX = pgon[0][X];
       maxY = minY = pgon[0][Y];
       for (numverts = 0; numverts < MAXVERTS && pgon[numverts][X] != -1;
           numverts++) {
           /* just counting the vertexes */
           maxX = fmax(maxX, pgon[numverts][X]);
           minX = fmin(minX, pgon[numverts][X]);
           maxY = fmax(maxY, pgon[numverts][Y]);
           minY = fmin(minY, pgon[numverts][Y]);
       }

       // outside the bounding box
       if (x < minX || x > maxX
            || y < minY || y > maxY)
         return 0;
   
       for (i = 0; i < numverts; i++) {
           double x1=pgon[i][X];
           double y1=pgon[i][Y];
           double x2=pgon[(i + 1) % numverts][X];
           double y2=pgon[(i + 1) % numverts][Y];
           double d=(y - y1) * (x2 - x1) - (x - x1) * (y2 - y1); // vector product of PiPi+1 and PiP0
   
           if ((y1 >= y) != (y2 >= y)) {
               crossings += y2 - y1 >= 0 ? d >= 0 : d <= 0;
           }

           // if test point lies on a polygon side or very close to a polygon side.
           // always view as if it were inside the the polygone.  
           if (!d && fmin(x1,x2) <= x && x <= fmax(x1,x2)
               && fmin(y1,y2) <= y && y <= fmax(y1,y2)) {
               return 1;
           }
       }
       return crossings & 0x01;
   }
   