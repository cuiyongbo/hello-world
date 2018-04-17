:orphan:

***********************
Memory Allocation Hooks
***********************

The GNU C Library lets you modify the behavior of *malloc*, *realloc*, and *free* by specifying appropriate hook functions.
You can use these hooks to help you debug programs that use dynamic memory allocation, for example.

The hook variables are declared in :file:`malloc.h`.

#. Variable: __malloc_hook

   The value of this variable is a pointer to the function that *malloc* uses whenever it is called.
   You should define this function to look like *malloc*; that is, like::

      void *function (size_t size, const void *caller)

#. Variable: __realloc_hook

   The value of this variable is a pointer to function that *realloc* uses whenever it is called.
   You should define this function to look like *realloc*; that is, like::

      void *function (void *ptr, size_t size, const void *caller)

#. Variable: __free_hook

   The value of this variable is a pointer to function that *free* uses whenever it is called.
   You should define this function to look like *free*; that is, like::

      void function (void *ptr, const void *caller)

#. Variable: __memalign_hook

   The value of this variable is a pointer to function that *aligned_alloc, memalign, posix_memalign*
   and *valloc* use whenever they are called. You should define this function to
   look like *aligned_alloc*; that is, like::

      void *function (size_t alignment, size_t size, const void *caller)


.. note:: 
   
   The value of *caller* is the return address found on the stack when
   the *malloc/realloc/free/aligned_alloc/memalign/posix_memalign/valloc*
   function was called. This value allows you to trace the memory
   consumption of the program.


You must make sure that the function you install as a hook for one of these functions does not call
that function recursively without restoring the old value of the hook first! Otherwise, your program
will get stuck in an infinite recursion. Before calling the function recursively, one should make sure
to restore all the hooks to their previous value. When coming back from the recursive call, all the
hooks should be resaved since a hook might modify itself.

An issue to look out for is the time at which the malloc hook functions can be safely installed.
If the hook functions call the malloc-related functions recursively, it is necessary that *malloc*
has already properly initialized itself at the time when *__malloc_hook* etc. is assigned to.
On the other hand, if the hook functions provide a complete *malloc* implementation of their own,
it is vital that the hooks are assigned to before the very first *malloc* call has completed,
because otherwise a chunk obtained from the ordinary, un-hooked *malloc* may later be handed to
* __free_hook*, for example.

Here is an example showing how to use *__malloc_hook* and *__free_hook* properly. It installs
a function that prints out information every time *malloc* or *free* is called. We just assume
here that *realloc* and *memalign* are not used in our program.

.. code-block:: c

   /* Prototypes for __malloc_hook, __free_hook */
   #include <malloc.h>
   

   typedef void *(*malloc_hook_func)(size_t __size, const void *); 
   typedef void *(*free_hook_func)(void* ptr, const void *); 

   static malloc_hook_func old_malloc_hook = NULL;
   static free_hook_func old_free_hook = NULL;

   /* Prototypes for our hooks.  */
   static void my_init_hook (void);
   static void *my_malloc_hook (size_t, const void *);
   static void my_free_hook (void*, const void *);
   
   static void my_init (void)
   {
     old_malloc_hook = __malloc_hook;
     old_free_hook = __free_hook;
     __malloc_hook = my_malloc_hook;
     __free_hook = my_free_hook;
   }
   
   static void* my_malloc_hook (size_t size, const void *caller)
   {
     void *result;
     /* Restore all old hooks */
     __malloc_hook = old_malloc_hook;
     __free_hook = old_free_hook;
     /* Call recursively */
     result = malloc (size);
     /* Save underlying hooks */
     old_malloc_hook = __malloc_hook;
     old_free_hook = __free_hook;
     /* printf might call malloc, so protect it too. */
     printf ("malloc (%u) returns %p\n", (unsigned int) size, result);
     /* Restore our own hooks */
     __malloc_hook = my_malloc_hook;
     __free_hook = my_free_hook;
     return result;
   }
   
   static void my_free_hook (void *ptr, const void *caller)
   {
     /* Restore all old hooks */
     __malloc_hook = old_malloc_hook;
     __free_hook = old_free_hook;
     /* Call recursively */
     free (ptr);
     /* Save underlying hooks */
     old_malloc_hook = __malloc_hook;
     old_free_hook = __free_hook;
     /* printf might call free, so protect it too. */
     printf ("freed pointer %p\n", ptr);
     /* Restore our own hooks */
     __malloc_hook = my_malloc_hook;
     __free_hook = my_free_hook;
   }
   
   int main ()
   {
     my_init ();
     void* ptr = malloc(8);
     free(ptr);
     return 0;
   }

The *mcheck* function (see **Heap Consistency Checking**) works by installing such hooks.

Another example is memory operation taken from :file:`jansson/memory.c`.

.. code-block:: c

   typedef void *(*json_malloc_t)(size_t);
   typedef void (*json_free_t)(void *);
   
   void json_set_alloc_funcs(json_malloc_t malloc_fn, json_free_t free_fn);
   void json_get_alloc_funcs(json_malloc_t *malloc_fn, json_free_t *free_fn);
   
   /* memory function pointers */
   static json_malloc_t do_malloc = malloc;
   static json_free_t do_free = free;
   
   void *jsonp_malloc(size_t size)
   {
      if(!size)
         return NULL;
   
      return (*do_malloc)(size);
   }
   
   void jsonp_free(void *ptr)
   {
      if(!ptr)
         return;
   
      (*do_free)(ptr);
   }
   
   void json_set_alloc_funcs(json_malloc_t malloc_fn, json_free_t free_fn)
   {
      do_malloc = malloc_fn;
      do_free = free_fn;
   }
   
   void json_get_alloc_funcs(json_malloc_t *malloc_fn, json_free_t *free_fn)
   {
      if (malloc_fn)
         *malloc_fn = do_malloc;
      if (free_fn)
         *free_fn = do_free;
   }

