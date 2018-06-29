*************
ulimit Manual
*************

**Name**

	ulimit - limit the use of system-wide resources.

**Syntax**

	ulimit [-acdfHlmnpsStuv] [limit]

**Options**

	.. code-block:: none
	
		-S   Change and report the soft limit associated with a resource. 
		-H   Change and report the hard limit associated with a resource. 
	
		-a   All current limits are reported. 
		-c   The maximum size of core files created. 
		-d   The maximum size of a process's data segment. 
		-f   The maximum size of files created by the shell(default option) 
		-l   The maximum size that can be locked into memory. 
		-m   The maximum resident set size. 
		-n   The maximum number of open file descriptors. 
		-p   The pipe buffer size. 
		-s   The maximum stack size. 
		-t   The maximum amount of cpu time in seconds. 
		-u   The maximum number of processes available to a single user. 
		-v   The maximum amount of virtual memory available to the process. 
	
	ulimit provides control over the resources available to the shell and to processes 
	started by it, on systems that allow such control.
	
	The soft limit is the value that the kernel enforces for the corresponding resource. 
	The hard limit acts as a ceiling for the soft limit.
	
	An unprivileged process may only set its soft limit to a value in the range from 0 up to the hard limit, 
	and (irreversibly) lower its hard limit. A privileged process can make arbitrary changes to either limit value.
	
	When setting new limits, if neither '-H' nor '-S' is supplied, both the hard and soft limits are set.
	
	Restricting per user processes ( -u) can be useful for limiting the potential effects of a fork bomb.

**Examples**

	.. code-block:: sh

		$ ulimit -a
		core file size          (blocks, -c) 0
		data seg size           (kbytes, -d) unlimited
		scheduling priority             (-e) 0
		file size               (blocks, -f) unlimited
		pending signals                 (-i) 15811
		max locked memory       (kbytes, -l) 64
		max memory size         (kbytes, -m) unlimited
		open files                      (-n) 1024
		pipe size            (512 bytes, -p) 8
		POSIX message queues     (bytes, -q) 819200
		real-time priority              (-r) 0
		stack size              (kbytes, -s) 8192
		cpu time               (seconds, -t) unlimited
		max user processes              (-u) 15811
		virtual memory          (kbytes, -v) unlimited
		file locks                      (-x) unlimited
		
		$ ulimit -Hn
		4096

	