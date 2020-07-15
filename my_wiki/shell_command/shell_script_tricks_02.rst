**********************
Shell Script Tricks 02
**********************

#. Call scripts from shell / python script
   
    .. code-block:: sh

        # Call shell script from another shell script
        source `pwd`/reload.sh

        # Call python script from shell script
        python `pwd`/reload.py

        # Call python script from another python script
        import start # import start.py as module
        def main():
            if is_process_stopped(program_name):
                return start.main() # call start.py function
            else:
                return reload_process(program_name)

#. Difference between `source` and `.`
   
   `.` is the traditional source command, inherited from the ancient bourne shell. 
   `source` is just a bash builtin that does exactly the same as `.`, presumably 
   because it's more readable. You'll see `help source` and `help .` shows the same info.

   ``source script`` run the script in the current process, and all variable assignments
   are preserved even after the script has finished. (and you don't have to be explicitly `export`).

#. Pass argument(s) to shell function

    * Shell functions have their own command line argument.
    * Use variable $1, $2..$n to access argument passed to the function.
    * The syntax is as follows::

        name(){
          arg1=$1
          arg2=$2
          command on $arg1
        }

    To invoke the the function use the following syntax: ``name foo bar``