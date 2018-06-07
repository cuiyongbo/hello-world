File inspection command
=======================

   See :doc:`file_inspectors`.


ps Command
==========

   See :doc:`ps_command`.


smem Command
============

   See :doc:`smem_man_doc`.

kill & killall Command
======================

   See :doc:`kill_command`.


grep Command
============

   See :doc:`grep_command`


find Command
============

   See :doc:`find_command`


nohup Command
=============

   See :doc:`nohup_command`


Pipe & Redirect
===============

   .. code-block:: sh
   
      $ more < main.cpp # redirect input
      $ kill -HUP 1234 >killout.txt 2>killerr.txt # redirect stdout to killout.txt and stderr to killerr.txt
      $ kill -1 1234 >/dev/null 2>&1 # discard all output
      $ ls -lh >>directoryEntries.txt # redirect stdout to directoryEntries.txt in append mode
      $ ps | sort -h
   
   .. note::
      
      * 0 - stdin
      * 1 - stdout
      * 2 - stderr
        
      the "&" in "2>&1" cannot be omitted, otherwise the command will be interpreted as
      "redirect stderr to a file named 1." "&" indicates that what follows is a file 
      descriptor and not a filename.  


System V IPC Status Command
===========================

   See :doc:`system_v_ipc_facility`.


ls Command
==========

   See :doc:`ls_info`.


crontab Command
===============

   See :doc:`crontab_info`.


chmod Command
=============

   See :doc:`chmod_info`.


Compress / decompress command
=============================

   See :doc:`tar_info`.


File / directory copy and move
==============================

   See :doc:`file_cp_mv`

