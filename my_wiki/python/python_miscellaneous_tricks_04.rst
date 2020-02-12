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

#. Python to copy file

    .. code-block:: py

        >>> import shutil
        >>> [p for p in dir(shutil) if 'copy' in p]
        ['copy', 'copy2', 'copyfile', 'copyfileobj', 'copymode', 'copystat', 'copytree']

#. Python to get occurrence map of list

    .. code-block:: py

        >>> from collections import Counter
        >>> l = [1,1,1,2,2,3,3,4,5]
        >>> Counter(l)
        Counter({1: 3, 2: 2, 3: 2, 4: 1, 5: 1})

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
