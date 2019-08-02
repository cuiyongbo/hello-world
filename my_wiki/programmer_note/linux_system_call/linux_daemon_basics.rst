************
Linux Daemon
************

#. nginx worker process daemon
   
    Refer to master process's signal handling: ``ngx_init_signals``, ``ngx_signal_handler``.

#. nginx daemonize: ``ngx_int_t ngx_daemon(ngx_log_t *log)``
   
#. nginx architecture: event-driven, asynchronous, non-blocking

#. nginx worker process event cycle - 1
   
    ``ngx_start_worker_processes``, ``ngx_spawn_process``, 
    ``ngx_worker_process_cycle``, ``ngx_process_events_and_timers``

    In the last function call, nginx processes two queue, ``ngx_posted_accept_events`` and ``ngx_posted_events``.
    and invokes callback to dispatch events. 

#. nginx worker process event cycle - select module

    .. code-block:: c

        // ngx_event.c
        void ngx_process_events_and_timers(ngx_cycle_t *cycle)
        {
        
            // add events to event queue
            (void)ngx_process_events(cycle, timer, flags);
        
        
            // drain events in event queue
            ngx_event_process_posted(cycle, &ngx_posted_accept_events);
            ngx_event_process_posted(cycle, &ngx_posted_events);
        }

        // ngx_event.h
        #define ngx_process_events   ngx_event_actions.process_events

        // static ngx_int_t ngx_select_init(ngx_cycle_t *cycle, ngx_msec_t timer)
        ngx_event_actions = ngx_select_module_ctx.actions;

        // ngx_select.c
        static ngx_event_module_t  ngx_select_module_ctx = {
            &select_name,
            NULL,                                  /* create configuration */
            ngx_select_init_conf,                  /* init configuration */
            {
                ngx_select_add_event,              /* add an event */
                ngx_select_del_event,              /* delete an event */
                ngx_select_add_event,              /* enable an event */
                ngx_select_del_event,              /* disable an event */
                NULL,                              /* add an connection */
                NULL,                              /* delete an connection */
                NULL,                              /* trigger a notify */
                ngx_select_process_events,         /* process the events */
                ngx_select_init,                   /* init the events */
                ngx_select_done                    /* done the events */
            }
        };

        static ngx_int_t ngx_select_process_events(ngx_cycle_t *cycle, ngx_msec_t timer, ngx_uint_t flags)
        {
        
            // ...
            ready = select(max_fd + 1, &work_read_fd_set, &work_write_fd_set, NULL, tp);
        
            // ...
            // add event to queue   
            queue = ev->accept ? &ngx_posted_accept_events : &ngx_posted_events;
            ngx_post_event(ev, queue);
        }


.. [#] `Daemon programming howto <http://www.enderunix.org/docs/eng/daemon.php>`_
.. [#] `Daemon example <https://github.com/jirihnidek/daemon/blob/master/src/daemon.c>`_
.. [#] `Linux to create a daemon <https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux>`_
.. [#] `why fork twice <https://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon>`_
.. [#] `Nginx architecture <https://www.ashnik.com/nginx-architecture-an-insight-part-1/>`_
.. [#] `Nginx source code analysis <https://github.com/suraj-bk/nginx>`_
