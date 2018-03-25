C++ class example
=================

.. code-block:: c++ 
   :caption: class example

   #include <stdio.h>
   #include <string.h>
   
   struct  Integer
   {
      Integer():
         size(0), data(NULL)
      {
         printf("Default constructor\n");
      }
   
      Integer(int n):
         size(n), data(NULL)
       {
         data = new int[size];
         printf("1-Argument constructor\n");
      }
   
      Integer(const Integer& other) {
         size = other.size;
         data = new int[size];
         memcpy(data, other.data, size*sizeof(int));
         printf("Copy constructor\n");
      }
   
       Integer& operator=(const Integer& other) {
         if(data != NULL) {
            delete[] data;
            size = 0;
         }
         
         size = other.size;
         data = new int[size];
         memcpy(data, other.data, size*sizeof(int));
         printf("operator=()\n");
      
         return *this;
      }
   
      ~Integer() {
         delete[] data;
         data = NULL;
         size = 0;
         printf("Destructor\n");
      }
   
      int size;
      int* data;
   };
   
   
   int main()
   {
      Integer a(2);
   
      a.data[0] = 123456;
      a.data[1] = 11;
   
      if(true)
      {
         Integer b = a;
         printf("%p\n", a.data);
         printf("%p\n", b.data);
      }
   
      Integer c(3);
      c = a;
   
      printf("%d\n", c.data[0]);
   
      return 0;
   }
   
   