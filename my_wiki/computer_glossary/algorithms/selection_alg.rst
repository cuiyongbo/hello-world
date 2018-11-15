*******************
Selection Algorithm
*******************

#. Partial selection sort

   A simple example of selection by partial sorting is to use the partial selection sort.
   
   The obvious linear time algorithm to find the minimum (or maximum) – iterating over 
   the list and keeping track of the minimum (or maximum) element so far – can be seen 
   as a partial selection sort that selects the 1 smallest element. However, many other 
   partial sorts also reduce to this algorithm for the case k = 1, such as a partial heap sort.
   
   More generally, a partial selection sort yields a simple selection algorithm which takes **O(kn)** 
   time. This is asymptotically inefficient, but can be sufficiently efficient if k is small, and is 
   easy to implement. Concretely, we simply find the minimum value and move it to the beginning, repeating 
   on the remaining list until we have accumulated k elements, and then return the kth element. Here is 
   partial selection sort-based algorithm::
   
      function select(list, k)
          for i from 1 to k
              minIndex = i
              for j from i+1 to n
                  if list[j] < list[minIndex]
                      minIndex = j
              swap(list[i], list[minIndex])
          return list[k]
   
   .. code-block:: cpp
   
      void local_kth_element(int* a, int n, int k)
      {
          for(int i=0; i<k; i++)
          {
              int minIdx=i;
              for(int j=i+1; j<n; j++)
              {
                  if(a[j] < a[minIdx])
                      minIdx=j;
              }
              { int tmp=a[i]; a[i]=a[minIdx]; a[minIdx]=tmp; }
          }
      }
   
      int main()
      {
          std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
          std::cout << "Originally\n";
          for(int n: v)
              std::cout << n << " ";
          std::cout << '\n'; 
      
          local_kth_element(v.data(), (int)v.size(), 3);
          std::cout << "local_kth_element(3)\n";
          for(int n: v)
              std::cout << n << " ";
          std::cout << '\n'; 
      }
   
   .. code-block:: c
      :caption: Taken from *More Programming Pearls*
   
      void select(arr, l, u, k)
      {
   
         if(l < u)
         {
            swap(a[l], arr[randint(l, u)])
            m = l
            pivot = arr[m]
            for(i=l+1; i<=u; i++)
               if (arr[i] < pivot)
                  swap(arr[++m], arr[i])
            swap(arr[l], arr[m])
            if(m<k)
               select(arr, m+1, u, k)
            else if(m>k)
               select(arr, l , m-1, k)
         }
      }
   
   .. code-block:: none
      :caption: Taken from **Introduction to algorithms**
   
      Randomized-Select(A, p, r, i)
         if p==r
            return A[p]
         q = Randomized-Partition(A, p, r)
         k = q-p+1
         if i == k
            return A[q]
         else if i<k
            return Randomized-Select(A, p, q-1, i)
         else
            return Randomized-Select(A, q+1, r, i-k)
   
      # treat i as an index to the desired element
      Randomized-Select_2(A, p, r, i)
         if p==r
            return A[p]
         q = Randomized-Partition(A, p, r)
         if i == q
            return A[q]
         else if i < q
            return Randomized-Select(A, p, q-1, i)
         else
            return Randomized-Select(A, q+1, r, i-k)


#. Introselect

   In computer science, :abbr:`introselect (introspective selection)` is a selection algorithm that is a hybrid of 
   quickselect and median of medians which has fast average performance and optimal worst-case performance. 
   Introselect is related to the introsort sorting algorithm: these are analogous refinements of the basic 
   quickselect and quicksort algorithms, in that they both start with the quick algorithm, which has good 
   average performance and low overhead, but fall back to an optimal worst-case algorithm (with higher overhead) 
   if the quick algorithm does not progress rapidly enough. Both algorithms were introduced by *David Musser,* 
   with the purpose of providing generic algorithms for the C++ STL which had both fast average performance 
   and optimal worst-case performance, thus allowing the performance requirements to be tightened. 
   However, in most C++ STL implementations, another introselect algorithm is used, which combines 
   quickselect and heapselect, and has a worst-case running time of ``O(n log n).`` 