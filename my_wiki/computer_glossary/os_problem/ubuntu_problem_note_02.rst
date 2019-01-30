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
