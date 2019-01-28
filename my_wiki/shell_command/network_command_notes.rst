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