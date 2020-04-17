****************
Network Commands
****************

#. Ubuntu to get current username.

    .. code-block:: sh

        $ whoami
        beats

#. hostname note

    .. code-block:: sh

        $ hostname --help
        Program options:
            -a, --alias            alias names
            -A, --all-fqdns        all long host names (FQDNs)
            -b, --boot             set default hostname if none available
            -d, --domain           DNS domain name
            -f, --fqdn, --long     long host name (FQDN)
            -F, --file             read host name or NIS domain name from given file
            -i, --ip-address       addresses for the host name
            -I, --all-ip-addresses all addresses for the host
            -s, --short            short host name
            -y, --yp, --nis        NIS/YP domain name

        # get IP address
        $ hostname -I
        192.168.198.130

        # get computer name
        $ hostname -a
        dream-lover
        $ hostname -f
        dream-lover.example.com

#. uname note

    .. code-block:: sh

        $ uname --help
          -a, --all                print all information, in the following order,
                                     except omit -p and -i if unknown:
          -s, --kernel-name        print the kernel name
          -n, --nodename           print the network node hostname
          -r, --kernel-release     print the kernel release
          -v, --kernel-version     print the kernel version
          -m, --machine            print the machine hardware name
          -p, --processor          print the processor type or "unknown"
          -i, --hardware-platform  print the hardware platform or "unknown"
          -o, --operating-system   print the operating system

        $ uname -n
        dream-lover

#. Ubuntu to change host name without reboot.

    .. code-block:: sh

        natsume@ubuntu:etc$ hostnamectl
           Static hostname: ubuntu
                 Icon name: computer-vm
                   Chassis: vm
                Machine ID: e614c5f076c64bc4a90230c0c04a0dc6
                   Boot ID: 5d90532e43874b6a9a6356b34a02e028
            Virtualization: vmware
          Operating System: Ubuntu 16.04.5 LTS
                    Kernel: Linux 4.15.0-43-generic
              Architecture: x86-64

        $ hostnamectl --help
        hostnamectl [OPTIONS...] COMMAND ...

        Query or change system hostname.
            -h --help              Show this help
               --version           Show package version
               --no-ask-password   Do not prompt for password
            -H --host=[USER@]HOST  Operate on remote host
            -M --machine=CONTAINER Operate on local container
               --transient         Only set transient hostname
               --static            Only set static hostname
               --pretty            Only set pretty hostname

        Commands:
            status                 Show current hostname settings
            set-hostname NAME      Set system hostname
            set-icon-name NAME     Set icon name for host
            set-chassis NAME       Set chassis type for host
            set-deployment NAME    Set deployment environment for host
            set-location NAME      Set location for host

        $ hostnamectl set-hostname mlubuntu
        $ hostname
        mlubuntu

#. netstat note

    .. code-block:: sh

        # lo means loopback interface, en means ethernet interface

        $ netstat -ni
        Name  Mtu   Network       Address            Ipkts Ierrs    Opkts Oerrs  Coll
        lo0   16384 127           127.0.0.1        1147015     -  1147015     -     -
        en0   1500  fe80::1060: fe80:4::1060:d416  4833405     -  3764022     -
        ...

        $ netstat -rn
        Routing tables

        Internet:
        Destination        Gateway            Flags        Refs      Use   Netif Expire
        default            172.17.0.1         UGSc            5        0     en0
        127                127.0.0.1          UCS             0        0     lo0
        127.0.0.1          127.0.0.1          UH              1   413730     lo0
        ...

        $ netstat -f inet -p tcp
        Active Internet connections
        Proto Recv-Q Send-Q  Local Address          Foreign Address        (state)
        tcp4       0      0  172.17.56.124.56377    17.188.165.202.5223    ESTABLISHED
        tcp4       0      0  172.17.56.124.56372    17.57.145.72.5223      ESTABLISHED

#. ifconfig note

    .. code-block:: sh

        $ ifconfig lo0
        lo0: flags=8049<UP,LOOPBACK,RUNNING,MULTICAST> mtu 16384
            options=1203<RXCSUM,TXCSUM,TXSTATUS,SW_TIMESTAMP>
            inet 127.0.0.1 netmask 0xff000000
            inet6 ::1 prefixlen 128
            inet6 fe80::1%lo0 prefixlen 64 scopeid 0x1
            nd6 options=201<PERFORMNUD,DAD>

        $ ifconfig en0
        en0: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500
            ether ac:bc:32:ad:b7:81
            inet6 fe80::1060:d416:a6b1:64d8%en0 prefixlen 64 secured scopeid 0x4
            inet 172.17.56.124 netmask 0xffff0000 broadcast 172.17.255.255
            nd6 options=201<PERFORMNUD,DAD>
            media: autoselect
            status: active

#. find the IP of hosts on the LAN

    .. code-block:: sh

        $ ping -b 127.0.0.1 # not work on macos

