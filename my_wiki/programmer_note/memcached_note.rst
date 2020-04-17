Memcached Note
==============

memcached is a **distributed memory object caching system**,
generic in nature, but originally intended for use in speeding up dynamic
web applications by alleviating database load.

You can think of it as a **short-term memory** for your applications.

Also note that Memcached on its own is simply a key/value store daemon.
Installing it does not automatically accelerate or cache any of your data:
**Your applications need to be programmed to utilize the service.**

.. toctree::

    memcached/memcached_introduction
    memcached/memcached_design_philosophy
    memcached/memcached_faq


.. rubric:: Footnotes

.. [#] `Memcached repository <https://github.com/memcached/memcached.git>`_
.. [#] `Memcached Wiki repository <https://github.com/memcached/memcached.wiki.git>`_
.. [#] `libmemcached <https://github.com/whupro2017/libmemcached.git>`_
