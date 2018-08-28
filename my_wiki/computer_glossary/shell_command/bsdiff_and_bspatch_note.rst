***************************
Binary diff and patch tools
***************************

#. bsdiff — generate a patch between two binary files

   Usage: ``bsdiff oldfile newfile patchfile``

   bsdiff compares *oldfile* to *newfile* and writes to *patchfile*,
   a binary patch suitable for use by **bspatch(1).**  

   bsdiff uses memory equal to 17 times the size of *oldfile,* 
   and requires an absolute minimum working set size of 8 times 
   the size of *oldfile.*


#. bspatch — apply a patch built with **bsdiff(1)**

   Usage: ``bspatch oldfile newfile patchfile``

   bspatch generates *newfile* from *oldfile* and *patchfile* 
   where patchfile is a binary patch built by **bsdiff(1).**

   bspatch uses memory equal to the size of *oldfile* plus the size of *newfile,* 
   but can tolerate a very small working set without a dramatic loss of performance.
