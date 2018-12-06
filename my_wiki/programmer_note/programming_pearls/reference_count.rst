***************
Reference Count
***************

.. contents::
   :local:

Reference Count - C++
=====================

Reference counting is not an automatic performance winner. Reference counting,
execution speed, and resource conservation form a delicate interaction that
must be evaluated carefully if performance is an important consideration.
Reference counting may help or hurt performance depending on the usage pattern.
The case in favor of reference counting is strengthened by any one of
the following items:

   - The target object is a large resource consumer
     
   - The resource in question is expensive to allocate and free
     
   - A high degree of sharing; the reference count is likely to be
     high due to the use of the assignment operator and copy constructor

   - The creation or destruction of a reference is relatively cheap

If you reverse these items, you start leaning towards skipping reference counting
in favor of the plain uncounted object.


Reference Count - JANSSON
=========================

Reference Count
---------------

The reference count is used to track whether a value is still in use
or not. When a value is created, it's reference count is set to 1. If
a reference to a value is kept (e.g. a value is stored somewhere for
later use), its reference count is incremented, and when the value is
no longer needed, the reference count is decremented. When the reference
count drops to zero, there are no references left, and the value can be destroyed.

.. function:: json_t *json_incref(json_t *json)

   Increment the reference count of *json* if it's not *NULL*.
   Returns *json*.

.. function:: void json_decref(json_t *json)

   Decrement the reference count of *json*. As soon as a call to
   :func:`json_decref()` drops the reference count to zero, the value
   is destroyed and it can no longer be used.

Functions creating new JSON values set the reference count to 1. These
functions are said to return a **new reference**. Other functions
returning (existing) JSON values do not normally increase the
reference count. These functions are said to return a **borrowed
reference**. So, if the user will hold a reference to a value returned
as a borrowed reference, he must call :func:`json_incref`. As soon as
the value is no longer needed, :func:`json_decref` should be called
to release the reference.

Normally, all functions accepting a JSON value as an argument will
manage the reference, i.e. increase and decrease the reference count
as needed. However, some functions **steal** the reference, i.e. they
have the same effect as if the user called :func:`json_decref()` on
the argument right after calling the function. These functions are
suffixed with ``_new`` or have ``_new_`` somewhere in their name.

For example, the following code creates a new JSON array and appends
an integer to it::

  json_t* array = json_array();
  json_t* integer = json_integer(42);
  json_array_append(array, integer);
  json_decref(integer);

Note how the caller has to release the reference to the integer value
by calling :func:`json_decref()`. By using a reference stealing
function :func:`json_array_append_new()` instead of
:func:`json_array_append()`, the code becomes much simpler::

  json_t *array = json_array();
  json_array_append_new(array, json_integer(42));

In this case, the user doesn't have to explicitly release the
reference to the integer value, as :func:`json_array_append_new()`
steals the reference when appending the value to the array.


Circular References
-------------------

A circular reference is created when an object or an array is,
directly or indirectly, inserted inside itself. The direct case is
simple::

  json_t* obj = json_object();
  json_object_set(obj, "foo", obj);

Jansson will refuse to do this, and :func:`json_object_set()` (and
all the other such functions for objects and arrays) will return with
an error status. The indirect case is the dangerous one::

  json_t* arr1 = json_array();
  json_t* arr2 = json_array();
  json_array_append(arr1, arr2);
  json_array_append(arr2, arr1);

In this example, the array ``arr2`` is contained in the array
``arr1``, and vice versa. Jansson cannot check for this kind of
indirect circular references without a performance hit, so it's up to
the user to avoid them.

If a circular reference is created, the memory consumed by the values
cannot be freed by :func:`json_decref()`. The reference counts never
drops to zero because the values are keeping the references to each
other. Moreover, trying to encode the values with any of the encoding
functions will fail. The encoder detects circular references and
returns an error status.


Reference count - MSVC implementation
=====================================

