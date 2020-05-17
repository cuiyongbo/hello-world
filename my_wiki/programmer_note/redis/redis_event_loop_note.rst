Redis Event Loop Note
=====================

.. code-block:: c

    typedef struct aeEventLoop {
       int maxfd;   /* highest file descriptor currently registered */
       int setsize; /* max number of file descriptors tracked */
       long long timeEventNextId;
       time_t lastTime;     /* Used to detect system clock skew */
       aeFileEvent *events; /* Registered events */
       aeFiredEvent *fired; /* Fired events */
       aeTimeEvent *timeEventHead;
       int stop;
       void *apidata; /* This is used for polling API specific data */
       aeBeforeSleepProc *beforesleep;
       aeBeforeSleepProc *aftersleep;
    } aeEventLoop;

    int main(int argc, char** argv)
    {
        // ...
        aeSetBeforeSleepProc(server.el,beforeSleep);
        aeSetAfterSleepProc(server.el,afterSleep);
        aeMain(server.el);
        aeDeleteEventLoop(server.el);
        return 0;
    }

    // the event loop would be single threaded if threaded I/O is disabled
    void aeMain(aeEventLoop *eventLoop) {
       eventLoop->stop = 0;
       while (!eventLoop->stop) {
           if (eventLoop->beforesleep != NULL)
               eventLoop->beforesleep(eventLoop);
           aeProcessEvents(eventLoop, AE_ALL_EVENTS|AE_CALL_AFTER_SLEEP);
       }
    }
