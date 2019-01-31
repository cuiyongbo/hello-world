****************************
Bash Completion Builtin Note
****************************

Three builtin commands are available to manipulate the programmable completion facilities: 
**compgen** to specify how the arguments to a particular command are to be completed, 
and **complete, compopt** to modify the completion as it is happening.

.. code-block:: sh
    :caption: Syntaxes

    compgen [option] [word]

    complete [-abcdefgjksuv] [-o comp-option] [-DEI] [-A action] [-G globpat]
                [-W wordlist] [-F function] [-C command] [-X filterpat]
                [-P prefix] [-S suffix] name [name …]
                complete -pr [-DEI] [name …]

    compopt [-o option] [-DEI] [+o option] [name]


**complete** options::

    -F function
    
    The shell function function is executed in the current shell environment. 
    When it is executed, `$1` is the name of the command whose arguments are 
    being completed, `$2` is the word being completed, and `$3` is the word preceding 
    the word being completed. When it finishes, the possible completions are retrieved 
    from the value of the `COMPREPLY` array variable.