*****************
Cpp Memory Layout
*****************

#. cpp memory layout

    .. image:: images/memory_layout.png

#. cpp to decide byteorder

    .. image:: images/os_byteorder.png

    According to the memory layout, the byteorder is little-endian.

    .. code-block:: c
        :caption: Take from */usr/include/i386/endian.h*

        /*
           Definitions for byteorder, according to significance of bytes,
           from low addresses to high addresses. The value is what you get by
           putting '4' in the most significant byte, '3' in the second most
           significant byte, '2' in the second least significant byte, and '1'
           in the least significant byte, and then writing down one digit for
           each byte, starting with the byte at the lowest address at the left,
           and proceeding to the byte with the highest address at the right.
        */

        #define __LITTLE_ENDIAN 1234
        #define __BIG_ENDIAN    4321
        #define __PDP_ENDIAN    3412
