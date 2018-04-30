:orphan:

***************
Reference Count
***************

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

