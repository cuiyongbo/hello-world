************
Linux Daemon
************

#. nginx worker process daemon
   
    Refer to master process's signal handling: ``ngx_init_signals``, ``ngx_signal_handler``.

#. nginx daemonize: ``ngx_int_t ngx_daemon(ngx_log_t *log)``
   
#. nginx architecture: event-driven, asynchronous, non-blocking

#. nginx worker process event cycle: 
   
    ``ngx_start_worker_processes``, ``ngx_spawn_process``, 
    ``ngx_worker_process_cycle``, ``ngx_process_events_and_timers``

    In the last function call, nginx processes two queue, ``ngx_posted_accept_events`` and ``ngx_posted_events``.
    and invokes callback to dispatch events. 

.. [#] `Daemon programming howto <http://www.enderunix.org/docs/eng/daemon.php>`_
.. [#] `Daemon example <https://github.com/jirihnidek/daemon/blob/master/src/daemon.c>`_
.. [#] `Linux to create a daemon <https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux>`_
.. [#] `why fork twice <https://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon>`_
.. [#] `Nginx architecture <https://www.ashnik.com/nginx-architecture-an-insight-part-1/>`_
.. [#] `Nginx source code analysis <https://github.com/suraj-bk/nginx>`_


