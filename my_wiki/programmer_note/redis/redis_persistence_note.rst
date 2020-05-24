Redis persistence Note
======================

Redis persistence options:

    - :abbr:`RDB (Redis Database)` persistence performs point-in-time snapshots of your DB at specified intervals.

    - :abbr:`AOF (Append-Only File)` persistence logs every write operation received by the server,
      that will be played again at server startup, reconstructing the original dataset. Commands are
      logged using the same format as the Redis protocol itself, in an append-only fashion.
      Redis is able to rewrite the log in the background when it gets too big.

    - It is possible to combine both AOF and RDB in the same instance, where the AOF file will
      be used to reconstruct the original dataset when Redis restarts.

    - You can disable persistence completely if you wish.

#. Snapshotting

    By default Redis saves snapshots of the dataset on disk, in a binary file called ``dump.rdb``.
    Whenever Redis needs to dump the dataset to disk, this is what happens:

        - Redis ``forks``. We now have a child and a parent process.
        - The child starts to write the dataset to a temporary RDB file.
        - When the child is done writing the new RDB file, it replaces the old one.

    This method allows Redis to benefit from :abbr:`COW (copy-on-write)` semantics.

    .. code-block:: none
        :caption: Related ``redis-cli`` commands

        // save (will block main thread)
        void saveCommand(client *c)
            rdbSave(server.rdb_filename,rsiptr)

        // bgsave (fork a child and do the save stuff in that child)
        void bgsaveCommand(client *c)
            rdbSaveBackground(server.rdb_filename,rsiptr)
                redisFork()
                    rdbSave(filename,rsi)

#. SAVE directive in ``redis.conf``

    .. code-block:: none

        ################################ SNAPSHOTTING  ################################
        #
        # Save the DB on disk: save <seconds> <changes>
        #
        #   Will save the DB if both the given number of seconds and the given
        #   number of write operations against the DB occurred.
        #
        #   For example:
        #       ``save 900 1`` means after 900 sec (15 min) if at least 1 key changed
        #       ``save 300 10` after 300 sec (5 min) if at least 10 keys changed
        #
        #   Note: you can disable saving completely by commenting out all "save" lines.
        #
        #   It is also possible to remove all the previously configured save
        #   points by adding a save directive with a single empty string argument
        #   like in the following example: ``save ""``
        save 900 1
        save 300 10
        save 60 10000

        # By default Redis will stop accepting writes if RDB snapshots are enabled
        # (at least one save point) and the latest background save failed.
        # This will make the user aware (in a hard way) that data is not persisting
        # on disk properly, otherwise chances are that no one will notice and some
        # disaster will happen.
        #
        # If the background saving process will start working again Redis will
        # automatically allow writes again.
        #
        # However if you have setup your proper monitoring of the Redis server
        # and persistence, you may want to disable this feature so that Redis will
        # continue to work as usual even if there are problems with disk,
        # permissions, and so forth.
        stop-writes-on-bgsave-error yes

        rdbcompression yes
        rdbchecksum yes

        # The filename where to dump the DB
        dbfilename dump.rdb

        rdb-del-sync-files no

        # The working directory.
        #
        # The DB will be written inside this directory, with the filename specified
        # above using the 'dbfilename' configuration directive.
        #
        # The Append Only File will also be created inside this directory.
        #
        # Note that you must specify a directory here, not a file name.
        dir ./

#. AOF mode in ``redis.conf``

    .. code-block:: none

        ############################## APPEND ONLY MODE ###############################
        # By default Redis asynchronously dumps the dataset on disk. This mode is
        # good enough in many applications, but an issue with the Redis process or
        # a power outage may result into a few minutes of writes lost (depending on
        # the configured save points).
        #
        # The Append Only File is an alternative persistence mode that provides
        # much better durability. For instance using the default data fsync policy
        # (see later in the config file) Redis can lose just one second of writes in a
        # dramatic event like a server power outage, or a single write if something
        # wrong with the Redis process itself happens, but the operating system is
        # still running correctly.
        #
        # AOF and RDB persistence can be enabled at the same time without problems.
        # If the AOF is enabled on startup Redis will load the AOF, that is the file
        # with the better durability guarantees.
        #
        # Please check http://redis.io/topics/persistence for more information.

        appendonly no
        appendfilename "appendonly.aof"

        # The fsync() call tells the Operating System to actually write data on disk
        # instead of waiting for more data in the output buffer. Some OS will really flush
        # data on disk, some other OS will just try to do it ASAP.
        #
        # Redis supports three different modes:
        #
        # no: don't fsync, just let the OS flush the data when it wants. Faster.
        # always: fsync after every write to the append only log. Slow, Safest.
        # everysec: fsync only one time every second. Compromise.
        #
        # The default is "everysec", as that's usually the right compromise between
        # speed and data safety. It's up to you to understand if you can relax this to
        # "no" that will let the operating system flush the output buffer when
        # it wants, for better performances (but if you can live with the idea of
        # some data loss consider the default persistence mode that's snapshotting),
        # or on the contrary, use "always" that's very slow but a bit safer than
        # everysec.
        #
        # More details please check the following article:
        # http://antirez.com/post/redis-persistence-demystified.html
        #
        # If unsure, use "everysec".

        # appendfsync always
        appendfsync everysec
        # appendfsync no

        # When the AOF fsync policy is set to always or everysec, and a background
        # saving process (a background save or AOF log background rewriting) is
        # performing a lot of I/O against the disk, in some Linux configurations
        # Redis may block too long on the fsync() call. Note that there is no fix for
        # this currently, as even performing fsync in a different thread will block
        # our synchronous write(2) call.
        #
        # In order to mitigate this problem it's possible to use the following option
        # that will prevent fsync() from being called in the main process while a
        # BGSAVE or BGREWRITEAOF is in progress.
        #
        # This means that while another child is saving, the durability of Redis is
        # the same as "appendfsync none". In practical terms, this means that it is
        # possible to lose up to 30 seconds of log in the worst scenario (with the
        # default Linux settings).
        #
        # If you have latency problems turn this to "yes". Otherwise leave it as
        # "no" that is the safest pick from the point of view of durability.

        no-appendfsync-on-rewrite no

        auto-aof-rewrite-percentage 100
        auto-aof-rewrite-min-size 64mb
        aof-load-truncated yes
        aof-use-rdb-preamble yes
