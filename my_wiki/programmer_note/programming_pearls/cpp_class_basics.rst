****************
C++ Class Basics
****************

#. Access control

    .. image:: images/cpp_class_access_control.png

#. ``delete this`` in cpp

    Basically you are not advised to do ``delete this`` operation unless

        * The object you delete was allocated on heap or free store.
        * You will **NEVER** use the pointer again after you delete it.

#. Declare class constructor as ``private/protected``

    Here are some of the uses of ``private/protected`` constructor:

        * Objects can only be created on heap [heap-based object]
        * Lose the chance to be inherited [**private only**]
        * Singleton Design Pattern
        * To limit the number of instance creation
        * To give meaningful name for object creation using static factory method [named constructor]

#. Prohibit class instance copy

    .. code-block:: cpp

        class NonAssignable {
        public:
            // disallow copying or assignmentf
            NonAssignable(NonAssignable const&) = delete;
            NonAssignable& operator=(NonAssignable const&) = delete;
            NonAssignable() {}
        };

        NonAssignable n1;
        NonAssignable n2 = n1; 'NonAssignable::NonAssignable(const NonAssignable &)' : attempting to reference a deleted function

#. Declare class destructor as ``private/protected``

    Basically, any time you want some other class to be responsible for the life cycle of your class'
    objects, or you have reason to prevent the destruction of an object, you can make the destructor private.

    For instance, if you're doing some sort of **reference counting** thing, you can have the object
    responsible for counting the number of references to itself and delete it when the number hits zero.
    A private destructor would prevent anybody else from deleting it when there were still references to it.

    .. code-block:: cpp

        class Water
        {
        protected:
            ~Water() {}
        // ...
        };

        delete w;
        // error C2248: 'Water::~Water' : cannot access protected member declared in class 'Water'


#. Declare class destructor as ``virtual``

    Many classes require some form of cleanup for an object before it goes away. Since the abstract
    class cannot know if a derived class requires such cleanup, it must assume that it does require some.
    We ensure proper cleanup by defining a virtual destructor in the base and overriding it suitably in derived classes.
    For example::

        class Ival_box
        {
           // ...
           virtual ~Ival_box() {}
        };

        void f(Ival_box* p)
        {
           // ...
           delete p;
        }

    The ``delete`` operator explicitly destroys the object pointed to by p. We have no way of knowing
    exactly to which class the object pointed to by p belongs, but thanks to Ival_box’s virtual
    destructor, proper cleanup as defined by that class’ destructor will be called.

#. Difference between assignment and copy constructor

    Copy constructor initializes an uninitialized object with an initialized one;
    while assignment re-initilizes an initialized object with another initialized one.

    You could replace copy construction by default construction plus assignment,
    but that would be less efficient.

    .. code-block:: cpp

        A(const A& other): m_data(other.m_data) {}
        A& operator=(const A& other)
        {
           if(this != &other)
           {
              cleanup(m_data);
              m_data = other.m_data;
           }
           return *this;
        }

#. cpp enumerator type to overload `|` and `&`

    .. code-block:: cpp

        enum FileMode
        {
            FileMode_none = 0,
            FileMode_readOnly = 0x01,
            FileMode_writeOnly = 0x10,
            FileMode_readWrite = 0x100
        };

        FileMode operator | (FileMode l, FileMode r)
        {
            return FileMode(int(l) | int(r));
        }

        FileMode operator & (FileMode l, FileMode r)
        {
            return FileMode(int(l) & int(r));
        }

#. friend class

    Friendship is neither inherited nor transitive. For example

    .. code-block:: cpp

        class A {
            friend class B;
            int a;
            void f(B* p) {
               p->b++; // error: A is not a friend of B, despite B is a friend of A
            }
        };
        class B {
            friend class C;
            int b;
        };
        class C {
            void f(A* p) {
               p->a++; // error: C is not a friend of A, despite being a friend of a friend of A
            }
        };
        class D: public B {
           void f(A* p) {
              p->a++; // error: D is not a friend of A, despite being derived from a friend of A
           }
        };

#. Design pattern - Lazy loading

    Lazy loading is a design pattern commonly used in computer programming to defer initialization of an object
    until the point at which it is needed. It can contribute to efficiency in the program's operation if properly
    and appropriately used.

#. Design pattern - PIMPL

    The :abbr:`PIMPL (Pointer to IMPLementation)` Idiom  is a technique for implementation hiding
    in which a public class wraps a structure or class that cannot be seen outside the library
    the public class is part of. This hides internal implementation details and data from the
    user of the library.

.. rubric:: Footnotes

.. [#] `Private destructor for singleton class <https://stackoverflow.com/questions/2559750/private-destructor-for-singleton-class>`_
