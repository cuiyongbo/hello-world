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

    A more stable method:

    .. code-block:: sh

        $ diskutil list

        /dev/disk2 (external, physical):
           #:                       TYPE NAME                    SIZE       IDENTIFIER
           0:     FDisk_partition_scheme                        *2.0 TB     disk2
           1:               Windows_NTFS TOSHIBA_EXT             2.0 TB     disk2s1

        $ sudo mkdir /Volumes/toshiba

        # something insidious comes here, I'm not sure the exact commbinations
        # which make ``rw`` come into effect
        $ sudo mount_ntfs -t rw,sync,nobrowse /dev/disk2s1 /Volumes/toshiba

#. Mac to customize Thunder display

   Remove plugins in ``Thunder.app/Contents/plugins/``.
