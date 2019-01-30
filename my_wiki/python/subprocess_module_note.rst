**********************
Python Subprocess note
**********************

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

   *args* is required for all calls and should be a string, or a sequence of program arguments. 
   Providing a sequence of arguments is generally preferred, as it allows the module to take care 
   of any required escaping and quoting of arguments (e.g. to permit spaces in file names). 
   If passing a single string, either shell must be ``True`` or else the string must simply 
   name the program to be executed without specifying any arguments.

.. warning::

   Executing shell commands that incorporate unsanitized input from an
   untrusted source makes a program vulnerable to `shell injection
   <http://en.wikipedia.org/wiki/Shell_injection#Shell_injection>`_,
   a serious security flaw which can result in arbitrary command execution.
   For this reason, the use of ``shell=True`` is **strongly discouraged**
   in cases where the command string is constructed from external input::

      >>> from subprocess import call
      >>> filename = input("What file would you like to display?\n")
      What file would you like to display?
      non_existent; rm -rf / #
      >>> call("cat " + filename, shell=True) # Uh-oh. This will end badly...

   When using ``shell=True``, :func:`pipes.quote` can be used to properly
   escape whitespace and shell metacharacters in strings that are going to
   be used to construct shell commands.

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

.. code-block:: sh

   def start_process(program_name):
       print("Starting %s" % program_name)
       try:
           cmd = "nohup %s >/dev/null 2>&1 &" % program_name
           subprocess.check_output(cmd, shell=True)
       except subprocess.CalledProcessError as e:
           print("Failed to start %s, return code: %d, message: %s" % (program_name, e.returncode, e.output))
           return e.returncode
       else:
           time.sleep(5)
           if is_process_running(program_name):
               print("Succeeded in starting %s" % program_name)
               return 0
           else:
               print("Failed to start %s" % program_name)
               return 1
   