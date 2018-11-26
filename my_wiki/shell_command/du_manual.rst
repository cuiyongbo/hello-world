*********
du Manual
*********

**NAME**

   du - estimate file space usage

**DESCRIPTION**

   Summarize disk usage of each FILE, recursively for directories.

**Hot Options**

   .. option:: -0, --null

      end each output line with 0 byte rather than newline

   .. option:: -c, --total
         
      produce a grand total

   .. option:: -d, --max-depth=N
      
      print the total for a directory (or file, with --all) only if it is N or 
      fewer levels below the command line argument; ``--max-depth=0`` is the same as --summarize

   .. option:: -h, --human-readable
      
      print sizes in human readable format (e.g., 1K 234M 2G)

   .. option:: -L, --dereference
      
      dereference all symbolic links

   .. option:: -P, --no-dereference
      
      don't follow any symbolic links (this is the default)

   .. option:: -S, --separate-dirs
      
      do not include size of subdirectories

   .. option:: -s, --summarize
            
      display only a total for each argument. equivalent to ``-d 0``.

   .. option:: -t, --threshold=SIZE
         
      exclude entries smaller than SIZE if positive, or entries greater than SIZE if negative.
      If multi -t are specified, the last one takes effect.

   .. option:: --time=WORD
         
      show time as *WORD* instead of modification time: *atime, access, use, ctime or status.*
      show time of the last modification if *WORD* is unspecified.
      
   .. option:: --exclude=PATTERN
         
      exclude files that match PATTERN

      .. note:: 

         **PATTERN** is a shell pattern (not a regular expression). The pattern *?* matches any one character, 
         whereas \* matches any string (composed of zero, one or multiple characters). For example, the command
         ``du --exclude='*.o'`` will skip all files and subdirectories ending in *.o* (including the file *.o* itself).


**EXAMPLES**

   .. code-block:: sh
      
      $  du -ah -t 8K  | wc -l # file count whose size is no less than 8K
      $  du -ah -t -8M | wc -l # file count whose size is no larger than 8M

      $ du -h  -t 8M --time
      8.3M    2018-06-22 13:04        ./biology_glossary/images
      8.4M    2018-06-22 13:04        ./biology_glossary
      8.6M    2018-06-22 13:04        ./computer_glossary
      31M     2018-06-22 13:04        ./languages/images
      32M     2018-06-22 13:04        ./languages
      11M     2018-06-22 14:37        ./_build/html/programmer_note
      50M     2018-06-22 13:04        ./_build/html/_images
      77M     2018-06-22 14:37        ./_build/html
      84M     2018-06-22 14:37        ./_build
      138M    2018-06-22 16:39        .
      
      $ du -h  -t 8M --time -c
      8.3M    2018-06-22 13:04        ./biology_glossary/images
      8.4M    2018-06-22 13:04        ./biology_glossary
      ....
      138M    2018-06-22 16:39        total

      $ du -h -t 8K | sort -rh

      $ du -sch
      298M  .
      298M  total
      $ du -sh
      298M  .
      $ du -sh -I"_build"
      123M  .
      
      # GUN shell
      $ du -sh .
      307M    .
      $ du -sh _build/
      182M    _build/
      $ du -sh --exclude="_build"
      126M    .

      $ du -h -t 1M
      3.4G  ./past7/2018-11-26-Mon
      15G   ./past7
      15G   

