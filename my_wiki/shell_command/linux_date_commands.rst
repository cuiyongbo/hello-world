*************
Date Commands
*************

#. cal, ncal -- displays a calendar and the date of easter

    The cal utility displays a simple calendar in traditional format 
    and ncal offers an alternative layout, more options and the date
    of easter.  The new format is a little cramped but it makes a year 
    fit on a 25x80 terminal.  If arguments are not specified, the
    current month is displayed.

    .. option:: -m month
             
        Display the specified month.

    .. option:: -y      

        Display a calendar for the specified year.

#. ``date`` Usage
   
    .. code-block:: none

        $ date --help                                                                                            
        Usage: date [OPTION]... [+FORMAT]                                                                        
          or:  date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]]                                               
        Display the current time in the given FORMAT, or set the system date.                                    
                                                                                                                 
        Mandatory arguments to long options are mandatory for short options too.                                 
          -d, --date=STRING          display time described by STRING, not 'now'                                 
          -f, --file=DATEFILE        like --date; once for each line of DATEFILE                                 
          -I[FMT], --iso-8601[=FMT]  output date/time in ISO 8601 format.                                        
                                       FMT='date' for date only (the default),                                   
                                       'hours', 'minutes', 'seconds', or 'ns'                                    
                                       for date and time to the indicated precision.                             
                                       Example: 2006-08-14T02:34:56-0600                                         
          -R, --rfc-2822             output date and time in RFC 2822 format.                                    
                                       Example: Mon, 14 Aug 2006 02:34:56 -0600                                  
              --rfc-3339=FMT         output date/time in RFC 3339 format.                                        
                                       FMT='date', 'seconds', or 'ns'                                            
                                       for date and time to the indicated precision.                             
                                       Example: 2006-08-14 02:34:56-06:00                                        
          -r, --reference=FILE       display the last modification time of FILE                                  
          -s, --set=STRING           set time described by STRING                                                
          -u, --utc, --universal     print or set Coordinated Universal Time (UTC)                               
              --help     display this help and exit                                                              
              --version  output version information and exit                                                     
                                                                                                                 
        FORMAT controls the output.  Interpreted sequences are:                                                  
                                                                                                                 
          %%   a literal %                                                                                       
          %a   locale's abbreviated weekday name (e.g., Sun)                                                     
          %A   locale's full weekday name (e.g., Sunday)                                                         
          %b   locale's abbreviated month name (e.g., Jan)                                                       
          %B   locale's full month name (e.g., January)                                                          
          %c   locale's date and time (e.g., Thu Mar  3 23:05:25 2005)                                           
          %C   century; like %Y, except omit last two digits (e.g., 20)                                          
          %d   day of month (e.g., 01)                                                                           
          %D   date; same as %m/%d/%y                                                                            
          %e   day of month, space padded; same as %_d                                                           
          %F   full date; same as %Y-%m-%d                                                                       
          %g   last two digits of year of ISO week number (see %G)                                               
          %G   year of ISO week number (see %V); normally useful only with %V                                    
          %h   same as %b                                                                                        
          %H   hour (00..23)                                                                                     
          %I   hour (01..12)                                                                                     
          %j   day of year (001..366)                                                                            
          %k   hour, space padded ( 0..23); same as %_H                                                          
          %l   hour, space padded ( 1..12); same as %_I                                                          
          %m   month (01..12)                                                                                    
          %M   minute (00..59)                                                                                   
          %n   a newline                                                                                         
          %N   nanoseconds (000000000..999999999)                                                                
          %p   locale's equivalent of either AM or PM; blank if not known                                        
          %P   like %p, but lower case                                                                           
          %r   locale's 12-hour clock time (e.g., 11:11:04 PM)                                                   
          %R   24-hour hour and minute; same as %H:%M                                                            
          %s   seconds since 1970-01-01 00:00:00 UTC                                                             
          %S   second (00..60)                                                                                   
          %t   a tab                                                                                             
          %T   time; same as %H:%M:%S                                                                            
          %u   day of week (1..7); 1 is Monday                                                                   
          %U   week number of year, with Sunday as first day of week (00..53)                                    
          %V   ISO week number, with Monday as first day of week (01..53)                                        
          %w   day of week (0..6); 0 is Sunday                                                                   
          %W   week number of year, with Monday as first day of week (00..53)                                    
          %x   locale's date representation (e.g., 12/31/99)                                                     
          %X   locale's time representation (e.g., 23:13:48)                                                     
          %y   last two digits of year (00..99)                                                                  
          %Y   year                                                                                              
          %z   +hhmm numeric time zone (e.g., -0400)                                                             
          %:z  +hh:mm numeric time zone (e.g., -04:00)                                                           
          %::z  +hh:mm:ss numeric time zone (e.g., -04:00:00)                                                    
          %:::z  numeric time zone with : to necessary precision (e.g., -04, +05:30)                             
          %Z   alphabetic time zone abbreviation (e.g., EDT)                                                     
                                                                                                                 
        By default, date pads numeric fields with zeroes.                                                        
        The following optional flags may follow '%':                                                             
                                                                                                                 
          -  (hyphen) do not pad the field                                                                       
          _  (underscore) pad with spaces                                                                        
          0  (zero) pad with zeros                                                                               
          ^  use upper case if possible                                                                          
          #  use opposite case if possible                                                                       
                                                                                                                 
        After any flags comes an optional field width, as a decimal number;                                      
        then an optional modifier, which is either                                                               
        E to use the locale's alternate representations if available, or                                         
        O to use the locale's alternate numeric symbols if available.                                            
                                                                                                                                                             
#. Linux to get current calendar
   
    .. code-block:: sh

        $ cal
          June 2018
        Su Mo Tu We Th Fr Sa
                        1  2
         3  4  5  6  7  8  9
        10 11 12 13 14 15 16
        17 18 19 20 21 22 23
        24 25 26 27 28 29 30
    
        $ cal -m 8
         August 2018
        Su Mo Tu We Th Fr Sa
                  1  2  3  4
         5  6  7  8  9 10 11
        12 13 14 15 16 17 18
        19 20 21 22 23 24 25
        26 27 28 29 30 31


        $ cal 2018
                                   2018
      
            January               February               March
        Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
            1  2  3  4  5  6               1  2  3               1  2  3
         7  8  9 10 11 12 13   4  5  6  7  8  9 10   4  5  6  7  8  9 10
        14 15 16 17 18 19 20  11 12 13 14 15 16 17  11 12 13 14 15 16 17
        21 22 23 24 25 26 27  18 19 20 21 22 23 24  18 19 20 21 22 23 24
        28 29 30 31           25 26 27 28           25 26 27 28 29 30 31
                                                    
        ...

#. Linux ``date`` usage
   
    .. code-block:: sh
   
        # show current date
        $ date
        Sun Jul 15 23:07:11 CST 2018

        # get current unix timestamp
        $ date +%s
        1594909752

        # convert timestamp to current local time
        $ date -d @1564716345
        Fri, Aug  2, 2019 11:25:45

        # ditto, but with specified format
        $ date '+%Y-%m-%d' -d @1564716345
        2019-08-02