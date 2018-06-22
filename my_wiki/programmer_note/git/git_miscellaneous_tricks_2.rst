************
Git Tricks 2
************

**Good, better, best**

#. Remove unused reference
   
   .. figure:: images/unsupported_reference.png

      Solution: ``git update-ref -d refs/original/refs/heads/master``

#. Remove file/directory from commit history
   
   .. code-block:: sh

      $ git filter-branch -f --index-filter 'git rm -r --ignore-unmatch python-2.7.14-docs-pdf-a4/'
      $ git filter-branch -f --index-filter 'git rm  --cached --ignore-unmatch *.docx'
      $ git filter-branch -f --index-filter 'git rm  --ignore-unmatch "google test frame.docx"'