*************
uptime Manual
*************

**NAME**
   
   uptime - Tell how long the system has been running.

**DESCRIPTION**

   uptime gives a one line display of the following information.  The current time, 
   how long the system has been running, how many users are currently logged on, 
   and the system load averages for the past 1, 5, and 15 minutes.

   System load averages is the average number of processes that are either in a runnable 
   or uninterruptable state. A process in a runnable state is either using the CPU or waiting 
   to use the CPU. A process in uninterruptable state is waiting for some I/O access, e.g. waiting 
   for disk. The averages are taken over the three time intervals. Load averages are not normalized 
   for the number of CPUs in a system, so a load average of 1 means a single CPU system is loaded all 
   the time while on a 4 CPU system it means it was idle 75% of the time.

**OPTIONS**

   .. option:: -p, --pretty
         
      show uptime in pretty format

   .. option:: -s, --since
      
      system up since, in yyyy-mm-dd MM:HH:SS format

**FILES**

   +---------------+----------------------------------------------+
   | /var/run/utmp | information about who is currently logged on |
   +---------------+----------------------------------------------+
   | /proc         | process information                          |
   +---------------+----------------------------------------------+


**EXAMPLE**

   .. code-block:: sh

      $ uptime -p
      up 1 hour, 19 minutes
      $ uptime -s
      2018-06-14 09:03:22
      $ uptime 
      10:25:08 up  1:21,  2 users,  load average: 0.01, 0.33, 0.35
