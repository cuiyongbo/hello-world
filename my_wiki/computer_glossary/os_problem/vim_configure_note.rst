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

        "set tab width, there is some problem with makefile
        set tabstop=4
    
        "indent automatically
        set autoindent
    
        "replace tab with space
        set expandtab
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


#. vim replacement
   
   In command mode, type, For example, ``%s/old-pattern/new-pattern/g``. 