********************
Preprocessor symbols
********************

#. Preprocessor convert to string(#)
   
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


#. Preprocessor concatenate(##)
   

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

