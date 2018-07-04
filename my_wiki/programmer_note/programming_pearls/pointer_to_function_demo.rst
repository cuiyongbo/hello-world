********************
Pointer to Functions
********************

.. code-block:: cpp

   typedef void (*sig_t) (int);
   sig_t signal(int sig, sig_t func);

   typedef void(*PF)();

   // array of pointers to functions
   PF edit_ops[] = { 
      // edit operations 
      &cut, &paste, &copy, &search
   };

   PF file_ops[] = { 
      // file management 
      &open, &append, &close, &write
   };

   PF* button2 = edit_ops; 
   PF* button3 = file_ops;

   button2[2]();  // call button2’s 3rd function


.. code-block:: c
   :caption: Shell sort (Knuth, Vol3)

   #include <iostream>
   #include <string.h>

   #define element_of(a) (sizeof(a)/sizeof(a[0]))
   
   struct User {
       const char* name;
       const char* id;
       int dept;
   };
   
   User heads[] = {
       {"Ritchie D.M", "dmr", 11271},
       {"Sethi R.", "ravi", 11272},
       {"Szymanski T.G.", "tgs", 11273},
       {"Schryer N.L.", "nls", 11274},
       {"Schryer N.L.", "nls", 11275},
       {"Kernighan B.W.", "bwk", 11276},
   };

   void print_id(User* v,int n)
   {
       for(int i=0;i<n;i++)
           std::cout << v[i].name << '\t' << v[i].id << '\t' << v[i].dept << '\n';
   }

   typedef int (*CMP)(const void*, const void*);
   
   // not stable
   void shellSort(void* base, size_t count, size_t elementSize, CMP cmp)
   {
       for(int gap= (int)count/2; gap>0; gap /= 2)
       {
           for(int i=gap; i<count; i++)
           {
               for(int j=i-gap; j>=0; j -= gap)
               {
                   char* b = static_cast<char*>(base);
                   char* pj = b + j*elementSize; // &base[j]
                   char* pjg = b + (j+gap)*elementSize; // &base[j+gap]
                   if(cmp(pj, pjg)>0)
                   {
                       // swap base[j] and base[j+gap]
                       for(size_t k=0; k<elementSize; k++)
                       {
                           char temp = pj[k];
                           pj[k] = pjg[k];
                           pjg[k] = temp;
                       }
                   }
               }
           }
       }
   }
   
   int intCmp(const void* l, const void* r)
   {
       int a = *(int*)l;
       int b = *(int*)r;
       return a==b ? 0 : (a>b) ? 1 : -1;
   }
   
   int cmpByName(const void* l, const void* r)
   {
       return strcmp(static_cast<const User*>(l)->name, static_cast<const User*>(r)->name);
   }
   
   int cmpByDepartmentId(const void* l, const void* r)
   {
       return static_cast<const User*>(l)->dept - static_cast<const User*>(r)->dept;
   }
      
   int main(int argc, const char * argv[]) {
       int a[] = {5,4,3,2,1};
       shellSort(a, element_of(a), sizeof(a[0]), intCmp);
       std::cout << "original order:\n";
       print_id(heads, element_of(heads));
       std::cout << '\n';
       
       std::cout << "order by name in alphabatical order:\n";
       shellSort(heads, element_of(heads), sizeof(heads[0]), cmpByName);
       print_id(heads, element_of(heads));
       std::cout << '\n';
       
       std::cout << "order by department id:\n";
       shellSort(heads, element_of(heads), sizeof(heads[0]), cmpByDepartmentId);
       print_id(heads, element_of(heads));
       std::cout << '\n';
       
       return 0;
   }  