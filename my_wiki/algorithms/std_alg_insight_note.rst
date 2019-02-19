*******************************
Standard Algorithm Library Note
*******************************

#. copy and copy_if
 
    .. code-block:: cpp

        template<class InputIt, class OutputIt>
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
        {
            while(first != last)
            {
                *d_first++ = *first++;
            }
            return d_first;
        }

        template<class InputIt, class OutputIt, class UnaryPredicate>
        OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred)
        {
            while(first != last)
            {
                if(pred(*first))
                    *d_first++ = *first;
                first++;
            }
            return d_first;
        }
    
    .. note:: 

        In practice, implementations of `std::copy` avoid multiple assignments and use bulk copy functions 
        such as `std::memmove` if the value type is TriviallyCopyable.

        When copying overlapping ranges, `std::copy` uses strategy adopted by `std::memmove.` 

        pred - unary predicate which returns ​true for the required elements. 

        The expression `pred(v)` must be convertible to `bool` for every argument v of type (possibly const) VT, 
        where VT is the value type of InputIt, regardless of value category, and must not modify v. Thus, a parameter 
        type of VT& is not allowed, nor is VT unless for VT a move is equivalent to a copy.

#. remove and remove_if
   
    .. code-block:: cpp

        template<class ForwardIt, class T>
        ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
        {
            first = std::find(first, last, value);
            if(first != last)
            {
                for(ForwardIt i=first; ++i != last; )
                {
                    if(!(*i == value))
                        *first++ = std::move(*i);
                }
                return first;
            }
        }

        template<class ForwardIt, class UnaryPredicate>
        ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
        {
            first = std::find(first, last, value);
            if(first != last)
            {
                for(ForwardIt i=first; ++i != last; )
                {
                    if(!p(*i))
                        *first++ = std::move(*i);
                }
                return first;
            }
        }

    .. note:: 

        Removing is done by shifting (by means of move assignment) the elements in the range 
        in such a way that the elements that are not to be removed appear in the beginning of the range. 
        Relative order of the elements that remain is preserved and the physical size of the container is unchanged. 

        Complexity: Exactly `std::distance(first, last)` applications of the predicate.

        UnaryPredicate - ditto.

    .. important:: 

        A call to remove is typically followed by a call to a container's erase method, 
        which erases the unspecified values and reduces the physical size of the container 
        to match its new logical size.
    
        The similarly-named container member functions `list::remove`, `list::remove_if`, 
        `forward_list::remove`, and `forward_list::remove_if` erase the removed elements.

        These algorithms cannot be used with associative containers such as `std::set` and `std::map` 
        because ForwardIt does not dereference to a MoveAssignable type (the keys in these containers are not modifiable).

#. remove_copy and remove_copy_if

    .. code-block:: cpp
    
        template<class InputIt, class OutputIt, class T>
        OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, const T& value)
        {
            for(; first != last; ++first)
            {
                if(!(*first == value))
                    *d_first++ = *first;
            }
            return d_first;
        }
        
        template<class InputIt, class OutputIt, class UnaryPredicate>
        OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred)
        {
            for(; first != last; ++first)
            {
                if(!pred(*first))
                    *d_first++ = *first;
            }
            return d_first;
        }

#. reverse
   
    .. code-block:: cpp
    
        template<class BidirIt>
        void reverse(BidirIt first, BidirIt last)
        {
            for(; first != last && first != --last; ++first)
                std::iter_swap(first, last);
        }

#. rotate
   
    .. code-block:: cpp

        template<class _BidIt> inline
        void _Rotate(_BidIt _First, _BidIt _Mid, _BidIt _Last)
        {   // rotate [_First, _Last), _Mid as the pivot
            reverse(_First, _Mid);
            reverse(_Mid, _Last);
            reverse(_First, _Last);
        }
   
    .. note::
   
        `reverse` can be seen as an instance of `rotate` where the pivot is the midpoint.

#. unique
   
    .. code-block:: cpp

        template<class ForwardIt>
        ForwardIt unique(ForwardIt first, ForwardIt last)
        {
            if(first == last)
                return last;

            ForwardIt result = first;
            while(++first != last)
            {
                if(!(*result == *first) && (++result != first))
                    *result = std::move(*first)
            }
            return ++result;
        }

        template<class ForwardIt, class BinaryPredicate>
        ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
        {
            if(first == last)
                return last;

            ForwardIt result = first;
            while(++first != last)
            {
                if(!p(*result == *first) && (++result != first))
                    *result = std::move(*first)
            }
            return ++result;
        }

    .. note::

        Eliminates all but the first element from every consecutive group of equivalent elements 
        from the range `[first, last)` and returns a past-the-end iterator for the new logical end of the range.
        Removing is done by shifting the elements in the range in such a way that elements to be erased are overwritten. 
        Relative order of the elements that remain is preserved and **the physical size of the container is unchanged.**

        p -  binary predicate which returns ​true if the elements should be treated as equal. 

        The signature of the predicate function should be equivalent to the following::

            bool pred(const Type1& a, const Type2& b);

        Complexity: For nonempty ranges, exactly `std::distance(first,last) -1` applications of the corresponding predicate.

    