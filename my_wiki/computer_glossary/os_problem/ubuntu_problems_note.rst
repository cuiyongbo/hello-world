Ubuntu Problems
===============

#. Unable to lock the administration directory (/var/lib/dpkg/) is another process using it [solved]
   
   .. code-block:: sh 

      sudo rm /var/lib/dpkg/lock
      sudo dpkg --configure -a

#. Location where to find the downloaded files of apt-get [solved]

   .. code-block:: sh

      /var/cache/apt/*

#. download the source file of linux binary file [solved]

   Execute following command, It will be in your current directory:

   .. code-block:: sh

      sudo apt-get source pkg-name

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