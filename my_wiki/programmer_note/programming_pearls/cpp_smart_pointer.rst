*************
Smart Pointer
*************

A smart pointer is an object encapsulating a dumb pointer
by overloading the ``->`` and ``*`` operators.

-- Scott Meyers *Effective C++*

.. code-block:: c++
    :caption: Example take from *Effective C++*

    template <typename T>
    class RCPtr
    {
    public:
       T* operator->() const { return m_ptr; }
       T& operator*() const { return *m_ptr; }
       // ...

    private:
       T* m_ptr;
    };

.. code-block:: sh
    :caption: std::auto_ptr implementation taken from Ubuntu

    /**
     *  @brief  A simple smart pointer providing strict ownership semantics.
     *
     *  The Standard says:
     *  <pre>
     *  An @c auto_ptr owns the object it holds a pointer to.  Copying
     *  an @c auto_ptr copies the pointer and transfers ownership to the
     *  destination.  If more than one @c auto_ptr owns the same object
     *  at the same time the behavior of the program is undefined.
     *
     *  The uses of @c auto_ptr include providing temporary
     *  exception-safety for dynamically allocated memory, passing
     *  ownership of dynamically allocated memory to a function, and
     *  returning dynamically allocated memory from a function.  @c
     *  auto_ptr does not meet the CopyConstructible and Assignable
     *  requirements for Standard Library <a
     *  href="tables.html#65">container</a> elements and thus
     *  instantiating a Standard Library container with an @c auto_ptr
     *  results in undefined behavior.
     *  </pre>
     *  Quoted from [20.4.5]/3.
     *
     *  Good examples of what can and cannot be done with auto_ptr can
     *  be found in the libstdc++ testsuite.
     */
    template<typename _Tp>
    class auto_ptr
    {
    private:
        _Tp* _M_ptr;

    public:
        typedef _Tp element_type;

        explicit auto_ptr(element_type* __p = 0) throw() : _M_ptr(__p) { }

        auto_ptr(auto_ptr& __a) throw() : _M_ptr(__a.release()) { }

        template<typename _Tp1>
        auto_ptr(auto_ptr<_Tp1>& __a) throw() : _M_ptr(__a.release()) { }

        auto_ptr& operator=(auto_ptr& __a) throw()
        {
            reset(__a.release());
            return *this;
        }

        template<typename _Tp1>
        auto_ptr& operator=(auto_ptr<_Tp1>& __a) throw()
        {
            reset(__a.release());
            return *this;
        }

        ~auto_ptr() { delete _M_ptr; }

        /**
         *  @brief  Smart pointer dereferencing.
         *
         *  If this %auto_ptr no longer owns anything, then this
         *  operation will crash.  (For a smart pointer, <em>no longer owns
         *  anything</em> is the same as being a null pointer, and you know
         *  what happens when you dereference one of those...)
         */
        element_type& operator*() const throw()
        {
              _GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
              return *_M_ptr;
        }

        /**
         *  @brief  Smart pointer dereferencing.
         *
         *  This returns the pointer itself, which the language then will
         *  automatically cause to be dereferenced.
         */
        element_type* operator->() const throw()
        {
            _GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
            return _M_ptr;
        }

        element_type* get() const throw() { return _M_ptr; }

        element_type* release() throw()
        {
            element_type* __tmp = _M_ptr;
            _M_ptr = 0;
            return __tmp;
        }

        void reset(element_type* __p = 0) throw()
        {
            if (__p != _M_ptr)
            {
                delete _M_ptr;
                _M_ptr = __p;
            }
        }
    // ...
    };
