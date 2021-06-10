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

#. Access specifiers and pure virtual function

    Access specifiers apply in the same way as they would to any other name during name lookup.
    The fact that the function is virtual does not matter at all.

    If name lookup determines a viable function to be a virtual function, the access specifier of the
    virtual function is checked in the scope of **the static type of the object expression** used to
    name the function. At run time, the actual function to be called could be defined in the derived class
    with a completely different access specifier. This is because 'access specifiers' are a compile time phenomonon.

#. GCC branch predicate macro

    One of the most frequently used optimization techniques in the linux kernel is ``__builtin_expect``.
    when working with condition code(if-esle statements), we often know which branch is true or not. If
    compiler knows this information in advance, it can generate most optimized code.

    .. code-block:: c

        #define likely(x)      __builtin_expect(!!(x), 1)
        #define unlikely(x)    __builtin_expect(!!(x), 0)  

    .. warning::

        But don’t use “likely()” and “unlikely()” macros blindly. If prediction is correct, 
        it means there is 0 cycle of jump instruction, but if prediction is wrong, then it 
        will take several cycles, because processor needs to flush it’s pipeline which is worse 
        than no prediction.

    Accessing memory is the slowest CPU operation as compared to other CPU operations. 
    To avoid this limitation, CPU uses “CPU caches” e.g L1-cache, L2-cache etc. The idea 
    behind cache is, copy some part of memory into CPU itself. We can access cache memory
    much faster than any other memory. But the problem is, limited size of “cache memory”, 
    we can’t copy entire memory into cache. So, the CPU has to guess which memory is going
    to be used in the near future and load that memory into the CPU cache and above macros 
    are hint to load memory into the CPU cache.