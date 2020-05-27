Protocol Buffers Grammer Note
=============================

.. code-block:: proto

    syntax = "proto3";
    package tutorial;

    import "google/protobuf/timestamp.proto"

    message Person
    {
        string name = 1;
        int32 id = 2;
        string email = 3;

        enum PhoneType
        {
            MOBILE = 0;
            HOME = 1;
        }

        message PhoneNumber
        {
            string number = 1;
            PhoneType type = 2;
        }

        repeated PhoneNumber phones = 4;
        google.protobuf.Timestamp last_updated = 5;
    }

#. Scarlar type

    +----------+--------+----------+
    | PB       | C++    | Python   |
    +==========+========+==========+
    | double   | double | float    |
    | float    | float  | float    |
    +----------+--------+----------+
    | int32    | int32  | int      |
    | int64    | int64  | int      |
    | uint32   | uint32 | int      |
    | uint64   | uint64 | int      |
    +----------+--------+----------+
    | sint32   | int32  | int      |
    | sint64   | int64  | int      |
    +----------+--------+----------+
    | fixed32  | uint32 | int      |
    | fixed64  | uint64 | int      |
    | sfixed32 | int32  | int      |
    | sfixed64 | int64  | int      |
    +----------+--------+----------+
    | bool     | bool   | bool     |
    +----------+--------+----------+
    | string   | string | str(py3) |
    | bytes    | string | bytes    |
    +----------+--------+----------+

#. Field Numbers

    Each field in the message definition has a unique number.
    These numbers are used to identify your fields in the message
    binary format, and **should not be changed once your message type is in use.**
    Note that field numbers in the range 1 through 15 take one byte to encode,
    including the field number and the field's type. Field numbers in the
    range 16 through 2047 take two bytes. So you should reserve the field
    numbers 1 through 15 for very frequently occurring message elements.
    Remember to leave some room for frequently occurring elements that
    might be added in the future.

    The smallest field number you can specify is 1, and the largest is :math:`2^{29} - 1`.
    You also cannot use the numbers 19000 through 19999 (``FieldDescriptor::kFirstReservedNumber`` through ``FieldDescriptor::kLastReservedNumber``), as they are reserved for the PB implementation.

#. Field Rules

    - required (proto2 only)
    - optional (proto2 only)
    - repeated (may repeat zero or more times)

    .. note::

        In proto3, ``repeated`` fields of scalar numeric types use ``packed`` encoding by default.

#. Comments: support C/C++ style ``//`` and ``/*...*/`` syntax.

#. Reserved Fields

    .. code-block:: proto

        message Foo
        {
            reserved 2,15, 9 to 11;
            reserved "foo", "bar";
        }

    ``reserved`` notify ``protoc`` that the field number(s)
    or field name(s) has been removed or commented out.
    and the compiler will complain if any future users try to
    reuse these identifiers.

    Note that you can't mix field names and field numbers in a ``reserved`` statement.

#. Default Values

    - For strings, the default value is the empty string.
    - For bytes, the default value is empty bytes.
    - For bools, the default value is false.
    - For numeric types, the default value is zero.
    - For enums, the default value is the first defined enum value, which must be 0.
    - For message fields, the field is not set. Its exact value is language-dependent.
    - The default value for repeated fields is empty.

#. Enumerations

    .. code-block:: proto

        message MyMessage1
        {
            enum EnumAllowingAlias
            {
                option allow_alias = true;
                UNKNOWn = 0;
                STARTED = 1;
                RUNNING = 1;
            }

        message MyMessage2
        {
            enum EnumNotAllowingAlias
            {
                UNKNOWn = 0;
                STARTED = 1;
                // RUNNING = 1; // Uncomment this line will cause protoc to issue an error
            }
        }}

    every enum definition must contain a constant that maps to zero
    as its first element. This is because:

        - There must be a zero value, so that we can use 0 as a numeric default value.
        - The 0 value needs to be the 1st element, to maintain compatibility with proto2 semantics.

#. Importing Definitions

    .. code-block:: proto

        // new.proto
        // All definitions are moved here

        // old.proto
        // This is the proto that all clients are importing.
        import public "new.proto";
        import "other.proto";

        // client.proto
        import "old.proto";
        // You use definitions from old.proto and new.proto, but not other.proto

    .. code-block:: sh
        :caption: protoc related options

        -IPATH, --proto_path=PATH
        Specify the directory in which to search for
        imports. May be specified multiple times;
        directories will be searched in order. If not
        given, the current working directory is used.
        If not found in any of the these directories,
        the --descriptor_set_in descriptors will be
        checked for required proto file.

#. Nested Types

    .. code-block:: proto

        message SearchResponse
        {
            message Result
            {
                string url = 1;
                string titile = 2;
                repeated string snippets = 3;
            }
            repeated Result results = 1;
        }

        message SomeOtherMessage
        {
            SearchResponse.Result result = 1;
        }

        message Outer
        {
            message MiddleAA
            {
                message Inner
                {
                    int64 ival = 1;
                    bool booy = 2;
                }
            }

            message MiddleBB
            {
                message Inner
                {
                    int32 ival = 1;
                    bool booly = 2;
                }
            }
        }

#. Packages

    You can add an optional ``package`` specifier to a proto file
    to prevent name clashes between protocol message types.

    In C++ the generated classes are wrapped inside a C++ namespace.
    For example, Open would be in the name space ``foo::bar``.

    .. code-block:: proto

        // foo_bar.proto
        package foo.bar;
        message Open {...}

        // other.proto
        message Foo
        {
            ...
            foo.bar.Open open = 1;
            ...
        }

#. Maps

    Associative map: ``map<key_type, value_type> map_field = N;``

    where ``key_type`` can be any integral or string type except for
    floating point types and ``bytes``. ``value_type`` can be any type except another map.

    Note that:

        - Map fields can't be ``repeated``.
        - ``enum`` is not a valid ``key_type``.

    Out of backwards compatibility, The map syntax is equivalent to
    the following on the wire:

    .. code-block:: proto

        message MapFieldEntry
        {
            key_type key = 1;
            value_type = 2;
        }

        repeated MapFieldEntry map_field = N;

#. Defining RPC Services

    The following code define an RPC service
    with a method ``Search`` which takes ``SearchRequest`` as
    its parameter and return ``SearchReponse`` as its reponse.

    .. code-block:: proto

        service SearchService
        {
            rpc Search (SearchRequest) returns (SearchReponse);
        }


.. rubric:: Footnotes

.. [#] `proto3 grammer <https://developers.google.com/protocol-buffers/docs/proto3>`_
