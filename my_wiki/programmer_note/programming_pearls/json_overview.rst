*************
Json Overview
*************

:abbr:`JSON (JavaScript Object Notation)` is a lightweight data-interchange format.
It is easy for humans to read and write. It is easy for machines to parse and generate.
It is based on a subset of the JavaScript Programming Language, **JSON is a text format**
that is completely language independent but uses conventions that are familiar to programmers
of the C-family of languages, including C, C++, C#, Java, JavaScript, Perl, Python, and many others.
These properties make JSON an ideal data-interchange language.

JSON is built on two structures:

   * A collection of name/value pairs. In various languages, this is realized as
     an object, record, struct, dictionary, hash table, keyed list, or associative array.

   * An ordered list of values. In most languages, this is realized as an array, vector, list, or sequence.

These are universal data structures. Virtually all modern programming languages support them in one form or another.
It makes sense that a data format that is interchangeable with programming languages also be based on these structures.

.. image:: images/json_object.gif
.. image:: images/json_array.gif
.. image:: images/json_value.gif
.. image:: images/json_string.gif
.. image:: images/json_number.gif


#. JSON does not support comments

#. Python type VS JSON type conversion table

   +-------------------+---------------+
   | Python            | JSON          |
   +===================+===============+
   | dict              | object        |
   +-------------------+---------------+
   | list, tuple       | array         |
   +-------------------+---------------+
   | str, unicode      | string        |
   +-------------------+---------------+
   | int, long, float  | number        |
   +-------------------+---------------+
   | True              | true          |
   +-------------------+---------------+
   | False             | false         |
   +-------------------+---------------+
   | None              | null          |
   +-------------------+---------------+

   .. note::

      Locate module::

         >>> json.__file__
         '/usr/lib/python2.7/json/__init__.pyc'


#. python `json` api

   .. function:: json.dump(obj, fp, **options)

      Serialize `obj` as a JSON formatted stream to `fp`.

   .. function:: json.dumps(obj, **options)

      Serialize `obj` to a JSON formatted string.

   .. function:: json.load(fp[, *options])

      Deserialize `fp` (a .read()-supporting file-like object containing a JSON document) to a Python object.

   .. function:: json.loads(s[, *options])

      Deserialize `s` (a str or unicode instance containing a JSON document) to a Python object.
