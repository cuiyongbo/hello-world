Redis-cli Note
==============

#. Show help about Redis command

    *redis-cli* provides online help for most Redis commands,
    using the ``help`` command. The command can be used in two forms:

        - ``help @<category>`` shows all the commands about a given category.
          The categories are: @generic, @list, @set, @sorted_set, @hash, @pubsub,
          @transactions, @connection, @server, @scripting, @hyperloglog.

        - ``help <commandname>`` shows specific help for the command given as argument.

#. Clear the terminal screen

    - ``clear`` command
    - CTRL + L

#. History and completion

    You can access a history of commands executed, in order to avoid retyping
    them again and again, by pressing the arrow keys (up and down). The history
    is preserved between restarts of the CLI, in a file called ``.rediscli_history``
    inside the user home directory.

    It is possible to use a different history filename by setting the ``REDISCLI_HISTFILE`` environment variable, and disable it by setting it to ``/dev/null``.

    The CLI is also able to perform command names completion by pressing the *TAB* key.

#. Run the same command N times

    It's possible to run the same command multiple times by
    prefixing the comand name by a number. e.g.

    .. code-block:: sh

        127.0.0.1:6379> 5 incr mycounter
        (integer) 1
        (integer) 2
        (integer) 3
        (integer) 4
        (integer) 5

#. General commands

    - type
    - exists, del
    - expire, pexpire, persist, ttl
    - expireat, pexpireat
    - rename
    - keys
