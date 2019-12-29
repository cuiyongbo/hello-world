**************
MacOS Problems
**************

#.  You have not agreed to the Xcode license

	Run: ``sudo xcodebuild -license accept``.

#. 显示/不显示隐藏文件和文件夹

	.. code-block:: sh

		# display
		defaults write com.apple.finder AppleShowAllFiles -boolean true ; killall Finder

		# hide
		defaults write com.apple.finder AppleShowAllFiles -boolean false; killall Finder

#. 更改文件的显示属性

	.. code-block:: sh

		chflags hidden filename
		chflags nohidden filename

	e.g. sudo chflags nohidden /Applications/Parallels\ Desktop.app

#. Itunes下載的 app 目錄

	Location: ``/Users/cherry/Music/iTunes/iTunes Media/Mobile Applications/``。

#. Mac 图片目录

	Location::

		/Library/User Pictures
		/Library/Desktop Pictures

#. Mac to edit environment

	.. code-block:: sh

		vi .bash_profile
		source .bash_profile

	.. image:: images/edit_enviroment.png

#. QQ 背景图片 tag

	.. code-block:: html

		<div class="lay_background" id="lay_bg" style="width: 1440px; height: 839px;">
		<img class="lay_background_img lay_background_img_fade_out" id="lay_bg_img" alt="" src="backgroud_image_uri">
		</div>

#. Kugou 音乐资源tag

	.. code-block:: html

		<audio class="music" id="myAudio" src="music_file_uri"> </audio>

		<div class="jspPane" style="padding: 0px; top: 0px; width: 448px;">
		＃lyric zone
		</div>

#. Mac disk format map

	.. image:: images/mac_osx_disk_format.png

	#. GUID Partition Map: Used for all Intel-based Mac computers.
	#. Master Boot Record: Used for Windows partitions that will be formatted as MS-DOS (FAT) or ExFAT.
	#. Apple Partition Map: Used for compatibility with older PowerPC-based Mac computers.

	.. note::

		Formatting an external drive to use as a boot volume for Intel-based Macs is easy to do,
		but if you miss one crucial step, your efforts will be wasted. Appleis new Macs require
		the :abbr:`GPT (GUID Partition Table)` scheme for bootable disks instead of the older
		:abbr:`APM (Apple Partition Map)`. The problem is that Disk Utility formats external
		drives with APM by default.

#. Start up from macOS Recovery

	#. Turn on or restart your Mac, then immediately hold down one of these combinations:
	#. Command-R Install the latest macOS that was installed on your Mac, without upgrading to a later version.
	#. Option-Command-R Upgrade to the latest macOS that is compatible with your Mac (require accessing internet).
	#. Release the keys when you see the Apple logo or a spinning globe.
	#. When you see the macOS Utilities window, continue to the next section to determine whether to erase your startup disk or begin installing macOS.

	.. image:: images/macos_sierra_recovery_mode.jpg

#. Choose startup disk

	#. Hold down the **Option** key immediately after turning on or restarting your Mac.
	#. Release the **Option** key when you see the Startup Manager window.
	#. Select your startup disk, then click the **arrow** under its icon, or press **Return**.

	.. image:: images/macos_sierra_startup_disk.png

#. How to reset NVRAM on your Mac

	If you experience issues related to settings stored in NVRAM, resetting NVRAM might help.

	:abbr:`NVRAM (nonvolatile random-access memory)` is a small amount of memory that your Mac
	uses to store certain settings and access them quickly. Settings that can be stored in NVRAM
	include sound volume, display resolution, startup-disk selection, time zone, and recent kernel
	panic information. The settings stored in NVRAM depend on your Mac and the devices you're using with your Mac.

	If you experience issues related to these settings or others, resetting NVRAM might help.
	For example, if your Mac starts up from a disk other than the one selected in Startup Disk preferences,
	or a question mark icon briefly appears before your Mac starts up, you might need to reset NVRAM.

	Shut down your Mac, then turn it on and immediately press and hold these four keys together:
	**Option, Command, P, and R**. You can release the keys after about 20 seconds, during which
	your Mac might appear to restart.

	.. note::

		some problem information:

			* Failed to locate volume with UUID xxxx
			* Couldn't find Mac OS X (Server) install data.

#. diskutil command

	.. code-block:: sh

		sudo diskutil list
		/dev/disk0 (internal, physical):
		#:                       TYPE NAME                    SIZE       IDENTIFIER
		0:      GUID_partition_scheme                        *500.3 GB   disk0
		1:                        EFI EFI                     209.7 MB   disk0s1
		2:          Apple_CoreStorage Macintosh HD            499.4 GB   disk0s2
		3:                 Apple_Boot Recovery HD             650.0 MB   disk0s3

		sudo diskutil info /dev/disk0
		sudo diskutil info disk0s2
		sudo diskutil listFilesystems
		sudo diskutil unmount | umount [force] device
		sudo diskutil unmountDisk | umountDisk [force] device
		sudo diskutil mount [readOnly] [-mountPoint path] device
		sudo diskutil mountDisk device

#. Mac to mount a dmg file manually

	In order to manually mount DMG file, you'll need to use :command:`hdiutil` command.
	You don't have to be a privileged user, so can do it as your own user.

	.. code-block:: sh

		hdiutil attach /path_to_dmg_file # mount
		hdiutil eject /Volumes/dmg_mount_point #unmount

#. Mac to reset network

	Rename :file:`/Library/Preferences/SystemConfiguration/preferences.plist` and reboot.

	.. note:: Your customizations, such as hostname, will also be reset.

#. Mac to restart network

	Run: ``sudo killall -HUP mDNSResponder``

#. mac to block software autoupdate

	added software websites to your **hosts** file.
	such as::

		0.0.0.0 www.sublimetext.com
		0.0.0.0 www.sublimetextcn.com
		0.0.0.0 www.parallels.com
		0.0.0.0 www.piriform.com
		0.0.0.0 liveupdate.mac.sandai.net

#. mac to prohibit Parallel Desktop from generating virtual machines' Applications folders

	.. image:: images/parallel_desktop_appication_folder.png
	.. image:: images/parallel_desktop_appication_folder_setting.png
	.. image:: images/parallel_desktop_appication_folder_warnning.png

#. mac to view connected wifi password

	.. image:: images/keychain_to_view_wifi_passwd.png
