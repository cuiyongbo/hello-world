How to install Ubuntu on MacBook using USB Stick
================================================

UNetbootin (Automated, graphical approach)
------------------------------------------

**UNetbootin for Mac OS X** can be used to automate the process of extracting the Ubuntu ISO file to USB, 
and making the USB drive bootable. **The resulting USB drive, however, can be booted on PCs only**. 
If attempting to make a USB drive that can be booted from a Mac, follow the instructions below.

Manual Approach
---------------

We would encourage Mac users to download Ubuntu Desktop Edition by burning a CD for the time being. 
But if you would prefer to use a USB, please follow the instructions below.


.. note::

   this procedure requires an .img file that you will be required to create from the .iso file you download.

   TIP: Drag and Drop a file from Finder to Terminal to 'paste' the full path without typing and risking type errors.

#. Download the desired file and open the Terminal

#. Convert the .iso file to .img using the convert option of :command:`hdiutil`
   
   .. code-block:: sh

      hdiutil convert /path/to/ubuntu.iso -format UDRW -o /path/to/target.img

   .. note:: 

      Note: OS X tends to put the ``.dmg`` ending on the output file automatically.

#. Insert your flash media and run :command:`diskutil` to determine the device node assigned to your flash media.

   .. code-block:: sh

      diskutil list


#. Run

   .. code-block:: sh

      diskutil unmountDisk /dev/diskN # replace N with the disk number from the last command.

   .. note::

      If you see the error "Unmount of diskN failed: at least one volume could not be unmounted", 
      **start Disk Utility.app and unmount the volume (don't eject)**.

#. Execute
   
   .. code-block:: sh
   
      sudo dd if=/path/to/downloaded.img of=/dev/diskN bs=1m

   .. note::

      Replace /path/to/downloaded.img with the path where the image file is located; for example, ./ubuntu.img or ./ubuntu.dmg.


#. Using /dev/rdisk instead of /dev/disk may be faster.

   .. note:: 

      If you see the error dd: Invalid number '1m', you are using GNU dd. Use the same command but replace ``bs=1m`` with ``bs=1M``.

      If you see the error dd: /dev/diskN: Resource busy, make sure the disk is not in use. Start Disk Utility.app and unmount the volume (don't eject).


#. Run following command and remove your flash media when the command completes.

   .. code-block:: sh

      diskutil eject /dev/diskN

#. Restart your Mac and press **alt** while the Mac is restarting to choose the USB-Stick

