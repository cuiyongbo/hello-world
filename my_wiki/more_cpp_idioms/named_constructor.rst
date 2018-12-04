*****************
Named constructor
*****************

In C++, constructors are distinguished from each other only based on the type, 
the order and the number of parameters. Of course when a class has multiple 
constructors, each constructor has a different purpose. However, in C++ it 
is hard to capture that ”semantic” difference in the interface of the class 
because all the constructors have the same name and only parameters can 
distinguish between them.

The named constructor idiom uses a set of static member functions with meaningful names 
to create objects instead of constructors. Constructors are either private or protected 
and clients have access only to the public static functions.

.. code-block:: cpp

   class SongList
   {
      static SongList* createListByGenre(Genre g);
      static SongList* createListByArtist(std::string artist);
   
   protected:
      SongList();
   };