****************
Move Constructor
****************

.. code-block:: cpp
   :caption: Sample Solution

   template <class T>  
   struct proxy
   {
     T *resource_;
   };
   
   } // detail
   
   template <class T>
   class MovableResource
   {
     private:
       T * resource_;
   
     public:
       explicit MovableResource (T * r = 0) : resource_(r) { }
       ~MovableResource() throw() { delete resource_; }   // Assuming std::auto_ptr like behavior.
   
       MovableResource (MovableResource &m) throw () // The "Move constructor" (note non-const parameter)
         : resource_ (m.resource_)
       {
         m.resource_ = 0; // Note that resource in the parameter is moved into *this.
       }
   
       MovableResource (detail::proxy<T> p) throw () // The proxy move constructor
         : resource_(p.resource_)
       {
         // Just copying resource pointer is sufficient. No need to NULL it like in the move constructor.
       }
   
       MovableResource & operator = (MovableResource &m) throw () // Move-assignment operator (note non-const parameter)
       {
         // copy and swap idiom. Must release the original resource in the destructor.
         MovableResource temp (m); // Resources will be moved here.
         temp.swap (*this);
         return *this;
       }
   
       MovableResource & operator = (detail::proxy<T> p) throw ()
       {
         // copy and swap idiom. Must release the original resource in the destructor.
         MovableResource temp (p);
         temp.swap(*this);
         return *this;
       }
   
       void swap (MovableResource &m) throw ()
       {
         std::swap (this->resource_, m.resource_);
       }
   
       operator detail::proxy<T> () throw () // A helper conversion function. Note that it is non-const
       {
         detail::proxy<T> p;
         p.resource_ = this->resource_;
         this->resource_ = 0;     // Resource moved to the temporary proxy object.
         return p;
       }
   };

   MovableResource<int> func()
   {
     MovableResource<int> m(new int());
     return m;
   }
   int main()
   {
     MovableResource<int> a(func()); // Assuming this call is not return value optimized (RVO'ed).
   }  


.. code-block:: cpp
   :caption: Alternatives

   template<class T>
   class MovableResource
   {
     mutable bool owner;
     T* px;
   
   public:
     explicit MovableResource(T* p=0)
          : owner(p), px(p) {}
   
     MovableResource(const MovableResource& r)
          : owner(r.owner), px(r.release()) {}
   
     MovableResource & operator = (const MovableResource &r)
     {
       if ((void*)&r != (void*)this)
       {
         if (owner)
           delete px;
         owner = r.owner;
         px = r.release();
       }
       return *this;
     }
   
     ~MovableResource() { if (owner) delete px; }
     T& operator*() const { return *px; }
     T* operator->() const { return px; }
     T* get()    const { return px; }
     T* release()  const { owner = false; return px; } // mutable 'ownership' changed here.
   }; 