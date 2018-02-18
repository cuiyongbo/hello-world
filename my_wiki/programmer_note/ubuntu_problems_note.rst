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
