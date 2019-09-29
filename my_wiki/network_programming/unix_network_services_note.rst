**********************
Unix Internet services
**********************

#. install xinetd: ``sudo apt install xinetd``

#. view supported services

    .. code-block:: sh

        $ pwd
        /etc/xinet.d

        $ ls
        chargen  chargen-udp  daytime  daytime-udp  discard  discard-udp
        echo  echo-udp  servers  services  time  time-udp

#. enable or disable a service

    .. code-block:: sh

        # default: off
        # description: An xinetd internal service which generate characters.  The
        # xinetd internal service which continuously generates characters until the
        # connection is dropped.  The characters look something like this:
        # !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefg
        # This is the tcp version.
        service chargen
        {
            disable         = no
            type            = INTERNAL
            id              = chargen-stream
            socket_type     = stream
            protocol        = tcp
            user            = root
            wait            = no
        }

        # This is the udp version.
        service chargen
        {
            disable         = yes
            type            = INTERNAL
            id              = chargen-dgram
            socket_type     = dgram
            protocol        = udp
            user            = root
            wait            = yes
        }

#. restart xinetd after modifying the configure: ``sudo service restart xinetd``

#. test services

    .. code-block:: sh

        # you may need install telnetd
        telnet localhost daytime
