************
Progress bar
************

.. code-block:: python

    #!/usr/bin/env python
    
    import sys, time
    
    class ProgressBar:
    
        def __init__(self):
           self.bytesDownloaded = 0
           self.tickNum = 0
           self.ticks = ['|', '/', '-', '\\', ' ']
           #self.ticks = ['.     ', '..    ', '...   ', '....  ', '..... ', '......', '      ']
           self.gb = 1 << 30
           self.mb = 1 << 20
           self.kb = 1 << 10
    
        def update(self, dataSize):
           self.bytesDownloaded += dataSize
    
           if dataSize == 0:
              self.tickNum = -1
           if self.bytesDownloaded >= self.gb:
              localSize = "%4dG%4.2fM" % (self.bytesDownloaded / self.gb, (self.bytesDownloaded%self.gb) / float(self.mb))
           elif self.bytesDownloaded >= self.mb:
              localSize = "%4dM%4.2fK" % (self.bytesDownloaded / self.mb, (self.bytesDownloaded%self.mb) / float(self.kb))
           else:
              localSize = "%4.2fK" % (self.bytesDownloaded/float(self.kb))
    
           text = "\rDownloading: %s\t%13s" % (self.ticks[self.tickNum], localSize)
           self.tickNum += 1
           self.tickNum = self.tickNum % (len(self.ticks)-1)
           sys.stdout.write(text)
           sys.stdout.flush()
    
    if __name__ == "__main__":
        bar = ProgressBar()
    
        for i in xrange(100):
            time.sleep(0.1)
            bar.update(1024*100*10)    
    
        bar.update(0)
        print 
        print "Downloading done"
