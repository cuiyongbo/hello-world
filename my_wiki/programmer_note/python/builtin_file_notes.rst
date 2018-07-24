**********
File notes
**********

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
      #. review json code.
      #. https://en.wikipedia.org/wiki/Jordan_curve_theorem
      #. introduction to algorithm - data structure
      #. http://geomalgorithms.com/
      #. http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
      #. https://en.wikipedia.org/wiki/Normal_distribution
      #. https://en.wikipedia.org/wiki/Discrete_uniform_distribution
      #. https://en.wikipedia.org/wiki/Selection_algorithm