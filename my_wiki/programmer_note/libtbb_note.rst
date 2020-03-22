***********
libtbb note
***********

:abbr:`TBB(Thread Building Block)` is a library that supports scalable parallel programming using standard ISO C++ code.
It does not require special languages or compilers. It is designed to promote scalable data parallel programming.
Additionally, it fully supports **nested parallelism**, so you can build larger parallel components from smaller
parallel components. To use the library, you specify tasks, not threads, and **let the library map tasks onto threads**
in an efficient manner.

Many of the library interfaces employ generic programming, in which interfaces are defined by requirements on types and not specific types.
The C++ :abbr:`STL (Standard Template Library)` is an example of generic programming. Generic programming enables TBB to be flexible yet efficient.
The generic interfaces enable you to customize components to your specific needs.

The net result is that TBB enables you to specify parallelism far more conveniently than using raw threads, and at the same time can improve performance.


.. toctree::

    libtbb/libtbb_parallel_for_note
    libtbb/libtbb_faq


.. rubric:: Footnotes

.. [#] `libtbb repository <https://github.com/oneapi-src/oneTBB.git>`_
.. [#] `libtbb documentation <https://software.intel.com/en-us/tbb-user-guide#tutorial_title>`_

