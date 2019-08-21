***************
CPP thread note
***************

.. method:: static unsigned int hardware_concurrency() noexcept

    Returns the number of concurrent threads supported by the implementation. 
    The value should be considered only a hint.

.. method:: bool joinable() const noexcept

    Checks if the thread object identifies an active thread of execution. 
    Specifically, returns true if ``get_id() != std::thread::id()``. 
    So a default constructed thread is not joinable.

    A thread that has finished executing code, but has not yet been joined 
    is still considered an active thread of execution and is therefore joinable.
 
.. method:: void join()

    Blocks the current thread until the thread identified by ``*this`` finishes its execution.
    The completion of the thread identified by ``*this`` synchronizes with the corresponding 
    successful return from ``join()``.

    No synchronization is performed on ``*this`` itself (??). Concurrently calling ``join()`` 
    on the same ``std::thread`` object from multiple threads constitutes a data race that results 
    in undefined behavior.   

.. method:: void detach()

    Separates the thread of execution from the thread object, allowing execution 
    to continue independently. Any allocated resources will be freed once the thread exits.

    After calling detach ``*this`` no longer owns any thread.

.. method:: void swap( thread& other ) noexcept

    Exchanges the underlying handles of two thread objects.

.. method:: std::thread::id get_id() const noexcept
.. method:: std::thread::native_handle  native_handle()

#. Compile program with ``-pthread`` flag

#. Get current thread id
   
   - call ``std::this_thread::get_id()``
   - call ``pthread_self()``

#. Argument passing and thred function return value
   
    The arguments to the thread function are moved or copied by value. 
    If a reference argument needs to be passed to the thread function, 
    it has to be wrapped (e.g. with ``std::ref`` or ``std::cref``).

    Any return value from the function is ignored. If the function throws an exception, 
    ``std::terminate`` is called. In order to pass return values or exceptions back to 
    the calling thread, ``std::promise`` or ``std::async`` may be used.

#. ``thread local`` keyword - thread storage duration
   
    The storage for the object is allocated when the thread begins and deallocated when the thread ends. 
    Each thread has its own instance of the object. Only objects declared ``thread_local`` have this storage duration. 