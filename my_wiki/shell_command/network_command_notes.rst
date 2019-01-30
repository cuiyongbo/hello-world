****************
Network Commands
****************


#. Ubuntu to get current username.

    .. code-block:: sh

        $ whoami
        cuiyb

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
        wl-server-build
        $ hostname -f
        wl-server-build.mapbar.com

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
        wl-server-build

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