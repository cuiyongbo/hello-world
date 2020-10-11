*************
Smart Pointer
*************

A smart pointer, which belongs to :abbr:`RAII (Resource Acquisition Is Initialized)` technology,
is an object encapsulating a dumb pointer by overloading the ``->`` and ``*`` operators.

.. note::

    - ``std::auto_ptr`` is deprecated since C++11, since copy operation will make rvalue point to null
    - 为防止资源泄漏，请使用 RAII 对象，它们在构造函数中获取资源，并在析构函数中是释放资源
    - 两个建议使用的 RAII classes 分别是 ``std::unique_ptr`` 和 ``std::shared_ptr``。前者不允许 copy 动作，后者允许 copy 动作。

.. code-block:: cpp

    template <typename T>
    class RCPtr {
    public:
       T* operator->() const { return m_ptr; }
       T& operator*() const { return *m_ptr; }
       // ...

    private:
       T* m_ptr;
    };

    class unique_ptr {
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

        // Disable copy from lvalue.
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;
    };

    class shared_ptr {
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


.. rubric:: Footnotes

.. [#] `C++内存管理 <https://mp.weixin.qq.com/s/YpQekaHi7-0bn76qkQg0uw>`_
