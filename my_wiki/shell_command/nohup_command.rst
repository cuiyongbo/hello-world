*************
nohup command
*************

**NAME**
   
   nohup - run a command immune to hangups, with output to a non-tty

**SYNOPSIS**

   .. code-block:: sh

      nohup COMMAND [ARG]...
      nohup OPTION

**DESCRIPTION**

   Run *COMMAND*, ignoring hangup signals::

      --help display this help and exit

      --version
         output version information and exit

   If standard input is a terminal, redirect it from :file:`/dev/null`. 
   If standard output is a terminal, append output to ``'nohup.out'`` if possible,
   ``'$HOME/nohup.out'`` otherwise. If standard error is a terminal, redirect it to standard output.
   To save output to *FILE*, use ``'nohup COMMAND > FILE'``.

**EXAMPLE**

   .. code-block:: sh

      $ nohup ./server &>run.log # redirect stderr and stdout to run.log



