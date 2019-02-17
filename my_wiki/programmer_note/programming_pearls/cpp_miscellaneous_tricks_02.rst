*****************************
C/C++ Miscellaneous Tricks 02
*****************************

#. unnamed namespace
   
    It is often useful to wrap a set of declarations in a namespace simply to protect against 
    the possibility of name clashes. and sometimes we don't even want to bother naming it. 
    In that case, we can simply leave the namespace without a name::

        namespace
        {
            int a;
            void f() {}
        }

    and it is equivalent to::

        namespace someCollection    
        {
            int a;
            void f() {}
        }
        using namespace someCollection;

#. ``sizeof`` operator

    .. code-block:: cpp

        sizeof( type )   
        sizeof expression

    Queries size of the object or type.
    Used when actual size of the object must be known.
    Both versions return a constant of type ``std::size_t``.
    
    ``sizeof`` cannot be used with function types, incomplete types, or bit-field glvalues.
    When applied to a reference type, the result is the size of the referenced type.
    When applied to a class type, the result is the size of an object of that class
    plus any additional padding required to place such object in an array.
    When applied to an empty class type, always returns 1.
    When applied to an expression, ``sizeof`` does not evaluate the expression,
    and even if the expression designates a polymorphic object, the result is the
    size of the static type of the expression.

#. ``alignof`` operator

    ``alignof( type-id )`` Queries alignment requirements of a type. Returns a value of type ``std::size_t``.
   
    Returns the alignment, a value of type ``std::size_t`` in bytes, required for any
    instance of the type indicated by *type-id*, which is either complete type, an
    array type, or a reference type.
   
    If the type is reference type, the operator returns the alignment of referenced type;
    if the type is array type, alignment requirement of the element type is returned.
   
#. ``offsetof`` macro
   
    .. code-block:: cpp

        // offsetof is a macro defined in stddef.h
        #define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE*)0)->MEMBER))

        // MSVC implementation
        #define offsetof(s,m)   (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )

    .. code-block:: c
        :caption: Taken from Jansson

        #define container_of(ptr_, type_, member_)  ((type_ *)((char *)ptr_ - offsetof(type_, member_)))
        #define json_to_object(json_)  container_of(json_, json_object_t, json)

