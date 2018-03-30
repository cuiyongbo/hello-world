``delete this`` in c++
======================

Basically you are not advised to do ``delete this`` operation unless

   * The class you delete was allocated on heap or free store.
   * You will ``NEVER`` use the pointer again after you delete it.


Declare class constructor as private
====================================

Here are some of the uses of private constructor :

   * Objects can only be created on heap
   * Singleton Design Pattern
   * To limit the number of instance creation
   * To give meaningful name for object creation using static factory method
   * Static Utility Class or Constant Class
   * To prevent Subclassing (lose the chance to be inherited)
   * Builder Design Pattern and thus for creating immutable classes


Declare class destructor as ``private/protected``
=================================================

Basically, any time you want some other class to be responsible for the life cycle of your class' objects,
or you have reason to prevent the destruction of an object, you can make the destructor private.

For instance, if you're doing some sort of reference counting thing, you can have the object
(or manager that has been "friend"ed) responsible for counting the number of references to itself
and delete it when the number hits zero. A private destructor would prevent anybody else from
deleting it when there were still references to it.

.. code-block:: c++

   delete w;
   // error C2248: 'Water::~Water' : cannot access protected member declared in class 'Water'


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
   
   