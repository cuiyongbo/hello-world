pstree note
===========

**NAME**: pstree - display a tree of processes

**SYNOPSIS**: `pstree [-a] [-c] [-h|-Hpid] [-l] [-n] [-p] [-u] [-Z] [-A|-G|-U] [pid|user]`

**DESCRIPTION**

    pstree  shows  running  processes  as  a  tree.  The tree is rooted at either pid or init if pid is omitted.  
    If a user name is specified, all process trees rooted at processes owned by that user are shown.

    pstree visually merges identical branches by putting them in square brackets and prefixing them with 
    the repetition count, e.g. ::

        init-+-getty
            |-getty
            |-getty
            ‘-getty

    becomes: ``init---4*[getty]``

    Child threads of a process are found under the parent process and are shown with the process name in curly braces, 
    e.g. ``icecast2---13*[{icecast2}]``

**Hot Options**

.. code-block:: none

    -a     Show command line arguments. 

    -c     Disable compaction of identical subtrees.  By default, subtrees are compacted whenever possible.

    -g     Show PGIDs.  Process Group IDs are shown as decimal numbers in parentheses after each process name.  -g implicitly disables compaction.

    -p     Show PIDs.  PIDs are shown as decimal numbers in parentheses after each process name.  -p implicitly disables compaction.

    -s     Show parent processes of the specified process.
    