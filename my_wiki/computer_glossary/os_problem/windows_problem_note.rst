Windows Problems
================

只有自己足够强大，才能不被别人践踏。

只有自己格外努力，才能显得毫不费力。

#. Windows 10 锁屏壁纸位置

    Solution::

        $HOME\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_***\LocalState\Assets
        Batch rename: dir | rename * *.jpg
        Batch rename: find . -type f -exec mv \{\} \{\}.jpg \;

#. Windows software

    .. code-block:: none

        Zeal (similar to Dash)
        Sublime text
        Nodepad++
        福昕阅读器
        TortoiseGit (need git for windows of course)
        Visual Studio 2019 (well, still need to install a bunch of dependencies)
        Chrome
        360 zip
        Postman
        ScreenToGif

#. Chrome plugin

    .. code-block:: none

        Saladict
        Proxy SwitchyOmega
        百度广告屏蔽

#. VS plugin collection

    .. code-block:: none

        Colorful-IDE
        Highlight all occurrence of selected words
        TGit
        Visual Assist

#. VS Precompile setting and error C1083

    Solution::

        For the entire project, you should choose the options "Use Precompiled Header (/Yu)", "stdafx.h", "$(IntDir)\$(TargetName).pch".
        For the stdafx.cpp file , you should specify these options: "Create Precompiled Header (/Yc)",   "stdafx.h", "$(IntDir)\$(TargetName).pch".

#. VS 工程环境变量定义

    Solution: ``Project: "property"-"C/C++"-"Preprocessor"-"Macros"``

#. VS fatal error LNK1112: module machine type 'X86' conflicts with target machine type 'x64'

    Solution: ``工程 "property" - "Config manager" - "platform": Win32 --> X64``

#. VS '__LINE__Var' : undeclared identifier

    Solution: ``Project: "property" - "C/C++" - "All Options" - "Debug information format" : "Program Database (/Zi)"``

#. VS Enable String Pooling

    Solution: ``"property" - "C/C++" - "Code Generation" - "Enable String Pooling" - "Yes (/GF)"``

#. VS gtest 选择性运行测试用例

    Solution: ``Project: "property" - "Debug" - "Command Arguments"  - "--gtest_filter = MemoryLeak*.*"``

#. VS 不编译指定的源文件

    Solution: ``File: "property" - "General" - "Exclude from build"  - "yes"``

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

    See the Use Run time library options [#Run time library options]_ for more information.

#. VS ``__debugbreak()``

    This works even in Release

#. VS Error C2220

   Solution: ``Don't use /WX to compile ["Property" - "C/C++" - "Treat warning as error"]``

#. VS Disable source control

    Solution::

        Tools - Options - Source Control - Current source control plugin, choose "none"
        Search $VSDIR and rename <Microsoft.TeamFoundation.Git.Provider.dll>

#. VS Change defalut file open location

    Solution: Search <DefaultFileOpenLocation> in Regedit, change its value with your desired directory

#. VS Clear MRUList

    Solution::

        File: HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\FileMRUList
        Project: HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\ProjectMRUList

#. VS Cannot step into function when debugging

    Solution::

        Remove the solution's suo file (contains debug information, user settings such as break points,
        bookmarks, and other user settings.), and rebuild the project.

    .. note::

        The :abbr:`.suo (solution user options)` file contains per-user solution options.
        This file should not be checked in to source code control. The suo file is a structured storage,
        or compound, file stored in a binary format. You save user information into streams with the name
        of the stream being the key that will be used to identify the information in the suo file. The file
        is used to store user preference settings, and is created automatically when Visual Studio saves
        a solution. Refer to Solution User Options File [#Solution User Options File]_ for more information.

#. VS console app exits without pause even running with `Ctrl + F5`

    Solution: ``Settings - Linker - SubSystem - Console (/SUBSYSTEM:CONSOLE)``

#. Inspect shared memory usage

   .. image:: images/windows_view_shared_memory_usage.png

#. XShell gets frozen after accidently typing "Ctrl - S"

    Solution: Press ``Ctrl - Q`` to unfreeze.

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

#. windows10 to prohibite ``hiberfil.sys`` from generating： ``powercfg -h off``.

#. windows10 to turn off Windows Defender

    Open Regedit, Modify entry ``HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SecurityHealthService`` value to 4.

#. windows10 to hide ESP Partition

    .. image:: images/remove_esp_partition.PNG

#. windows10 to remove EFI partition

    .. image:: images/clean_efi_partition.PNG

#. windows10 to view installed product key

    Open **regedit** and locate to
    ``HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\SoftwareProtectionPlatform\BackupProductKeyDefault``.

#. windows10 to refresh DNS cache or flush hosts changes： ``ipconfig /flushdns``.

#. vs cannot pass argument to python script in custom build tool

    Add ``"%*"`` to following regedit table entry:

    .. image:: images/vs_py_argument_passing_custom_build_tool_01.jpg
    .. image:: images/vs_py_argument_passing_custom_build_tool_02.jpg

#. Note pad++ change tab to space

    Solution: ``Settings`` - ``Preferences``

    .. image:: images/note_pad_tab_to_space_01.jpg
    .. image:: images/note_pad_tab_to_space_02.jpg

#. Note pad++ 实现类似vs中的行复制粘贴功能: 安装插件 ``Visual Studio Line Copy``.

#. windows to delete service

    .. code-block:: sh

        # sc delete service_name
        # service_name can be obtained from service property
        > sc delete CDPUserSvc_8d2c2
        [SC] DeleteService SUCCESS

#. VS 中文显示乱码

    .. image:: images/vs_chiness_display_solution.png

#. Windows terminal 中 VIM 字体和系统不一致: 安装 ``Microsoft YaHei Mono.ttf`` 字体.
#. ssh login without inputing password every time: ``ssh-copy-id -i path/to/.ssh/id_rsa.pub username@hostname``.
#. Windows terminal 文本粘贴格式混乱: 关掉 vim 自动缩进功能.

#. Windows terminal to split screen

    .. code-block:: json

        // Add any keybinding overrides to this array.
        // To unbind a default keybinding, set the command to "unbound"
        "keybindings": [
            {"command": "nextTab", "keys": ["ctrl+pgdn"]},
            {"command": "prevTab", "keys": ["ctrl+pgup"]},
            {"keys": ["alt+shift+="], "command": {"action": "splitPane", "split": "vertical", "splitMode": "duplicate"}},
            {"keys": ["alt+shift+-"], "command": {"action": "splitPane", "split": "horizontal", "splitMode": "duplicate"}}
        ]

#. Windows 下查看错误码

    Refer to "Tools" - "Error Lookup". Or just run ``errlook.exe``
    in  ``C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools``.

.. rubric:: Footnotes

.. [#] `Run time library options <https://msdn.microsoft.com/en-us/library/aa267384(v=vs.60).aspx>`_
.. [#] `Solution User Options File <https://docs.microsoft.com/en-us/visualstudio/extensibility/internals/solution-user-options-dot-suo-file?view=vs-2017>`_
