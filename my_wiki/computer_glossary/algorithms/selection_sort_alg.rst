**************
Selection Sort
**************

**Keywords**: in-place sort.

Introduction
============



C++ implementation
==================

.. code-block:: cpp

   template<typename T, BinPre BinCmp>
   void selectionSort(T* array, size_t count, BinCmp cmp)
   {
      if(count <= 1)
         return;

      for(size_t i=0; i != count; i++)
      {
         size_t pos = i;
         for(size_t j = i+1; j < count; j++)
         {
            if(!cmp(arr[pos], arr[j])
               pos = j;
         }

         if(pos != i)
            swap(arr[pos], arr[i]);
      }
   }