.. code-block:: cpp

   class _Ref_count_base
   { // common code for reference counting
   private:
     virtual void _Destroy() = 0;
     virtual void _Delete_this() = 0;
   
   private:
     _Atomic_counter_t _Uses;
     _Atomic_counter_t _Weaks;
   
   protected:
     _Ref_count_base()
       { // construct
       _Init_atomic_counter(_Uses, 1);
       _Init_atomic_counter(_Weaks, 1);
       }
   
   public:
     virtual ~_Ref_count_base() _NOEXCEPT
       { // ensure that derived classes can be destroyed properly
       }
   
     bool _Incref_nz()
       { // increment use count if not zero, return true if successful
       for (; ; )
         { // loop until state is known
         _Atomic_integral_t _Count =
           _Load_atomic_counter(_Uses);
   
         if (_Count == 0)
           return (false);
   
         if (_Compare_increment_atomic_counter(_Uses, _Count))
           return (true);
         }
       }
   
     unsigned int _Get_uses() const
       { // return use count
       return (_Get_atomic_count(_Uses));
       }
   
     void _Incref()
       { // increment use count
       _MT_INCR(_Mtx, _Uses);
       }
   
     void _Incwref()
       { // increment weak reference count
       _MT_INCR(_Mtx, _Weaks);
       }
   
     void _Decref()
       { // decrement use count
       if (_MT_DECR(_Mtx, _Uses) == 0)
         { // destroy managed resource, decrement weak reference count
         _Destroy();
         _Decwref();
         }
       }
   
     void _Decwref()
       { // decrement weak reference count
       if (_MT_DECR(_Mtx, _Weaks) == 0)
         _Delete_this();
       }
   
     long _Use_count() const
       { // return use count
       return (_Get_uses());
       }
   
     bool _Expired() const
       { // return true if _Uses == 0
       return (_Get_uses() == 0);
       }
   
     virtual void *_Get_deleter(const _XSTD2 type_info&) const
       { // return address of deleter object
       return (0);
       }
   };

.. code-block:: cpp

   template<class _Ty>
     class _Ref_count
     : public _Ref_count_base
     { // handle reference counting for object without deleter
   public:
     _Ref_count(_Ty *_Px)
       : _Ref_count_base(), _Ptr(_Px)
       { // construct
       }
   
   private:
     virtual void _Destroy()
       { // destroy managed resource
       delete _Ptr;
       }
   
     virtual void _Delete_this()
       { // destroy self
       delete this;
       }
   
     _Ty * _Ptr;
     };

.. code-block:: cpp

   template<class _Ty,
     class _Dx>
     class _Ref_count_del
     : public _Ref_count_base
     { // handle reference counting for object with deleter
   public:
     _Ref_count_del(_Ty *_Px, _Dx _Dt)
       : _Ref_count_base(), _Ptr(_Px), _Dtor(_Dt)
       { // construct
       }
   
     virtual void *_Get_deleter(const _XSTD2 type_info& _Typeid) const
       { // return address of deleter object
       return ((void *)(_Typeid == typeid(_Dx) ? &_Dtor : 0));
       }
   
   private:
     virtual void _Destroy()
       { // destroy managed resource
       _Dtor(_Ptr);
       }
   
     virtual void _Delete_this()
       { // destroy self
       delete this;
       }
   
     _Ty * _Ptr;
     _Dx _Dtor;  // the stored destructor for the controlled object
     };

.. code-block:: cpp

   template<class _Ty,
     class _Dx,
     class _Alloc>
     class _Ref_count_del_alloc
     : public _Ref_count_base
     { // handle reference counting for object with deleter and allocator
   public:
     typedef _Ref_count_del_alloc<_Ty, _Dx, _Alloc> _Myty;
     typedef typename _Alloc::template rebind<_Myty>::other _Myalty;
   
     _Ref_count_del_alloc(_Ty *_Px, _Dx _Dt, _Myalty _Al)
       : _Ref_count_base(), _Ptr(_Px), _Dtor(_Dt), _Myal(_Al)
       { // construct
       }
   
     virtual void *_Get_deleter(const _XSTD2 type_info& _Typeid) const
       { // return address of deleter object
       return ((void *)(_Typeid == typeid(_Dx) ? &_Dtor : 0));
       }
   
   private:
     virtual void _Destroy()
       { // destroy managed resource
       _Dtor(_Ptr);
       }
   
     virtual void _Delete_this()
       { // destroy self
       _Myalty _Al = _Myal;
       _Al.destroy(this);
       _Al.deallocate(this, 1);
       }
   
     _Ty * _Ptr;
     _Dx _Dtor;  // the stored destructor for the controlled object
     _Myalty _Myal;  // the stored allocator for this
     };
