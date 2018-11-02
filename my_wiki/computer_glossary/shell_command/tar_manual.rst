***********************
compress and decompress
***********************

.. note::

   打包:将多个文件或目录生成一个文件;
   压缩:通过压缩算法把一个大文件压缩成一个小文件.

.. contents::
   :local:


tar Command
===========

**DESCRIPTION**
   
   .. code-block:: sh

      tar [-] A --catenate --concatenate | c --create | d --diff --compare | --delete 
                        | r --append | t --list | --test-label | u --update 
                        | x --extract --get [options] [pathname ...]


   Tar stores and extracts files from a tape or disk archive.

   The first argument to tar should be a function; either one of the letters ``Acdrtux``, 
   or one of the long function names. A function letter need not be prefixed with "-",
   and may be combined with other single-letter options. A long function name must be
   prefixed with "--". Some options take a parameter; with the single-letter form these
   must be given as separate arguments. With the long form, they may be given by appending
   ``=value`` to the option.

**FUNCTION LETTERS**

   **Main operation mode**

      .. option:: -A, --catenate, --concatenate
      
         append tar files to an archive

      .. option:: -c, --create
         
         create a new archive

      .. option:: -d, --diff, --compare
         
         find differences between archive and file system

      .. option:: --delete
      
         delete from the archive (not on mag tapes!)

      .. option:: -r, --append
         
         append files to the end of an archive

      .. option:: -t, --list
         
         list the contents of an archive

      .. option:: --test-label
         
         test the archive volume label and exit

      .. option:: -u, --update
         
         only append files newer than copy in archive

      .. option:: -x, --extract, --get
         
         extract files from an archive

      .. option:: -v, --verbose
           
         verbosely list files processed

      .. option:: -f, --file ARCHIVE
           
         use archive file or device ARCHIVE

      .. option:: -C, --directory DIR
           
         change to directory DIR

      .. option:: -j, --bzip2
      .. option:: -z, --gzip, --gunzip --ungzip
      .. option:: -Z, --compress, --uncompress


      .. option:: --skip-old-files
           
         don't replace existing files when extracting, silently skip over them

      .. option:: -X, --exclude-from FILE
           
           exclude patterns listed in FILE

.. note::

   z 选项表示 tar.gz 是使用 gzip 压缩的文件;
   j 选项表示 tar.bz2 是使用 bzip2 压缩的文件.

