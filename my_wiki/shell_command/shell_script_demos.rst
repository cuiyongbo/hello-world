******************
Shell Script Demos
******************

.. code-block:: sh
    :caption: md2html.sh

    #!/usr/bin/env bash

    # extract filename without extension
    # https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash
    #filename=`pwd`/readme.md
    #ext="${filename##*.}"
    #name="${filename%.*}"
    #
    #echo ${filename}
    #echo ${ext}
    #echo ${name}
    
    if [ $# -ne 1 ]; then
        echo "Usage: `basename $0` dirname"
        exit 1
    fi
    
    if [ ! -e $1 ]; then
        echo "Parameter error: <$1> doesn't exist!"
        exit 1
    fi
    
    if [ ! -d $1 ]; then
        echo "Parameter error: <$1> is not a directory!"
        exit 1
    fi
        
    files=`find $1 -name "*.md"`
    for i in ${files}; do
        filename=$i
        name="${filename%.*}"
        #echo ${name}.html
        pandoc -f markdown -t html $i > ${name}.html
    done
