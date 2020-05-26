Protocol Buffers - Google's data interchange format
===================================================


#. error: AC_CONFIG_MACRO_DIRS([m4]) conflicts with ACLOCAL_AMFLAGS=-I m4

    A line-ending problem

#. PB to install static libraries only using: ``./configure --disable-shared``
#. PB to specify install location: ``./configure --prefix=/path/to/installation``

#. protoc: error while loading shared libraries: libprotoc.so.23: cannot open shared object file: No such file or directory

    Solution: ``export LD_LIBRARY_PATH=/usr/local/lib``


.. rubric:: Footnotes

.. [#] `Protocol Buffers <https://github.com/protocolbuffers/protobuf.git>`_
.. [#] `Protocol Buffers CPP tutorial <https://developers.google.com/protocol-buffers/docs/cpptutorial>`_
