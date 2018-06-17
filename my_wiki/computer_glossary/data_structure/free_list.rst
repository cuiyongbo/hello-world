*********
Free list
*********

Overview
========

A free list is a data structure used in a scheme for dynamic memory allocation. 
It operates by connecting unallocated regions of memory together in a linked list, 
using the first word of each unallocated region as a pointer to the next. It is most 
suitable for allocating from a **memory pool**, where all objects have the same size.

Free lists make the allocation and deallocation operations very simple. To free a region, 
one would just link it to the free list. To allocate a region, one would simply remove a 
single region from the end of the free list and use it. If the regions are variable-sized, 
one may have to search for a region of large enough size, which can be expensive.

Free lists have the disadvantage, inherited from linked lists, of poor locality of reference 
and so poor data cache utilization, and they do not automatically consolidate adjacent regions 
to fulfill allocation requests for large regions, unlike the buddy allocation system. Nevertheless, 
they're still useful in a variety of simple applications where a full-blown memory allocator is 
unnecessary or requires too much overhead.


Implementation in C
===================

.. code-block:: c

   typedef unsigned char   uint8;
   static const int MEMORY_ALIGN = 8;
   
   #define print_msg_to_stderr(expression) \
       fprintf(stderr, "%s:assertion \"%s\" failed: file \"%s\", line %d, in function \"%s\"\n", \
           __DATE__, expression, __FILE__, __LINE__, __FUNCTION__)
   
   struct MemPoolItem
   {
       struct MemPoolItem* next;
   };
   
   typedef struct MemPoolItem MemPoolItem;
   
   struct MemPools
   {
       size_t m_poolSize;
       size_t m_memoryUsage;
   
       MemPoolItem* m_normalObjList;   // linked list of normal objects
       size_t m_pos;   // free position in current normal pool
   
       MemPoolItem* m_largeObjList; // linked list of large objects
   };
   
   typedef struct MemPools MemPools;
   
   void* MemPools_malloc(MemPools* pool, size_t size)
   {
       if(pool)
           return NULL;
   
       // rouding up to a multile of MEMORY_ALIGN  
       size = (size + MEMORY_ALIGN - 1) & (-MEMORY_ALIGN);
   
       MemPoolItem* item = NULL;
   
       // allocate memory for a large object
       if(size+MEMORY_ALIGN > pool->m_poolSize)
       {
           item = (MemPoolItem*)malloc(size+MEMORY_ALIGN);
           if(item != NULL)
           {
               item->next = pool->m_largeObjList;
               pool->m_largeObjList = item;
               pool->m_memoryUsage += (size+MEMORY_ALIGN);
               return ((uint8*)item) + MEMORY_ALIGN;
           }
           else
           {
               print_msg_to_stderr("item = (MemPoolItem*)malloc(size+MEMORY_ALIGN)");
               return NULL;
           }
       }
   
       // a new pool is needed
       if(pool->m_normalObjList == NULL || pool->m_pos + size > pool->m_poolSize)
       {
           item = (MemPoolItem*)malloc(pool->m_poolSize);
           if(item == NULL)
           {
               print_msg_to_stderr("item = (MemPoolItem*)malloc(size+MEMORY_ALIGN)");
               return NULL;
           }
   
           pool->m_memoryUsage += pool->m_poolSize;
           item->next = pool->m_normalObjList;
           pool->m_normalObjList = item;
           pool->m_pos = MEMORY_ALIGN;
       }
   
       void* rtn = ((uint8*)pool->m_normalObjList) + pool->m_pos;
       pool->m_pos += size;
       return rtn;
   }

