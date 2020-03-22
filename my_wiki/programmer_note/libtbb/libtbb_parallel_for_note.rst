Parallel_for Note
=================

.. warning::

    Typically a loop needs to take at least a million clock cycles
    to make it worth using ``parallel_for``. e.g. a loop that take at least
    500 microseconds on a 2 GHz processor might benefit from ``parallel_for``.

Let's begin with this code sample:

    .. code-block:: cpp

        void parallel_for_test_classical(int loopCount, int nap_in_millisecond)
        {
            class Scaffold
            {
            public:
                Scaffold(int nap): m_interval(nap) {cout << "constructor" << endl;}
                Scaffold(const Scaffold& rhs): m_interval(rhs.m_interval) {cout << "copy constructor" << endl;}
                ~Scaffold() {cout << "destructor" << endl;}

                void operator() (const tbb::blocked_range<std::size_t> &r) const
                {
                    cout << "chunk size: " << r.size() << endl;
                    for (std::size_t i = r.begin(); i != r.end(); ++i)
                    {
                        usleep(m_interval);
                    }
                }

            private:
                int m_interval;
            };

            const int grainSize = 10;
            tbb::parallel_for(tbb::blocked_range<std::size_t>(0, loopCount, grainSize), Scaffold(nap_in_millisecond));
        }

Now crack the code: ``tbb::parallel_for`` first breaks the iteration space,
going from 0 to ``loopCount`` with a grain size of ``grainSize`` (used for *Controlling Chunking*,
default to 1 if unspecified), into chunks, and then runs each chunk on a separate thread, which calls
the ``Scaffold`` object, in which ``operator()`` processes a chunk.

Simple, isn't it? But you should be aware of more details:

An instance of ``Scaffold`` needs member fields that remember all the local variables that were defined
outside the original loop but used inside it. Usually, ``Scaffold()`` will initialize these fields,
``parallel_for`` requires that the body object have a copy constructor, which is invoked to create a
separate copy (or copies) for each worker thread. It also invokes the destructor to destroy these copies.
In most cases, the implicitly generated copy constructor and destructor work correctly. If they do not,
it is almost always the case (as usual in C++) that you must define both to be consistent.

#. Lambda expressions

    The above code would be much user-friendly if we use ``lambda`` expression:

    .. code-block:: cpp

        void parallel_for_test_lambda(int loopCount, int nap_in_millisecond)
        {
            tbb::blocked_range<size_t> range(0, loopCount);
            tbb::parallel_for(tbb::blocked_range<size_t>(0, loopCount),
                [&] (const tbb::blocked_range<std::size_t> &r) {
                    for (std::size_t i = r.begin(); i != r.end(); ++i)
                    {
                        usleep(nap_in_millisecond);
                    }
            });
        }

#. Automatic chunking

    tbb chooses chunk sizes automatically, depending upon load balancing needs.
    The heuristic attempts to limit overheads while still providing ample opportunities for load balancing.
    The default automatic chunking is recommended for most uses. As with most heuristics, however,
    there are situations where controlling the chunk size more precisely might yield better performance.

#. Controlling Chunking

    Chunking is controlled by a partitioner and a grainsize.To gain the most control over chunking,
    you specify both:

        - Specify partitioner object as the third argument to ``parallel_for``. Doing so turns off automatic chunking.
        - Specify the grainsize when constructing the range.

.. note::

    A general rule of thumb for parallelizing loop nests is to parallelize the outermost one possible.
    The reason is that each iteration of an outer loop is likely to provide a bigger grain of work
    than an iteration of an inner loop.
