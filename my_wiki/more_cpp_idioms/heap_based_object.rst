*****************
heap-based object
*****************

.. code-block:: cpp

   #include <iostream>
   
   class HeapOnly
   {
   public:
      HeapOnly() {}
      void destroy() { delete this; }
   
   protected:
      ~HeapOnly() {}
   };
   
   class NoHeap
   {
   protected:
      static void* operator new(std::size_t);
      static void* operator new[](std::size_t);
   };