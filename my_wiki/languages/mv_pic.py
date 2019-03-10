#!/usr/bin/env python
import os

'''
#. list files with "os.listdir()"
#. pick picture: rst line start with ".. figure::" and ".. image:: " 
#. file name start with "english_notes_": move picture to "english_note_book/images"
#. file name start with "japanese_notes_": move picture to "japanese_note_book/images"

#. read english_study.rst
#. pick one line, and open file
#. pick picture: rst line start with ".. figure::" and ".. image:: " 
#. move picture to "english_note_book/images"
#. repeat 3-4 until file content is exhausted
#. go to step 2 until english_study.rst is exhausted
'''

def scan_toc_tree(filename, dest_dir):
    with open(filename) as f:
        for line in f:
            line = line.strip() + ".rst"
            if os.path.isfile(line):
                #print(line)
                scan_file(line, dest_dir)

def scan_file(filename, dest_dir):
    with open(filename) as f:
        for line in f:
            line = line.strip()
            if line.startswith((".. figure::", ".. image::")):
                idx = line.find("images")
                #print(line[idx:])
                if os.path.isfile(line[idx:]):
                    #print("%s, %s" % (line[idx:], dest_dir+ "/" + line[idx:]))
                    os.rename(line[idx:], dest_dir+ "/" + line[idx:])


if __name__ == "__main__":
    scan_toc_tree("japanese_study.rst", "japanese_note_book/")
    scan_toc_tree("english_study.rst", "english_note_book/")
