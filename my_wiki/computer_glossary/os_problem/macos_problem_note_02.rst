*****************
MacOS Problems 02
*****************

#. show or hide "Allow Apps downloaded from Anywhere"

   .. code-block:: sh

        sudo spctl --master-enable # hide
        sudo spctl --master-disable # show


#. MacOS to enable read and write on NTFS disk

    add ``LABEL=Driver_name none ntfs rw,auto,nobrowse``
    to ``/etc/fstab``. for example,

    .. code-block:: sh

        LABEL=Elements_SE none ntfs rw,auto,nobrowse
        LABEL=TOSHIBA_EXT none ntfs rw,auto,nobrowse

    and Unmount the NTFS drive and plug it again.
