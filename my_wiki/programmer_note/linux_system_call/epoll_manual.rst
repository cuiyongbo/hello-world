***************************************
epoll - I/O event notification facility
***************************************

.. code-block:: c
    :caption: epoll interfaces

        #include <sys/epoll.h>

        int epoll_create(int size);
        int epoll_create1(int flags);

        int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

        int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
        int epoll_pwait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout,
                      const sigset_t *sigmask);

        typedef union epoll_data {
            void        *ptr;
            int          fd;
            uint32_t     u32;
            uint64_t     u64;
        } epoll_data_t;

        struct epoll_event {
            uint32_t     events;      /* Epoll events */
            epoll_data_t data;        /* User data variable */
        };


**DESCRIPTION**

    The epoll API performs a similar task to poll(2): monitoring multiple file descriptors to see
    if I/O is possible on any of them. The epoll API can be used either as an **edge-triggered** or a
    **level-triggered** (the default) interface and scales well to large numbers of watched file descriptors. The
    following system calls are provided to create and manage an epoll instance:

        * epoll_create(2) creates an epoll instance and returns a file descriptor referring to that instance.
        *  Interest in particular file descriptors is then registered via epoll_ctl(2).
        *  epoll_wait(2) waits for I/O events, blocking the calling thread if no events are currently available.

    The epoll event distribution interface is able to behave both as ET and as LT.
    The difference between the two mechanisms can be described as follows.
    Suppose that this scenario happens:

        #. The file descriptor that represents the read side of a pipe (rfd) is registered on the epoll instance.
        #. A pipe writer writes 2 kB of data on the write side of the pipe.
        #. A call to epoll_wait(2) is done that will return rfd as a ready file descriptor.
        #. The pipe reader reads 1 kB of data from rfd.
        #. Another call to epoll_wait(2) is done.

    If the rfd file descriptor has been added to the epoll interface using the EPOLLET flag,
    the call to epoll_wait(2) done in step 5 will probably hang despite the available data still
    present in the file input buffer; meanwhile the remote peer might be expecting a response based
    on the data it already sent. The reason for this is that ET mode delivers events only when changes
    occur on the monitored file descriptor. So, in step 5 the caller might end up waiting for some data
    that is already present inside the input buffer.

    In the above example, an event on rfd will be generated because of the write done in 2 and the event
    is consumed in 3. Since the read operation done in 4 does not consume the whole buffer data, the
    call to epoll_wait(2) done in step 5 might block indefinitely.

    An application that employs the EPOLLET flag should use nonblocking file descriptors to avoid having
    a blocking read or write starve a task that is handling multiple file descriptors. The suggested way
    to use epoll as an EPOLLET interface is as follows:

        * with nonblocking file descriptors; and
        * by waiting for an event only after read(2) or write(2) return EAGAIN.

    By contrast, when used as a LT interface, epoll is simply a faster poll(2),
    and can be used wherever the latter is used since it shares the same semantics.

#. What happens if you register the same file descriptor on an epoll instance twice?

    ou will probably get EEXIST. However, it is possible to add a duplicate (dup(2), dup2(2),
    fcntl(2) F_DUPFD) descriptor to the same epoll instance. This can be a useful technique for
    filtering events, if the duplicate file descriptors are registered with different events masks.

#. Can two epoll instances wait for the same file descriptor? If so, are events reported to both epoll file descriptors?

    Yes, and events would be reported to both. However, careful programming may be needed to do this correctly.

#. Is the epoll file descriptor itself poll/epoll/selectable?

    Yes.  If an epoll file descriptor has events waiting, then it will indicate as being readable.

#. What happens if one attempts to put an epoll file descriptor into its own file descriptor set?

    The epoll_ctl(2) call will fail (EINVAL). However, you can add an epoll file descriptor
    inside another epoll file descriptor set.

#. Can I send an epoll file descriptor over a UNIX domain socket to another process?

    Yes, but it does not make sense to do this, since the receiving process would not
    have copies of the file descriptors in the epoll set.

#. Will closing a file descriptor cause it to be removed from all epoll sets automatically?

    Yes, but be aware of the following point. A file descriptor is a reference to an open file
    description (see open(2)).  Whenever a descriptor is duplicated via dup(2),  dup2(2),  fcntl(2)
    F_DUPFD,  or fork(2), a new file descriptor referring to the same open file description is created.
    An open file description continues to exist until all file descriptors referring to it have been closed.
    A file descriptor is removed from an epoll set only after all the file descriptors referring to the
    underlying open file description have been closed (or before if the descriptor is explicitly removed using
    epoll_ctl(2) EPOLL_CTL_DEL). This means that even after a file descriptor that is part of an epoll set has
    been closed, events may be reported for that file descriptor if other file descriptors referring to the same
    underlying file description remain open.

#. If more than one event occurs between epoll_wait(2) calls, are they combined or reported separately?

    They will be combined.

#. Do I need to continuously read/write a file descriptor until EAGAIN when using the EPOLLET flag ?

    Receiving an event from epoll_wait(2) should suggest to you that such file descriptor is ready
    for the requested I/O operation. You must consider it ready until the next (nonblocking)
    read/write yields EAGAIN. When and how you will use the file descriptor is entirely up to you.

    For packet/token-oriented files (e.g., datagram socket, terminal in canonical mode), the only way
    to detect the end of the read/write I/O space is to continue to read/write until EAGAIN.

    For stream-oriented files (e.g., pipe, FIFO, stream socket), the condition that the read/write I/O space
    is exhausted can also be detected by checking the amount of data read from / written to the target file
    descriptor. For example, if you call read(2) by asking to read a certain amount of data and read(2) returns
    a lower number of bytes, you can be sure of having exhausted the read I/O space for the file descriptor.
    The same is true when writing using write(2). Avoid this latter technique if you cannot guarantee that the
    monitored file descriptor always refers to a stream-oriented file.
