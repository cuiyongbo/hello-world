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

#.  No `xrange` function in Python3 any more, use `range` instead