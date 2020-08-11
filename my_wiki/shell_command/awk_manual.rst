**********
awk Manual
**********

NAME: mawk - pattern scanning and text processing language

**SYNOPSIS**

    .. code-block:: sh

        mawk [-W option] [-F value] [-v var=value] [--] 'program text' [file ...]
        mawk [-W option] [-F value] [-v var=value] [-f program-file] [--] [file ...]

**DESCRIPTION**

    An AWK program is a sequence of ``pattern {action}`` pairs and function definitions.  
    Short programs are entered on the command line usually enclosed in ``' '`` to avoid 
    shell interpretation. Longer programs can be read in from a file with the *-f* option.  
    Data input is read from the list of files on the command line or from standard input 
    when the list is empty.  The input is broken into records as determined by the record 
    separator variable, *RS*.  Initially, ``RS = "\n"`` and records are synonymous with lines.  
    Each record is compared against each *pattern* and if it matches, the program text for 
    ``{action}`` is executed.


**OPTIONS**

    .. option:: -F value       

        sets the field separator, FS, to value.

    .. option:: -f file 

        Program text is read from file instead of from the command line.  
        Multiple -f options are allowed.

    .. option:: -v var=value   

        assigns value to program variable var.

    .. note::

        ``--`` indicates the unambiguous end of options.


**Basics**

    A pattern can be::

        BEGIN
        END
        expression
        expression , expression

    One, but not both, of ``pattern {action}`` can be omitted. If ``{action}`` is omitted it is 
    implicitly ``{ print }``. If pattern is omitted, then it is implicitly matched.  **BEGIN** 
    and *END* patterns require an action.

    Statements are terminated by newlines, semi-colons or both. Groups of statements such as actions 
    or loop bodies are blocked via ``{ ... }`` as in C. The last statement in a block doesn't need a
    terminator. Blank lines have no meaning; an empty statement is terminated with a semi-colon. 
    Long statements can be continued with a backslash, ``\``.  A statement can be broken without a 
    backslash after a comma, left brace, &&, ||, *do*, *else*, the right parenthesis of an *if*, 
    *while* or *for* statement, and the right parenthesis of a function definition. A comment starts 
    with *#* and extends to, but does not include the end of line.

    The following statements control program flow inside blocks::

        if ( expr ) statement
        if ( expr ) statement else statement
        while ( expr ) statement
        do statement while ( expr )
        for ( opt_expr ; opt_expr ; opt_expr ) statement
        for ( var in array ) statement
        continue
        break

    Records are read in one at a time, and stored in the field variable ``$0``.  
    The record is split into fields which are stored in ``$1, $2, ..., $NF``.  
    The built-in variable **NF** is set to the number of fields, and **NR** and **FNR** 
    are incremented by 1. Fields above $NF are set to "".

    Assignment to ``$0`` causes the fields and NF to be recomputed. Assignment to NF or 
    to a field causes ``$0`` to be reconstructed by concatenating the $i's separated by **OFS**.  
    Assignment to a field with index greater than NF, increases NF and causes $0 to be reconstructed.

    Data input stored in fields is string, unless the entire field has numeric form and then 
    the type is number and string. For example,

        .. code-block:: sh

            echo 24 24E |
            mawk '{ print($1>100, $1>"100", $2>100, $2>"100") }'
            0 1 1 1

    $0 and $2 are string and $1 is number and string. The first comparison is numeric, 
    the second is string, the third is string (100 is converted to "100"), and the last is string.

    The expression syntax is similar to C. Primary expressions are numeric constants, string constants, 
    variables, fields, arrays and function calls. The identifier for a variable, array or function can 
    be a sequence of letters, digits and underscores, that does not start with a digit. Variables are 
    not declared; they exist when first referenced and are initialized to null.

    New expressions are composed with the following operators in order of increasing precedence::

        assignment          =  +=  -=  *=  /=  %=  ^=
        conditional         ?  :
        logical or          ||
        logical and         &&
        array membership    in
        matching            ~   !~
        relational          <  >   <=  >=  ==  !=
        concatenation       (no explicit operator)
        add ops             +  -
        mul ops             *  /  %
        unary               +  -
        logical not         !
        exponentiation      ^
        inc and dec         ++ -- (both post and pre)
        field               $

    Assignment, conditional and exponentiation associate right to left; 
    the other operators associate left to right. Any expression can be parenthesized.

    The following variables are built-in and initialized before program execution::

        ARGC      number of command line arguments.
        ARGV      array of command line arguments, 0..ARGC-1.
        CONVFMT   format for internal conversion of numbers to string, initially = "%.6g".
        ENVIRON   array indexed by environment variables.  An environment string, var=value is stored as ENVIRON[var] = value.
        FILENAME  name of the current input file.
        FNR       current record number in FILENAME.
        FS        splits records into fields as a regular expression.
        NF        number of fields in the current record.
        NR        current record number in the total input stream.
        OFMT      format for printing numbers; initially = "%.6g".
        OFS       inserted between fields on output, initially = " ".
        ORS       terminates each record on output, initially = "\n".
        RLENGTH   length set by the last call to the built-in function, match().
        RS        input record separator, initially = "\n".
        RSTART    index set by the last call to match().
        SUBSEP    used to build multiple array subscripts, initially = "\034".

    There are two output statements, `print` and `printf` ::

        print  
        writes $0  ORS to standard output.

        print expr1, expr2, ..., exprn
        writes expr1 OFS expr2 OFS ... exprn ORS to standard output.  
        Numeric expressions are converted to string with OFMT.

        printf format, expr-list
        duplicates the printf C library function writing to standard output.  
        The complete ANSI C format specifications are recognized with 
        conversions %c, %d, %e, %E, %f, %g, %G, %i, %o, %s, %u, %x, %X and %%, 
        and conversion qualifiers h and l.

    The argument list to print or printf can optionally be enclosed in parentheses.  
    Print formats numbers using *OFMT* or "%d" for exact integers. "%c" with a numeric 
    argument prints the corresponding 8 bit character, with a string argument it prints 
    the first character of the string. The output of print and printf can be redirected 
    to a file or command by appending ``>`` file, ``>>`` file or ``|`` command to the end 
    of the print statement. Redirection opens file or command only once, subsequent redirections 
    append to the already open stream. By convention, mawk associates the filename */dev/stderr* 
    with *stderr* which allows print and printf to be redirected to *stderr*. mawk also associates
    ``-`` and */dev/stdout* with stdin and stdout which allows these streams to be passed to functions.

    The input function *getline* has the following variations::

        getline
        reads into $0, updates the fields, NF, NR and FNR.

        getline < file
        reads into $0 from file, updates the fields and NF.

        getline var
        reads the next record into var, updates NR and FNR.

        getline var < file
        reads the next record of file into var.

        command | getline
        pipes a record from command into $0 and updates the fields and NF.

        command | getline var
        pipes a record from command into var.

    Getline returns 0 on end-of-file, -1 on error, otherwise 1.
    Commands on the end of pipes are executed by */bin/sh*.


