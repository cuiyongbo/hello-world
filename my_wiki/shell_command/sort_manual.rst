*******************************
sort - sort lines of text files
*******************************

**DESCRIPTION**

   Syntax: ``sort [OPTION]... [FILE]...``

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
      and C the beginning character position in the field. *OPTS*
      is one or more single-letter ordering options,
      which override global ordering options for that key.
      If no key is given, use the entire line as the key.

   .. option:: -s, --stable

      stabilize sort by disabling last-resort comparison

   .. option:: -t, --field-separator=SEP

      use SEP instead of non-blank to blank transition

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

      $ sort -k 2 test
      05 360
      01 baidu
      02 bing
      03 google
      04 yahoo

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

      $ sort -b -t, -k1 pastWeekTi_Monday_08_00.txt -o result2

      $ df -h | sort -k 3 -h
      Filesystem      Size  Used Avail Use% Mounted on
      none            100M     0  100M   0% /run/user
      none            4.0K     0  4.0K   0% /sys/fs/cgroup
      none            5.0M     0  5.0M   0% /run/lock
      udev             20G  4.0K   20G   1% /dev
      tmpfs           4.0G  3.3M  4.0G   1% /run
      /dev/sda1       236M   40M  184M  18% /boot
      tmpfs           4.0G  1.4G  2.7G  33% /tmp/FriedPan
      none             20G  4.1G   16G  21% /run/shm
      /dev/dm-0       157G  141G  8.8G  95% /




