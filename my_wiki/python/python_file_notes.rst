************************
Python File module notes
************************

#. File Object
   
   .. code-block:: python
   
      >>> dir(file)
      ['close', 'closed', 'encoding', 'errors', 'fileno', 'flush', 'isatty', 'mode', 'name', 
      'newlines', 'next', 'read', 'readinto', 'readline', 'readlines', 'seek', 'softspace', 
      'tell', 'truncate', 'write', 'writelines', 'xreadlines']
   
      # seek(offset[, whence]) -> None.  Move to new file position.
      # 
      # Argument offset is a byte count.  Optional argument whence defaults to
      # 0 (offset from start of file, offset should be >= 0); other values are 1
      # (move relative to current position, positive or negative), and 2 (move
      # relative to end of file, usually negative, although many platforms allow
      # seeking beyond the end of a file).  If the file is opened in text mode,
      # only offsets returned by tell() are legal.  Use of other offsets causes
      # undefined behavior.
      # Note that not all file objects are seekable.

#. open(name[, mode[, buffering]])

   Open a file, returning an object of the file type described in section File Objects. 
   If the file cannot be opened, ``IOError`` is raised. When opening a file, it’s preferable 
   to use *open()*  instead of invoking the file constructor directly.

   The first two arguments are the same as for stdio’s ``fopen().``

   The most commonly-used values of *mode* are 'r' for reading, 'w' for writing (truncating the file if it already exists), 
   and 'a' for appending (which on some Unix systems means that all writes append to the end of the file regardless of the 
   current seek position). **If mode is omitted, it defaults to 'r'. The default is to use text mode,** which may convert '\n' 
   characters to a platform-specific representation on writing and back on reading. Thus, **when opening a binary file, 
   you should append 'b' to the mode value to open the file in binary mode,** which will improve portability. 
   (Appending 'b' is useful even on systems that don’t treat binary and text files differently, where it serves as documentation.)

   The optional *buffering* argument specifies the file’s desired buffer size: 0 means unbuffered, 1 means line buffered, any other 
   positive value means use a buffer of (approximately) that size (in bytes). A negative buffering means to use the system default, 
   which is usually line buffered for tty devices and fully buffered for other files. If omitted, the system default is used.

   Modes 'r+', 'w+' and 'a+' open the file for updating (reading and writing); note that 'w+' truncates the file. Append 'b' to 
   the mode to open the file in binary mode, on systems that differentiate between binary and text files; on systems that don’t 
   have this distinction, adding the 'b' has no effect.

#. os.fdopen(fd [, mode='r' [, bufsize]])

   Return an open file object connected to a file descriptor fd. mode and bufsize is of the same meaning as in builtin ``open().``

#. codecs.open(filename, mode='rb', encoding=None, errors='strict', buffering=1)
   
   Open an encoded file using the given mode and return
   a wrapped version providing transparent encoding/decoding.

   Note: The wrapped version will only accept the object format
   defined by the codecs, i.e. Unicode objects for most builtin
   codecs. Output is also codec dependent and will usually be
   Unicode as well.

   Files are always opened in binary mode, even if no binary mode
   was specified. This is done to avoid data loss due to encodings
   using 8-bit values. The default file mode is 'rb' meaning to
   open the file in binary read mode.

   encoding specifies the encoding which is to be used for the file.

   errors may be given to define the error handling. It defaults
   to 'strict' which causes ``ValueErrors`` to be raised in case an
   encoding error occurs.

   ``buffering`` has the same meaning as for the builtin open() API.
   It defaults to line buffered.

   The returned wrapped file object provides an extra attribute
   .encoding which allows querying the used encoding. This attribute 
   is only available if an encoding was specified as parameter.

#. Get file size

   .. code-block:: py
   
      # unit: byte
      # Solution 1
      >>> f = open("/tmp/realtime/realtime.data")
      >>> f.seek(0, 2) 
      >>> f.tell()
      5000920
      >>> f.close()
   
      # Solution 3
      >>> os.path.getsize("/tmp/realtime/realtime.data")
      5000920
   
      # Solution 3
      >>> statinfo = os.stat("/tmp/realtime/realtime.data")
      >>> statinfo
      posix.stat_result(st_mode=33188, st_ino=25500270, st_dev=24L, st_nlink=1, st_uid=0, st_gid=0, 
      st_size=5000920, st_atime=1532485035, st_mtime=1532485035, st_ctime=1532485035)
   
      # getsize() insight
      def getsize(filename):
         """Return the size of a file, reported by os.stat()."""
         return os.stat(filename).st_size

#. Traverse a file

   .. code-block:: py
   
      >>> f.seek(0,0)
      >>> for line in f:
      ...     if(len(line.strip(' \r\n\t'))):
      ...             print line,
      ...
      *************
      Pending tasks
      *************
      #. speed up ti tile compilation
         - extract PointMap building
         - Grid splitting
         
#. ``file.read()`` return less data than it have read
   
   .. code-block:: py

      # Problem
      >>> f = open('traffic_info.nkvds.bak')
      >>> f.tell()
      0L
      >>> data = f.read(64)
      >>> f.tell()
      4096L

      # Solution
      >>> f = open(f.name, "rb")
      >>> f.tell()
      0L
      >>> data = f.read(64)
      >>> f.tell()
      64L

      # Indeed, append "b" to mode when you open a binary file.

#. check if a file exists
   
   .. code-block:: py

      os.path.isfile(path)
      os.path.ispath(path) # check if directory exists
      os.path.exists(path) # file + directory

#. python to implement unix touch
   
   .. code-block:: py
      
      import os
      def touch(fname, times=None):
          with open(fname, 'a'):
              os.utime(fname, times)
