*************
Binary peeker
*************

#. hexdump or hd

    The hexdump utility is a filter which displays the specified files, 
    or the standard input, if no files are specified, in a user specified format.
    
    The hot options are as follows::
   
        -C      
        Canonical hex+ASCII display.  

        -x      
        Two-byte hexadecimal display.
   
        -n length
        Interpret only length bytes of input.
   
        -s offset
        Skip offset bytes from the beginning of the input.

        -e format_string
        Format output

**EXAMPLE**

.. code-block:: sh

    $ hd higherLayerSpeedMap
    00000000  01 00 00 00 00 00 00 00  00 00 00 00 d3 10 0c 03  |................|
    00000010  00 00 00 00 2f 00 68 00  69 00 67 00 68 00 65 00  |..../.h.i.g.h.e.|
    00000020  72 00 4c 00 61 00 79 00  65 00 72 00 53 00 70 00  |r.L.a.y.e.r.S.p.|
    00000030  65 00 65 00 64 00 4d 00  61 00 70 00 2d 00 31 00  |e.e.d.M.a.p.-.1.|
    00000040  35 00 34 00 33 00 39 00  38 00 39 00 37 00 38 00  |5.4.3.9.8.9.7.8.|
    00000050  30 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |0...............|
    00000060  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|

    $ hd -n8 -s 12 higherLayerSpeedMap
    0000000c  d3 10 0c 03 00 00 00 00                           |........|

    $ hd -n8 -s 12 -x higherLayerSpeedMap
    0000000c  d3 10 0c 03 00 00 00 00                           |........|
    000000c    10d3    030c    0000    0000 

    $ xxd higherLayerSpeedMap
    0000000: 0100 0000 0000 0000 0000 0000 d310 0c03  ................
    0000010: 0000 0000 2f00 6800 6900 6700 6800 6500  ..../.h.i.g.h.e.
    0000020: 7200 4c00 6100 7900 6500 7200 5300 7000  r.L.a.y.e.r.S.p.
    0000030: 6500 6500 6400 4d00 6100 7000 2d00 3100  e.e.d.M.a.p.-.1.
    0000040: 3500 3400 3300 3900 3900 3100 3400 3600  5.4.3.9.9.1.4.6.
    0000050: 3000 0000 0000 0000 0000 0000 0000 0000  0...............

    $ find . -name '*.dat' -exec hexdump -n4 -e '"@%d\n"' \{\} \; > test

    $ head test
    @1566163800
    @1566214200
    @1566169200

    $ date -f test | head
    Mon Aug 19 05:30:00 CST 2019
    Mon Aug 19 19:30:00 CST 2019
    Mon Aug 19 11:00:00 CST 2019
