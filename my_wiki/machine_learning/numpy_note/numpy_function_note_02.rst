**********************
numpy Function Note 02
**********************

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