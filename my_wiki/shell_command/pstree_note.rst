pstree note
===========

**NAME**: pstree - display a tree of processes

**DESCRIPTION**

    pstree  shows  running  processes  as  a  tree.  The tree is rooted at either pid or init if pid is omitted.  
    If a user name is specified, all process trees rooted at processes owned by that user are shown.

    pstree visually merges identical branches by putting them in square brackets and prefixing them with 
    the repetition count, e.g.

    .. code-block:: none
    
        init-+-getty
            |-getty
            |-getty
            ‘-getty

    becomes: ``init---4*[getty]``

    Child threads of a process are found under the parent process and are shown with the process name in curly braces, 
    e.g. ``icecast2---13*[{icecast2}]``
