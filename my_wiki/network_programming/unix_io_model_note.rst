********************
Linux I/O Model Note
********************

.. note:: Refers to *Unix Network Programming, volume 1, chapter 6* for further information.

In general, there are 5 kinds of I/O models:

    - Blocking I/O Model
    - Non-blocking I/O Model (often involving polling)
    - I/O Multiplexing Model (like select and poll) (similar to multithreading with blocking I/O)
    - Signal-driven I/O Model (involving signal handling with SIGIO)
    - Asynchronous I/O Model (event queue)

The main difference between asynchronous I/O model and the signal-driven I/O model is
that with signal-driven I/O, the kernel tells us when an I/O operation can be initiated,
but with asynchronous I/O, the kernel tells us when an I/O operation is complete, that is,
data has been copied from kernel buffer to application buffer.

POSIX defines synchronous I/O and asynchronous I/O as follows:

    * A synchronous I/O operation causes the requesting process to be blocked until that I/O operation completes.

    * An asynchronous I/O operation does not cause the requesting process to be blocked.

According to these definitions, the first four models are all synchronous,
while asynchronous I/O model match the asynchronous I/O definition.
