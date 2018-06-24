***********
sort Manual
***********

**NAME**
   
   sort - sort lines of text files

**SYNOPSIS**

   sort [OPTION]... [FILE]...

**DESCRIPTION**

   Write sorted concatenation of all FILE(s) to standard output.

**Hot Options**

   .. option:: -b, --ignore-leading-blanks
      
      ignore leading blanks

   .. option:: -d, --dictionary-order
      
      consider only blanks and alphanumeric characters

   .. option:: -f, --ignore-case
      
      fold lower case to upper case characters

   .. option:: -g, --general-numeric-sort
      
      compare according to general numerical value

   .. option:: -h, --human-numeric-sort
      
      compare human readable numbers (e.g., 2K 1G)

   .. option:: -n, --numeric-sort
              
      compare according to string numerical value

   .. option:: -r, --reverse
      
      reverse the result of comparisons

   .. option:: -k, --key=POS1[,POS2]
         
      start a key at POS1, end it at POS2 (origin 1)

      *POS* is F[.C][OPTS], where F is the field number 
      and C the character position in the field. *OPTS* 
      is one or more single-letter ordering options, 
      which override global ordering options for that key.  
      If no key is given, use the entire line as the key.

   .. option:: -s, --stable
              
      stabilize sort by disabling last-resort comparison

   .. option:: -t, --field-separator=SEP
      
      use SEP instead of non-blank to blank transition

   .. option:: -z, --zero-terminated
              
      end lines with 0 byte, not newline

   .. option:: -c, --check=diagnose-first
      
      check for sorted input; do not sort

   .. option:: -u, --unique
            
      with -c, check for strict ordering; without -c, output only the first of an equal run

**Examples**

   .. code-block:: sh

      $ cat test
      01 baidu
      02 bing
      03 google
      04 yahoo
      05 360
      $ sort -k 2,2 test 
      05 360
      01 baidu
      02 bing
      03 google
      04 yahoo

      $ sort -k 2,2 test > test2
      $ sort -c test2
      sort: test2:2: disorder: 01 baidu

      $ cat test2
      01 Joe Sr.Designer
      02 Marie Jr.Developer
      03 Albert Jr.Designer
      04 Dave Sr.Developer

      # sort according to the 3rd field.
      $ sort -k 3 test2
      03 Albert Jr.Designer
      02 Marie Jr.Developer
      01 Joe Sr.Designer
      04 Dave Sr.Developer

      # sort according to the 3rd field, but ignore the first three characters.
      $ sort -k 3.3 test2
      01 Joe Sr.Designer
      03 Albert Jr.Designer
      02 Marie Jr.Developer
      04 Dave Sr.Developer

      




