***********
smem Manual
***********

**NAME**
   
   smem - Report memory usage with shared memory divided proportionally.

**DESCRIPTION**

   **smem reports physical memory usage, taking shared memory pages into account.** Unshared memory is
   reported as the :abbr:`USS (Unique Set Size)`. Shared memory is divided evenly among the processes  
   sharing  that  memory. The unshared USS plus a process's proportion of shared memory is reported 
   as the :abbr:`PSS (Proportional Set Size)`. The USS and PSS only include physical memory usage.
   They do not include memory that has been swapped out to disk.

**Hot Options**

   .. option:: -H, --no-header
           
      Disable header line.

   .. option:: -k, --abbreviate
         
      Show unit suffixes.

   .. option:: -t, --totals
         
      Show totals.

   .. option:: -c COLUMNS, --columns=COLUMNS
         
      Columns to show.

   .. option:: -P PROCESSFILTER, --processfilter=PROCESSFILTER
            
      Process filter regular expression.

   .. option:: -r, --reverse
         
      Reverse sort.

   .. option: -s SORT, --sort=SORT
         
      Field to sort on.

**FILES**

   .. code-block:: sh

      /proc/$pid/cmdline
      /proc/$pid/smaps
      /proc/$pid/stat
      /proc/meminfo
      /proc/version

.. code-block:: sh
   :caption: Examples

   $ smem -tk -P past_ti_com
     PID User     Command                         Swap      USS      PSS      RSS 
    4448 cuiyb    /usr/bin/python /usr/bin/sm        0     5.2M     5.4M     7.2M 
    1578 cuiyb    /etc/ncserver/past_ti_compi        0    17.1M    17.4M    19.7M 
   -------------------------------------------------------------------------------
       2 1                                           0    22.3M    22.7M    26.9M 
