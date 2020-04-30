**********************
Ubuntu problem note 04
**********************

#. See the default system page size

    .. code-block:: sh

        getconf PAGESIZE
        4096

    .. note::

        Find more interesting features about :command:`getconf` by ``man getconf``,
        some examples::

                # display the maximum length of a filename in the /tmp directory
                getconf NAME_MAX /tmp
                255
                getconf CHAR_BIT
                8
