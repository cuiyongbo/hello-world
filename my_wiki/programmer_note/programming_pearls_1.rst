C/C++ int-string Conversion
===========================

#. string --> number
   
   .. code-block:: c++

      int num1 = atoi(str);
      long num2 = atol(str);
      double num3 = atof(str);

#. number --> string
   
   .. code-block:: c++

      int sprintf( char* buffer, const char* format, ... );
      int snprintf( char* buffer, std::size_t buf_size, const char* format, ... );

      // using sprintf
      char* buffer[32];
      int value = 4564;
      sprintf(buffer, "%d", value);
      
      // using snprintf
      char buffer[10];
      int value = 234452;
      snprintf(buffer, 10, "%d", value);


.. note::

   you can convert a string to integer type, or otherwise, using :class:`std::istringstream` 
   and :class:`std::ostringstream` like this::

      istringstream convert1(Text); //string Text="456"
      convert1 >> Number; //string to int, Number=456
      ostringstream convert2;
      convert2 << Number;
      Text = convert2.str(); //int to string, Text="456"
      