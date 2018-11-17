Windows Problems
================

#. Windows 10 锁屏壁纸位置
   
   Solution::

      $HOME\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_***\LocalState\Assets
      Batch rename: dir | rename * *.jpg

#. VS Precompile setting and error C1083
   
   Solution::

      For the entire project, you should choose the options "Use Precompiled Header (/Yu)", "stdafx.h", "$(IntDir)\$(TargetName).pch".
      For the stdafx.cpp file , you should specify these options: "Create Precompiled Header (/Yc)",   "stdafx.h", "$(IntDir)\$(TargetName).pch".

#. VS 工程环境变量定义
   
   Solution::

      Project: "property"-"C/C++"-"Preprocessor"-"Macros"

#. VS fatal error LNK1112: module machine type 'X86' conflicts with target machine type 'x64'
   
   Solution::

      工程 "property" - "Config manager" - "platform": Win32 --> X64
   
#. VS '__LINE__Var' : undeclared identifier
   
   Solution::

      Project: "property" - "C/C++" - "All Options" - "Debug information format" : "Program Database (/Zi)"

#. VS Enable String Pooling
   
   Solution::

      Project: "property" - "C/C++" - "Code Generation" - "Enable String Pooling" - "Yes (/GF)"
      
#. VS gtest 选择性运行测试用例
   
   Solution::

      Project: "property" - "Debug" - "Command Arguments"  - "--gtest_filter = MemoryLeak*.*"

#. VS 不编译指定的源文件
   
   Solution:

      File: "property" - "General" - "Exclude from build"  - "yes"

#. VS warning LNK4075: ignoring '/INCREMENTAL' due to '/OPT:ICF'(or '/OPT:REF') specification

   Solution::

      Project: "property" - "Linker" - "All Options" - "References" - "No (/OPT:NOREF)"
      Project: "property" - "Linker" - "All Options" - "Enable COMDAT Folding" - "No (/OPT:NOICF)"

#. VS warning C4627 and error C1010

   Solution::

      Solution 1. add '#include "stdafx.h"' to your source
      Solution 2. Project: "property" - "C/C++" - "Precompiled Header" - "Not Using Precompiled Headers"

#. VS warning LNK4098: defaultlib 'LIBCMT' conflicts with use of other libs; use /NODEFAULTLIB:library
   
   Solution::

      The run-time libraries now contain directives to prevent mixing different types.
      You will receive this warning if you try to use different types or debug and non-debug
      versions of the run-time library in the same program. For example, if you compiled one
      file to use one kind of run-time library and another file to use another kind (for example,
      single-threaded versus multithreaded) and tried to link them, you will get this warning.
      You should compile all source files to use the same run-time library. 

   See the Use `Run-Time Library (/MD, /MT, /LD) compiler options <https://msdn.microsoft.com/en-us/library/aa267384(v=vs.60).aspx>`_ 
   for more information.
   
#. VS ``__debugbreak()``
   
   Solution::

      This works even in Release

#. VS Error C2220

   Solution::

      Don't use /WX to compile ["Property" - "C/C++" - "Treat warning as error"]

#. VS Disable source control
   
   Solution::

      Tools - Options - Source Control - Current source control plugin, choose "none"
      Search $VSDIR and rename <Microsoft.TeamFoundation.Git.Provider.dll>
   
#. VS Change defalut file open location
   
   Solution::

      Search <DefaultFileOpenLocation> in Regedit, change its value with your desired directory 

#. VS Clear MRUList

   Solution::

      File: HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\FileMRUList
      Project: HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\ProjectMRUList

#. VS Cannot step into function when debugging
   
   Solution::

      Remove the solution's suo file (contains debug information, user settings such as break points, 
      bookmarks, and other user settings.), and rebuild the project.

   **NOTE:** The :abbr:`.suo (solution user options)` file contains per-user solution options. 
   This file should not be checked in to source code control. The suo file is a structured storage, 
   or compound, file stored in a binary format. You save user information into streams with the name 
   of the stream being the key that will be used to identify the information in the suo file. The file 
   is used to store user preference settings, and is created automatically when Visual Studio saves 
   a solution. Refer to 
   `Solution User Options File <https://docs.microsoft.com/en-us/visualstudio/extensibility/internals/solution-user-options-dot-suo-file?view=vs-2017>`_
   for more information.

#. VS console app exits without pause even running with Ctrl + F5
   
   Solution::

      Settings - Linker - SubSystem - Console (/SUBSYSTEM:CONSOLE)

#. Inspect shared memory usage
   
   .. image:: images/windows_view_shared_memory_usage.png

#. Sublime Text "git_binary" setting problem.
   
   .. image:: images/sublime_text_git_binary_setting.png

   Set git_binary setting to your full git path in user profile.
   for example::

      "git_binary": "C:/Program Files/Git/cmd/git.exe"

#. Sublime Text "ignore_vcs_packages" setting.
   
   .. image:: images/sublime_ignore_vcs_packages_error.png

   added ``"ignore_vcs_packages":true`` to user settings.

#. XShell gets frozen after accidently typing "Ctrl - S"
   
   Solution::

      Press "Ctrl - Q" to unfreeze.

      To disable this altogether, stick ``stty -ixon`` in a startup script. 
      To allow any key to get things flowing again, use ``stty ixany``.

      PS: It's neither the terminal nor the shell that does this, but the OS's terminal driver.

#. VS disable spelling check
   
   .. image:: images/disable_spelling_check.png

#. Windows 10 to disable hibernation
   
   .. code-block:: none

      > powercfg /hibernate off

      > powercfg /?
      POWERCFG /COMMAND [ARGUMENTS]
      Description:
        Enables users to control power settings on a local system.
        For detailed command and option information, run "POWERCFG /? <COMMAND>"

#. windows10 to prohibite hiberfil.sys from generating
   
   .. code-block:: none

      > powercfg -h off

#. windows10 to turn off Windows Defender
   
   Open Regedit, Modify entry ``HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SecurityHealthService`` value to 4.

#. windows10 to hide ESP Partition
   
   .. image:: images/remove_esp_partition.PNG

#. windows10 to remove EFI partition
   
   .. image:: images/clean_efi_partition.PNG

#. windows10 to view installed product key
   
   Open **regedit** and locate to 
   ``HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\SoftwareProtectionPlatform\BackupProductKeyDefault``.

