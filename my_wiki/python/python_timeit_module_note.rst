*************************
Python timeit Module Note
*************************

.. function:: timeit.timeit(stmt='pass', setup='pass', timer=<default timer>, number=1000000, globals=None)

    Create a Timer instance with the given statement, setup code and timer function
    and run its ``timeit()`` method with ``number`` executions. The optional ``globals`` argument
    specifies a namespace in which to execute the code.

    It returns the time it takes to execute the main statement a number of times, measured in seconds as a float

#. Basics

    .. code-block:: sh

        # Execute from command line
        $ python3 -m timeit 'sum(i for i in range(100))'
        100000 loops, best of 3: 3.24 usec per loop
        $ python3 -m timeit "import time; time.time()"
        1000000 loops, best of 3: 0.438 usec per loop

    .. code-block:: py

        # Execute in interpreter
        >>> import timeit
        >>> timeit.timeit('c in text', setup='text="sample"; c="g"')
        0.020711200000732788

#. import namespace

    .. code-block:: sh

        # access functions you define

        $ cat test.py
        #!/usr/bin/env python3

        import timeit

        def test():
            L = [i for i in range(100)]

        if __name__ == "__main__":
            result = timeit.timeit("test()", setup="from __main__ import test", number=100)
            print("toatl duration: {} ms".format(result*1000))

        $ python3 test.py
        toatl duration: 0.2223999999841908 ms

        # access current global namespace

        $ cat test.py
        #!/usr/bin/env python3

        import timeit, requests

        g_url = "http://www.baidu.com"

        def test():
            req = requests.request("GET", g_url)
            if req.status_code != 200:
                print("request failed because {}".format(req.reason))

        if __name__ == "__main__":
            result = timeit.timeit("test()", globals=globals(), number=100)
            print("toatl duration: {} ms".format(result*1000))

        $ python3 test.py
        toatl duration: 2489.3807000007655 ms

