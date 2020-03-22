******************************
Python collections Module Note
******************************

#. ``defaultdict`` example

    Using ``list`` as the ``default_factory``, it is easy to group a sequence of key-value pairs
    into a dictionary of lists.

    .. code-block:: py

        >>> s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
        >>> d = defaultdict(list)
        >>> for k, v in s:
        ...     d[k].append(v)
        ...
        >>> d
        defaultdict(<class 'list'>, {'yellow': [1, 3], 'blue': [2, 4], 'red': [1]})

    Setting the ``default_factory`` to ``set`` makes the defaultdict useful for building a dictionary of sets:

    .. code-block:: py

        >>> s = [('red', 1), ('blue', 2), ('red', 3), ('blue', 4), ('red', 1), ('blue', 4)]
        >>> d = defaultdict(set)
        >>> for k, v in s:
        ...     d[k].add(v)
        ...
        >>> sorted(d.items())
        [('blue', {2, 4}), ('red', {1, 3})]

    Setting the ``default_factory`` to ``int`` makes the defaultdict useful for counting:

    .. code-block:: py

        >>> s = 'mississippi'
        >>> d = defaultdict(int)
        >>> for k in s:
        ...     d[k] += 1
        ...
        >>> sorted(d.items())
        [('i', 4), ('m', 1), ('p', 2), ('s', 4)]

    The function ``int()`` which always returns zero is just a special case of constant functions.
    A faster and more flexible way to create constant functions is to use a lambda function which
    can supply any constant value (not just zero):

    .. code-block:: py

        >>> def constant_factory(value):
        ...     return lambda: value
        ...
        >>> d = defaultdict(constant_factory('<missing>'))
        >>> d.update(name="John", action="run")
        >>> '%(name)s %(action)s to %(object)s' % d
        'John run to <missing>'
        >>> s
        'mississippi'
        >>> d = defaultdict(constant_factory(4))
        >>> for k in s: d[k] += 1
        >>> sorted(d.items())
        [('i', 8), ('m', 5), ('p', 6), ('s', 8)]


#. ``Counter`` example

    .. code-block:: py

        >>> from collections import Counter
        >>> l = [1,1,1,2,2,3,3,4,5]
        >>> Counter(l)
        Counter({1: 3, 2: 2, 3: 2, 4: 1, 5: 1})

        >>> s = ['red', 'blue', 'red', 'green', 'blue', 'blue']
        >>> Counter(s)
        Counter({'blue': 3, 'red': 2, 'green': 1})

        >>> import re
        >>> words = re.findall(r'\w+', open("./languages/english_note_book/english_notes_01.rst").read().lower())
        >>> Counter(words).most_common(5)
        [('a', 667), ('the', 598), ('definition', 592), ('usage', 527), ('of', 525)]

