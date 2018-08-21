*******************************
std associative container - map
*******************************

#. User-defined structure as key

   .. code-block:: cpp
    
      #include <stdio.h>
      #include <map>
      #include <unordered_map>
      #include <functional>

      /*
         template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<std::pair<const Key, T> >
         > class map;
      */

      /*
         template<
             class Key,
             class T,
             class Hash = std::hash<Key>,
             class KeyEqual = std::equal_to<Key>,
             class Allocator = std::allocator< std::pair<const Key, T> >
         > class unordered_multimap;
      */
      
      typedef long long int64;
      struct TrafficCamera {
          // Camera information
      };

      struct Point {
          int x, y;
      };
      
      Point Point_make(int x, int y) 
      {
          Point o;
          o.x = x;
          o.y = y;
          return o;
      }
      
      bool operator== (const Point& l, const Point& r) {
          return l.x == r.x && l.y == r.y;
      }

      bool operator< (const Point& l, const Point& r) {
          int64 lp = (int64)l.x << 32 | l.y;
          int64 rp = (int64)r.x << 32 | r.y;
          return lp < rp;
      }
      
      namespace std
      {
          template<> struct hash<Point> {
              size_t operator() (const Point& s) const {
                  return ((long long)s.x) << 32 | s.y;
              }
          };
      }

      void test_unordered_multimap()
      {
         std::unordered_multimap<Point, int> m1;
         m1.emplace(Point_make(1, 2), 1);
         m1.emplace(Point_make(3,4), 1);
         m1.emplace(Point_make(3,7), 1);
         printf("unordered_multimap size: %d.\n", (int)m1.size());
      }
      
       void test_map()
      {
         std::map<Point, TrafficCamera>m1;
         TrafficCamera camera;
         m1.emplace(Point_make(1,2), camera);
         m1.emplace(Point_make(3,4), camera);
         m1.emplace(Point_make(3,7), camera);
         printf("map size: %d.\n", (int)m1.size());
      }

#. std::unordered_multimap::equal_range()

   .. code-block:: cpp
      :caption: Language Support

      //(since C++11)
      std::pair<iterator,iterator> equal_range( const Key& key ); 
      std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

   Returns a range containing all elements with key *key* in the container. The range
   is defined by two iterators, the first pointing to the first element of the wanted range
   and the second pointing past the last element of the range.

   Return a ``std::pair`` containing a pair of iterators defining the wanted range
   if elements are found. Otherwise, past-the-end (``end()``) iterators are returned
   as both elements of the pair.

   In average case linear in the number of elements with the key *key*,
   worst case linear in the size of the container.

   .. code-block:: c++
      :caption: Example taken from cppreference

      #include <iostream>
      #include <unordered_map>
       
      int main()
      {  
         std::unordered_multimap<int,char> map = {{1,'a'},{2,'b'},{1,'d'},{2,'b'}};
         auto range = map.equal_range(1);
         for (auto it = range.first; it != range.second; ++it)
            std::cout << it->first << ' ' << it->second << '\n';
         std::cout << std::distance(range.first, range.second) << "\n"; 
      }