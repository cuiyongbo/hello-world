SVN Note 01
===========

#. Check top n commits

    .. code-block:: none

        $ svn log -l 100 | grep thomas
        r669891 | thomas01 | 2021-06-09 20:19:26 +0800 (Wed, 09 Jun 2021) | 1 line
        r668290 | thomas01 | 2021-06-09 13:33:35 +0800 (Wed, 09 Jun 2021) | 1 line

#. View file changes between current TIP and a specific commit: ``svn diff -r r610388 path/to/certain_file``