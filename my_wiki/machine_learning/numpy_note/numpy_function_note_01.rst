**********************
numpy Function Note 01
**********************

.. function:: linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
    
    Return evenly spaced numbers over a specified interval.
    
    Returns `num` evenly spaced samples, calculated over the
    interval [`start`, `stop`].
    
    The endpoint of the interval can optionally be excluded.
    
    Parameters::

        start : scalar
            The starting value of the sequence.
        stop : scalar
            The end value of the sequence, unless `endpoint` is set to False.
            In that case, the sequence consists of all but the last of ``num + 1``
            evenly spaced samples, so that `stop` is excluded. Note that the step
            size changes when `endpoint` is False.
        num : int, optional
            Number of samples to generate. Default is 50. Must be non-negative.
        endpoint : bool, optional
            If True, `stop` is the last sample. Otherwise, it is not included.
            Default is True.
        retstep : bool, optional
            If True, return (`samples`, `step`), where `step` is the spacing
            between samples.
        dtype : dtype, optional
            The type of the output array.  If `dtype` is not given, infer the data
            type from the other input arguments.
    
    Returns::

        samples : ndarray
            There are `num` equally spaced samples in the closed interval
            ``[start, stop]`` or the half-open interval ``[start, stop)``
            (depending on whether `endpoint` is True or False).
        step : float, optional
           Size of spacing between samples. Only returned if `retstep` is True.

    See Also::

        arange : Similar to `linspace`, but uses a step size (instead of the
                 number of samples).
        logspace : Samples uniformly distributed in log space.
        
    Examples::

        >>> np.linspace(2.0, 3.0, num=5)
        array([ 2.  ,  2.25,  2.5 ,  2.75,  3.  ])
        >>> np.linspace(2.0, 3.0, num=5, endpoint=False)
        array([ 2. ,  2.2,  2.4,  2.6,  2.8])
        >>> np.linspace(2.0, 3.0, num=5, retstep=True)
        (array([ 2.  ,  2.25,  2.5 ,  2.75,  3.  ]), 0.25)
        
    Graphical illustration::

        >>> import matplotlib.pyplot as plt
        >>> N = 8
        >>> y = np.zeros(N)
        >>> x1 = np.linspace(0, 10, N, endpoint=True)
        >>> x2 = np.linspace(0, 10, N, endpoint=False)
        >>> plt.plot(x1, y, 'o')
        >>> plt.plot(x2, y + 0.5, 'o')
        >>> plt.ylim([-0.5, 1])
        >>> plt.show()

    .. image:: images/linspace_fig_1.png

.. function:: arange([start,] stop[, step,], dtype=None)
    
    Return evenly spaced values within a given interval.
    
    Values are generated within the half-open interval ``[start, stop)``
    For integer arguments the function is equivalent to the Python built-in
    `range <http://docs.python.org/lib/built-in-funcs.html>`_ function,
    but returns an ndarray rather than a list.
    
    When using a non-integer step, such as 0.1, the results will often not
    be consistent. It is better to use ``linspace`` for these cases.
    
    Parameters::

        start : number, optional
            Start of interval. The interval includes this value. default to 0.
        stop : number
            End of interval. The interval does not include this value, except
            in some cases where `step` is not an integer and floating point
            round-off affects the length of `out`.
        step : number, optional
            Spacing between values. For any output `out`, default to 1.
            If `step` is specified as a position argument, `start` must also be given.
        dtype : dtype
            The type of the output array.
    
    Returns::

        arange : ndarray
            Array of evenly spaced values.
        
            For floating point arguments, the length of the result is
            ``ceil((stop - start)/step)``. Because of floating point overflow,
            this rule may result in the last element of `out` being greater
            than `stop`.
    
    See Also::

        linspace : Evenly spaced numbers with careful handling of endpoints.
        ogrid: Arrays of evenly spaced numbers in N-dimensions.
        mgrid: Grid-shaped arrays of evenly spaced numbers in N-dimensions.
    
    Examples::

        >>> np.arange(3)
        array([0, 1, 2])
        >>> np.arange(3.0)
        array([ 0.,  1.,  2.])
        >>> np.arange(3,7)
        array([3, 4, 5, 6])
        >>> np.arange(3,7,2)
        array([3, 5])