**EXAMPLES**

#. emulate cat
    
    .. code-block:: sh

        { print }

#. emulate wc

    .. code-block:: sh

        { 
        chars += length($0) + 1  # add one for the \n
        words += NF
        }
        END{ print NR, words, chars }

#. count the number of unique "real words"

    .. code-block:: sh

        BEGIN { FS = "[^A-Za-z]+" }
        { for(i = 1 ; i <= NF ; i++)  word[$i] = "" }
        END { delete word[""]
        for ( i in word )  cnt++
        print cnt
        }

#. sum the second field of every record based on the first field
    
    .. code-block:: sh

        $1 ~ /credit|gain/ { sum += $2 }
        $1 ~ /debit|loss/  { sum -= $2 }
        END { print sum }

#. sort a file, comparing as string

    .. code-block:: sh

        { line[NR] = $0 "" }  # make sure of comparison type
                            # in case some lines look numeric

        END { isort(line, NR); for(i = 1 ; i <= NR ; i++) print line[i]}

        #insertion sort of A[1..n]
        function isort( A, n, i, j, hold)
        {
        for( i = 2 ; i <= n ; i++)
        {
            hold = A[j = i]
            while ( A[j-1] > hold )
            { j-- ; A[j+1] = A[j] }
            A[j] = hold
        }
        # sentinel A[0] = "" will be created if needed
        }

#. compute sum and average

    .. code-block:: sh

        $ echo 'a=1 b=2 c=3' | grep -Eo '[0-9]+' | awk 'BEGIN{sum=0}{sum += $1}END{print "sum =", sum}'
        sum = 6

        $ echo 'a=1 b=2 c=3' | grep -Eo '[0-9]+' | awk 'BEGIN{sum=0}{sum += $1}END{print "average =", sum/NR}'
        average = 2

