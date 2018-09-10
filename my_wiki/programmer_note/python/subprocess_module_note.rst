***************
Subprocess note
***************

.. code-block:: py

   #!/usr/bin/env python

   import subprocess
   
   patch_count_lists = range(100, 700, 100)
   
   exe = "./tidiff.exe"
   thread_args = "-t 1"
   diff_args = "diff realtime.data-old realtime.data-new"
   
   log_file = "profile.log"
   with open(log_file, "a") as log:
      for count in patch_count_lists:
         cmd = "{0} {1} {2} {3}".format(exe, thread_args, diff_args, count)
         msg = subprocess.check_output(cmd)
         #msg = subprocess.check_output("./tidiff --test")
         log.write(msg)
      log.close()
