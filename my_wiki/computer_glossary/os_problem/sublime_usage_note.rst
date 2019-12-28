******************
Sublime Text Usage
******************

**Sublime-rst-completion**

#. emphasis: ctrl+alt+i (super+shift+i on Mac)
#. strong emphasis (bold):  ctrl+alt+b (super+shift+b on Mac)
#. literal literal text (inline code): ctrl+alt+k (super+shift+k on Mac)
#. magical table: ctrl+t, enter (Linux or Windows) or super+shift+t, enter (Mac)
#. simple table: ctrl+t, s (Linux or Windows) or super+shift+t, s (Mac)
#. Folding/unfolding: shift + TAB (alt + TAB in Mac) [put the cursor in a completed header]
#. adjust header level: ctrl + + (plus key) and ctrl + - (minus key) (alt + + and alt + -, in Mac)
#. render preview: ctrl + shift + r
#. Folding/unfolding: shift + TAB (alt + TAB in Mac)
#. Navigation: alt+down and alt+up move the cursor position to the closer next or previous header respectively.
   alt+shift+down and alt+shift+up to the same, but only between headers with the same or higher level

**Sublime Text**

#. Hightlighten one word: Ctrl + D
#. Swap lines: Ctrl + Shift + Up/Down (Windows), Ctrl + Command + Up/Down (Mac)
#. Switch Tabs: Option + Command + Letf/Right (Mac)
#. New Window: Shift + Command + N (Mac)
#. Close Window: Shift + Command + W (Mac)
#. Close File: Command + W (Mac)
#. Show/Hide side bar: Ctrl + K + B (Windows), Command + K + B (Mac)

#. Vertical Selection:

    Ctrl + Alt + Up/Down (Windows/Linux)
    Ctrl + Shift + Up/Down (Mac)

    .. note::

        For Windows using Intel graphics cards, there are HotKeys setup that
        cause ``Ctrl + Alt + Up/Down`` to rotate screen, you need to disable
        these HotKeys for this to work on Windows.

        .. image:: images/intel-graphics-options.png

        The hotkeys may not work because the modifier has been assigned to "Mission Control"
        and "Application Windows". To get around this, uncheck the options in "System Preference"
        \- "Keyboad" \- "Shortcuts" \- "Mission Control".

        .. image:: images/Mac-MissionControl-shortcuts-setting.png

#. Open package control: Cmd + Shift + P (mac), Ctrl + Shift + P (windows)
#. Move backward/forward: Ctrl + - / Shift + Ctrl + -
#. Quick open file - Cmd + P / Cmd + T (mac)
#. Preview markdown file: install markdown html preview, then "Ctrl + shift + m"
#. Find in files - Cmd + shift + F (mac)
#. Insert Line After - Cmd + Enter
#. Insert Line Before - Shift + Cmd + Enter (replace Cmd with Ctrl on windows)

**Sublime Text Configure**

.. code-block:: none
    :caption: Hot Configure

    "color_scheme": "Packages/Color Scheme - Default/Solarized (Light).tmTheme",
    "trim_trailing_white_space_on_save": true,
    "ensure_newline_at_eof_on_save": true,
    "font_face": "monaco",
    "disable_tab_abbreviations": true,
    "translate_tabs_to_spaces": true,
    "tab_size": 4,
    "save_on_focus_lost": true,
    "highlight_line": true,
    "word_wrap": "true",
    "fade_fold_buttons": false,
    "bold_folder_labels": true,
    "highlight_modified_tabs": false,
    "default_line_ending": "unix",
    "auto_find_in_selection": true,
    "update_check": false


**Plugin Collection**

#. Pretty Json
#. Sublime-rst-complement
