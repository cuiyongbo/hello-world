****************
Point in Polygon
****************




Example
=======

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
   
   #define fmin(a,b) (((a)>(b))?(b):(a))
   #define fmax(a,b) (((a)>(b))?(a):(b))
   
   static int pointinpoly(const double point[2], double pgon[MAXVERTS][2])
   {
       int i, numverts, crossings = 0;
       double x = point[X], y = point[Y];
   
       for (numverts = 0; numverts < MAXVERTS && pgon[numverts][X] != -1;
           numverts++) {
           /* just counting the vertexes */
       }
   
       for (i = 0; i < numverts; i++) {
           double x1=pgon[i][X];
           double y1=pgon[i][Y];
           double x2=pgon[(i + 1) % numverts][X];
           double y2=pgon[(i + 1) % numverts][Y];
           double d=(y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
   
           if ((y1 >= y) != (y2 >= y)) {
               crossings +=y2 - y1 >= 0 ? d >= 0 : d <= 0;
           }
           if (!d && fmin(x1,x2) <= x && x <= fmax(x1,x2)
               && fmin(y1,y2) <= y && y <= fmax(y1,y2)) {
               return 1;
           }
       }
       return crossings & 0x01;
   }
   