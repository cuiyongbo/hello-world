**********
Gdb Basics
**********

breakpoint howto
================

+---------------------+--------------------------------------------------------------+
| Command             | Description                                                  |
+=====================+==============================================================+
| b file.c: N         | Set a breakpoint at line number N of file “file.c”           |
+---------------------+--------------------------------------------------------------+
| b file.c: funcname  | Set a breakpoint at funcname of file “file.c”                |
+---------------------+--------------------------------------------------------------+
| b Class\:\:function | Set a breakpoint at Class\:\:function                        |
+---------------------+--------------------------------------------------------------+
| b N if condition    | Set a conditional breakpoint at line N of the current file   |
+---------------------+--------------------------------------------------------------+
| info break          | List all breakpoints                                         |
+---------------------+--------------------------------------------------------------+
| enable/disable N    | Enable or disable breakpoint number N                        |
+---------------------+--------------------------------------------------------------+
| enable N once       | Enable given breakpoint once, and disable it after it is hit |
+---------------------+--------------------------------------------------------------+
| delete              | delete all breakpoints, watchpoints or catchpoints           |
+---------------------+--------------------------------------------------------------+
| d N                 | Remove breakpoint number N                                   |
+---------------------+--------------------------------------------------------------+

