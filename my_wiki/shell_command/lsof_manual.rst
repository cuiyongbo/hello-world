***********
lsof Manual
***********

**Brief**

The Linux lsof command lists information about files that are open by processes running on the system.
(The lsof command itself stands for “list of open files.”)


**Hot Options**

   If any list request option is specified, other list requests must be specifically requested - e.g.,
   if -U is specified for the listing of UNIX socket files, NFS files won't be listed unless -N is also
   specified; or if a user list is specified with the -u option, UNIX domain socket files, belonging
   to users not in the list, won't be listed unless the -U option is also specified.

   Normally list options that are specifically stated are ORed - i.e., specifying the ``-i -ufoo`` options
   produces a listing of all network files OR files belonging to processes owned by user 'foo'.
   The exceptions are::

      1) the '^' (negated) login name or user ID (UID), specified with the -u option;

      2) the '^' (negated) process ID (PID), specified with the -p option;

      3) the '^' (negated) process group ID (PGID), specified with the -g option;

      4) the '^' (negated) command, specified with the -c option;

      5) the ('^') negated TCP or UDP protocol state names, specified with the -s [p:s] option.

   Since they represent exclusions, they are applied without ORing or ANDing and take effect
   before any other selection criteria are applied.

   The -a option may be used to AND the selections.  For example, specifying ``-a -U -ufoo``
   produces a listing of only UNIX socket files that belong to processes owned by user 'foo'.

   **Caution**: the -a option causes all list selection options to be ANDed; it can't be used to cause ANDing
   of selected pairs of selection options by placing it between them, even though its placement there is
   acceptable. ** Wherever -a is placed, it causes the ANDing of all selection options.**

   .. option:: -U

      selects the listing of UNIX domain socket files.

   .. option:: -c c

      selects the listing of files for processes executing the command
      that begins with the characters of c. Multiple commands may be
      specified, using multiple -c options. They are joined in a single ORed set
      before participating in AND option selection.

      If c begins with a '^', then the following characters specify a command name
      whose processes are to be ignored (excluded.)

   .. option:: +c w

      defines the maximum number of initial characters of the name,
      supplied by the UNIX dialect, of the UNIX command associated
      with a process to be printed in the COMMAND column. (The lsof default is nine.)

      Note that many UNIX dialects do not supply all command name characters
      to lsof in the files and structures from which lsof obtains command name.
      Often dialects limit the number of characters supplied in those sources.
      For example, Linux 2.4.27 and Solaris 9 both limit command name length
      to 16 characters.

      If w is zero ('0'), all command characters supplied to lsof
      by the UNIX dialect will be printed.

      If w is less than the length of the column title, "COMMAND",
      it will be raised to that length.

   .. option::  -p s

      excludes or selects the listing of files for the processes whose PID are in the comma-separated set
      s - e.g., "123" or "123,^456". (There should be no spaces in the set.)

   .. option:: -i [i]

      selects the listing of files any of whose Internet address matches the address specified in i.
      If no address is specified, this option selects the listing of all Internet and x.25 (HP-UX) network files.

      If -i4 or -i6 is specified with no following address, only files of the indicated IP version,
      IPv4 or IPv6, are displayed.

      An Internet address is specified in the form (Items in square brackets are optional.)::

         [46][protocol][@hostname|hostaddr][:service|port]

      where::

         46 specifies the IP version, If neither '4' nor
            '6' is specified, the following address
            applies to all IP versions.

         protocol is a protocol name - TCP, UDP

         hostname is an Internet host name.

         hostaddr is a numeric Internet IPv4 address in
              dot form; or an IPv6 numeric address in
              colon form, enclosed in brackets, if the
              UNIX dialect supports IPv6.  When an IP
              version is selected, only its numeric
              addresses may be specified.

         service is an /etc/services name - e.g., smtp or a list of them.

         port is a port number, or a list of them.

         At least one address component - 4, 6, protocol, hostname, hostaddr, or service - must be supplied.
         The '@' character, leading the host specification, is always required; as is the ':', leading the
         port specification.

         Service names and port numbers may be combined in a list whose entries are separated by commas
         and whose numeric range entries are separated by minus signs. There may be no embedded spaces,
         and all service names must belong to the specified protocol.  Since service names may contain
         embedded minus signs, the starting entry of a range can't be a service name; it can be a port
         number, however.

      Here are some sample addresses::

         -i6 - IPv6 only
         TCP:25 - TCP and port 25
         @1.2.3.4 - Internet IPv4 host address 1.2.3.4
         @[3ffe:1ebc::1]:1234 - Internet IPv6 host address [3ffe:1ebc::1], port 1234
         UDP:who - UDP who service port
         TCP@lsof.itap:513 - TCP, port 513 and host name lsof.itap
         tcp@foo:1-10,smtp,99 - TCP, ports 1 through 10, service name smtp, port 99, host name foo
         tcp@bar:1-smtp - TCP, ports 1 through smtp, host bar
         :time - either TCP, UDP or UDPLITE time service port

         $ sudo lsof -i TCP:daytime
         COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
         xinetd  9267 root    5u  IPv4  46946      0t0  TCP *:daytime (LISTEN)


**Example**

