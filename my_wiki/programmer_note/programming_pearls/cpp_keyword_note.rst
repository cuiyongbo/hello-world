************
CPP Keywords
************

#. default

    * switch statement: as the declaration of the default case label.

    * explicitly-defaulted function definition: as an explicit instruction
      to the compiler to generate special member function or a comparison operator for a class

    .. code-block:: c
        :caption: GUN thread implementation

        class thread
        {
            // ...
            thread() noexcept = default;
            thread(thread&) = delete;
            thread(const thread&) = delete;
            thread& operator=(const thread&) = delete;
        }

#. delete

    * delete expression
    * allocation functions as the name of operator-like functions
    * deleted functions

    .. note::

        If the special syntax ``= delete``; is used, the function is defined as deleted.
        Any use of a deleted function is ill-formed (the program will not compile).
        This includes calls, both explicit (with a function call operator) and implicit
        (a call to deleted overloaded operator, special member function, allocation function etc),
        constructing a pointer or pointer-to-member to a deleted function, and even the use of
        a deleted function in an unevaluated expression. However, implicit ODR-use of a non-pure
        virtual member function that happens to be deleted is allowed.

        If the function is overloaded, overload resolution takes place first, and the program
        is only ill-formed if the deleted function was selected::

            struct sometype
            {
                void* operator new(std::size_t) = delete;
                void* operator new[](std::size_t) = delete;
            };
            sometype* p = new sometype; // error: attempts to call deleted sometype::operator new

        The deleted definition of a function must be the first declaration in a translation unit:
        a previously-declared function cannot be redeclared as deleted::

            struct sometype { sometype(); };
            sometype::sometype() = delete; // error: must be deleted on the first declaration

#. explicit specifier

    Specifies that a constructor or conversion function is explicit,
    that is, it cannot be used for implicit conversions and copy-initialization.

    .. code-block:: cpp

        struct B
        {
            explicit B(int) { }
            explicit B(int, int) { }
            explicit operator bool() const { return true; }
        };

    .. note::

        A constructor with a single non-default parameter that is declared
        without the function specifier explicit is called a **converting constructor**.

#. override specifier

    ``override`` Specifies that a virtual function overrides another virtual function.

#. final specifier

    When used in a virtual function declaration or definition, `final` ensures that the function
    is virtual and specifies that it may not be overridden by derived classes.

    When used in a class definition, `final` specifies that this class cannot be derived from.

    .. code-block:: cpp

        struct Base
        {
            virtual void foo();
        };

        struct A : Base
        {
            void foo() final; // A::foo is overridden and it is the final override
            void bar() final; // Error: non-virtual function cannot be overridden or be final
        };

        struct B final : A // struct B is final
        {
            void foo() override; // Error: foo cannot be overridden as it's final in A
        };

        struct C : B {}; // Error: B is final

#. inline

    In the C and C++ programming languages, an inline function is one qualified with the keyword ``inline``;
    this serves two purposes:

        * Firstly, it serves as a compiler directive that suggests that the compiler  substitute the body
          of the function inline by performing inline expansion, i.e. by inserting the  function code at
          the address of each function call, thereby avoiding the overhead of a function call.

        * The second purpose of inline is to change linkage behavior; the details of this are complicated.
          This is necessary due to the C/C++'s separate compilation and linkage model, specifically because
          the function body must be duplicated in all translation units where it is used, to allow inlining
          during compiling, which, if the function has external linkage, causes a collision during linking
          (it violates uniqueness of external symbols).

    Indiscriminate uses of inline function can result in larger code (bloated executable file),
    minimal or no performance gain, and in some cases even a loss in performance.
    The compiler cannot inline the function in all circumstances, even when inlining is forced.


    For code portability, the following preprocessor directives can be used::

        #ifdef _MSC_VER
        #define forceinline __forceinline
        #elif defined(__GNUC__)
        #define forceinline __attribute__((always_inline)) inline
        #else
        #define forceinline inline
        #endif

#. Scoped enumerations

    .. code-block:: none

        enum struct|class name { enumerator = constexpr , enumerator = constexpr , ... }    (1)
        enum struct|class name : type { enumerator = constexpr , enumerator = constexpr , ... } (2)

    1) declares a scoped enumeration type whose underlying type is int (the keywords class and struct are exactly equivalent)
    2) declares a scoped enumeration type whose underlying type is type

    Both scoped enumeration types and unscoped enumeration types whose underlying type
    is fixed can be initialized from an integer without a cast. However, There are no implicit
    conversions from the values of a scoped enumerator to integral types,
    although ``static_cast`` may be used to obtain the numeric value of the enumerator.
    And a named constant of the enumeration's type can be only accessd using scope resolution operator.

    .. code-block:: cpp

        enum class Color
        {
            red,
            green=20,
            blue
        };

        Color r = Color::blue;
        int n = static_cast<int>(r); // n = 21

        enum class altitude: char
        {
            high='h',
            low='l'
        };

        std::ostream& operator<<(std::ostream& os, Color c)
        {
            switch(c)
            {
                case Color::red: os << "red"; break;
                case Color::green: os << "green"; break;
                case Color::blue: os << "blue"; break;
                default: os.setstate(std::ios_base::failbit);
            }
            return os;
        }

        std::ostream& operator<<(std::ostream& os, altitude al)
        {
            return os << static_cast<char>(al);
        }

    .. code-block:: cpp
        :caption: Taken from **OSRM** project

        struct RouteParameters : public BaseParameters
        {
            enum class AnnotationsType
            {
                None = 0,
                Duration = 0x01,
                Nodes = 0x02,
                Distance = 0x04,
                Weight = 0x08,
                Datasources = 0x10,
                Speed = 0x20,
                All = Duration | Nodes | Distance | Weight | Datasources | Speed
            };

            // ...
        };

        inline RouteParameters::AnnotationsType operator|(RouteParameters::AnnotationsType lhs,
                                                          RouteParameters::AnnotationsType rhs)
        {
            return (RouteParameters::AnnotationsType)(
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(lhs) |
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(rhs));
        }

        inline RouteParameters::AnnotationsType operator|=(RouteParameters::AnnotationsType lhs,
                                                           RouteParameters::AnnotationsType rhs)
        {
            return lhs = lhs | rhs;
        }

