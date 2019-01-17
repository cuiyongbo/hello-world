******************
Python psutil note
******************

..function:: class psutil.Process(pid=None)

    Represents an OS process with the given pid. If pid is omitted current process pid (``os.getpid()``) is used. 
    Raise ``NoSuchProcess`` if pid does not exist. On Linux pid can also refer to a thread ID (the id field returned 
    by ``threads()`` method). When accessing methods of this class always be prepared to catch ``NoSuchProcess``, 
    ``ZombieProcess`` and ``AccessDenied`` exceptions. 

.. function:: parent()

    Returns the parent process as a Process object preemptively checking whether PID has been reused. 
    If no parent PID is known return None.

.. function:: children(recursive=False)

    Return the children of this process as a list of Process instances. 
    If *recursive* is True return all the parent descendants::

        # A ─┐
        #    │
        #    ├─ B (child) ─┐
        #    │             └─ X (grandchild) ─┐
        #    │                                └─ Y (great grandchild)
        #    ├─ C (child)
        #    └─ D (child)

        >>> p.children()
        B, C, D
        >>> p.children(recursive=True)
        B, X, Y, C, D

    Note that in the example above if process X disappears process Y won’t be returned 
    either as the reference to process A is lost. This concept is well summaried by this unit test.

#. Find process by name
   
    Check string against ``Process.name()``::

        import psutil

        def find_procs_by_name(name):
            "Return a list of processes matching 'name'."
            ls = []
            for p in psutil.process_iter(attrs=['name']):
                if p.info['name'] == name:
                    ls.append(p)
            return ls

    A bit more advanced, check string against ``Process.name()``, ``Process.exe()`` 
    and ``Process.cmdline()``::

        import os
        import psutil
        
        def find_procs_by_name(name):
            "Return a list of processes matching 'name'."
            ls = []
            for p in psutil.process_iter(attrs=["name", "exe", "cmdline"]):
                if name == p.info['name'] or \
                        p.info['exe'] and os.path.basename(p.info['exe']) == name or \
                        p.info['cmdline'] and p.info['cmdline'][0] == name:
                    ls.append(p)
            return ls

#. Terminate my children

    This may be useful in unit tests whenever sub-processes are started. 
    This will help ensure that no extra children (zombies) stick around to 
    hog resources::

        import psutil
        
        def reap_children(timeout=3):
            "Tries hard to terminate and ultimately kill all the children of this process."
            def on_terminate(proc):
                print("process {} terminated with exit code {}".format(proc, proc.returncode))
        
            procs = psutil.Process().children()
            # send SIGTERM
            for p in procs:
                p.terminate()
            gone, alive = psutil.wait_procs(procs, timeout=timeout, callback=on_terminate)
            if alive:
                # send SIGKILL
                for p in alive:
                    print("process {} survived SIGTERM; trying SIGKILL" % p)
                    p.kill()
                gone, alive = psutil.wait_procs(alive, timeout=timeout, callback=on_terminate)
                if alive:
                    # give up
                    for p in alive:
                        print("process {} survived SIGKILL; giving up" % p)

#. Kill process tree

    .. code-block:: py

        import os, signal, psutil
        
        def kill_proc_tree(pid, sig=signal.SIGTERM, include_parent=True,
                           timeout=None, on_terminate=None):
            """Kill a process tree (including grandchildren) with signal
            "sig" and return a (gone, still_alive) tuple.
            "on_terminate", if specified, is a callabck function which is
            called as soon as a child terminates.
            """
            if pid == os.getpid():
                raise RuntimeError("I refuse to kill myself")
            parent = psutil.Process(pid)
            children = parent.children(recursive=True)
            if include_parent:
                children.append(parent)
            for p in children:
                p.send_signal(sig)
            gone, alive = psutil.wait_procs(children, timeout=timeout,
                                            callback=on_terminate)
            return (gone, alive)


.. rubric:: Footnotes

.. [#] `psutil doc <https://psutil.readthedocs.io/en/latest/#processes>`_