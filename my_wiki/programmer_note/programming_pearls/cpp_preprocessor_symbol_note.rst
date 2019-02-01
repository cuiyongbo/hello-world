********************
Preprocessor symbols
********************

#. Stringizing(#)
   
    .. code-block:: c

        /* 
           A single macro will paste the token itself, yielding literally "%" "MAX_LEN" "s";
           a second macro causes the token value to be pasted.
        */

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
      
        #define MAX_LEN 5
        #define STR1(x) #x
        #define STR(x) STR1(x)
      
        int main()
        {
            char buff[MAX_LEN+1];
            scanf("%"STR(MAX_LEN)"s", buff);
            printf("%s\n", buff);
            return 0;
        }

    .. code-block:: c

        static void pr_limits(char*, int);
        #define doit(name) pr_limits(#name, name)

    .. code-block:: c
        :caption: Taken from *GUN Documentation*

        #define WARN_IF(EXP) \
        do { if (EXP) \
                fprintf (stderr, "Warning: " #EXP "\n"); } \
        while (0)

        WARN_IF (x == 0);

        // do { if (x == 0)
        //           fprintf (stderr, "Warning: " "x == 0" "\n"); } while (0);
        

#. Token concatenation(##)

    .. code-block:: cpp

        class StringWapper
        {
        public:
            static StringWapper* fromWString(const wchar_t* str)
            {
                return new StringWapper;
            }
        
            StringWapper():m_bufferSize(0), m_buffer(NULL) {}
        
        private:
            size_t m_bufferSize;
            wchar_t* m_buffer;    
        };
        
        #define _CS(ansiString) StringWapper::fromWString(L##ansiString)
      
        int main()
        {
            StringWapper* wrapper = _CS("Hello world");
            delete wrapper;
            return 0;
        }
   
    .. code-block:: c
        :caption: used to define a c vector

        #define vector_declare(VectorName, Type)        \
        typedef struct VectorName {     \
        size_t m_capacity; \
        size_t m_count; \
        Type* m_buffer; \
        } VectorName; \
        void VectorName##_construct(VectorName* o, size_t initSize); \
        void VectorName##_destruct(VectorName* o); \
        void VectorName##_reserve(VectorName* o, size_t size); \
        void VectorName##_resize(VectorName* o, size_t size); \
        void VectorName##_push_back(VectorName* o, Type obj);

#. Preprocessor Macros
   
    .. code-block:: cpp

        int main()
        {
           std::cout << "File: " << __FILE__ << '\n';
           std::cout << "Function: " << __FUNCTION__ << '\n';
           std::cout << "Line No: " << __LINE__ << '\n';
           std::cout << "Date: " << __DATE__ << '\n';
           std::cout << "Time: " << __TIME__ << '\n';
           return 0;
        }

        // Output:
        // File: test.cpp
        // Function: main
        // Line No: 28
        // Date: Sep  4 2018
        // Time: 23:06:22

    .. note:: 

        ``__FUNCTION__`` is non-standard, ``__func__`` exists in C99 / C++11.


    .. code-block:: c
        :caption: Taken from *GUN documentations* 
    
        struct Command
        {
            char *name;
            void (*function) (void);
        };
        
        #define COMMAND(NAME) { #NAME, NAME ## _func}
        
        struct Command commands[] = {
            COMMAND(help),
            COMMAND(quit),
            // ...
        };


.. rubric:: Footnotes

.. [#] `Stringizing(#) <https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html#Stringizing>`_
.. [#] `Token concatenation(##) <https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation>`_
.. [#] `Swallowing the Semicolon <https://gcc.gnu.org/onlinedocs/cpp/Swallowing-the-Semicolon.html#Swallowing-the-Semicolon>`_
