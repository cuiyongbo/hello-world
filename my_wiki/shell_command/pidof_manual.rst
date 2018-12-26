************
pidof Manual
************

**DESCRIPTION**

   Pidof finds the process id's (pids) of the named programs. 
   Hot Options::

      -s    
      Single shot - this instructs the program to only return one pid.

      -x     
      Scripts too - this causes the program to also return pid of shells 
      running the named scripts.

      -o omitpid
      Tells pidof to omit processes with that pid. The special pid %PPID can be used
      to name the parent process of the pidof program, in other words the calling shell  
      or shell script.

**NOTES**

   pidof is actually the same program as **killall5**; the program behaves according to the name
   under which it is called.

   When pidof is invoked with a full pathname to the program it should find the pid of, it is
   reasonably safe. Otherwise it is possible that it returns pids of running programs that happen
   to have the same name as the program you're after but are actually other programs. Note that
   that the executable name of running processes is calculated with **readlink(2)**, so symbolic
   links to executables will also match.


.. code-block:: sh

   $ pidof traffic_data_updater 
   31808

   # kill nginx
   p=$(pidof nginx)
   kill $p