***************
Ubuntu Problems
***************

#. Unable to lock the administration directory (`/var/lib/dpkg/`) is another process using it
   
    .. code-block:: sh 

        sudo rm /var/lib/dpkg/lock
        sudo dpkg --configure -a

#. Location where to find the downloaded files of apt-get

    .. code-block:: sh

        /var/cache/apt/*

#. download the source file of linux binary file

    Execute following command, It will be in your current directory: ``sudo apt-get source pkg-name``.

#. Inspect shared memory usage
   
    .. image:: images/ubuntu_view_shared_memory_usage.png

#. Change cursor shape in terminal
   
    "Edit" - "Profile Preferences" - "General" - "Cursor Shape".

    .. image:: images/terminal_cursor_shape_configure.png

#. Show current time
   
    .. code-block:: sh
   
        $ date
        Sun Jul 15 23:07:11 CST 2018

#. Terminal switch to root.
      
    .. code-block:: sh

        sudo -i 

#. Ubuntu to disable system failure reporting.
   
    .. image:: images/ubuntu_system_failure_report.png
   
    .. code-block:: sh

        $ sudo gpedit /etc/default/apport
        # set enable to 0

#. Ubuntu to change docker location
   
    .. code-block:: sh

        ~$ gsettings set com.canonical.Unity.Launcher launcher-position Left
        ~$ gsettings set com.canonical.Unity.Launcher launcher-position Bottom
        # Note you may not excute these commands with sudo.

#. Ubuntu to install pthread manual
   
    Run ``sudo apt-get install manpages-posix manpages-posix-dev``.

#. Ubuntu to update vim
   
    Run ``sudo apt-get install vim``.

#. Ubuntu to remove LibreOffice suite.
   
    Run ``sudo apt-get purge LibreOffice*``.

#. Ubuntu to remove Amazon from Launcher.
   
    Run ``sudo find /usr/share/applications/ -iname "*amazon*" -delete``.

#. Reinstall Vmware Tool
   
    .. code-block:: sh

        $ tar -zxf VMwareTools-10.1.6-5214329.tar.gz --directory ~/Desktop/
        $ cd ~/Desktop/vmware-tool
        $ sudo ./vmware-install.pl

#. Ubuntu to show shortcut panel
   
    Press super key and hold it.

    .. image:: images/dash_home_shortcuts.png

#. Ubuntu to disable update popup

    .. image:: images/disable_ubuntu_update_popup.jpg