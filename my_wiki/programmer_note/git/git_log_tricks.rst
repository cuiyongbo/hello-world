*******
Git log
*******

.. code-block:: sh
    :caption: Hot hits options

    # Limit the number of commits to output to number
    git log  -<number>

    # Skip number commits before starting to show the commit output
    git log  --skip=<number>

    # Show commits more recent than a specific date
    git log  --since=<date>
    git log  --after=<date>

    # Show commits older than a specific date
    git log  --until=<date>
    git log  --before=<date>

    # Limits the commits output to ones with author/committer header
    # lines match the specific pattern (regular expression)
    git log  --author=<pattern>
    git log  --committer=<pattern>

    # Limit the commits output to ones with log messages that matches the specified
    # pattern (regular expression). With more than one --grep=<pattern>, commits
    # whose message matches any of the given patterns are chosen.
    git log  [--invert-grep] [--regexp-ignore-case] [--all-match] --grep=<pattern>

    # list <commits> in remote tracking branch.
    # if <pattern> is given, limit remote-tracking branches to ones matching given shell blob.
    git log --remotes[=pattern]

    # list both local and remote branch <commits>.
    git --all

    # Instead of showing the full 40-byte hexadecimal commit object name,
    # show only a partial prefix, Non default number of digits can be
    # specified with “--abbrev=<n>”.
    --abbrev-commit

    # Show the full 40-byte hexadecimal commit object name.
    --no-abbrev-commit

    # Show colored diff. --color (i.e. without =<when>) is the same as --color=always.
    # <when> can be one of always, never, or auto.
    --color[=<when>]
    --no-color == --color=never

    # Show a word diff, using the <mode> to delimit changed words.
    # By default, words are delimited by whitespace; see --word-diff-regex below.
    # The <mode> defaults to plain, and must be one of: color, plain, porcelain, none
    --word-diff[=<mode>]

    # Pretty-print the contents of the commit logs in a given format,
    # where <format> can be one of oneline, short, medium, full, fuller, email, raw,
    # format:<string> and tformat:<string>. When <format> is none of the above,
    # and has %placeholder in it, it acts as if --pretty=tformat:<string> were given
    # When =<format> part is omitted, it defaults to medium.
    git log --pretty[=<format>]

    # Continue listing the history of a file beyond renames (works only for a single file).
    git --follow


**Examples**

#. git log pretty example

    .. code-block:: sh
        :caption: git-branches-by-commit-date

        #!/usr/bin/sh
        # Credit http://stackoverflow.com/a/2514279

        for branch in `git branch -r | grep -v HEAD`
        do
           echo -e `git show --format="%ai %ar by %an" $branch | head -n 1` \\t$branch
        done |
           sort -r

        #for branch in `git branch -r | grep -v HEAD`
        #do
        #  echo -e `git show --pretty=format:"%Cred %cn %Cgreen %ar %Creset" $branch | head -n 1` $branch
        #done |
        #  sort -r


#. git log graph example

    .. code-block:: sh

        $ git log --graph --oneline master
        * fb11f8a change project configure
        *   3e7203e Merge branch 'ti_style_bug'
        |\
        | * 95b8386 Fixed day ti style not changed when route removed or created.
        |/
        *   b866f8c Merge branch 'add_routing_cases'
        |\
        | * 06dee2f Add TEST_F(RoutingRationalityTest, badCaseNaviCore3265)
        | * 3957e89 Add TEST_F(RoutingRationalityTest, badCaseNaviCore3263)
        | * a1ab2c3 Add TEST_F(RoutingRationalityTest, trafficLight6)
        |/
        *   673e8f1 Merge branch 'support_prefer_online'
        |\
        | * 41db56c refactor
        | * 50aba92 support prefer online
        |/
        *   3c5de50 Merge branch 'real3d-broken'

#. Check the commit history of a specific file

    .. code-block:: sh

        # First
        $ gitk [--follow] <fileName>

        # Second
        $ git log --follow -p  --word-diff=color <fileName>
        # --follow ensures that you see file renames
        # -p ensures that you see how the file gets changed

        # Third
        $ git blame <fileName>
        cdc116f5 (cuiyb 2018-01-31 11:44:16 +0800  9) .. toctree::
        cdc116f5 (cuiyb 2018-01-31 11:44:16 +0800 10)    :maxdepth: 2
        cdc116f5 (cuiyb 2018-01-31 11:44:16 +0800 11)
        92b6a9e1 (cuiyb 2018-01-31 12:02:43 +0800 12)    introduction
        3e3f34ff (cuiyb 2018-02-10 10:56:42 +0800 13)    README
        92b6a9e1 (cuiyb 2018-01-31 12:02:43 +0800 14)    tutorial
        052012bc (cuiyb 2018-04-02 20:05:21 +0800 15)    faq

#. Format output

    .. code-block:: sh

        $ git log -3 --format=format:'%h:%s'
        64ce04de:added loon pic
        2ddcc7cc:added a tree pic
        96074ea8:added cross-grained
