Section 2.4 - Hash Functions for Strings
========================================

Now we will examine some hash functions suitable for storing strings of characters. We start with a simple summation function:

.. code-block:: java

   int hashForString(String x, int M) 
   {
      char ch[];
      ch = x.toCharArray();

      int i, sum;
      for (sum=0, i=0; i < x.length(); i++)
        sum += ch[i];

      return sum % M;
    }

This function sums the ASCII values of the letters in a string. If the hash table size **M** is small compared to the resulting summations, then this hash function should do a good job of distributing strings evenly among the hash table slots, because it gives equal weight to all characters in the string. This is an example of the folding approach to designing a hash function. **Note that the order of the characters in the string has no effect on the result**. A similar method for integers would add the digits of the key value, assuming that there are enough digits to keep any one or two digits with bad distribution from skewing the results of the process and generate a sum much larger than **M**.

As with many other hash functions, the final step is to apply the modulus operator to the result, using table size **M** to generate a value within the table range. If the sum is not sufficiently large, then the modulus operator will yield a poor distribution. For example, because the ASCII value for "A" is 65 and "Z" is 90, sum will always be in the range 650 to 900 for a string of ten upper case letters. For a hash table of size 100 or less, a reasonable distribution results. For a hash table of size 1000, the distribution is terrible because only slots 650 to 900 can possibly be the home slot for some key value, and the values are not evenly distributed even within those slots.

Here is a much better hash function for strings:

.. code-block:: java

   // Use folding on a string, summed 4 bytes at a time
   long hashForStringWithFolding(String s, int M) 
   {
      int intLength = s.length() / 4;
      long sum = 0;
      for (int j = 0; j < intLength; j++) 
      {
          long mult = 1;
          char c[] = s.substring(j * 4, (j * 4) + 4).toCharArray();
          for (int k = 0; k < c.length; k++) 
          {
            sum += c[k] * mult;
            mult <<= 8;
          }
      }
      return(Math.abs(sum) % M);
   }

This function takes a string as input. It processes the string four bytes at a time, and interprets each of the four-byte chunks as a single long integer value. The integer values for the four-byte chunks are added together. In the end, the resulting sum is converted to the range 0 to M-1 using the modulus operator.

For example, if the string "aaaabbbb" is passed to sfold, then the first four bytes ("aaaa") will be interpreted as the integer value 1,633,771,873, and the next four bytes ("bbbb") will be interpreted as the integer value 1,650,614,882. Their sum is 3,284,386,755 (when treated as an unsigned integer). If the table size is 101 then the modulus function will cause this key to hash to slot 75 in the table. Note that for any sufficiently long string, the sum for the integer quantities will typically cause a 32-bit integer to overflow (thus losing some of the high-order bits) because the resulting values are so large. But this causes no problems when the goal is to compute a hash function.

The reason that hashing by summing the integer representation of four letters at a time is superior to summing one letter at a time is because the resulting values being summed have a bigger range. This still only works well for strings long enough (say at least 7-12 letters), but the original method would not work well for short strings either. Another alternative would be to fold two characters at a time.
