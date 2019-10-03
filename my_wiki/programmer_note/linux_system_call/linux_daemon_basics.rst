************
Linux Daemon
************

.. note::

    Daemon is a terminology involving concepts like process group, session, controlling terminal.
    Refer to *Advanced Programming in Unix Environment, 3rd edition, section 9.4, 9.5, 9.6*
    and :manpage:`intro(2)` for details. and a dedicated example can be found in
    *Unix Network Programming, volume 1, 3rd edition, section 13.4*.

#. nginx daemonize: ``ngx_int_t ngx_daemon(ngx_log_t *log)``


.. rubric:: Footnotes

.. [#] `Daemon programming howto <http://www.enderunix.org/docs/eng/daemon.php>`_
.. [#] `Daemon example <https://github.com/jirihnidek/daemon/blob/master/src/daemon.c>`_
.. [#] `Linux to create a daemon <https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux>`_
.. [#] `why fork twice <https://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon>`_