.. function:: reduceat(a, indices, axis=0, dtype=None, out=None)
    
    Performs a (local) reduce with specified slices over a single axis.
    
    For i in ``range(len(indices))``, `reduceat` computes
    ``ufunc.reduce(a[indices[i]:indices[i+1]])``, which becomes the i-th
    generalized "row" parallel to `axis` in the final result (i.e., in a
    2-D array, for example, if `axis = 0`, it becomes the i-th row, but if
    `axis = 1`, it becomes the i-th column).  There are three exceptions to this:
    
    * when ``i = len(indices) - 1`` (so for the last index),
      ``indices[i+1] = a.shape[axis]``.
    * if ``indices[i] >= indices[i + 1]``, the i-th generalized "row" is
      simply ``a[indices[i]]``.
    * if ``indices[i] >= len(a)`` or ``indices[i] < 0``, an error is raised.
    
    The shape of the output depends on the size of `indices`, and may be
    larger than `a` (this happens if ``len(indices) > a.shape[axis]``).
    
    Parameters::

     a : array_like
         The array to act on.
     indices : array_like
         Paired indices, comma separated (not colon), specifying slices to
         reduce.
     axis : int, optional
         The axis along which to apply the reduceat.
     dtype : data-type code, optional
         The type used to represent the intermediate results. Defaults
         to the data type of the output array if this is provided, or
         the data type of the input array if no output array is provided.
     out : ndarray, None, or tuple of ndarray and None, optional
         A location into which the result is stored. If not provided or `None`,
         a freshly-allocated array is returned. For consistency with
         :ref:`ufunc.__call__`, if given as a keyword, this may be wrapped in a
         1-element tuple.
     
    Returns::

        r : ndarray
            The reduced values. If `out` was supplied, `r` is a reference to
            `out`.
    
    Notes::

        A descriptive example:
        
        If `a` is 1-D, the function `ufunc.accumulate(a)` is the same as
        ``ufunc.reduceat(a, indices)[::2]`` where `indices` is
        ``range(len(array) - 1)`` with a zero placed
        in every other element:
        ``indices = zeros(2 * len(a) - 1)``, ``indices[1::2] = range(1, len(a))``.
        
        Don't be fooled by this attribute's name: `reduceat(a)` is not
        necessarily smaller than `a`.

    Examples::

        To take the running sum of four successive values:
        
        >>> np.add.reduceat(np.arange(8),[0,4, 1,5, 2,6, 3,7])[::2]
        array([ 6, 10, 14, 18])
        
        A 2-D example:
        
        >>> x = np.linspace(0, 15, 16).reshape(4,4)
        >>> x
        array([[  0.,   1.,   2.,   3.],
               [  4.,   5.,   6.,   7.],
               [  8.,   9.,  10.,  11.],
               [ 12.,  13.,  14.,  15.]])
        
         # reduce such that the result has the following five rows:
         # [row1 + row2 + row3]
         # [row4]
         # [row2]
         # [row3]
         # [row1 + row2 + row3 + row4]
        
        >>> np.add.reduceat(x, [0, 3, 1, 2, 0])
        array([[ 12.,  15.,  18.,  21.],
               [ 12.,  13.,  14.,  15.],
               [  4.,   5.,   6.,   7.],
               [  8.,   9.,  10.,  11.],
               [ 24.,  28.,  32.,  36.]])
        
         # reduce such that result has the following two columns:
         # [col1 * col2 * col3, col4]
        
        >>> np.multiply.reduceat(x, [0, 3], 1)
        array([[    0.,     3.],
               [  120.,     7.],
               [  720.,    11.],
               [ 2184.,    15.]])

#. Sum array every 10 elements and return a new array
   
   .. code-block:: py

        >>> x = np.linspace(0, 100, 100)
        >>> np.add.reduceat(x, np.arange(0, x.shape[0], 10))
        array([ 45.45454545, 146.46464646, 247.47474747, 348.48484848,
               449.49494949, 550.50505051, 651.51515152, 752.52525253,
               853.53535354, 954.54545455])
