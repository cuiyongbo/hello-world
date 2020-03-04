*********************************
MacOS Bootable installer Creation
*********************************

.. code-block:: sh

    Usage: createinstallmedia --volume <path to volume to convert> --applicationpath <path to Install OS X Yosemite.app> [--force]

    Arguments:

        --volume, A path to a volume that can be unmounted and erased to create the install media.
        --applicationpath, A path to copy of the OS installer application to create the bootable media from.
        --nointeraction, Erase the disk pointed to by volume without prompting for confirmation.

    Example: createinstallmedia --volume /Volumes/Untitled --applicationpath "/Applications/Install OS X Yosemite.app"

    This tool must be run as root.

    $ sudo /Applications/Install_Yosemite.app/Contents/Resources/createinstallmedia --volume /Volumes/Yosemite \
            --applicationpath /Applications/Install_Yosemite.app --nointeraction


.. rubric:: Footnotes

.. [#] `How to create a bootable installer for macOS <https://support.apple.com/en-us/HT201372>`_

