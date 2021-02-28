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
        $ sudo mount_ntfs -o rw,sync,nobrowse /dev/disk2s1 /Volumes/toshiba

    Free third-party tools:

        - ntfs-3g

#. Mac to customize Thunder display

    Remove plugins in ``Thunder.app/Contents/plugins/``.

#. Mac to install Homebrew

    Run: ``/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"``.
    and after finishing installation, run: ``brew install git gcc gdb valgrind python3 unzip htop pidof`` to
    install softwares.

#. Homebrew to remove package and dependencies

    .. code-block:: sh

        # inspect package dependencies

        $ brew info python
        ...
        ==> Dependencies
        Build: pkg-config ✘
        Required: gdbm ✔, openssl@1.1 ✔, readline ✔, sqlite ✔, xz ✔
        ...

        # install brew-rmtree
        $ brew tap beeftornado/rmtree && brew install brew-rmtree

        # try and test
        $ brew rmtree package_name

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
    - Parallel Desktop / VirtualBox
    - Python3
    - Thunder
    - Visual studio code
    - iStatistica
    - Typora [markdown编辑器]

#. VirtualBox to configure UbuntuServer VM

    * Install VM: remember to install `openSSH` while installing

    * change software sources to domestic ones

        Choose `aliyun unbuntu sources`_ according to installed OS version. 
        backup `/etc/apt/sources.list` and replace its contents, then run `sudo apt update`.

    * configure network if you can ping VM from host

        Go to VM's Settings, Network, Adapater 1, change "Attach to" from "NAT" to "Bridged Adapter".
        If you can't ping host from VM, perhaps you should check firewall settings. 
        for me I just turn off the firewall of macbook.

    * configure shared folder settings.

        Go to VM's Settings, Shared Folders, add host folder you wish to share.
        Then in VM you need to install vb guest option packages by running: `sudo apt install virtualbox-guest-utils`.
        After installation you will find the shared folder prefixed with `sf_` in `/media`, still you can't access it,
        so the last step is to add yourself to `vboxsf` group by runnig `sudo adduser your_account vboxsf`.
        Finally enjoy yourself with VB.

.. rubric:: Footnotes

.. [#] `aliyun unbuntu sources <https://developer.aliyun.com/mirror/ubuntu?spm=a2c6h.13651102.0.0.3e221b114p7WHD>`_

#. Mac to use OPTION key as ALT key

    In termianl's Setting, Descriptor Files, Keyboard, check "Use Option key as Meta key". 
