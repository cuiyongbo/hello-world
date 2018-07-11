***********
lsof Manual
***********

**Brief**

The Linux lsof command lists information about files that are open by processes running on the system. 
(The lsof command itself stands for “list of open files.”) 


**Hot Options**


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
      sendmail 605 root    2w  VCHR  13,2            6815752 /devices/pseudo/mm@0:null
      sendmail 605 root    3r  DOOR             0t0       58
              /var/run/name_service_door(door to nscd[81]) (FA:->0x30002b156c0)
      sendmail 605 root    4w  VCHR  21,0           11010052 
                              /devices/pseudo/log@0:conslog->LOG
      sendmail 605 root    5u  IPv4 0x300010ea640      0t0      TCP *:smtp (LISTEN)
      sendmail 605 root    6u  IPv6 0x3000431c180      0t0      TCP *:smtp (LISTEN)
      sendmail 605 root    7u  IPv4 0x300046d39c0      0t0      TCP *:submission (LISTEN)
      sendmail 605 root    8wW VREG         281,3       32  8778600 /var/run/sendmail.pid

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
      SystemUIS  283 cherry   12u  IPv4 0x760f57132b6a173d      0t0  UDP *:*
      SystemUIS  283 cherry   16u  IPv4 0x760f57132b6a4b7d      0t0  UDP *:*
      SystemUIS  283 cherry   19u  IPv4 0x760f57132b6a101d      0t0  UDP *:*
      identitys  315 cherry   20u  IPv4 0x760f571329c34f7d      0t0  UDP *:*
      sharingd   333 cherry    4u  IPv4 0x760f57132b1b259d      0t0  UDP *:*
      sharingd   333 cherry    8u  IPv4 0x760f57132b1b27fd      0t0  UDP *:*
      sharingd   333 cherry    9u  IPv4 0x760f571329c3861d      0t0  UDP *:*
      sharingd   333 cherry   10u  IPv4 0x760f571329c38add      0t0  UDP *:*
      sharingd   333 cherry   15u  IPv4 0x760f57132b6a3add      0t0  UDP *:*
      cloudd     346 cherry   12u  IPv4 0x760f5713356ff6a5      0t0  TCP 192.168.199.169:53150->17.248.158.181:https (ESTABLISHED)
      WiFiAgent  400 cherry    5u  IPv4 0x760f57132b6a60dd      0t0  UDP *:*
      com.apple  505 cherry    6u  IPv4 0x760f57133a5150d5      0t0  TCP 192.168.199.169:49477->111.206.76.49:https (ESTABLISHED)
      Python    2041 cherry    5u  IPv4 0x760f571336b290d5      0t0  TCP 192.168.199.169:50896->202.89.233.100:https (ESTABLISHED)
      Python    2662 cherry    5u  IPv4 0x760f5713372a40d5      0t0  TCP 192.168.199.169:51361->202.89.233.101:https (ESTABLISHED)
      Python    4322 cherry    5u  IPv4 0x760f5713331ec2c5      0t0  TCP 192.168.199.169:53144->202.89.233.100:https (SYN_SENT)
      Python    4828 cherry    5u  IPv4 0x760f57133a4e44b5      0t0  TCP 192.168.199.169:53152->202.89.233.100:https (ESTABLISHED)

      # List open files with udp connection
      $ lsof -i udp
      COMMAND   PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      loginwind 111 cherry    8u  IPv4 0x760f57132b6a315d      0t0  UDP *:*
      UserEvent 275 cherry    5u  IPv4 0x760f57132b6a503d      0t0  UDP *:*
      SystemUIS 283 cherry   11u  IPv4 0x760f57132b6a199d      0t0  UDP *:*
      SystemUIS 283 cherry   12u  IPv4 0x760f57132b6a173d      0t0  UDP *:*
      SystemUIS 283 cherry   15u  IPv4 0x760f57132b6a491d      0t0  UDP *:59531
      SystemUIS 283 cherry   16u  IPv4 0x760f57132b6a4b7d      0t0  UDP *:*
      SystemUIS 283 cherry   19u  IPv4 0x760f57132b6a101d      0t0  UDP *:*
      identitys 315 cherry   20u  IPv4 0x760f571329c34f7d      0t0  UDP *:*
      sharingd  333 cherry    4u  IPv4 0x760f57132b1b259d      0t0  UDP *:*
      sharingd  333 cherry    8u  IPv4 0x760f57132b1b27fd      0t0  UDP *:*
      sharingd  333 cherry    9u  IPv4 0x760f571329c3861d      0t0  UDP *:*
      sharingd  333 cherry   10u  IPv4 0x760f571329c38add      0t0  UDP *:*
      sharingd  333 cherry   15u  IPv4 0x760f57132b6a3add      0t0  UDP *:*
      WiFiAgent 400 cherry    5u  IPv4 0x760f57132b6a60dd      0t0  UDP *:*

      # List open files with tcp connection
      $ lsof -i tcp 
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      com.apple  505 cherry    4u  IPv4 0x760f57133427dbbd      0t0  TCP macbook-pro.lan:53165->203.208.40.77:https (ESTABLISHED)
      com.apple  505 cherry    6u  IPv4 0x760f57133a5150d5      0t0  TCP macbook-pro.lan:49477->111.206.76.49:https (ESTABLISHED)
      Python    2041 cherry    5u  IPv4 0x760f571336b290d5      0t0  TCP macbook-pro.lan:50896->202.89.233.100:https (ESTABLISHED)
      Python    2662 cherry    5u  IPv4 0x760f5713372a40d5      0t0  TCP macbook-pro.lan:51361->202.89.233.101:https (ESTABLISHED)
      plugin_ho 3145 cherry   23u  IPv4 0x760f5713372a6dad      0t0  TCP localhost:51004 (LISTEN)
      Python    4322 cherry    5u  IPv4 0x760f5713343264b5      0t0  TCP macbook-pro.lan:53182->202.89.233.101:https (ESTABLISHED)
      com.apple 4596 cherry   10u  IPv4 0x760f571332cbe0d5      0t0  TCP macbook-pro.lan:53166->120.92.73.9:xtgui (ESTABLISHED)
      com.apple 4596 cherry   12u  IPv4 0x760f571332cbe0d5      0t0  TCP macbook-pro.lan:53166->120.92.73.9:xtgui (ESTABLISHED)

      # List open files with IPV4 address
      c$ lsof -i 4
      COMMAND    PID   USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
      loginwind  111 cherry    8u  IPv4 0x760f57132b6a315d      0t0  UDP *:*
      UserEvent  275 cherry    5u  IPv4 0x760f57132b6a503d      0t0  UDP *:*
      SystemUIS  283 cherry   11u  IPv4 0x760f57132b6a199d      0t0  UDP *:*
      SystemUIS  283 cherry   12u  IPv4 0x760f57132b6a173d      0t0  UDP *:*
      SystemUIS  283 cherry   15u  IPv4 0x760f57132b6a491d      0t0  UDP *:59531
      SystemUIS  283 cherry   16u  IPv4 0x760f57132b6a4b7d      0t0  UDP *:*
      SystemUIS  283 cherry   19u  IPv4 0x760f57132b6a101d      0t0  UDP *:*
      identitys  315 cherry   20u  IPv4 0x760f571329c34f7d      0t0  UDP *:*
      sharingd   333 cherry    4u  IPv4 0x760f57132b1b259d      0t0  UDP *:*
      sharingd   333 cherry    8u  IPv4 0x760f57132b1b27fd      0t0  UDP *:*
      sharingd   333 cherry    9u  IPv4 0x760f571329c3861d      0t0  UDP *:*
      sharingd   333 cherry   10u  IPv4 0x760f571329c38add      0t0  UDP *:*
      sharingd   333 cherry   15u  IPv4 0x760f57132b6a3add      0t0  UDP *:*
      WiFiAgent  400 cherry    5u  IPv4 0x760f57132b6a60dd      0t0  UDP *:*
      com.apple  505 cherry    4u  IPv4 0x760f57133427dbbd      0t0  TCP macbook-pro.lan:53165->203.208.40.77:https (ESTABLISHED)
      com.apple  505 cherry    6u  IPv4 0x760f57133a5150d5      0t0  TCP macbook-pro.lan:49477->111.206.76.49:https (ESTABLISHED)
      Python    2041 cherry    5u  IPv4 0x760f571336b290d5      0t0  TCP macbook-pro.lan:50896->202.89.233.100:https (ESTABLISHED)
      Python    2662 cherry    5u  IPv4 0x760f5713372a40d5      0t0  TCP macbook-pro.lan:51361->202.89.233.101:https (ESTABLISHED)
      plugin_ho 3145 cherry   23u  IPv4 0x760f5713372a6dad      0t0  TCP localhost:51004 (LISTEN)
      com.apple 4596 cherry   10u  IPv4 0x760f571332cbe0d5      0t0  TCP macbook-pro.lan:53166->120.92.73.9:xtgui (ESTABLISHED)
      com.apple 4596 cherry   12u  IPv4 0x760f571332cbe0d5      0t0  TCP macbook-pro.lan:53166->120.92.73.9:xtgui (ESTABLISHED)
