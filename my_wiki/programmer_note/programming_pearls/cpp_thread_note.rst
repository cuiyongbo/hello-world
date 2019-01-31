***************
CPP thread note
***************

.. method:: static unsigned int hardware_concurrency() noexcept;

    Returns the number of concurrent threads supported by the implementation. 
    The value should be considered only a hint.

.. method:: bool joinable() const noexcept

    Checks if the thread object identifies an active thread of execution. 
    Specifically, returns true if ``get_id() != std::thread::id()``. 
    So a default constructed thread is not joinable.

    A thread that has finished executing code, but has not yet been joined 
    is still considered an active thread of execution and is therefore joinable.
 
.. method:: void join();

    Blocks the current thread until the thread identified by ``*this`` finishes its execution.
    The completion of the thread identified by ``*this`` synchronizes with the corresponding 
    successful return from ``join()``.

    No synchronization is performed on ``*this`` itself (??). Concurrently calling ``join()`` 
    on the same ``std::thread`` object from multiple threads constitutes a data race that results 
    in undefined behavior.   

.. method:: void detach();

    Separates the thread of execution from the thread object, allowing execution 
    to continue independently. Any allocated resources will be freed once the thread exits.

    After calling detach ``*this`` no longer owns any thread.

.. method:: std::thread::id get_id() const noexcept;

    Returns a value of ``std::thread::id`` identifying the thread associated with ``*this``.

.. method:: std::thread::native_handle  native_handle();

    Returns the implementation defined underlying thread handle.

.. method:: void swap( thread& other ) noexcept;

    Exchanges the underlying handles of two thread objects.
