Git log
=======


.. code-block:: sh
   :caption: Hot hits options 

   git log  -<number> 
   # Limit the number of commits to output to number

   git log  --skip=<number>
   # Skip number commits before starting to show the commit output

   git log  --since=<date>
   git log  --after=<date>
   # Show commits more recent than a specific date
   
   git log  --until=<date>
   git log  --before=<date>
   # Show commits older than a specific date
   
   git log  --author=<pattern>
   git log  --committer=<pattern>
   # Limits the commits output to ones with author/committer header
   # lines match the specific pattern (regular expression)
   
   git log  [--invert-grep] [--regexp-ignore-case] [--all-match] --grep=<pattern>
   # Limit the commits output to ones with log messages that matches the specified
   # pattern (regular expression). With more than one --grep=<pattern>, commits
   # whose message matches any of the given patterns are chosen.

   git log --remotes[=pattern]
   # list <commits> in remote tracking branch.
   # if <pattern> is given, limit remote-tracking branches to ones matching given shell blob.

   git --all
   # list both local and remote branch <commits>.

   --abbrev-commit
   # Instead of showing the full 40-byte hexadecimal commit object name, 
   # show only a partial prefix, Non default number of digits can be 
   # specified with “--abbrev=<n>”.

   --no-abbrev-commit
   # Show the full 40-byte hexadecimal commit object name.

   --color[=<when>]
   --no-color == --color=never
   # Show colored diff. --color (i.e. without =<when>) is the same as --color=always.
   # <when> can be one of always, never, or auto.

   --word-diff[=<mode>]
   # Show a word diff, using the <mode> to delimit changed words.
   # By default, words are delimited by whitespace; see --word-diff-regex below.
   # The <mode> defaults to plain, and must be one of: color, plain, porcelain, none

   git log --pretty[=<format>]
   # Pretty-print the contents of the commit logs in a given format,
   # where <format> can be one of oneline, short, medium, full, fuller, email, raw,
   # format:<string> and tformat:<string>. When <format> is none of the above,
   # and has %placeholder in it, it acts as if --pretty=tformat:<string> were given
   # When =<format> part is omitted, it defaults to medium.

