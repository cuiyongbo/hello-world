********
VIM Note
********

#. VI v.s. VIM

    Pronounced (vee-aye), vi stands for **visual instrument.** It is a widely-used default text editor
    for Unix-based systems and is shipped with virtually all versions of Unix. It exclusively uses
    the keyboard and provides a very efficient interface for editing programs and scripts.

    The name Vim is an acronym for **Vi IMproved** because Vim is an extended version of the vi editor,
    with many additional features designed to be helpful in editing program source code. Originally,
    the acronym stood for **Vi IMitation,** but that was changed with the release of Vim 2.0 in December 1993.

#. Ubuntu to update VIM

    Solution: ``sudo apt-get install vim``.

#. Look for vim tutorial

    Run ``vimtutor`` in your terminal.
    Refer to ``man vimtutor`` for more information.

#. vim configure

    .. code-block:: sh
        :caption: Edit **.vimrc** in your **HOME** directory

        "set tab width
        set tabstop=4

        "indent automatically
        set autoindent

        "replace tab with space
        set expandtab

        " do not replace tab with space
        set noexpandtab

        "mark syntax with different colors
        syntax on

        " enable / disable highlighten search result
        "set hlsearch / nohlsearch

        "show line No
        set number

        "hide line No
        "set nonumber

        "case-insensitive when searching
        "set ic

        "case-sensitive when searching
        set noic

        "show status infomation
        set ruler

        "enable / disable auto wrap when searching
        set wrapscan
        set nowrapscan

        set smartindent
        set autoindent

#. vim shortcuts

    .. code-block:: none

        Search and find - Shift + # (vim)
        Show Current Line in bottom - Ctrl + G
        Completion - Ctrl + N / P
        Jump to line n - n, gg
        Jump to the begin - gg
        Jump to the end - Shift + G
        Jump to the begin of current line - Shift + ^
        Jump to the end of current line - Shift + $
        x 删除光标下的字符 ("dl" 的缩写)
        X 删除光标前的字符 ("dh" 的缩写)
        D 从当前位置删除到行尾 ("d$" 的缩写)
        dw 从当前位置删除到下一个单词开头
        db 从当前位置删除到前一个单词的开头
        diw 删除光标上的单词 (不包括空白字符)
        daw 删除光标上的单词 (包括空白字符)
        dG 删除到文件末
        dgg 删除到文件首

#. vim search

    * In Normal mode type the  ``/``  character.

    * Now type 'errroor' <ENTER>.  This is the word you want to search for.

    * To search for the same phrase again, simply type ``n``.
      To search for the same phrase in the opposite direction, type ``N``.

    * To search for a phrase in the backward direction, use ``?`` instead of ``/``.

    * To go back to where you came from press ``CTRL-O``. Repeat to go back further.
      ``CTRL-I`` goes forward.

    **NOTE:** When the search reaches the end of the file it will continue
    at the start, unless the 'wrapscan' option has been reset.

    .. code-block:: sh

        /hello\c # case-insensitive search
        /hello\C # case-sensitive search

#. vim replacement

    In command mode, type, For example, ``:%s/old-pattern/new-pattern/g``.

#. vim to replace only whole-word matches

    In command mode, run ``:%s/\<old-word\>/new-word/g``.

    .. code-block:: sh

        :%s/foo/bar/gci
        # Change each 'foo' (case insensitive due to the i flag) to 'bar'; ask for confirmation.
        # This may be wanted after using :set noignorecase to make searches case sensitive (the default).

        :%s/foo/bar/gcI
        # Change each 'foo' (case sensitive due to the I flag) to 'bar'; ask for confirmation.

#. vim sustitute - backreference

    .. code-block:: sh

        :%s/\(pipefd\)/g_\1/gc

#. vim to replace existing tab with space

   Type: ``:retab``.

#. shiftwidth and cindent

    A program is much easier to understand when the lines have been properly
    indented.  Vim offers various ways to make this less work.  For C or C style
    programs like Java or C++, set the **cindent** option. Set the **shiftwidth** option
    to the amount of spaces you want for a deeper level. Four spaces will work fine.
    One ":set" command will do it: ``:set cindent shiftwidth=4``.

    With this option enabled, when you type something such as ``if (x)``, the next
    line will automatically be indented an additional level.

    When you type something in curly braces ({}), the text will be indented at the
    start and unindented at the end. The unindenting will happen after typing the
    '}', since Vim can't guess what you are going to type.

#. vim to turn off autoindent

    .. code-block:: sh

        set nosmartindent
        set noautoindent

#. vim to tune color scheme

    .. code-block:: sh

        $ whereis vim
        vim: /usr/bin/vim /usr/bin/vim.basic /usr/bin/vim.tiny /etc/vim /usr/share/vim
        $ cd /usr/share/vim/vimXX/colors/
        $ ls # list system schemes
        README.txt    default.vim  elflord.vim   koehler.vim  pablo.vim      shine.vim  zellner.vim
        blue.vim      delek.vim    evening.vim   morning.vim  peachpuff.vim  slate.vim
        darkblue.vim  desert.vim   industry.vim  murphy.vim   ron.vim        torte.vim

        $ cat README.txt
        README.txt for color scheme files

        These files are used for the ":colorscheme" command.  They appear in the
        Edit/Color Scheme menu in the GUI.
        ...

        # in comand mode, use ":colorscheme" command to find the current scheme
        # ":colorscheme theme_name" to preview colorscheme
        # add ``colorscheme theme`` in ``~/.vimrc`` to set default scheme

#. vim to disable mouse mode: ``set mouse=``

.. rubric:: Footnotes

.. [#] `Vim search and replace <https://vim.fandom.com/wiki/Search_and_replace>`_
.. [#] `vimcolors <https://vimcolors.com/>`_
