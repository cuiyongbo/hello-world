**********
nginx conf
**********

#. nginx worker process daemon
   
    Refer to master process's signal handling: ``ngx_init_signals``, ``ngx_signal_handler``.

#. nginx daemonize: ``ngx_int_t ngx_daemon(ngx_log_t *log)``
#. nginx architecture: event-driven, asynchronous, non-blocking

#. nginx worker process event cycle - 1
   
    ``ngx_start_worker_processes``, ``ngx_spawn_process``, 
    ``ngx_worker_process_cycle``, ``ngx_process_events_and_timers``

    In the last function call, nginx processes two queues, ``ngx_posted_accept_events`` and ``ngx_posted_events``.
    and invokes callback to dispatch events. 

#. nginx worker process event cycle - select module

    .. code-block:: c

        static ngx_int_t ngx_event_process_init(ngx_cycle_t *cycle)
        {
            // initialize two event queues
            ngx_queue_init(&ngx_posted_accept_events);
            ngx_queue_init(&ngx_posted_events);
        
            // initialize selected module
            if (module->actions.init(cycle, ngx_timer_resolution) != NGX_OK) {
                /* fatal */
                exit(2);
            }
        }

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

        static ngx_int_t ngx_select_init(ngx_cycle_t *cycle, ngx_msec_t timer)
        {
            // ...
            ngx_event_actions = ngx_select_module_ctx.actions;
            // ...
        }

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
            ready = select(max_fd + 1, &work_read_fd_set, &work_write_fd_set, NULL, tp);
        
            // add event to queue   
            queue = ev->accept ? &ngx_posted_accept_events : &ngx_posted_events;
            ngx_post_event(ev, queue);
        }

#. nginx worker process event cycle - epoll module
   
    .. code-block:: c

        typedef struct {
            ngx_int_t  (*add)(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags);
            ngx_int_t  (*del)(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags);
            ngx_int_t  (*enable)(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags);
            ngx_int_t  (*disable)(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags);
            ngx_int_t  (*add_conn)(ngx_connection_t *c);
            ngx_int_t  (*del_conn)(ngx_connection_t *c, ngx_uint_t flags);
            ngx_int_t  (*notify)(ngx_event_handler_pt handler);
            ngx_int_t  (*process_events)(ngx_cycle_t *cycle, ngx_msec_t timer, ngx_uint_t flags);
            ngx_int_t  (*init)(ngx_cycle_t *cycle, ngx_msec_t timer);
            void       (*done)(ngx_cycle_t *cycle);
        } ngx_event_actions_t;

        typedef struct {
            ngx_str_t              *name;
            void                 *(*create_conf)(ngx_cycle_t *cycle);
            char                 *(*init_conf)(ngx_cycle_t *cycle, void *conf);
            ngx_event_actions_t     actions;
        } ngx_event_module_t;

        static ngx_event_module_t  ngx_epoll_module_ctx = {
             &epoll_name,
             ngx_epoll_create_conf,               /* create configuration */
             ngx_epoll_init_conf,                 /* init configuration */
             {
                 ngx_epoll_add_event,             /* add an event */
                 ngx_epoll_del_event,             /* delete an event */
                 ngx_epoll_add_event,             /* enable an event */
                 ngx_epoll_del_event,             /* disable an event */
                 ngx_epoll_add_connection,        /* add an connection */
                 ngx_epoll_del_connection,        /* delete an connection */
                 ngx_epoll_process_events,        /* process the events */
                 ngx_epoll_init,                  /* init the events */
                 ngx_epoll_done,                  /* done the events */
             }
        };
        
        static ngx_int_t ngx_epoll_init(ngx_cycle_t *cycle, ngx_msec_t timer)
        {
            // ...
            ep = epoll_create(cycle->connection_n / 2);

            // ...       
            ngx_event_actions = ngx_epoll_module_ctx.actions;
        }

        // event process in event cycle
        #define ngx_process_events   ngx_event_actions.process_events
        #define ngx_done_events      ngx_event_actions.done
        #define ngx_add_event        ngx_event_actions.add
        #define ngx_del_event        ngx_event_actions.del
        #define ngx_add_conn         ngx_event_actions.add_conn
        #define ngx_del_conn         ngx_event_actions.del_conn
        #define ngx_notify           ngx_event_actions.notify

        static ngx_int_t ngx_epoll_process_events(ngx_cycle_t *cycle, ngx_msec_t timer, ngx_uint_t flags)
        {
            // ...
            events = epoll_wait(ep, event_list, (int) nevents, timer);

            // ...
            queue = rev->accept ? &ngx_posted_accept_events : &ngx_posted_events;
            ngx_post_event(rev, queue);
        }

.. rubric:: Footnotes

.. [#] `Nginx architecture <https://www.ashnik.com/nginx-architecture-an-insight-part-1/>`_
.. [#] `Nginx source code analysis <https://github.com/suraj-bk/nginx>`_
.. [#] `Inside the nginx <https://www.nginx.com/blog/inside-nginx-how-we-designed-for-performance-scale/>`
