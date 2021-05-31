comm Command Note
=================

SYNOPSIS: ``comm [OPTION]... FILE1 FILE2``

**DESCRIPTION**

    Compare sorted files FILE1 and FILE2 line by line. [**in lexicographical order**]

    With no options, produce three-column output.  Column one contains lines unique 
    to FILE1, column two contains lines unique to FILE2, and column three contains 
    lines common to both files::

        -1     suppress column 1 (lines unique to FILE1)
        -2     suppress column 2 (lines unique to FILE2)
        -3     suppress column 3 (lines that appear in both files)

.. code-block:: sh

    # Print only lines present in both file1 and file2.
    comm -12 file1 file2

    # Print lines in file1 not in file2
    # comm -13 file1 file2  