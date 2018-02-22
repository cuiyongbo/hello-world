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

