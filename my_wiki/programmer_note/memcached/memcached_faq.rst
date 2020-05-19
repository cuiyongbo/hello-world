Memcached FAQ
=============

#. libmemcached build problem

    - .in'ig.status: error: cannot find input file: Makefile
    - configure: error: cannot find install-sh, install.sh, or shtool in "." "./.." "./../.."
    - autolocal: ' is already registered with AC_CONFIG_FILES
    - $ ./test.py: No such file or directory
    - ...

    Probable due to line ending problem, fix it using: ``find . -maxdepth 1 -type f -exec dos2unix \{\} \;``.

#. error: this statement may fall through [-Werror=implicit-fallthrough=]

    Solution: ``make CFLAGS='-Wno-implicit-fallthrough' CXXFLAGS='-Wno-implicit-fallthrough'``

#. Is memcached atomic?

    Aside from any bugs you may come across, yes all commands are internally atomic.
    Issuing multiple sets at the same time has no ill effect, aside from the last one
    in being the one that sticks.

#. libmemcached build customization

    .. code-block:: sh

        $ ./configure -h

        Usage: ./configure [OPTION]... [VAR=VALUE]...

        To assign environment variables (e.g., CC, CFLAGS...), specify them as
        VAR=VALUE.  See below for descriptions of some of the useful variables.

        Installation directories:
          --prefix=PREFIX         install architecture-independent files in PREFIX
                                  [/usr/local]
          --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                                  [PREFIX]

        By default, `make install' will install all the files in
        `/usr/local/bin', `/usr/local/lib' etc.  You can specify
        an installation prefix other than `/usr/local' using `--prefix',
        for instance `--prefix=$HOME'.

          --enable-shared[=PKGS]  build shared libraries [default=yes]
          --enable-static[=PKGS]  build static libraries [default=yes]

        Some influential environment variables:
          CC          C compiler command
          CFLAGS      C compiler flags
          LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
                      nonstandard directory <lib dir>
          LIBS        libraries to pass to the linker, e.g. -l<library>
          CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
                      you have headers in a nonstandard directory <include dir>
          CPP         C preprocessor
          CXX         C++ compiler command
          CXXFLAGS    C++ compiler flags
          CXXCPP      C++ preprocessor

          LIBEVENT_CPPFLAGS
                      C preprocessor flags for LIBEVENT headers
          LIBEVENT_LDFLAGS
                      linker flags for LIBEVENT libraries

        $ ./configure --prefix=$HOME/third-party/libmemcached LIBS=-levent


#. Build Debuged memcached: ``./configure CFLAGS='-g'``

#. libevent to specify the location to install

    .. code-block:: sh

        $ ./configure -h

        ...

        Optional Features:

          --enable-shared[=PKGS]  build shared libraries [default=yes]
          --enable-static[=PKGS]  build static libraries [default=yes]

        # clean your repository and re-build the project if problems happened
        $ ./configure --prefix=$HOME/third-party/libevent --enable-shared=false

#. libmemcached consistent hashing

    .. note::

        There are two common types of hashing algorithm, consistent and modula.

        With consistent hashing algorithms, the same key when applied to a list
        of servers always uses the same server to store or retrieve the keys,
        even if the list of configured servers changes. This means that you
        can add and remove servers from the configure list and always use the
        same server for a given key.

        Any consistent hashing algorithm has some limitations. When you add servers to
        an existing list of configured servers, keys are distributed to the new servers
        as part of the normal distribution. When you remove servers from the list, the
        keys are re-allocated to another server within the list, meaning that the cache
        needs to be re-populated with the information. Also, a consistent hashing algorithm
        does not resolve the issue where you want consistent selection of a server across
        multiple clients, but where each client contains a different list of servers.
        The consistency is enforced only within a single client.

        If you use only a single memcached instance for each client, or your list of memcached servers
        configured for a client never changes, then the selection of a hashing algorithm is irrelevant,
        as it has no noticeable effect.

        If you change your servers regularly, or you use a common set of servers that are shared among a
        large number of clients, then using a consistent hashing algorithm should help to ensure that your
        cache data is not duplicated and the data is evenly distributed.

    .. code-block:: cpp

        static inline memcached_return_t memcached_send(...)
        {
            uint32_t server_key= memcached_generate_hash_with_redistribution(ptr, group_key, group_key_length);
            memcached_instance_st* instance= memcached_instance_fetch(ptr, server_key);
            ...
        }

        static uint32_t dispatch_host(const Memcached *ptr, uint32_t hash)
        {
            switch (ptr->distribution)
            {
            case MEMCACHED_DISTRIBUTION_CONSISTENT:
            case MEMCACHED_DISTRIBUTION_CONSISTENT_WEIGHTED:
            case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA:
            {
                uint32_t num= ptr->ketama.continuum_points_counter;
                WATCHPOINT_ASSERT(ptr->ketama.continuum);
                memcached_continuum_item_st *begin, *end, *left, *right, *middle;
                begin= left= ptr->ketama.continuum;
                end= right= ptr->ketama.continuum + num;
                while (left < right)
                {
                  middle= left + (right - left) / 2;
                  if (middle->value < hash)
                    left= middle + 1;
                  else
                    right= middle;
                }
                if (right == end)
                  right= begin;
                return right->index;
            }
            ...
        }

#. distributed lock

    Distributed locks are a very useful primitive in many environments
    where different processes must operate with shared resources in a mutually exclusive way.

#. memcached cache hit

    .. code-block:: sh

        telnet ip port
        stats
        ...
        STAT cmd_get 2260
        STAT get_hits 514
        STAT get_misses 1746
        # hit rate = get_hits / cmd_get

.. rubric:: Footnotes

.. [#] https://dev.mysql.com/doc/mysql-ha-scalability/en/ha-memcached-using-hashtypes.html
.. [#] https://redis.io/topics/distlock
.. [#] https://bluxte.net/musings/2009/10/28/simple-distributed-lock-memcached/
