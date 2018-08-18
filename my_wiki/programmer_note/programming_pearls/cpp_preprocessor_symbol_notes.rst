********************
Preprocessor symbols
********************

#. Preprocessor convert to string(#)
   


#. Preprocessor concatenate(##)
   
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
