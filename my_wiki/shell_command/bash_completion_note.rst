********************
Bash Completion note
********************

First, run ``apt list bash-completion`` check if **bash_completion** has been installed.

.. code-block:: sh

    # A completion function for the cd builtin
    # based on the cd completion function from the bash_completion package
    _comp_cd()
    {
        local IFS=$' \t\n'    # normalize IFS
        local cur _skipdot _cdpath
        local i j k
    
        # Tilde expansion, which also expands tilde to full pathname
        case "$2" in
        \~*)    eval cur="$2" ;;
        *)      cur=$2 ;;
        esac
    
        # no cdpath or absolute pathname -- straight directory completion
        if [[ -z "${CDPATH:-}" ]] || [[ "$cur" == @(./*|../*|/*) ]]; then
            # compgen prints paths one per line; could also use while loop
            IFS=$'\n'
            COMPREPLY=( $(compgen -d -- "$cur") )
            IFS=$' \t\n'
        # CDPATH+directories in the current directory if not in CDPATH
        else
            IFS=$'\n'
            _skipdot=false
            # preprocess CDPATH to convert null directory names to .
            _cdpath=${CDPATH/#:/.:}
            _cdpath=${_cdpath//::/:.:}
            _cdpath=${_cdpath/%:/:.}
            for i in ${_cdpath//:/$'\n'}; do
                if [[ $i -ef . ]]; then _skipdot=true; fi
                k="${#COMPREPLY[@]}"
                for j in $( compgen -d -- "$i/$cur" ); do
                    COMPREPLY[k++]=${j#$i/}        # cut off directory
                done
            done
            $_skipdot || COMPREPLY+=( $(compgen -d -- "$cur") )
            IFS=$' \t\n'
        fi
    
        # variable names if appropriate shell option set and no completions
        if shopt -q cdable_vars && [[ ${#COMPREPLY[@]} -eq 0 ]]; then
            COMPREPLY=( $(compgen -v -- "$cur") )
        fi
    
        return 0
    }
    
    # Tell readline to quote appropriate and append slashes to directories;
    # use the bash default completion for other arguments
    complete -o filenames -o nospace -o bashdefault -F _comp_cd cd


.. rubric:: Footnotes

.. [#] `Programmable Completion <http://www.gnu.org/software/bash/manual/bash.html#Programmable-Completion>`_
.. [#] `Programmable Completion Builtins <http://www.gnu.org/software/bash/manual/bash.html#Programmable-Completion-Builtins>`_
.. [#] `More examples <http://bash-completion.alioth.debian.org/>`_
