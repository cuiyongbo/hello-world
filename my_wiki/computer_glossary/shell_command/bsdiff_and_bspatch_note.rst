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

#. Complexity
   
   bsdiff is quite memory-hungry. It requires **max(17*n, 9*n+m) + O(1)** bytes of memory, 
   where n is the size of the old file and m is the size of the new file. bspatch requires 
   **n+m+O(1)** bytes.

   bsdiff runs in :math:`O((n+m) \log n)` time; bspatch runs in **O(n+m)** time;
   Providing that ``off_t`` is defined properly, bsdiff and bspatch support files 
   of up to :math:`2^{61}-1` bytes.

   See `Naïve Differences of Executable Code <http://www.daemonology.net/papers/bsdiff.pdf>`_ 
   for further information.

#. qsufsort
   
   - `paper <http://www.larsson.dogma.net/ssrev-tr.pdf>`_
   - `code  <http://www.larsson.dogma.net/qsufsort.c>`_
   - `Go example <https://golang.org/src/index/suffixarray/qsufsort.go>`_