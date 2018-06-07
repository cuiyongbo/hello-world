:orphan:

***************
crontab Command
***************

**NAME**
   
   crontab -- maintain crontab files for individual users (V3)

**SYNOPSIS**

   .. code-block:: sh

      crontab [-u user] file
      crontab [-u user] { -l | -r | -e }

**DESCRIPTION**

   The crontab utility is the program used to install, deinstall or list the tables
   used to drive the :manpage:`cron(8)` daemon in Vixie Cron. Each user can have
   their own crontab, and they are not intended to be edited directly.

   If the :file:`/usr/lib/cron/cron.allow` file exists, then you must be listed
   therein in order to be allowed to use this command. If the :file:`/usr/lib/cron/cron.allow`
   file does not exist but the :file:`/usr/lib/cron/cron.deny` file does exist, then you must
   not be listed in the :file:`/usr/lib/cron/cron.deny`  file in order to use this command.
   If neither of these files exists, then depending on site-dependent configuration parameters,
   only the super user will be allowed to use this command, or all users will be able to use
   this command.

   The format of these files is one username per line, with no leading or trailing whitespace.
   Lines of other formats will be ignored, and so can be used for comments.

   The first form of this command is used to install a new crontab from some named *file* or
   standard input if the pseudo-filename '-' is given.

   The following options are available::

      -u      
         Specify the name of the user whose crontab is to be tweaked.
         If this option is not given, crontab examines "your" crontab,
         i.e., the crontab of the person executing the command. 
         Note that su(1) can confuse crontab and that if you are running
         inside of su(1) you should always use the -u option for safety's sake.

      -l      
         Display the current crontab on standard output.

      -r      
         Remove the current crontab.

      -e      
         Edit the current crontab using the editor specified by the
         VISUAL or EDITOR environment variables. The specified editor
         must edit the file in place; any editor that unlinks the file
         and recreates it cannot be used. After you exit from the editor,
         the modified crontab will be installed automatically.


   .. note:: 

      Although :manpage:`cron(8)` and :manpage:`crontab(5)` are officially
      supported under Darwin, their functionality has been absorbed into :manpage:`launchd(8)`,
      which provides a more flexible way of automatically executing commands. 


**Example**

   .. code-block:: sh

      # Execute script every five minutes.
      # Solution one, but may not be supported by certain OS
      */5 * * * * /xxx/task.sh

      # Solution two
      0,5,10,15,20,25,30,35,40,45,50,55 * * * * /xx/task.sh

      # Edit this file to introduce tasks to be run by cron.
      # 
      # Each task to run has to be defined through a single line
      # indicating with different fields when the task will be run
      # and what command to run for the task
      # 
      # To define the time you can provide concrete values for
      # minute (m), hour (h), day of month (dom), month (mon),
      # and day of week (dow) or use '*' in these fields (for 'any').
      # Notice that tasks will be started based on the cron's system
      # daemon's notion of time and timezones.
      # 
      # Output of the crontab jobs (including errors) is sent through
      # email to the user the crontab file belongs to (unless redirected).
      # 
      # For example, you can run a backup of all your user accounts
      # at 5 a.m every week with:
      0 5 * * 1 tar -zcf /var/backups/home.tgz /home/
      # 
      # For more information see the manual pages of crontab(5) and cron(8)
      # 
      # m h  dom mon dow   command
      */2 * * * * echo "hell world"
