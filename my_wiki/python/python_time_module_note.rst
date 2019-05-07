******************
Python time Module
******************

Hot APIs
========

.. class:: time.struct_time

   The type of the time value sequence returned by gmtime(), localtime(), and strptime(). 
   It is an object with a named tuple interface: values can be accessed by index and 
   by attribute name. The following values are present:

   +-----------------+----------+---------------------------+
   | Index Attribute | Values   | Range                     |
   +=================+==========+===========================+
   | 0               | tm_year  | (for example, 1993)       |
   +-----------------+----------+---------------------------+
   | 1               | tm_mon   | range [1, 12]             |
   +-----------------+----------+---------------------------+
   | 2               | tm_mday  | range [1, 31]             |
   +-----------------+----------+---------------------------+
   | 3               | tm_hour  | range [0, 23]             |
   +-----------------+----------+---------------------------+
   | 4               | tm_min   | range [0, 59]             |
   +-----------------+----------+---------------------------+
   | 5               | tm_sec   | range [0, 61]             |
   +-----------------+----------+---------------------------+
   | 6               | tm_wday  | range [0, 6], Monday is 0 |
   +-----------------+----------+---------------------------+
   | 7               | tm_yday  | range [1, 366]            |
   +-----------------+----------+---------------------------+
   | 8               | tm_isdst | 0, 1 or -1                |
   +-----------------+----------+---------------------------+

**Note** that unlike the C structure, the month value is a range of [1, 12], not [0, 11]. 
A year value will be handled as described under Year 2000 (Y2K) issues above.

In calls to *mktime()*, tm_isdst may be set to 1 when daylight savings time is in effect, 
and 0 when it is not. A value of -1 indicates that this is not known, and will usually 
result in the correct state being filled in.

When a tuple with an incorrect length is passed to a function expecting a *struct_time*, 
or having elements of the wrong type, a :exc:`TypeError` is raised.


.. function:: time.time()

   Return the **time in seconds since the epoch** as a floating point number. 
   Note that even though the time is always returned as a floating point number, 
   not all systems provide time with a better precision than 1 second. While this 
   function normally returns non-decreasing values, it can return a lower value than 
   a previous call if the system clock has been set back between the two calls.

   .. note::

      The *time.time()* function returns the number of seconds since the epoch, as seconds. 
      Note that the "epoch" is defined as the start of January 1st, 1970 in UTC. So the 
      epoch is defined in terms of UTC and establishes a global moment in time. 
      *time.time()* returns the same value at the same moment wherever you are.

.. function:: time.ctime([secs])

   Convert a time expressed in seconds since the epoch to a string representing **local time**. 
   If *secs* is not provided or *None*, the current time as returned by *time()* is used. 
   *ctime(secs)* is equivalent to *asctime(localtime(secs))*. 

.. function:: time.gmtime([secs])

   Convert a time expressed in seconds since the epoch to a *struct_time* in UTC 
   in which the *dst* flag is always zero. If *secs* is not provided or *None*, 
   the current time as returned by *time()* is used. Fractions of a second are 
   ignored.

.. function:: time.localtime([secs])

   Like *gmtime()* but converts to local time.
   The *dst* flag is set to 1 when DST applies to the given time.

.. function:: time.mktime(t)

   This is the inverse function of *localtime()*. Its argument is the *struct_time* 
   or full 9-tuple (since the dst flag is needed; use -1 as the dst flag if it is unknown) 
   which expresses the time in local time, not UTC. It returns a floating point number, for 
   compatibility with *time()*. If the input value cannot be represented as a valid time, 
   either :exc:`OverflowError` or :exc:`ValueError` will be raised (which depends on whether 
   the invalid value is caught by Python or the underlying C libraries). The earliest date 
   for which it can generate a time is platform-dependent.


.. function:: time.asctime([t])

   Convert a tuple or *struct_time* representing a time as returned by *gmtime()* or *localtime()* 
   to a 24-character string of the following form: 'Sun Jun 20 23:21:05 1993'. If t is not provided, 
   the current time as returned by *localtime()* is used. 

   Locale information is not used.

   Note Unlike the C function of the same name, there is no trailing newline.


.. function:: time.sleep(secs)

   Suspend execution of the current thread for the given number of seconds. The argument may 
   be a floating point number to indicate a more precise sleep time. The actual suspension 
   time may be less than that requested because any caught signal will terminate the *sleep()* 
   following execution of that signal’s catching routine. Also, the suspension time may be longer 
   than requested by an arbitrary amount because of the scheduling of other activity in the system.


.. function:: time.clock()

   On Unix, return the current processor time as a floating point number expressed in seconds. 
   The precision, and in fact the very definition of the meaning of “processor time”, depends 
   on that of the C function of the same name, but in any case, this is the function to use for 
   benchmarking Python or timing algorithms.

   On Windows, this function returns wall-clock seconds elapsed since the first call to this function, 
   as a floating point number, based on the Win32 function *QueryPerformanceCounter()*. The resolution 
   is typically better than one microsecond.

.. function:: time.strftime(format[, t])

   Convert a tuple or *struct_time* representing a time as returned by *gmtime()* or *localtime()* to a 
   string as specified by the *format* argument. If *t* is not provided, the current time as returned by 
   *localtime()* is used. *format* must be a string. :exc:`ValueError` is raised if any field in *t* is 
   outside of the allowed range. *strftime()* returns a locale depedent byte string; the result may be 
   converted to unicode by doing ``strftime(<myformat>).decode(locale.getlocale()[1])``.

   Here is an example, a format for dates compatible with that specified in the RFC 2822 Internet 
   email standard::

      >>> time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
      'Tue, 05 Jun 2018 06:24:33 +0000


