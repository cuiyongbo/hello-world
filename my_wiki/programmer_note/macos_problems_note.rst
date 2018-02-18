MacOs Problems
============== 

#.  You have not agreed to the Xcode license. [solved]
   
   .. code-block:: sh

      sudo xcodebuild -license accept

#. 显示隐藏文件和文件夹
   
   .. code-block:: sh

      defaults write com.apple.finder AppleShowAllFiles -boolean true ; killall Finder

#. 不显示隐藏文件和文件夹
   
   .. code-block:: sh

      defaults write com.apple.finder AppleShowAllFiles -boolean false; killall Finder

#. 更改文件的显示属性
   
   .. code-block:: sh

      chflags hidden filename
      chflags nohidden filename
      e.g. sudo chflags nohidden /Applications/Parallels\ Desktop.app

#. Itunes下載的 app 目錄

   Location:: 

      /Users/cherry/Music/iTunes/iTunes Media/Mobile Applications/

#. 编辑环境变量

   .. code-block:: sh
   
      vi .bash_profile # 打开.bash_profile添加待编辑的环境变量信息,保存
      source .bash_profile # 生效

   .. image:: images/edit_enviroment.png