#. more examples
    
    .. code-block:: sh
    
        gawk '{ sum += $1 }; END { print sum }' file
        gawk -F: '$0 ~ /^#/ {next}; {print $1}' /etc/passwd | sort | uniq | wc -l
        awk '$0 ~ /^#/{next}; {FS=":"}; {print $NF}' /etc/passwd
        awk -F: '{print $NF, $(NF-1)}' /etc/passwd

        echo | awk '{var1="v1";var2="v2";var3="v3"; print var1"="var2"="var3;}'
        echo | awk 'BEGIN{i=0;print "start i=" i;} {i++;} END{print "end i=" i;}'
        echo -e "A line 1\nA line 2" | awk 'BEGIN{print "start"} {print} END{print "end"}'

        awk 'END{print NR}' out (统计 out 的行数) # wc -l out
        awk '{print $2,$3}' out (打印 out 文件每行的第2,3个字段)
        echo -e "line1 f2 f3\nline2 f4 f5" | awk '{print $NF,$(NF-1)}' (打印每行的最后两个字段)
        seq 5 | awk 'BEGIN{sum=0;} {print $1;sum+=$1} END{print "sum:"sum}'

        # 传递外部变量示例
        export VAR=1024;
        echo | awk -v VAL=$VAR '{print VAL}' 
        echo | awk '{print v1,v2}' v1=$VAR1 v2=$VAR2

        # 算术运算示例:
        awk '{a="b"; print a++,++a;}' # 进行算术运算时,操作数自动转换为数值,非数值类型转换为0
        awk '{a=7;print a+=6,a=a-3,a*=3}'
        awk '{a=1;b=2;print (a>5&&b<=2),(a>5||b<=2)}'
        awk '{a="100testa";if(a ~ /^100*/){print "ok";} else {print "fail";} }'
        awk '{a="b";print a=="b" ? "ok" : "err";}'
        awk '{a="b";arr[0]="b";arr[1]="c";print (a in arr)}'
        awk '{a="b";arr[0]="b";arr["b"]="d";print (a in arr)}'

        # next - skip remaining patterns on this input line
        awk 'NR%2==1 {next} {print NR,$0}' out # 打印偶数行

        # getline 将 date 命令的输出输入到变量 out,split 将 out 的内容以数组的形式存入 mon, 数组下标从1开始
        awk '{"date" | getline out; print out;split(out,mon);print mon[1]}'
        awk '{while("ls" | getline) print}'
        echo | awk '{printf("hello world!") > "test"}'
        echo | awk '{printf("hello world!") >> "test"}'

        # 流程控制语句(类似 C 语言)示例:
        awk 'BEGIN{
        test=100;
        if(test>90){
        print "very good"
        }
        else if(test>60){
        print "good"
        }
        else {
        print "no pass"
        }
        }'
        
        awk 'for(k in ENVIRON) print ENVIRON[k]'
        
        awk '{
        total=0;
        for(i=0;i<100;i++)
        total+=i;
        }'
        
        awk '{
        test=100;total=0;
        while(i<=test){total+=i;i++;}
        print total;
        }'

        awk '{
        test=100;total=0;
        do {
            total+=i;i++
        } while(i<=test);
        print total;
        }'
        # break,continue的用法类似

        # 数组( awk 中数组为 associative array) 示例
        awk '{
        arr[1]="sun";arr[2]="moon";arr[3]="earth";
        arr["night"]="sleep";
        for(term in arr) {
        print arr[term]
        }
        }' # 无序输出

        awk '{
        info="Hello world";
        lens=split(info,tA," ");
        for(k in tA) print k,tA[k];
        }

        awk '{
        info="Hello world";
        lens=split(info,tA," ");
        for(k=1;k<=lens;k++) {print k,tA[k];}
        }' # 有序输出

        awk '{
        info="Hello world";
        lens=split(info,tA," ");
        print length(tA),lens;
        }'

        awk '{
        arr["a"]="a1";arr["b"]="b1";
        if("c" in arr){print "found";}
        for(k in arr) {print k,arr[k];}
        }'

        awk '{
        arr["a"]="a1";arr["b"]="b1";
        delete arr["b"];              
        for(k in arr) {print k,arr[k];}
        }' # 删除键值

        awk '{
        for(i=1;i<=9;i++) {
        for(j=1;j<=9;j++) {
        arr[i,j]=i*j;
        }
        }
        for(m in arr){
        split(m, arr2, SUBSEP);print arr2[1],"*",arr2[2],"=",arr[m];
        }
        }'

        # 内置函数主要分为算术函数,字符串函数,I/O 函数,时间函数.
        awk '{OFMT="%.3f";fs=sin(1);fe=exp(10);fi=int(3.14);print fs,fe,fi;}'
        awk '{print "Enter your name:";getline name;print name;}'
        awk '{printf("%.2f,%.2u,%.2g,%X,%o\n",123.113,-1.244,1.2345,123.113,123.113)}'
        awk '{srand();fr=int(100*rand());print fr;}'
        awk '{info="this is a test23test!";gsub(/[0-9]+/,"!",info);print info;}'
        awk '{info="this is a test";print index(info,"test")?"ok":"not found";}'
        awk '{info="this is a test";split(info, tA," ");print length(tA);for(k in tA){print k,tA[k];}}'
        awk '{info="this is a test";print substr(info,4,10);}'
        awk '{b=system("ls -al");print b;}'
        awk '{while("cat out"|getline){print $0;};close("out");}'
        awk '{while(getline<"out"){print $0;};close("out");}'

        ps aux | grep -i word | grep -v grep | awk '{print $2}'(提取PID)

