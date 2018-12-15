********************************************
cut: remove sections from each line of files
********************************************

SYNOPSIS: ``cut OPTION... [FILE]...``

**DESCRIPTION**

   Print selected parts of lines from each FILE to standard output.

   .. option:: -d, --delimiter=DELIM
              
      use DELIM instead of TAB for field delimiter

   .. option:: -f, --fields=LIST
              
      select only these fields; also print any line 
      that contains no delimiter character, unless the -s option is specified

   .. option:: -s, --only-delimited
      
      do not print lines not containing delimiters

   .. option:: --output-delimiter=STRING
      
      use STRING as the output delimiter the default is to use the input delimiter

   .. option:: -b, --bytes=LIST
              
      select only these bytes

.. code-block:: sh
   :caption: Example

   $ cat sample 
   Andhra Pradesh
   Arunachal Pradesh
   Assam
   Bihar
   Chhattisgarh
   
   $ cut -d" " -f1 sample | sort -r
   Chhattisgarh
   Bihar
   Assam
   Arunachal
   Andhra
   
   $ cut -d" " -f 1-3 --output-delimiter="," sample
   Andhra,Pradesh
   Arunachal,Pradesh
   Assam
   Bihar
   Chhattisgarh
   
   $ cut -b 1-5 sample # output first 5 bytes
   Andhr
   Aruna
   Assam
   Bihar
   Chhat
