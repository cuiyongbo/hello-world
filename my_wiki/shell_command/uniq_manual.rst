************************************
uniq - report or omit repeated lines
************************************

Usage: ``uniq [OPTION]... [INPUT [OUTPUT]]``

**OPTIONS**

    .. option: -c, --count
        
        prefix lines by the number of occurrences

    .. option:: -d, --repeated
                
        only print duplicate lines, one for each group

    .. option:: -i, --ignore-case
                
        ignore differences in case when comparing

    .. option:: -u, --unique
                
        only print unique lines

    .. option:: -s, --skip-chars=N
        
        avoid comparing the first N characters

    .. option:: -w, --check-chars=N
                
        compare no more than N characters in lines

.. note:: 

    uniq does not detect repeated lines unless they are adjacent.  
    You may want to sort the input first, or use ``sort -u`` without uniq.  

**Example**

.. code-block:: sh

    $ echo "this is this and that is not this" > sample
    $ cat sample | tr " " "\n" | sort | uniq -c | sort -r
            3 this
            2 is
            1 that
            1 not
            1 and
    $ cat sample | tr " " "\n" | sort | uniq -d
    is
    this
    $ cat sample | tr " " "\n" | sort | uniq -u
    and
    not
    that
