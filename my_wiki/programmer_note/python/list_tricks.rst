***********
List tricks
***********

#. Using Lists as Stacks

   The list methods make it very easy to use a list as a stack, where the last element 
   added is the first element retrieved (“last-in, first-out”). To add an item to the 
   top of the stack, use ``append().`` To retrieve an item from the top of the stack, 
   use ``pop()`` without an explicit index. For example:
   
   .. code-block:: py

      >>> stack = [3, 4,5]
      >>> stack.append(6)
      >>> stack.append(7)
      >>> stack
      [3, 4, 5, 6, 7]
      >>> stack.pop()
      7
      >>> stack
      [3, 4, 5, 6]
      >>> stack.pop()
      6
      >>> stack
      [3, 4, 5]

      # L.pop([index]) -> item -- remove and return item at index (default last).
      # Raises IndexError if list is empty or index is out of range.
   
#. Using Lists as Queues

   It is also possible to use a list as a queue, where the first element added is the first element 
   retrieved (“first-in, first-out”); however, lists are not efficient for this purpose. While appends 
   and pops from the end of list are fast, doing inserts or pops from the beginning of a list is slow 
   (because all of the other elements have to be shifted by one).
   
   To implement a queue, use ``collections.deque`` which was designed to have fast appends and pops from 
   both ends. For example:
   
   .. code-block:: py
   
      >>> from collections import deque
      >>> queue = deque(["Eric", "John", "Michael"])
      >>> queue.append("Terry")           # Terry arrives
      >>> queue.append("Graham")          # Graham arrives
      >>> queue.popleft()                 # The first to arrive now leaves
      'Eric'
      >>> queue.popleft()                 # The second to arrive now leaves
      'John'
      >>> queue                           # Remaining queue in order of arrival
      deque(['Michael', 'Terry', 'Graham'])