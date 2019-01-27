**********************
numpy Function Note 02
**********************

.. function:: numpy.ones(shape, dtype=None, order='C')

    Return a new array of given shape and type, filled with ones.
    
    Parameters::

        shape : int or sequence of ints
            Shape of the new array, e.g., ``(2, 3)`` or ``2``.
        dtype : data-type, optional
            The desired data-type for the array, e.g., `numpy.int8`.  Default is
            `numpy.float64`.
        order : {'C', 'F'}, optional, default: C
            Whether to store multi-dimensional data in row-major
            (C-style) or column-major (Fortran-style) order in
            memory.
    
    Examples::

        >>> np.ones(5)
        array([ 1.,  1.,  1.,  1.,  1.])
        >>> np.ones((2, 1))
        array([[ 1.],
               [ 1.]])

.. function:: numpy.zeros(shape, dtype=None, order='C')

    Similar to ``numpy.ones()``, but filled with zeros.

.. function:: numpy.empty(shape, dtype=float, order='C')
    
    Ditto, bute without initializing entries.

.. function:: numpu.full(shape, fill_value, dtype=None, order='C')

    Return a new array of given shape and type, filled with `fill_value`.
    
    Parameters::

        shape : int or sequence of ints
            Shape of the new array, e.g., ``(2, 3)`` or ``2``.
        fill_value : scalar
            Fill value.
        dtype : data-type, optional
            The desired data-type for the array  The default, `None`, means
             `np.array(fill_value).dtype`.
        order : {'C', 'F'}, optional
            Whether to store multidimensional data in C- or Fortran-contiguous
            (row- or column-wise) order in memory.
    
    Examples::

        >>> np.full((2, 2), np.inf)
        array([[ inf,  inf],
               [ inf,  inf]])
        >>> np.full((2, 2), 10)
        array([[10, 10],
               [10, 10]])

.. function:: numpy.full_like(a, fill_value, dtype=None, order='K', subok=True)
    
    Return a full array with the same shape and type as a given array.
    
    Parameters::

        a : array_like
            The shape and data-type of `a` define these same attributes of
            the returned array.
        order : {'C', 'F', 'A', or 'K'}, optional
            Overrides the memory layout of the result. 'C' means C-order,
            'F' means F-order, 'A' means 'F' if `a` is Fortran contiguous,
            'C' otherwise. 'K' means match the layout of `a` as closely
            as possible.
        subok : bool, optional.
            If True, then the newly created array will use the sub-class
            type of 'a', otherwise it will be a base-class array. Defaults
            to True.
    
    Examples::

        >>> x = np.arange(6, dtype=int)
        >>> np.full_like(x, 1)
        array([1, 1, 1, 1, 1, 1])
        >>> np.full_like(x, 0.1)
        array([0, 0, 0, 0, 0, 0])
        >>> np.full_like(x, 0.1, dtype=np.double)
        array([ 0.1,  0.1,  0.1,  0.1,  0.1,  0.1])
        >>> np.full_like(x, np.nan, dtype=np.double)
        array([ nan,  nan,  nan,  nan,  nan,  nan])
        >>> y = np.arange(6, dtype=np.double)
        >>> np.full_like(y, 0.1)
        array([ 0.1,  0.1,  0.1,  0.1,  0.1,  0.1])

.. function:: numpy.empty_like(prototype, dtype=None, order='K', subok=True)
.. function:: numpy.ones_like(a, dtype=None, order='K', subok=True)
.. function:: numpy.ones_like(a, dtype=None, order='K', subok=True)

    Ditto.

.. function:: numpy.eye(N, M=None, k=0, dtype=<class 'float'>, order='C')

    Return a 2-D array of shape (N, M) with ones on the diagonal and zeros elsewhere.

    Parameters::

        N : int
          Number of rows in the output.
        M : int, optional
          Number of columns in the output. If None, defaults to `N`.
        k : int, optional
          Index of the diagonal: 0 (the default) refers to the main diagonal,
          a positive value refers to an upper diagonal, and a negative value
          to a lower diagonal.
    
    Examples::

        >>> np.eye(2, dtype=int)
        array([[1, 0],
               [0, 1]])
        >>> np.eye(3, k=1)
        array([[ 0.,  1.,  0.],
               [ 0.,  0.,  1.],
               [ 0.,  0.,  0.]])
        >>> np.eye(3, k=-1)
        array([[0., 0., 0.],
               [1., 0., 0.],
               [0., 1., 0.]])

