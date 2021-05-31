************
xargs Manual
************

**NAME**
   
   xargs - build and execute command lines from standard input


**DESCRIPTION**

   This manual page documents the GNU version of xargs. 

   xargs reads items from the standard input, delimited by blanks (which can be protected 
   with double or single quotes or a backslash) or newlines, and executes the command 
   (default is **/bin/echo**) one or more times with any initial-arguments followed by 
   items read from standard input. Blank lines on the standard input are ignored.

   The command line for command is built up until it reaches a system-defined limit (unless 
   the -n and -L options are used). The specified command will be invoked as many times as 
   necessary to use up the list of input items. In general, there will be many fewer invocations 
   of command than there were items in the input. This will normally have significant performance  
   benefits. Some commands can usefully be executed in parallel too; see the -P option.

   Because Unix filenames can contain blanks and newlines, this default behaviour is often problematic; 
   **filenames containing blanks and/or newlines are incorrectly processed by xargs**. In these situations 
   it is better to use the ``-0`` option, which prevents such problems. When using this option you will need 
   to ensure that the program which produces the input for xargs also uses a null character as a separator.  
   If that program is GNU find for example, the -print0 option does this for you.

   If any invocation of the command exits with a status of 255, xargs will stop immediately without reading 
   any further input. An error message is issued on stderr when this happens.


**OPTIONS**

   .. option:: -0, --null
              
      Input items are terminated by a null character instead of by whitespace, 
      and the quotes and backslash are not special (every character is taken 
      literally). Disables the end of file string, which is treated like any 
      other argument. Useful when input items might contain white space, quote 
      marks, or backslashes. The GNU find ``-print0`` option produces input 
      suitable for this mode.

   .. option:: -a file, --arg-file=file

      Read items from file instead of standard input. If you use this option, 
      stdin remains unchanged when commands are run. Otherwise, stdin is redirected 
      from */dev/null*.

   .. option:: --delimiter=delim, -d delim

      Input items are terminated by the specified character. The specified delimiter 
      may be a single character, a C-style character escape such as \n, or an octal 
      or hexadecimal escape code. Octal and hexadecimal escape codes are understood as 
      for the printf command. Multibyte characters are not supported. When processing 
      the input, quotes and backslash are not special; every character in the input is 
      taken literally. The -d option disables any end-of-file string, which is treated 
      like any other argument. You can use this option when the input consists of simply 
      newline-separated items, although it is almost always better to design your program 
      to use ``--null`` where this is possible.

   .. option:: -n max-args, --max-args=max-args
              
      Use at most *max-args* arguments per command line. Fewer than *max-args* arguments will 
      be used if the size (see the -s option) is exceeded, unless the -x option is given, i
      n which case xargs will exit.

   .. option:: -r, --no-run-if-empty

      If the standard input does not contain any nonblanks, do not run the command.  
      Normally, the command is run once even if there is no input. This option is a GNU extension.

   .. option:: -t, --verbose
      
      Print the command line on the standard error output before executing it.


**Examples**

#. examples
   
   .. code-block:: sh
   
      find /tmp -name core -type f -print | xargs /bin/rm -f

      Find files named core in or below the directory /tmp and delete them.  
      Note that this will work incorrectly if there are any filenames containing newlines or spaces.

      find /tmp -name core -type f -print0 | xargs -0 /bin/rm -f

      Find files named core in or below the directory /tmp and delete them, processing filenames 
      in such a way that file or directory names containing spaces or newlines are correctly handled.

      find /tmp -depth -name core -type f -delete

      Find files named core in or below the directory /tmp and delete them, but more efficiently than 
      in the previous example (because we avoid the need to use fork(2) and exec(2) to launch rm and
      we don't need the extra xargs process).

      cut -d: -f1 < /etc/passwd | sort | xargs echo
      awk -F: '$0 ~ /^#/ {next}; {print $1}' /etc/passwd | sort

      Generates a compact listing of all the users on the system.

#. more examples
   
   .. code-block:: sh

      cat test.txt | xargs # 單行輸出
      cat test.txt | xargs -n3 # 多行輸出
      echo "nameXnameXnameXname" | xargs -dX -n2
      ls *.jpg | xargs -n1 -I cp {} /data/images # 複製當前目錄下的 jpg 文件到/data/images
      find . -type f -name "*.log" -print0 | xargs -0 rm –f # 刪除當前目錄下的 log文件
      find . -type f -name "*.cpp" -print0 | xargs -0 wc –l  # 統計一個目錄下源代碼行數
      find . -type f -name "*.jpg" -print | xargs tar -czvf images.tar.gz # 打包當前目錄下的 jpg 文件 到images.tar.gz
      cat url-list.txt | xargs wget –c # 下載url-list.txt裡的所有鏈接
      find . -name "*.pyc" | xargs rm –rf  # 刪除當前目錄及其子目錄下後綴為 pyc 的文件

      # Mostly use -exec option instead when coming to find command
      find . -type f -name "*.rst" -exec wc -l {} \; | sort
      find . -type f -name "*.log"  -delete

      # Delete all the excutables except scripts in current directory.
      file * | grep executable | grep -v script | xargs rm -f

      # append to many files
      # use sed 's/ /\n/' to split former pipe output with newline
      # use sh -c 'cmd args' to prevent shell from expanding '>> %'
      find . -name 'conf_template.value' | grep video | sed 's/ /\n/' | xargs -I'%' sh -c 'echo nice >> %'
