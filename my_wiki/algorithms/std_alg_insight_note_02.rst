**********************************
Standard Algorithm Library Note 02
**********************************

#. bound search
   
    .. code-block:: cpp

        template<class ForwardIt, class T, class Compare>
        bool binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp)
        {
            first = std::lower_bound(first, last, value, comp);
            return (!(first == last) && !(comp(value, *first)));
        }

        template<class ForwardIt, class T, class Compare>
        ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
        {
            typename std::iterator_traits<ForwardIt>::difference_type count, step;
            count = std::distance(first, last);
            ForwardIt it;
 
            while (count > 0) 
            {
                it = first;
                step = count/2;
                std::advance(it, step);
                if (comp(*it, value)) 
                {
                    first = ++it;
                    count -= step+1;
                }
                else
                {
                    count = step;
                }
            }
            return first;
        }

        template <class ForwardIt, class T, class Compare>
        ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
        {
            typename std::iterator_traits<ForwardIt>::difference_type count, step;
            count = std::distance(first, last);
            ForwardIt it;
            while(count > 0)
            {
                it = first;
                step = count/2;
                std::advance(it, step);
                if(!comp(value, *it))
                {
                    first = ++it;
                    count -= step+1;
                }
                else
                {
                    count = step;
                }
            }
            return first;
        }

        template<class ForwardIt, class T, class Compare>
        std::pair<ForwardIt,ForwardIt> equal_range(ForwardIt first, ForwardIt last, const T& value, Compare comp)
        {
            return std::make_pair(std::lower_bound(first, last, value, comp),
                                std::upper_bound(first, last, value, comp));
        }

    .. note::

        `upper_bound` returns an iterator pointing to the first element in the range `[first, last)` 
        that is greater than `value`. while `lower_bound` returns an iterator pointing to the first 
        element that is not less than `value`. Otherwise `last` if no such element is found.
        `equal_range` returns a range containing all elements equivalent to value in the range [first, last).
        If there are no elements not less than value, `last` is returned as the first element. 
        Similarly if there are no elements greater than value, `last` is returned as the second element

        comp - binary predicate which returns ​true if the first argument is less than the second. 
        
        Elements in the range `[first, last)` must be sorted using `comp`.

        Complexity: :math:`\log_2(last-first) + O(1)`

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
