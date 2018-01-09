#!/usr/bin/env python

import sys
import time

class ProgressBar:
	def __init__(self):
		self.bytesDownloaded = 0
		self.tickNum = 0
		self.ticks = ['|', '/', '-', '\\']
		self.gb = 1 << 30
		self.mb = 1 << 20
		self.kb = 1 << 10

	def update(self, dataSize):

		self.bytesDownloaded += dataSize
		
		if self.bytesDownloaded >= self.gb:
			text = "\rDownloading: %s\t%4dG%4.2fM" % \
					 (self.ticks[self.tickNum], self.bytesDownloaded / self.gb, (self.bytesDownloaded%self.gb) / float(self.mb))
		elif self.bytesDownloaded >= self.mb:
			text = "\rDownloading: %s\t%4dM%4.2fK" % \
					 (self.ticks[self.tickNum], self.bytesDownloaded / self.mb, (self.bytesDownloaded%self.mb) / float(self.kb))
		else:
			text = "\rDownloading: %s\t%4.2fK" % (self.ticks[self.tickNum], self.bytesDownloaded/float(self.kb))

		self.tickNum += 1
		self.tickNum = self.tickNum % len(self.ticks)

		sys.stdout.write(text)
		sys.stdout.flush()


if __name__ == "__main__":

	bar = ProgressBar()

	for i in xrange(200):
		time.sleep(0.1)
		bar.update(1024*100)		

	print 
	print "Downloading done"

