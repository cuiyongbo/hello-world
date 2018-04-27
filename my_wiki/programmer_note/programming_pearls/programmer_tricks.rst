Programmer's Tricks
===================

#. GCC to produce ASM

   .. code-block:: sh

      gcc -S test.c # then you will see test.s in current directory


#. See the default system page size

   .. code-block:: sh

      getconf PAGESIZE
      4096

   .. note::

      Find more interesting features about :command:`getconf` by ``man getconf``, some examples:

         .. code-block:: sh

            getconf NAME_MAX /tmp # display the maximum length of a filename in the /tmp directory
            255
            getconf CHAR_BIT
            8
