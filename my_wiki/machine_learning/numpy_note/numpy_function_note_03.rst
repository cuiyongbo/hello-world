**********************
numpy Function Note 03
**********************

.. function:: numpy.sum(a, axis=None, dtype=None, out=None, keepdims=<no value>, initial=<no value>)
.. function:: numpy.nansum(a, axis=None, dtype=None, out=None, keepdims=<no value>)

    Sum of array elements over a given axis. 
    `numpy.nansum` ditto except treating :abbr:`NaNs (Not a Numbers)` as zero.

    .. code-block:: py

        >>> np.sum([[0, 1], [0, 5]])
        6
        >>> np.sum([[0, 1], [0, 5]], axis=0)
        array([0, 6])
        >>> np.sum([[0, 1], [0, 5]], axis=1)
        array([1, 5])
        >>> np.sum([10], initial=5)
        15

.. function:: numpy.cumsum(a, axis=None, dtype=None, out=None)
.. function:: numpy.nancumsum(a, axis=None, dtype=None, out=None)

    Return the cumulative sum of the elements along a given axis.
    `numpy.nancumsum` ditto except treating :abbr:`NaNs (Not a Numbers)` as zero.

    .. code-block:: py

        >>> np.cumsum([1, np.nan, 2])
        array([ 1., nan, nan])
        >>> np.nancumsum([1, np.nan, 2])
        array([1., 1., 3.])