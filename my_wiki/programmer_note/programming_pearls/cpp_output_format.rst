*****************
Output Formatting
*****************

Formatting program output is an essential part of any serious application. 
Surprisingly, most C++ textbooks don't give a full treatment of output formatting. 
The purpose of this section is to describe the full range of formatting abilities 
available in C++. Formatting in the standard C++ libraries is done through the use 
of **manipulators,** special variables or objects that are placed on the output stream. 
Most of the standard manipulators are found in **<iostream>** and so are included automatically. 
The standard C++ manipulators are not keywords in the language, just like cin and cout, but it 
is often convenient to think of them as a permanent part of the language.

.. note::

   All manipulators that take arguments are defined in the header file **<iomanip>.** 
   This header file must be included to use such manipulators.

#. endl - places a new line character on the output stream. 
   This is identical to placing '\n' on the output stream.

#. Field width - setw()
   
   setw(), which adjusts the field with for the item about to be printed. it 
   takes an integer argument which is the minimum field width for the value 
   to be printed. it only affects the next value to be printed.

#. Justification - left, right, and internal
   
   internal separates the sign of a number from its digits. The sign is left justified 
   and the digits are right justified. This is a useful format in accounting and business 
   programs, but is rarely used in other applications.


   .. code-block:: cpp

      std::cout << setw(9) << -3.25 << '\n';
      std::cout << internal << setw(9) << -3.25 << '\n';
   
   Output::

            -3.25
      -      3.25

#. boolalpha and noboolalpha
   
   Boolean values (variables of type bool) are normally printed as 0 
   for false and 1 for true. It is sometimes nice to print out these 
   values as words. The *boolalpha* manipulator will print out true and 
   false values as true and false respectively. The **nobooolalpha** 
   manipulator will return the printed values to 1 and 0.

#. showpos and noshowpos
   
   This manipulator determines how **positive numbers** are printed. 
   A negative number is traditionally printed with a minus sign in front. 
   The lack of a minus sign means a positive value. However some accounting 
   and scientific applications traditionally place a plus sign in front of 
   positive numbers just to emphasize the fact that the number is positive. 
   Using the *showpos* manipulator makes this happen automatically. 
   The *noshowpos* manipulator returns the output state to placing nothing 
   in front of positive values.

#. Integer base and prefix - dec, oct, and hex; showbase and noshowbase; uppercase and nouppercase
   
   The *showbase* manipulator add "0" before an octal number, and "0X" 
   before a hexadecimal one.

   Numeric output consists largely of numeric digits. But there are a few places 
   where alphabetic characters make their appearance. These include the "0x" prefix 
   for hexadecimal numbers, the hexadecimal digits [a-f], and the "e" that is used 
   in scientific notation for large floating point numbers. In some applications, 
   it is important that these letters appear as uppercase letters instead of lowercase. 
   The *uppercase* manipulator enables this behavior.

   .. note:: 

      Negative integers are not printed as such in octal or hexadecimal. 
      Rather, the internal bit patterns are interpreted as always being 
      positive values. This can be a way to find the 2's complement of a 
      negative integer.

      Floating point values are always printed out in decimal format.

   .. code-block:: cpp

      #include <iostream>
      #include <iomanip>
      
      using namespace std;
      
      int main()
      {
          int a = 1234;
          int b = -1234;
          cout << showbase << uppercase;
          cout << "decimal: " << dec << a << '\t' << b << '\n';
          cout << "octal: " << oct << a << '\t' << b << '\n';
          cout << "hexadecimal: " << hex << a << '\t' << b << '\n';
          return 0;
      }

   Output::

      decimal: 1234  -1234
      octal: 02322   037777775456
      hexadecimal: 0X4D2   0XFFFFFB2E

#. Floating Point output - fixed and scientific; setprecision(); showpoint and noshowpoint
   
   There are 3 floating point formats: general, fixed, and scientific. 
   Fixed format always has a number, decimal point, and fraction part, 
   no matter how big the number gets, i.e., not scientific notation. 6.02e+17 
   would be displayed as 602000000000000000 instead of 6.02e+17.

   Scientific format always displays a number in scientific notation. 
   The value of one-fourth would not be displayed as 0.25, but as 2.5e-01 instead.

   General format is a mix of fixed and scientific formats. If the number is small enough, 
   fixed format is used. If the number gets too large, the output switches to scientific 
   format. General format is the default format for floating point values.

   Unfortunately, there is no manipulator to place the output stream back into general format. 
   The author of these notes considers this to be a design flaw in the standard C++ libraries. 
   There is a way to place the output stream back into general format, but it's not pretty 
   and requires more explanation than is appropriate here. In short, here's the magic incantation
   ``cout.unsetf(ios::fixed | ios::scientific);`` In order to use this statement, you need a using 
   declaration for the ios class.

   In general format, the precision is the maximum number of digits displayed. 
   This includes digits before and after the decimal point, but does not include 
   the decimal point itself. Digits in a scientific exponent are not included.

   In fixed and scientific formats, the precision is the number of digits after the decimal point.

   **Note** that the default output precision is 6.

   There is one aspect of printing numbers in general format that is either very nice or very 
   annoying depending on your point of view. When printing out floating point values, only as 
   many decimal places as needed (up to the precision) are used to print out the values. In 
   other words, trailing zeros are not printed. This is nice and compact, but impossible to 
   get decimal points to line up in tables.

   The *showpoint* manipulator forces trailing zeros to be printed, even though they are not needed. 
   By default this option is off. 