**********
cal Manual
**********

**NAME**

   cal, ncal -- displays a calendar and the date of easter

**DESCRIPTION**

   The cal utility displays a simple calendar in traditional format 
   and ncal offers an alternative layout, more options and the date
   of easter.  The new format is a little cramped but it makes a year 
   fit on a 25x80 terminal.  If arguments are not specified, the
   current month is displayed.

**HOT OPTIONS**

   .. option:: -m month
             
      Display the specified month.

   .. option:: -y      

      Display a calendar for the specified year.

**EXAMPLES**

   .. code-block:: sh

      $ cal
        June 2018
      Su Mo Tu We Th Fr Sa
                      1  2
       3  4  5  6  7  8  9
      10 11 12 13 14 15 16
      17 18 19 20 21 22 23
      24 25 26 27 28 29 30

      $ cal -m 8
       August 2018
      Su Mo Tu We Th Fr Sa
                1  2  3  4
       5  6  7  8  9 10 11
      12 13 14 15 16 17 18
      19 20 21 22 23 24 25
      26 27 28 29 30 31


      $ cal 2018
                                   2018
      
            January               February               March
      Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
          1  2  3  4  5  6               1  2  3               1  2  3
       7  8  9 10 11 12 13   4  5  6  7  8  9 10   4  5  6  7  8  9 10
      14 15 16 17 18 19 20  11 12 13 14 15 16 17  11 12 13 14 15 16 17
      21 22 23 24 25 26 27  18 19 20 21 22 23 24  18 19 20 21 22 23 24
      28 29 30 31           25 26 27 28           25 26 27 28 29 30 31
                                                  
             April                  May                   June
      Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
       1  2  3  4  5  6  7         1  2  3  4  5                  1  2
       8  9 10 11 12 13 14   6  7  8  9 10 11 12   3  4  5  6  7  8  9
      15 16 17 18 19 20 21  13 14 15 16 17 18 19  10 11 12 13 14 15 16
      22 23 24 25 26 27 28  20 21 22 23 24 25 26  17 18 19 20 21 22 23
      29 30                 27 28 29 30 31        24 25 26 27 28 29 30
                                                  
              July                 August              September
      Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
       1  2  3  4  5  6  7            1  2  3  4                     1
       8  9 10 11 12 13 14   5  6  7  8  9 10 11   2  3  4  5  6  7  8
      15 16 17 18 19 20 21  12 13 14 15 16 17 18   9 10 11 12 13 14 15
      22 23 24 25 26 27 28  19 20 21 22 23 24 25  16 17 18 19 20 21 22
      29 30 31              26 27 28 29 30 31     23 24 25 26 27 28 29
                                                  30
            October               November              December
      Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
          1  2  3  4  5  6               1  2  3                     1
       7  8  9 10 11 12 13   4  5  6  7  8  9 10   2  3  4  5  6  7  8
      14 15 16 17 18 19 20  11 12 13 14 15 16 17   9 10 11 12 13 14 15
      21 22 23 24 25 26 27  18 19 20 21 22 23 24  16 17 18 19 20 21 22
      28 29 30 31           25 26 27 28 29 30     23 24 25 26 27 28 29
                                                  30 31