#. Basic usage

   .. code-block:: sh

      # List all open files belonging to PID 11925:
      $ lsof -p 11925

      # List all open files belonging to processes owned by the user named "cherry":
      $ lsof -u cherry

      This command lists files that are open in the directory specified
      $ lsof +d '/Users/al' # does not descend into sub-directories
      $ lsof +D '/Users/al' # including sub-directories

      # See what application owns the specific file
      bash-3.00# lsof /var/run/sendmail.pid
      COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
      sendmail 605 root    8wW VREG  281,3       32 8778600 /var/run/sendmail.pid


#. Lsof output with a PID filter and txt file descriptors filtered out.

   .. code-block:: sh

      sh-3.00# lsof -a -p 605 -d ^txt
      COMMAND  PID USER   FD   TYPE  DEVICE SIZE/OFF     NODE NAME
      sendmail 605 root  cwd   VDIR  136,8     1024    23554 /var/spool/mqueue
      sendmail 605 root    0r  VCHR  13,2            6815752 /devices/pseudo/mm@0:null
      sendmail 605 root    1w  VCHR  13,2            6815752 /devices/pseudo/mm@0:null
      ...

   In this example user specifies three parameters to lsof. The first is -a (AND), which means
   that all parameters must hold true for a file to be displayed. The second parameter,
   -p 605, limits the output to PID 605, obtained from the ps command. The final parameter,
   -d ^txt, means that txt records are to be filtered out (the caret [^] means exclude).

   The output gives information about how the process behaves. The application's working directory
   is /var/spool/mqueue, as indicated by the cwd row. File descriptors 0, 1, and 2 are open to
   /dev/null (Solaris makes heavy use of symlinks, which is why the pseudo device is shown).
   FD 3 is a Solaris door (a high-speed Remote Procedure Call (RPC) interface), opened in read-only mode.
   FD 4 is where things get a bit more interesting, since it is a write-only handle to a character device,
   essentially /dev/log. From this, you can gather that the application logs to the UNIX syslog daemon,
   so /etc/syslog.conf dictates the location of the log files.

   As a network application, sendmail listens on network ports. File descriptors 5, 6, and 7 tell you
   that the application is listening on the Simple Mail Transfer Protocol (SMTP) port in both IPv4 and
   IPv6 mode and on the submission port in IPv4 mode. The final file descriptor is write-only and refers
   to /var/run/sendmail.pid. The capital W in the FD column indicates that the application has a write
   lock on the whole file. This file is used to make sure that only one instance of the application
   is open at a time.


#. Find out who is using a file system

   .. code-block:: sh

      bash-3.00# umount /export/home
      umount: /export/home busy
      bash-3.00# lsof /export/home
      COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
      bash    1943 root  cwd   VDIR  136,7     1024    4 /export/home/sean
      bash    2970 sean  cwd   VDIR  136,7     1024    4 /export/home/sean
      ct      3030 sean  cwd   VDIR  136,7     1024    4 /export/home/sean
      ct      3030 sean    1w  VREG  136,7        0   25 /export/home/sean/output

   In this example, a user (sean) is doing some work in his home directory.
   There are two instances of bash (a shell) running, with the current directory
   being sean's home directory. There is also an application named ct that is
   running out of the same directory and has its standard output (file descriptor 1)
   redirected to a file called output. To successfully unmount /export/home, these
   processes must be stopped.


#. Listen on internet

   .. code-block:: sh

      $ lsof -i :52976
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      com.apple 4596 cherry   10u  IPv4 0x760f571332c5b2c5      0t0  TCP macbook-pro.lan:52976->120.92.73.215:xtgui (ESTABLISHED)
      com.apple 4596 cherry   12u  IPv4 0x760f571332c5b2c5      0t0  TCP macbook-pro.lan:52976->120.92.73.215:xtgui (ESTABLISHED)

      $ lsof -i :0-1024
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      loginwind  111 cherry    8u  IPv4 0x760f57132b6a315d      0t0  UDP *:*
      UserEvent  275 cherry    5u  IPv4 0x760f57132b6a503d      0t0  UDP *:*
      SystemUIS  283 cherry   11u  IPv4 0x760f57132b6a199d      0t0  UDP *:*
      ...

      # List open files with udp connection
      $ lsof -i udp
      COMMAND   PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      loginwind 111 cherry    8u  IPv4 0x760f57132b6a315d      0t0  UDP *:*
      UserEvent 275 cherry    5u  IPv4 0x760f57132b6a503d      0t0  UDP *:*
      SystemUIS 283 cherry   11u  IPv4 0x760f57132b6a199d      0t0  UDP *:*
      ...

      # List open files with tcp connection
      $ lsof -i tcp
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      com.apple  505 cherry    4u  IPv4 0x760f57133427dbbd      0t0  TCP macbook-pro.lan:53165->203.208.40.77:https (ESTABLISHED)
      com.apple  505 cherry    6u  IPv4 0x760f57133a5150d5      0t0  TCP macbook-pro.lan:49477->111.206.76.49:https (ESTABLISHED)
      ...

      # List open files with IPV4 address
      c$ lsof -i 4
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      loginwind  111 cherry    8u  IPv4 0x760f57132b6a315d      0t0  UDP *:*
      UserEvent  275 cherry    5u  IPv4 0x760f57132b6a503d      0t0  UDP *:*
      ...
