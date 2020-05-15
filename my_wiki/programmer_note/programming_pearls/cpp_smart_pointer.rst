*************
Smart Pointer
*************

A smart pointer is an object encapsulating a dumb pointer
by overloading the ``->`` and ``*`` operators.

-- Scott Meyers *Effective C++*

.. code-block:: cpp

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

    class shared_ptr
    {
        // ...
        _Ty *get() const _NOEXCEPT
        {   // return pointer to resource
            return (this->_Get());
        }

        typename add_reference<_Ty>::type operator*() const _NOEXCEPT
        {   // return reference to resource
            return (*this->_Get());
        }

        _Ty *operator->() const _NOEXCEPT
        {   // return pointer to resource
            return (this->_Get());
        }
    };

    class shared_ptr
    {
        // ...
        typename add_reference<_Ty>::type operator*() const
        {   // return reference to object
            return (*this->_Myptr);
        }

        pointer operator->() const _NOEXCEPT
        {   // return pointer to class object
            return (_STD pointer_traits<pointer>::pointer_to(**this));
        }

        pointer get() const _NOEXCEPT
        {   // return pointer to object
            return (this->_Myptr);
        }
    };

