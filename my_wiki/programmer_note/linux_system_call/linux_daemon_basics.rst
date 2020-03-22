************
Linux Daemon
************

.. note::

    Daemon is a terminology involving concepts like process group, session, controlling terminal.
    Refer to *Advanced Programming in Unix Environment, 3rd edition, section 9.4, 9.5, 9.6*
    and :manpage:`intro(2)` for details. and a dedicated example can be found in
    *Unix Network Programming, volume 1, 3rd edition, section 13.4*.

.. note::

    There is also a library function called ``daemon()``, which detach program from the controlling
    terminal and run in the background as a system daemon. But note that The GNU C library implementation
    of this function was taken from BSD, and does not employ the **double-fork technique (i.e., fork(2), setsid(2), fork(2))**
    that is necessary to ensure that the resulting daemon process is not a session leader.
    Instead, the resulting daemon is a session leader. On systems that follow System V semantics (e.g., Linux),
    this means that if the daemon opens a terminal that is not already a controlling terminal for another session,
    then that terminal will inadvertently become the controlling terminal for the daemon.

#. nginx daemon: ``ngx_int_t ngx_daemon(ngx_log_t *log);``
#. memcached daemon: ``extern int daemonize(int nochdir, int noclose);``

.. rubric:: Footnotes

.. [#] `Daemon programming howto <http://www.enderunix.org/docs/eng/daemon.php>`_
.. [#] `Daemon example <https://github.com/jirihnidek/daemon/blob/master/src/daemon.c>`_
.. [#] `Linux to create a daemon <https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux>`_
.. [#] `why fork twice <https://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon>`_