.. function:: numpy.diag(v, k=0)

    Extract a diagonal or construct a diagonal array.
    
    Parameters::
        
        v : array_like
            If `v` is a 2-D array, return a copy of its `k`-th diagonal.
            If `v` is a 1-D array, return a 2-D array with `v` on the `k`-th
            diagonal.
        k : int, optional
            Diagonal in question. The default is 0. Use `k>0` for diagonals
            above the main diagonal, and `k<0` for diagonals below the main
            diagonal.
    
    See Also
    --------
    diagonal : Return specified diagonals.
    diagflat : Create a 2-D array with the flattened input as a diagonal.
    trace : Sum along diagonals.
    triu : Upper triangle of an array.
    tril : Lower triangle of an array.
    
    Examples::

        >>> x = np.arange(9).reshape((3,3))
        >>> x
        array([[0, 1, 2],
               [3, 4, 5],
               [6, 7, 8]])
        
        >>> np.diag(x)
        array([0, 4, 8])
        >>> np.diag(x, k=1)
        array([1, 5])
        >>> np.diag(x, k=-1)
        array([3, 7])

        >>> np.triu(x)
        array([[0, 1, 2],
               [0, 4, 5],
               [0, 0, 8]])
        >>> np.tril(x)
        array([[0, 0, 0],
               [3, 4, 0],
               [6, 7, 8]])
        >>> np.trace(x)
        12


        
        >>> np.diag(np.diag(x))
        array([[0, 0, 0],
               [0, 4, 0],
               [0, 0, 8]])

.. function:: numpy.random.randn(d0, d1, ..., dn)
    
    Return a sample (or samples) from the **standard normal distribution**.
    
    If positive, int_like or int-convertible arguments are provided,
    `randn` generates an array of shape ``(d0, d1, ..., dn)``, filled
    with random floats sampled from a univariate "normal" (Gaussian)
    distribution of mean 0 and variance 1 (if any of the :math:`d_i` are
    floats, they are first converted to integers by truncation). A single
    float randomly sampled from the distribution is returned if no
    argument is provided.
    
    This is a convenience function.  If you want an interface that takes a
    tuple as the first argument, use `numpy.random.standard_normal` instead.

    **Notes:** For random samples from :math:`N(\mu, \sigma^2)`,
    use: ``sigma * np.random.randn(...) + mu``.
    
    .. code-block:: py

        >>> np.random.randn()
        0.645152545916444

        # 2x4 arrary of sample from N(3, 6.25)
        >>> 2.5*np.random.randn(2, 4) + 3
        array([[ 0.18939233,  6.93669676,  5.05530613,  8.76836426],
           [-1.23591564,  4.20677073, -0.70279898,  4.72307524]])

        >>> np.random.standard_normal()
        0.38136833834275696
        >>> np.random.standard_normal((1, 5)).shape
        (1, 5)

.. function:: numpy.random.standard_normal(size=None)

    Draw samples from a standard Normal distribution (mean=0, stdev=1).

    Same as `numpy.random.randn` but take tuple as input.

.. function:: numpy.sum(a, axis=None, dtype=None, out=None, keepdims=<no value>, initial=<no value>)

    Sum of array elements over a given axis.

    .. code-block:: py

        >>> np.sum([[0, 1], [0, 5]])
        6
        >>> np.sum([[0, 1], [0, 5]], axis=0)
        array([0, 6])
        >>> np.sum([[0, 1], [0, 5]], axis=1)
        array([1, 5])
        >>> np.sum([10], initial=5)
        15
        >>> np.sum([10], dtype=np.float32)
        10.0

.. function:: numpy.argmax(a, axis=None, out=None)
.. function:: numpy.argmin(a, axis=None, out=None)

    Returns the indices of the maximum/minimum values along an axis.
    Same as `ndarray.argmax, argmin`.