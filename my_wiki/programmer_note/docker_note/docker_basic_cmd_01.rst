Docker Basics 01
================

#. command help

    .. code-block:: bash

        $ docker --help

        Usage:  docker [OPTIONS] COMMAND

        A self-sufficient runtime for containers

        Options:
        -H, --host list          Daemon socket(s) to connect to
        -v, --version            Print version information and quit
        ...

        Management Commands:
        app*        Docker App (Docker Inc., v0.9.1-beta3)
        builder     Manage builds
        buildx*     Build with BuildKit (Docker Inc., v0.5.1-docker)
        config      Manage Docker configs
        ...

        Commands:
        attach      Attach local standard input, output, and error streams to a running container
        build       Build an image from a Dockerfile
        commit      Create a new image from a container's changes
        cp          Copy files/folders between a container and the local filesystem
        ...

        Run 'docker COMMAND --help' for more information on a command.

    $ docker help run

    Usage:  docker run [OPTIONS] IMAGE [COMMAND] [ARG...]

    Run a command in a new container

    Options:
        --add-host list                  Add a custom host-to-IP mapping (host:ip)
        -a, --attach list                    Attach to STDIN, STDOUT or STDERR
        ...

#. list docker container information

    .. code-block:: bash

        $ docker help ps

        Usage:  docker ps [OPTIONS]

        List containers

        Options:
            -a, --all             Show all containers (default shows just running)
            -f, --filter filter   Filter output based on conditions provided
                --format string   Pretty-print containers using a Go template
            -n, --last int        Show n last created containers (includes all states) (default -1)
            -l, --latest          Show the latest created container (includes all states)
                --no-trunc        Don't truncate output
            -q, --quiet           Only display container IDs
            -s, --size            Display total file sizes

        $ docker ps
        CONTAINER ID   IMAGE                    COMMAND                  CREATED       STATUS      PORTS                NAMES
        178d57e07a45   docker/getting-started   "nginx -g 'daemon of…"   2 weeks ago   Up 2 days   0.0.0.0:80->80/tcp   heuristic_hopper

#. run a docker container

    .. code-block:: bash
        
        $ docker help exec

        Usage:  docker exec [OPTIONS] CONTAINER COMMAND [ARG...]

        Run a command in a running container

        Options:
            -d, --detach               Detached mode: run command in the background
                --detach-keys string   Override the key sequence for detaching a container
            -e, --env list             Set environment variables
                --env-file list        Read in a file of environment variables
            -i, --interactive          Keep STDIN open even if not attached
                --privileged           Give extended privileges to the command
            -t, --tty                  Allocate a pseudo-TTY
            -u, --user string          Username or UID (format: <name|uid>[:<group|gid>])
            -w, --workdir string       Working directory inside the container

        $ docker exec -it heuristic_hopper /bin/bash

