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

    .. option:: -A, --catenate, --concatenate
    
        append tar files to an archive

    .. option:: -c, --create
        
        create a new archive

    .. option:: -d, --diff, --compare
        
        find differences between archive and file system

    .. option:: --delete
    
        delete from the archive (not on mag tapes!)

    .. option:: -r, --append
        
        append files to the end of an archive.
        **Note:** You CANN'T update compressed file in-place.

    .. option:: -t, --list
        
        list the contents of an archive

    .. option:: -x, --extract, --get
        
        extract files from an archive

    .. option:: -v, --verbose
        
        verbosely list files processed

    .. option:: -f, --file ARCHIVE
        
        use archive file or device ARCHIVE

    .. option:: -C, --directory DIR
        
        change to directory DIR

    .. option:: --skip-old-files
        
        don't replace existing files when extracting, silently skip over them

    .. option:: -X, --exclude-from FILE
        
        exclude patterns listed in FILE

    .. option:: --exclude pattern

        exclude files, given as a PATTERN
         
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

        $ tar -jcvf filename.tar.bz2  filelist # 压缩文件
        $ tar -jtvf filename.tar.bz2 # 查看压缩文件内容
        $ tar -jxvf filename.tar.bz2 -C directory # 解压到指定文件目录
        $ tar -zcvf b2.tar.gz ./*
        $ tar --exclude *.pdf -zcvf b2.tar.gz ./* #排除当前目录下的 pdf 文件
        $ tar -ztvf b2.tar.gz
        $ tar -zxvf backup.tar.gz -C ./test/
        $ tar --newer "2017/01/01" -zcf  photo.tar.gz  ./Desktop/Screenshot/* #压缩比指定日期早的文件
        $ tar -zxvf photo.tar.gz *.png #只解压包内的 png 文件
        
        $ tar -zcf coke_cola_package.tar.gz coke_cola_package/* # pack and compress coke_cola_package/ into coke_cola_package.tar.gz
        $ rm -rf coke_cola_package/
        $ tar -xf coke_cola_package.tar.gz # uncompress coke_cola_package.tar.gz into coke_cola_package

        $ tar -czvf pepsi_helper.tar.gz pepsi_helper/ --exclude "pepsi_helper/config"

        # extract specified file(s)
        $ tar -zxf coke_cola_package.tar.gz --wildcards "*.cpp" # only extract cpp files
        $ tar -zxf coke_cola_package.tar.gz --wildcards "*stdafx.cpp"

        $ tar -tf log.tar 
        coke_cola_package.log.1
        coke_cola_package.log.2
        $ tar -rf log.tar coke_cola_package_cfg.ini 
        $ tar -tf log.tar 
        coke_cola_package.log.1
        coke_cola_package.log.2
        coke_cola_package_cfg.ini
        $ tar -f log.tar --delete coke_cola_package_cfg.ini 
        $ tar -tf log.tar 
        coke_cola_package.log.1
        coke_cola_package.log.2

        # remove file after added to archive file
        tar -rf log.tar --remove-files coke_cola_package.log.7
      
      
    .. code-block:: sh
        :caption: tarAndRemove.sh
        
        #!/usr/bin/env bash
        echo "Program name: $0"
        echo "PID: $$"
        echo "Parameter count: $#"
        for i in $@
        do 
            echo "taring $i.tar.gz ..."
            tar -czf $i.tar.gz $i 
            echo "rm $i ..." 
            rm -rf $i
        done


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
        ...
    
    With no FILE, or when FILE is -, read standard input.
   
.. code-block:: sh
    :caption: Examples

    $ gunzip -nk 05nanjing.txt.gz  # use the name of zip file
    $ gunzip -Nk 06nanjing.txt.gz  # use the original file name in the zip file

    $ ll *.gz
    -rw-r--r-- 1 beats 1049089 424943 Jun 28 14:56 06nanjing.txt.gz
    -rw-r--r-- 1 beats 1049089 424716 Jun 28 14:56 07nanjing.txt.gz
    -rw-r--r-- 1 beats 1049089 423827 Jun 28 14:56 08nanjing.txt.gz
    -rw-r--r-- 1 beats 1049089 422795 Jun 28 14:56 09nanjing.txt.gz

    $ find . -type f -name "*.gz" -exec gunzip -nk \{\} \;

    $ ll *.txt
    -rw-r--r-- 1 beats 1049089 1955776 Jun 28 14:56 06nanjing.txt
    -rw-r--r-- 1 beats 1049089 1952338 Jun 28 14:56 07nanjing.txt
    -rw-r--r-- 1 beats 1049089 1949276 Jun 28 14:56 08nanjing.txt
    -rw-r--r-- 1 beats 1049089 1944800 Jun 28 14:56 09nanjing.txt

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
        ...
      
      See "unzip -hh" or unzip.txt for more help.  Examples:
        unzip data1 -x joe   => extract all files except joe from zipfile data1.zip
        unzip -p foo | more  => send contents of foo.zip via pipe into program more
        unzip -fo foo ReadMe => quietly replace existing ReadMe if archive file newer
