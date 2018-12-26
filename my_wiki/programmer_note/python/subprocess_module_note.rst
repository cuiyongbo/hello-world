***************
Subprocess note
***************

.. method:: subprocess.call(*popenargs, **kwargs)

   Run command with arguments. Wait for command to complete, then
   return the *returncode* attribute.

    The arguments are the same as for the Popen constructor.  
    Example: ``retcode = call(["ls", "-l"]).``


.. method:: check_call(*popenargs, **kwargs)

   Same as call() function.  except when the exit code is none-zero, 
   It would raise **CalledProcessError.** The *CalledProcessError* object 
   will have the return code in the *returncode* attribute.

.. method:: check_output(*popenargs, **kwargs)

   Run command with arguments and return its output as a byte string.

   If the exit code was non-zero it raises a **CalledProcessError**. The
   CalledProcessError object will have the return code in the *returncode*
   attribute and output in the *output* attribute.

   The arguments are the same as for the Popen constructor. 
   Example::

      >>> import subprocess
      >>> subprocess.check_output(["ls", "-l", "/dev/null"])
      'crw-rw-rw- 1 root root 1, 3 Aug 21 15:08 /dev/null\n'

      # The stdout argument is not allowed as it is used internally.
      # To capture standard error in the result, use stderr=STDOUT.

      >>> subprocess.check_output(["/bin/sh", "-c", 
                                 "ls -l non_existent_file; exit 0"], 
                                 stderr=subprocess.STDOUT)
      'ls: cannot access non_existent_file: No such file or directory\n'

.. note:: 

   pass the arguments as a list.

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

.. code-block:: sh

   >>> msg = subprocess.check_output("ps -ef | grep -i traffic_data_updater | grep -v grep", shell=True)
   >>> msg
   'chenbw   28484     1 27 14:16 pts/4    00:13:44 /etc/ncserver/traffic-data-updater/traffic_data_updater\n'

