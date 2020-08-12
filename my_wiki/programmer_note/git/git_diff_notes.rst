Git diff
========

.. code-block:: sh
    :caption: Hot Options

    --name-only

    Show only names of changed files.

    --name-status

    Show only names and status of changed files. 
    See the description of the --diff-filter option on what the status letters mean.

    --color[=<when>]
    
    Show colored diff. The value must be always (the default), never, or auto.

    --stat[=width[,name-width]]

    Generate a diffstat. You can override the default output width for 80-column 
    terminal by --stat=width. The width of the filename part can
    be controlled by giving another width to it separated by a comma.

    --numstat

    Similar to --stat, but shows number of added and deleted lines in decimal notation 
    and pathname without abbreviation, to make it more machine friendly. 
    For binary files, outputs two - instead of saying 0 0.

    --shortstat

    Output only the last line of the --stat format containing total number of modified files, 
    as well as number of added and deleted lines.

.. code-block:: sh
    :caption: Examples

    $ git diff --shortstat 3f7d86b0de e0a1f4b15b
    11 files changed, 742 insertions(+), 213 deletions(-)

    $ git diff --shortstat HEAD~1
    11 files changed, 742 insertions(+), 213 deletions(-)

    $ git diff --numstat  3f7d86b0de e0a1f4b15b 
    245     0       make/archer/conf/strategy.conf.template
    ...

    $ git diff --stat e0a1f4b15b 3f7d86b0de
    make/archer/conf/strategy.conf.template        | 245 ----------------------------------------
    nframe/Ac2DxFrame/digest_recaller.cpp          |  37 ++++++----------
    ...
    11 files changed, 213 insertions(+), 742 deletions(-)

#. git to count number of line changed in between two commits

    .. code-block:: sh

        $ git diff --stat e0a1f4b15b 3f7d86b0de
        make/archer/conf/strategy.conf.template        | 245 ----------------------------------------
        nframe/Ac2DxFrame/digest_recaller.cpp          |  37 ++++++----------
        ...
        11 files changed, 213 insertions(+), 742 deletions(-)
        $ git diff --stat e0a1f4b15b 3f7d86b0de | awk 'BEGIN{sum=0}{sum+=$3}END{print "sum=", sum}'
        sum= 955