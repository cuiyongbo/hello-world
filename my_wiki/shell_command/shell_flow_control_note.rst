******************
Shell flow control
******************

#. Flow Control : if

   .. code-block:: sh
      :caption: Synposis
   
      if condition_1
         then
         # commands
      elif condition_2
         then
         # commands
      else
         # commands
      fi
   
   .. code-block:: sh
      :caption: Check if str is empty
   
      str="Hello World"
      str2=" "
      str3=""
      
      # You need a space on either side of the !=.
      # spaces between "[", "]" cannot be omitted.
   
      if [ ! -z "$str" -a "$str" != " " ]; then
              echo "Str is not null or space"
      fi
      
      if [ ! -z "$str2" -a "$str2" != " " ]; then
              echo "Str2 is not null or space"
      fi
      
      if [ ! -z "$str3" -a "$str3" != " " ]; then
              echo "Str3 is not null or space"
      fi


#. Flow Control : while/until

   .. code-block:: sh
      :caption: Synposis
   
      while / until condition
      do
         # commands
      done
   
   ``until`` excute the loop when the condition is false.
   
   Variant ``do ... while/until`` syntax::
   
      while/until 
            Commands ...
      do :; done
   
   .. code-block:: sh
   
      i=16
      while
            echo "this command is executed at least once $i"
            : ${start=$i}              # capture the starting value of i
            # some other commands      # needed for the loop
            i="$((i+1))"               # increment the variable of the loop.
            [ "$i" -lt 20 ]            # test the limit of the loop.
            # (( ++i < 20 ))
      do :;  done
      echo "Final value of $i///$start"
      echo "The loop was executed $(( i - start )) times "
   
   .. code-block:: sh
      :caption: Check if a process is alive
   
      result=""
      until
         sleep 5 
         result=$(ps aux | grep coke_cola_package | grep -v grep)
         [ -z "$result" ]
      do :; done

   .. code-block:: sh

      i=16
      start=$i
      while
         [ "$i" -lt 20 ]     # test the limit of the loop.
      do 
         echo "this command is executed at least once $i"
         i="$((i+1))"               # increment the variable of the loop.
      done
      echo "Final value of $i"
      echo "The loop was executed $(( i - start )) times "

#. Flow Control: case

   .. code-block:: sh
      :caption: Synposis
   
      case word in
         pattern1)
            Statement(s) to be executed if pattern1 matches
            ;; # similar to break in C/C++
         pattern2)
            Statement(s) to be executed if pattern2 matches
            ;;
         pattern3)
            Statement(s) to be executed if pattern3 matches
            ;;
         *)
           Default condition to be executed
           ;;
      esac
   
   .. code-block:: sh
      :caption: case example match specific string
   
      #!/usr/bin/env sh
   
      FRUIT="kiwi"
      
      case "$FRUIT" in
         "apple") echo "Apple pie is quite tasty." 
         ;;
         "banana") echo "I like banana nut bread." 
         ;;
         "kiwi") echo "New Zealand is famous for kiwi." 
         ;;
         *) echo "Sorry, I have no idea."
         ;;
      esac
   
   .. code-block:: sh
      :caption: case example prints file information
   
      #!/bin/sh
   
      option="${1}" 
      case ${option} in 
         -f) FILE="${2}" 
            echo "File name is $FILE"
            ;; 
         -d) DIR="${2}" 
            echo "Dir name is $DIR"
            ;; 
         *)  
            echo "`basename ${0}`:usage: [-f file] | [-d directory]" 
            exit 1 # Command to come out of the program with status 1
            ;; 
      esac 