**EXAMPLES**

   .. code-block:: sh

      # Create archive.tar from files foo and bar.
      $ tar -cf archive.tar foo bar
      
      # List all files in archive.tar verbosely.
      $ tar -tvf archive.tar
      
      # Extract all files from archive.tar.
      $ tar -xf archive.tar

      tar -jcvf filename.tar.bz2  filelist # 压缩文件
      tar -jtvf filename.tar.bz2 # 查看压缩文件内容
      tar -jxvf filename.tar.bz2 -C directory # 解压到指定文件目录
      tar -zcvf b2.tar.gz ./*
      tar --exclude *.pdf -zcvf b2.tar.gz ./* #排除当前目录下的 pdf 文件
      tar -ztvf b2.tar.gz
      tar -zxvf backup.tar.gz -C ./test/
      tar --newer "2017/01/01" -zcf  photo.tar.gz  ./Desktop/Screenshot/* #压缩比指定日期早的文件
      tar -zxvf photo.tar.gz *.png #只解压包内的 png 文件


gzip/gunzip command
===================

.. code-block:: sh
   :caption: Usage

   $ gzip -h
   Usage: gzip [OPTION]... [FILE]...
   Compress or uncompress FILEs (by default, compress FILES in-place).
   
   Mandatory arguments to long options are mandatory for short options too.
   
     -a, --ascii       ascii text; convert end-of-line using local conventions
     -c, --stdout      write on standard output, keep original files unchanged
     -d, --decompress  decompress
     -f, --force       force overwrite of output file and compress links
     -h, --help        give this help
     -k, --keep        keep (don't delete) input files
     -l, --list        list compressed file contents
     -L, --license     display software license
     -n, --no-name     do not save or restore the original name and time stamp
     -N, --name        save or restore the original name and time stamp
     -q, --quiet       suppress all warnings
     -r, --recursive   operate recursively on directories
         --rsyncable   make rsync-friendly archive
     -S, --suffix=SUF  use suffix SUF on compressed files
         --synchronous synchronous output (safer if system crashes, but slower)
     -t, --test        test compressed file integrity
     -v, --verbose     verbose mode
     -V, --version     display version number
     -1, --fast        compress faster
     -9, --best        compress better
   
   With no FILE, or when FILE is -, read standard input.
   
.. code-block:: sh
   :caption: Examples

   $ gunzip -nk 05nanjing.txt.gz  # use the name of zip file
   $ gunzip -Nk 06nanjing.txt.gz  # use the original file name in the zip file

   $ ll *.gz
   -rw-r--r-- 1 cuiyb 1049089 424943 Jun 28 14:56 06nanjing.txt.gz
   -rw-r--r-- 1 cuiyb 1049089 424716 Jun 28 14:56 07nanjing.txt.gz
   -rw-r--r-- 1 cuiyb 1049089 423827 Jun 28 14:56 08nanjing.txt.gz
   -rw-r--r-- 1 cuiyb 1049089 422795 Jun 28 14:56 09nanjing.txt.gz

   $ find . -type f -name "*.gz" -exec gunzip -nk \{\} \;

   $ ll *.txt
   -rw-r--r-- 1 cuiyb 1049089 1955776 Jun 28 14:56 06nanjing.txt
   -rw-r--r-- 1 cuiyb 1049089 1952338 Jun 28 14:56 07nanjing.txt
   -rw-r--r-- 1 cuiyb 1049089 1949276 Jun 28 14:56 08nanjing.txt
   -rw-r--r-- 1 cuiyb 1049089 1944800 Jun 28 14:56 09nanjing.txt

unzip command
=============

.. code-block:: sh

   $ unzip -h
      UnZip 6.00 of 20 April 2009, by Debian. Original by Info-ZIP.
      
      Usage: unzip [-Z] [-opts[modifiers]] file[.zip] [list] [-x xlist] [-d exdir]
        Default action is to extract files in list, except those in xlist, to exdir;
        file[.zip] may be a wildcard.  -Z => ZipInfo mode ("unzip -Z" for usage).
      
        -p  extract files to pipe, no messages     -l  list files (short format)
        -f  freshen existing files, create none    -t  test compressed archive data
        -u  update files, create if necessary      -z  display archive comment only
        -v  list verbosely/show version info       -T  timestamp archive to latest
        -x  exclude files that follow (in xlist)   -d  extract files into exdir
      modifiers:
        -n  never overwrite existing files         -q  quiet mode (-qq => quieter)
        -o  overwrite files WITHOUT prompting      -a  auto-convert any text files
        -j  junk paths (do not make directories)   -aa treat ALL files as text
        -U  use escapes for all non-ASCII Unicode  -UU ignore any Unicode fields
        -C  match filenames case-insensitively     -L  make (some) names lowercase
        -X  restore UID/GID info                   -V  retain VMS version numbers
        -K  keep setuid/setgid/tacky permissions   -M  pipe through "more" pager
        -O CHARSET  specify a character encoding for DOS, Windows and OS/2 archives
        -I CHARSET  specify a character encoding for UNIX and other archives
      
      See "unzip -hh" or unzip.txt for more help.  Examples:
        unzip data1 -x joe   => extract all files except joe from zipfile data1.zip
        unzip -p foo | more  => send contents of foo.zip via pipe into program more
        unzip -fo foo ReadMe => quietly replace existing ReadMe if archive file newer

.. code-block:: sh
   :caption: Examples

   $ unzip -l Windows系列跟苹果系列.zip 
   Archive:  Windows系列跟苹果系列.zip
     Length      Date    Time    Name
   ---------  ---------- -----   ----
      766780  2018-09-22 22:01   hosts
   ---------                     -------
      766780                     1 file
