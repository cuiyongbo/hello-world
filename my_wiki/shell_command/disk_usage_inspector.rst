********************
Disk Usage inspector
********************

#. du - estimate file space usage

    du summarize disk usage of each FILE, recursively for directories.
    Hot options::

        -0, --null
        end each output line with 0 byte rather than newline

        -c, --total
        produce a grand total

        -d, --max-depth=N
        print the total for a directory (or file, with --all)
        only if it is N or fewer levels below the command line
        argument; --max-depth=0 is the same as --summarize

        -s, --summarize
        display only a total for each argument. equivalent to -d 0.

        -h, --human-readable
        print sizes in human readable format (e.g., 1K 234M 2G)

        -L, --dereference
        dereference all symbolic links

        -P, --no-dereference
        don't follow any symbolic links (this is the default)

        -S, --separate-dirs
        do not include size of subdirectories

        -t, --threshold=SIZE
        exclude entries smaller than SIZE if positive, or entries
        greater than SIZE if negative. If multi -t are specified,
        the last one takes effect.

        --exclude=PATTERN
        exclude files that match PATTERN.
        PATTERN is a shell pattern (not a regular expression).

#. df - report file system disk space usage

    This manual page documents the GNU version of df.
    df displays information about the file system on
    which each FILE resides, or all file systems by default.

    If an argument is the absolute file name of a disk device node
    containing a mounted file system, df shows the space available
    on that file system rather than on the file system containing
    the device node (which is always the root file system).

    Hot Options::

        -a, --all
        include dummy file systems

        -B, --block-size=SIZE
        scale sizes by SIZE before printing them.
        SIZE is an integer and optional unit (example: 10M is 10*1024*1024).
        Units are K, M, G, T, P, E, Z, Y (powers of 1024).
        E.g., '-BM' prints sizes in units of 1024*1024 bytes.

        --total
        produce a grand total

        -h, --human-readable
        print sizes in human readable format (e.g., 1K 234M 2G)

        -t, --type=TYPE
        limit listing to file systems of type TYPE

        -T, --print-type
        print file system type

        -x, --exclude-type=TYPE
        limit listing to file systems not of type TYPE

.. code-block:: sh
    :caption: df Examples

    $  du -ah -t 8K  | wc -l # file count whose size is no less than 8K
    $  du -ah -t -8M | wc -l # file count whose size is no larger than 8M

    $ du -h  -t 8M --time
    8.3M    2018-06-22 13:04        ./biology_glossary/images
    8.4M    2018-06-22 13:04        ./biology_glossary
    77M     2018-06-22 14:37        ./_build/html
    84M     2018-06-22 14:37        ./_build
    138M    2018-06-22 16:39        .

    $ du -h  -t 8M --time -c
    8.3M    2018-06-22 13:04        ./biology_glossary/images
    8.4M    2018-06-22 13:04        ./biology_glossary
    ....
    138M    2018-06-22 16:39        total

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

    $ du -sh --exclude-from=/home/cuiyb/past_ti_pattern
    3.9G    .
    $ cat /home/cuiyb/past_ti_pattern
    route*
    tiData*
    teData*
    idList*
    temp*

    $ du -d 1 -h | sort -rh | head
    126G    .
    56G     ./server-manager
    24G     ./tile-server
    10G     ./poi-server
    ...


.. code-block:: sh
   :caption: df Examples

    $ df -hT --total
    Filesystem     Type      Size  Used Avail Use% Mounted on
    udev           devtmpfs   20G  4.0K   20G   1% /dev
    tmpfs          tmpfs     4.0G  640K  4.0G   1% /run
    /dev/dm-0      ext4      157G  135G   15G  91% /
    none           tmpfs     100M     0  100M   0% /run/user
    /dev/sda1      ext2      236M   40M  184M  18% /boot
    tmpfs          tmpfs     4.0G  2.0G  2.1G  49% /tmp/realtime
    ...
    total          -         214G  147G   61G  71% -

    $ df -h /dev/shm
    Filesystem      Size  Used Avail Use% Mounted on
    none             20G  469M   20G   3% /run/shm
