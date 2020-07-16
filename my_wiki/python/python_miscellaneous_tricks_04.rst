******************************
Python Miscellaneous Tricks 04
******************************

#. Sublime to set python3 as the defaul builder for python scripts

   `Tools` - `Build System` - `New Build System`, and paste follow code::

        {
            "cmd": ["/path/to/python3", "-u", "$file"],
            "file_regex": "^ ]*File \"(...*?)\", line ([0-9]*)",
            "selector": "source.python"
        }

   save it as `python3` and choose it as defaul build system.

#. No `xrange` function in Python3 any more, use `range` instead

#. sklearn.model_selection.ParameterGrid

    .. code-block:: py

        >>> from sklearn.model_selection import ParameterGrid
        >>> param_grid = {'a': [1, 2], 'b': [True, False]}
        >>> list(ParameterGrid(param_grid)) == (
        ...    [{'a': 1, 'b': True}, {'a': 1, 'b': False},
        ...     {'a': 2, 'b': True}, {'a': 2, 'b': False}])
        True

#. Python `tkinter` import error

    Python2: ``sudo apt install python-tk``.

    Python3: ``sudo apt install python3-tk``.

#. Python to get combinations of `list`

    .. code-block:: py

        import itertools
        help(itertools.combinations)

        # combinations(iterable, r) --> combinations object
        # Return successive r-length combinations of elements in the iterable.

        >>> list(itertools.combinations(range(iris.data.shape[1]), 2))
        [(0, 1), (0, 2), (0, 3), (1, 2), (1, 3), (2, 3)]

#. Python `smtpd`

    Solution: ``python -m smtpd --help``

#. Python SimpleHTTPServer

    Solution: ``python -m SimpleHTTPServer 3456``

    Browser: ``http://127.0.0.1:3456/``

#. Python to start interpreter without reading `$PYTHONSTARTUP` file

    .. code-block:: sh

        python3 -ic ''

        # -i
        # When a script is passed as first argument or the -c option is used,
        # enter interactive mode after executing the script or the command.
        # It does not read the $PYTHONSTARTUP file.
        #
        # -c command
        # Specify  the command to execute (see next section).

#. Numpy Bernoulli random generator

    .. code-block:: sh

        np.random.choice([0, 1], size=200, p=[0.7, 0.3])

        # sample for 200 examples, outputing 1 with a probability of 0.3
        # and 0 with 0.7

#. Python to reload a module

    .. code-block:: py

        # python 2.x
        reload(module)

        # python 3.x
        import importlib
        importlib.reload(module)

#. Text progress bar example

    .. code-block:: py

        chapter_name = 'volume-01'
        total = 1000
        width = len(str(total))
        current, remains = 1, total-1
        for url in page_urls:
            progress = '\rDownloading {}, current {:{}}, remain {:{}}'.format(chapter_name, current, width, remains, width)
            sys.stdout.write(progress)
            sys.stdout.flush()

            time.sleep(1)

            current += 1
            remains -= 1

        sys.stdout.write('\rFinish downloading {}, total {} pictures.{}'.format(chapter_name, total, ' ' * 100))
        sys.stdout.flush()
        print()

#. Python process pool

    .. code-block:: py

        from multiprocessing import Pool

        def f(x): return x*x

        with Pool(5) as p:
            p.map(f, range(10))


#. Reason to inherit from *object* when creating *class*

    In Python 3.x, it is not necessary because the language
    has done this behind the scene, and ``class newClass(object)``
    is written for compability with Python 2.x.

    In Python 2.x, it makes a big difference whether a class is
    inherited from *object*, classes defined with ``class newClass``
    are "classic" classes, while classes with ``classs newClass(object)``
    new classes. for more detatils refer to here [#python_class_inherits_object]_.

#. Python interpreter to print function definition

    .. code-block:: py

        # works only for objects that are imported
        >>> import re, inspect
        >>> print(inspect.getsource(re.compile))
        def compile(pattern, flags=0):
            "Compile a regular expression pattern, returning a pattern object."
            return _compile(pattern, flags)

#. Macos to install pip2

    .. code-block:: py

        curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
        sudo -H python get-pip.py

        # add installation path to you PATH if you encounter
        # WARNING: The scripts pip, pip2 and pip2.7 are installed in '/Users/cherry/Library/Python/2.7/bin'
        # which is not on PATH. Consider adding this directory to PATH

#. Python to calulate similarity ration between 2 sentences

    .. code-block:: py

        >>> import difflib
        >>> s1 = '社交网络'
        >>> s2 = '人际交往'
        >>> s3 = '社交活动'
        >>> def similarity(s1, s2):
        ...     return difflib.SequenceMatcher(None, s1, s2).ratio()
        ...
        >>> similarity(s1, s2)
        0.25
        >>> similarity(s1, s3)
        0.5
        >>> similarity(s2, s3)
        0.25
        >>> similarity(s2, s1)
        0.25

#. UnicodeDecodeError: 'utf-8' codec can't decode byte 0xc2 in position 63: invalid continuation byte

    You should ``open()`` file with ``encoding``. And you can check file encoding with

    .. code-block:: sh
        
        $ file -i perf.log.2020071618 
        perf.log.2020071618: text/plain; charset=iso-8859-1
    

.. rubric:: Footnotes

.. [#python_class_inherits_object] https://stackoverflow.com/questions/4015417/python-class-inherits-object.
