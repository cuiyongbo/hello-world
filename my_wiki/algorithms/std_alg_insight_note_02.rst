**********************************
Standard Algorithm Library Note 02
**********************************

#. partition and stable_partition
   
    .. code-block:: cpp

        template<class ForwardIt, class UnaryPredicate>
        ForwardIt partition(ForwardIt first, ForwardIt last UnaryPredicate p)
        {
            first = std::find_if_not(first, last, p);
            if(first == last)
                return first;
            for(ForwardIt it=std::next(first); it != last; ++it)
            {
                if(p(*it))
                {
                    std::iter_swap(iter, first);
                    ++first;
                }
            }
            return first;
        }

    .. note::

        `partition` reorders the elements in the range `[first, last)` in such a way that all elements 
        for which the predicate `p` returns `true` precede the elements for which predicate `p` 
        returns `false`. `stable_partition` dittos, but keeps the relative order of elements.
