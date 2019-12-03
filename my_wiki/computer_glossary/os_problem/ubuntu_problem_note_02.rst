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
