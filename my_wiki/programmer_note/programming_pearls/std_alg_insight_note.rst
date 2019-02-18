*******************************
Standard Algorithm Library Note
*******************************

#. copy and copy_if
 
    .. code-block:: cpp
        :caption: Possible implementation

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
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred)
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

