*********************
MacOS problem note 02
*********************

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

    Free third-party tools:

        - ntfs-3g

#. Mac to customize Thunder display

    Remove plugins in ``Thunder.app/Contents/plugins/``.

#. Mac to install Homebrew

    Run: ``/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"``.
    and after finishing installation, run: ``brew install git gcc gdb valgrind python3 unzip htop pidof`` to
    install softwares.

#. Mac to codesign gdb

    gdb requires special privileges to access Mach ports.
    You will need to codesign the binary. For instructions, see:

        https://sourceware.org/gdb/wiki/BuildingOnDarwin

    On 10.12 (Sierra) or later with SIP, you need to run this: ``echo "set startup-with-shell off" >> ~/.gdbinit``

    and further to stop mac from promoting "take control" when running gdb,
    run: ``sudo security authorizationdb write system.privilege.taskport allow``

    .. image:: images/gdb_take_control_notification.png

#. Dash Document location: ``/Users/cherry/Library/Application Support/Dash/DocSets``

#. Mac workhorses

    - Dash
    - eZip
    - Sublime Text 3
    - gdb, gcc
    - Moviest
    - Parallel Desktop
    - Python3
    - Thunder
