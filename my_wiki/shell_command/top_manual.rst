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
    
    15702 beats  20   0  293516  73948   3784 S  1.0  3.6   0:29.73 coke_cola_up 
    
    $ top -H -p15813 
    PID USER  PR  NI    VIRT    RES    SHR S %CPU %MEM  TIME+ COMMAND
    
    15813 beats     20   0   14704    320    212 S  0.0  0.0   0:00.00 a.out
    15815 beats     20   0   14704    320    212 S  0.0  0.0   0:00.00 a.out  
    
    # press "e" to change memory unit cycle from KB to EB
    $ top  -p10016
    PID USER  PR  NI    VIRT    RES    SHR S %CPU %MEM  TIME+ COMMAND
    
    10016 beats     20   0  241.7m  19.4m   3.0m S   1.7  0.0   0:11.11 pepsi_compile  
    
    # view process status according to name
    # press 'o' then enter COMMAND=process_name [could be a re pattern]
    # COMMAND=pepsi
    
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
    9251 beats     20   0  247912  20672   3440 S   1.0  0.1   1:19.13 pepsi_compile
    4523 beats     20   0   98676   3448   2516 S   0.0  0.0   0:28.74 pepsi_fetcher
    4525 beats     20   0   98676    988     56 S   0.0  0.0   0:33.66 pepsi_fetcher
    4526 beats     20   0   98884   1772    632 S   0.0  0.0   0:00.00 pepsi_fetcher
    4527 beats     20   0   98912   1732    572 S   0.0  0.0   0:00.00 pepsi_fetcher 

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
      ...

#. free - Display amount of free and used memory in the system
   
    ``free`` displays the total amount of free and used physical and swap memory in the system, 
    as well as the buffers used by the kernel. :option:`-h` shows all output fields automatically 
    scaled to shortest three digit unit and display the units of print out.

    .. code-block:: sh

        $ free -h
                total       used        free       shared    buff/cache   available
        Mem:    7.7G        3.6G        3.8G         17M        223M        3.9G
        Swap:   24G         61M         23G        

#.  htop - interactive process viewer

    .. code-block:: sh

        $ htop -h
        -C --no-color               Use a monochrome color scheme
        -d --delay=DELAY            Set the delay between updates, in tenths of seconds
        -h --help                   Print this help screen
        -s --sort-key=COLUMN        Sort by COLUMN (try --sort-key=help for a list)
        -u --user=USERNAME          Show only processes of a given user
        -p --pid=PID,[,PID,PID...]  Show only the given PIDs
        -v --version          Print version info