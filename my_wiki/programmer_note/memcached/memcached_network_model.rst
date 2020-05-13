Memcached Network Model
=======================

Framework: multithread I/O, event loop based on libevent.

Main thread is responsible for listening incoming connections,
and dispatching connections to worker threads using round robin.
and each worker runs a event loop, in which reads, writes are performed
on incoming connections.

#. Main thread calling hierarchy

    .. code-block:: c

        /* enter the event loop */
        while (!stop_main_loop) {
            if (event_base_loop(main_base, EVLOOP_ONCE) != 0) {
                retval = EXIT_FAILURE;
                break;
            }
        }

    .. code-block:: none

        main, server_sockets, server_socket (socket, bind, listen, et cetera)
            conn_new (conn_listening ONLY, register callback for listening socket, and add it to main_base)
                event_handler (callback for listening socket)
                    driver_machine (event processor)
                        dispatch_conn_new (dispatch incoming connections to workers using round robine)
                            write(thread->notify_send_fd) (notify worker)

#. Worker thread calling hierarchy

    .. code-block:: none

        memcached_thread_init(settings.num_threads);
            setup_thread(create pipe to communicate with main thread)
                event_set(thread->notify_receive_fd, thread_libevent_process);
                    thread_libevent_process(Processes an incoming "handle a new connection" item. This is called when input arrives on the libevent wakeup pipe.)
                        conn_new(register read, write event handler for a incoming connection)
                            event_set(sfd, event_handler) (register libevent handler)
                                driver_machine (event processor)
                                    read/write
            create_worker(worker_libevent, &threads[i]);
                worker_libevent (main event loop)
