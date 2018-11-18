*****************************
top - display Linux processes
*****************************

**DESCRIPTION**

   .. code-block:: none
      :caption: SYNOPSIS
          
         top -hv|-bcHiOSs -d secs -n max -u|U user -p pid -o fld -w [cols]

   The top program provides a dynamic real-time view of a running system.  
   It can display system summary information as well as a list of processes 
   or threads currently being managed by the Linux kernel.

**Hot Options**

   .. option:: -H,  Threads-mode operation
      
      Instructs top to display individual threads.

.. code-block:: sh
   :caption: Example

   $ top -p15702
   PID USER  PR  NI    VIRT    RES    SHR S %CPU %MEM  TIME+ COMMAND
   
   15702 cuiyb  20   0  293516  73948   3784 S  1.0  3.6   0:29.73 traffic_data_up 

   $ top -H -p15813 
   PID USER  PR  NI    VIRT    RES    SHR S %CPU %MEM  TIME+ COMMAND

   15813 cuiyb     20   0   14704    320    212 S  0.0  0.0   0:00.00 a.out
   15815 cuiyb     20   0   14704    320    212 S  0.0  0.0   0:00.00 a.out  

   # press "e" to change memory unit cycle from KB to EB
   $ top  -p10016
   PID USER  PR  NI    VIRT    RES    SHR S %CPU %MEM  TIME+ COMMAND

   10016 cuiyb     20   0  241.7m  19.4m   3.0m S   1.7  0.0   0:11.11 past_ti_compile  

.. code-block:: none
   :caption: Press "f" to enter Fields Management
   
   Fields Management for window 1:Def, whose current sort field is %CPU
   Navigate with Up/Dn, Right selects for move then <Enter> or Left commits,
   'd' or <Space> toggles display, 's' sets sort.  Use 'q' or <Esc> to end!

   * PID     = Process Id          
   * USER    = Effective User Name 
   * PR      = Priority            
   * NI      = Nice Value          
   * VIRT    = Virtual Image (KiB) 
   * RES     = Resident Size (KiB) 
   * SHR     = Shared Memory (KiB) 
   * S       = Process Status      
   * %CPU    = CPU Usage           
   * %MEM    = Memory Usage (RES)  
   * TIME+   = CPU Time, hundredths
   * COMMAND = Command Name/Line   
     PPID    = Parent Process pid  
     UID     = Effective User Id   
     RUID    = Real User Id        
     RUSER   = Real User Name      
     SUID    = Saved User Id       
     SUSER   = Saved User Name     
     GID     = Group Id            
     GROUP   = Group Name          
     PGRP    = Process Group Id    
     TTY     = Controlling Tty     
     TPGID   = Tty Process Grp Id  
     SID     = Session Id          
     nTH     = Number of Threads   
     P       = Last Used Cpu (SMP) 
     TIME    = CPU Time            
     SWAP    = Swapped Size (KiB)  
     CODE    = Code Size (KiB)     
     DATA    = Data+Stack (KiB)    
     nMaj    = Major Page Faults   
     nMin    = Minor Page Faults   
     nDRT    = Dirty Pages Count   
     WCHAN   = Sleeping in Function
     Flags   = Task Flags <sched.h>
     CGROUPS = Control Groups      
     SUPGIDS = Supp Groups IDs     
     SUPGRPS = Supp Groups Names   
     TGID    = Thread Group Id     
     ENVIRON = Environment vars    
     vMj     = Major Faults delta  
     vMn     = Minor Faults delta  
     USED    = Res+Swap Size (KiB) 
     nsIPC   = IPC namespace Inode 
     nsMNT   = MNT namespace Inode 
     nsNET   = NET namespace Inode 
     nsPID   = PID namespace Inode 
     nsUSER  = USER namespace Inode
     nsUTS   = UTS namespace Inode 
   