.. function:: time.strptime(string[, format])

   Parse a *string* representing a time according to a *format*. 
   The return value is a *struct_time* as returned by *gmtime()* or *localtime()*.

   The *format* parameter uses the same directives as those used by *strftime()*; 
   it defaults to ``"%a %b %d %H:%M:%S %Y"`` which matches the formatting returned by *ctime()*. 
   If *string* cannot be parsed according to *format*, or if it has excess data after parsing, 
   :exc:`ValueError` is raised. The default values used to fill in any missing data when more 
   accurate values cannot be inferred are ``(1900, 1, 1, 0, 0, 0, 0, 1, -1)``.

   For example::

      >>> time.strptime("14:30 6/5/2018", "%H:%S %m/%d/%Y")
      time.struct_time(tm_year=2018, tm_mon=6, tm_mday=5, tm_hour=14, tm_min=0, tm_sec=30, tm_wday=1, tm_yday=156, tm_isdst=-1)

   Support for the ``%Z`` directive is based on the values contained in *tzname* and whether *daylight* is true. 
   Because of this, it is platform-specific except for recognizing UTC and GMT which are always known (and are 
   considered to be non-daylight savings timezones).

   Only the directives specified in the documentation are supported. Because *strftime()* is implemented per platform 
   it can sometimes offer more directives than those listed. But *strptime()* is independent of any platform and thus 
   does not necessarily support all directives available that are not documented as supported.


Format Directives
=================

The following directives can be embedded in the format string used by *strftime()* and *strptime()*. 
They are shown without the optional field width and precision specification:

   +-----------+---------------------------------------------------------------+-------+
   | Directive | Meaning                                                       | Notes |
   +===========+===============================================================+=======+
   | %a        | Locale’s abbreviated weekday name.                            |       |
   +-----------+---------------------------------------------------------------+-------+
   | %A        | Locale’s full weekday name.                                   |       |
   +-----------+---------------------------------------------------------------+-------+
   | %b        | Locale’s abbreviated month name.                              |       |
   +-----------+---------------------------------------------------------------+-------+
   | %B        | Locale’s full month name.                                     |       |
   +-----------+---------------------------------------------------------------+-------+
   | %c        | Locale’s appropriate date and time representation.            |       |
   +-----------+---------------------------------------------------------------+-------+
   | %d        | Day of the month as a decimal number [01,31].                 |       |
   +-----------+---------------------------------------------------------------+-------+
   | %H        | Hour (24-hour clock) as a decimal number [00,23].             |       |
   +-----------+---------------------------------------------------------------+-------+
   | %I        | Hour (12-hour clock) as a decimal number [01,12].             |       |
   +-----------+---------------------------------------------------------------+-------+
   | %j        | Day of the year as a decimal number [001,366].                |       |
   +-----------+---------------------------------------------------------------+-------+
   | %m        | Month as a decimal number [01,12].                            |       |
   +-----------+---------------------------------------------------------------+-------+
   | %M        | Minute as a decimal number [00,59].                           |       |
   +-----------+---------------------------------------------------------------+-------+
   | %p        | Locale’s equivalent of either AM or PM.                       | \(1)  |
   +-----------+---------------------------------------------------------------+-------+
   | %S        | Second as a decimal number [00,61].                           | \(2)  |
   +-----------+---------------------------------------------------------------+-------+
   | %U        | Week number of the year (Sunday as the first day of the week) | \(3)  |
   |           | as a decimal number [00,53]. All days in a new year preceding |       |
   |           | the first Sunday are considered to be in week 0.              |       |
   +-----------+---------------------------------------------------------------+-------+
   | %w        | Weekday as a decimal number [0(Sunday),6].                    |       |
   +-----------+---------------------------------------------------------------+-------+
   | %W        | Week number of the year (Monday as the first day of the week) | \(3)  |
   |           | as a decimal number [00,53]. All days in a new year preceding |       |
   |           | the first Monday are considered to be in week 0.              |       |
   +-----------+---------------------------------------------------------------+-------+
   | %x        | Locale’s appropriate date representation.                     |       |
   +-----------+---------------------------------------------------------------+-------+
   | %X        | Locale’s appropriate time representation.                     |       |
   +-----------+---------------------------------------------------------------+-------+
   | %y        | Year without century as a decimal number [00,99].             |       |
   +-----------+---------------------------------------------------------------+-------+
   | %Y        | Year with century as a decimal number.                        |       |
   +-----------+---------------------------------------------------------------+-------+
   | %Z        | Time zone name (no characters if no time zone exists).        |       |
   +-----------+---------------------------------------------------------------+-------+
   | %%        | A literal '%' character.                                      |       |
   +-----------+---------------------------------------------------------------+-------+

Notes:

   (1) When used with the *strptime()* function, the ``%p`` directive only affects the output hour field 
       if the ``%I`` directive is used to parse the hour.

   (2) The range really is 0 to 61; this accounts for leap seconds and the (very rare) double leap seconds.
       
   (3) When used with the *strptime()* function, ``%U`` and ``%W`` are only used in calculations when the 
       day of the week and the year are specified.

#. Convert DateTime to timestamp
   
   .. code-block:: py

      >>> dt = datetime.datetime(2018, 12, 10, 17, 38, 0, 0)
      >>> time.mktime(dt.timetuple())
      1544434680.0      