**********************
Ubuntu problem note 02
**********************

#. Ubuntu to add :abbr:`PPA (Personal Package Archives)`

    .. code-block:: sh

        sudo add-apt-repository ppa:jonathonf/python-3.7
        sudo apt-get update

#. Ubuntu to enable ssh

   Install openssh: ``sudo apt install openssh-server``.

#. Ubuntu to view installed packages

    .. code-block:: sh

        $ apt list *completion
        Listing... Done
        bash-completion/xenial-updates,xenial-updates,now 1:2.1-4.2ubuntu1.1 all [installed]
        N: There is 1 additional version. Please use the '-a' switch to see it

        # list (work-in-progress)
        # list is somewhat similar to dpkg-query --list in that it can display a list of packages satisfying
        # certain criteria. It supports glob(7) patterns for matching package names as well as options to list
        # installed (--installed), upgradeable (--upgradeable) or all available (--all-versions) versions.

#. Ubuntu to flush DNS after modifing `hosts` file

    Solution: ``sudo systemctl restart NetworkManager``.

#. "ar: xxx.a: Malformed archive"

    Solution: remove library file, and rebuild.

#. Ubuntu to install boost

    .. code-block:: sh

        sudo apt update
        sudo apt install libboost-dev
        sudo apt install libboost-all-dev

#. Ubuntu to set a short password

    Solution: ``sudo passwd username``

#. Ubuntu to free cached memory manually

    .. code-block:: sh

        # free pagecache
        sync; sudo echo 1 > /proc/sys/vm/drop_caches

        # free dentries and inodes
        sync; sudo echo 2 > /proc/sys/vm/drop_caches

        # free pagecache, dentries and inodes
        sync; sudo echo 3 > /proc/sys/vm/drop_caches

    /proc/sys/vm/drop_caches (since Linux 2.6.16)

    Writing to this file causes the kernel to drop clean caches, dentries,
    and inodes from memory, causing that memory to become free. This can be
    useful for memory management testing and performing reproducible filesystem
    benchmarks. Because writing to this file causes the benefits of caching to be lost,
    it can degrade overall system performance. Because writing to this file is a nondestructive
    operation and dirty objects are not freeable, the user should run sync(1) first.

#. Ubuntu to install sogou input

    .. code-block:: sh

        sudo apt install fcitx

        # go to download installation package

        sudo dpkg -i deb_package_name

        sudo apt install -f # fix broken dependencies

#. Ubuntu to view partition table

    .. code-block:: sh

        parallels ~$ sudo fdisk -l /dev/sdb
        Disk /dev/sdb: 1.8 TiB, 2000365289472 bytes, 3906963456 sectors
        Units: sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disklabel type: dos
        Disk identifier: 0x16f2a91f

        Device     Boot Start        End    Sectors  Size Id Type
        /dev/sdb1        1985 3906961407 3906959423  1.8T  f W95 Ext'd (LBA)
        /dev/sdb5        2048 3906961407 3906959360  1.8T  7 HPFS/NTFS/exFAT

        parallels ~$ sudo fdisk -l /dev/sdc
        Disk /dev/sdc: 1.8 TiB, 2000398931968 bytes, 3907029164 sectors
        # ...
        Disk identifier: 0x390aedb2

        Device     Boot Start        End    Sectors  Size Id Type
        /dev/sdc1  *     2048 3907022847 3907020800  1.8T  7 HPFS/NTFS/exFAT

        parallels ~$ lsblk
        NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
        sdb      8:16   0  1.8T  0 disk
        ├─sdb5   8:21   0  1.8T  0 part /media/parallels/Elements_SE
        └─sdb1   8:17   0    1K  0 part
        sr0     11:0    1 1024M  0 rom
        sdc      8:32   0  1.8T  0 disk
        └─sdc1   8:33   0  1.8T  0 part /media/parallels/TOSHIBA_EXT
        sda      8:0    0   64G  0 disk
        ├─sda2   8:2    0    1K  0 part
        ├─sda5   8:5    0 1022M  0 part [SWAP]
        └─sda1   8:1    0   63G  0 part /

