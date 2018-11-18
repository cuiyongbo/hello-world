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

**OPTIONS**

   **Hot Options**

      .. option:: -H, --no-header
              
         Disable header line.

      .. option:: -p, --percent

         Show percentages.

      .. option:: -r, --reverse
         
         Reverse sort.

      .. option: -s SORT, --sort=SORT
         
         Field to sort on.

      .. option:: -k, --abbreviate
         
         Show unit suffixes.

      .. option:: -t, --totals
         
         Show totals.

   **SOURCE DATA**

      By default, smem will pull most of the data it needs from the */proc* filesystem of the system it 
      is running on. The *--source* option lets you used a tarred set of */proc* data saved earlier, possibly
      on a different machine. The *--kernel* and *--realmem* options let you specify a couple things that
      smem cannot discover on its own::

         .. option:: -K KERNEL, --kernel=KERNEL
              
            Path to an uncompressed kernel image. This lets smem include the size of the kernel's code
              and statically allocated data in the systemwide (-w) output.  (To  obtain  an  uncompressed
              image  of  a  kernel  on  disk, you may need to build the kernel yourself, then locate file
              vmlinux in the source tree.)

         -R REALMEM, --realmem=REALMEM
              Amount of physical RAM.  This lets smem detect the amount of memory used by  firmware/hard‐
              ware  in the systemwide (-w) output.  If provided, it will also be used as the total memory
              size to base percentages on.  Example: --realmem=1024M

         -S SOURCE, --source=SOURCE
              /proc data source.  This lets you specify an alternate source of the /proc data.  For exam‐
              ple,  you  can capture data from an embedded system using smemcap, and parse the data later
              on a different machine.  If the --source option is not included, smem reports memory  usage
              on the running system.


   **REPORT BY**

      If none of the following options are included, smem reports 
      memory usage by process::

         -m, --mappings
              Report memory usage by mapping.

         -u, --users
              Report memory usage by user.

         -w, --system
              Report systemwide memory usage summary.

   **FILTER BY**
       
      If none of these options are included, memory usage is reported for all processes, users, 
      or mappings. (Note: If you are running as a non-root user, and if you are not using the 
      **--source** options, then you will only see data from processes whose */proc/* information 
      you have access to.)

         .. option:: -M MAPFILTER, --mapfilter=MAPFILTER
              
            Mapping filter regular expression.

         .. option:: -P PROCESSFILTER, --processfilter=PROCESSFILTER
            
            Process filter regular expression.

         .. option:: -U USERFILTER, --userfilter=USERFILTER
            
            User filter regular expression.

   **OUTPUT FORMATTING**

      .. option:: -c COLUMNS, --columns=COLUMNS
         
         Columns to show.

**FILES**

   .. code-block:: sh

      /proc/$pid/cmdline
      /proc/$pid/smaps
      /proc/$pid/stat
      /proc/meminfo
      /proc/version


