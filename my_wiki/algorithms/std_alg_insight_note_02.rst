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

#. partial_sum

    .. code-block:: cpp

        #include <numeric>

        template< class InputIt, class OutputIt >
        OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first );

        template< class InputIt, class OutputIt, class BinaryOperation >
        OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first,
                      BinaryOperation op );


    Computes the partial sums of the elements in the subranges of the range ``[first, last)``
    and writes them to the range beginning at ``d_first.`` The first version uses ``operator+``
    to sum up the elements, which is Equivalent  to:

    .. code-block:: cpp

        *(d_first)   = *first;
        *(d_first+1) = *first + *(first+1);
        *(d_first+2) = *first + *(first+1) + *(first+2);
        *(d_first+3) = *first + *(first+1) + *(first+2) + *(first+3);
        ...

#. accumulate

    .. code-block:: cpp

        #include <numeric>

        template< class InputIt, class T >
        T accumulate( InputIt first, InputIt last, T init );

        template< class InputIt, class T, class BinaryOperation >
        T accumulate( InputIt first, InputIt last, T init, BinaryOperation op );

    Computes the sum of the given value init and the elements in the range ``[first, last).``
    The first version uses ``operator+`` to sum up the elements,
