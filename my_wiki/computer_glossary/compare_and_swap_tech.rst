****************
Compare-and-swap
****************

**Overview**

In computer science, :abbr:`CAS (compare-and-swap)` is an atomic instruction 
used in multithreading to achieve synchronization. It compares the contents 
of a memory location with a given value and, only if they are the same, 
modifies the contents of that memory location to a new given value. This is 
done as **a single atomic operation**. The atomicity guarantees that the new 
value is calculated based on up-to-date information; if the value had been 
updated by another thread in the meantime, the write would fail. The result 
of the operation must indicate whether it performed the substitution; this 
can be done either with a simple boolean response (this variant is often 
called *compare-and-set*), or by returning the previous value read from the 
memory location.

A CAS operation is an atomic version of the following pseudocode, 
where * denotes access through a pointer::

   function cas(p : pointer to int, old : int, new : int) returns bool 
   {
       if *p != old {
           return false
       }
       *p = new
       return true
   }

**This operation is used to implement synchronization primitives like semaphores and mutexes**, 
as well as more sophisticated lock-free and wait-free algorithms. 

Algorithms built around CAS typically read some key memory location and remember the old value. 
Based on that old value, they compute some new value. Then they try to swap in the new value using CAS, 
where the comparison checks for the location still being equal to the old value. If CAS indicates that 
the attempt has failed, it has to be repeated from the beginning: the location is re-read, a new value 
is re-computed and the CAS is tried again.

Instead of immediately retrying after a CAS fails, researchers have found that total system performance 
can be improved—in multiprocessor systems where many threads constantly update some particular shared 
variable—if threads that see their CAS fail use exponential backoff—in other words, wait a little before 
retrying the CAS.


**Example application: atomic adder**

As an example use case of CAS, here is an algorithm for atomically incrementing or decrementing an integer. 
This is useful in a variety of applications that use counters. The function add performs the action 
``*p <-- *p + a``, atomically and returns the final value stored in the counter. Unlike in the *cas* pseudocode 
above, there is no requirement that any sequence of operations is atomic except for *cas* ::

   function add(p : pointer to int, a : int) returns int 
   {
       done = false
       while not done {
           value = *p  // Even this operation doesn't need to be atomic.
           done = cas(p, value, value + a)
       }
       return value + a
   }


**Implementation in C**

Many C compilers support using CAS either with the C11 *stdatomic.h* functions, 
or some non-standard C extension of that particular C compiler, or by calling a function 
written directly in assembly language using the CAS instruction.

The following C function shows the basic behavior of a CAS variant that returns the old value 
of the specified memory location; however, this version does not provide the crucial guarantees 
of atomicity that a real CAS operation would::

   int compare_and_swap(int* reg, int oldval, int newval)
   {
     ATOMIC();
     int old_reg_val = *reg;
     if (old_reg_val == oldval)
        *reg = newval;
     END_ATOMIC();
     return old_reg_val;
   }

*old_reg_val* is always returned, but it can be tested following the *compare_and_swap* operation to see 
if it matches *oldval*, as it may be different, meaning that another process has managed to succeed in a 
competing *compare_and_swap* to change the reg value from *oldval*.

For example, an **election protocol** can be implemented such that every process checks the result of *compare_and_swap* 
against its own PID (= *newval*). The winning process finds the *compare_and_swap* returning the initial non-PID value 
(e.g., zero). For the losers it will return the winning PID::

   bool compare_and_swap(int *accum, int *dest, int newval)
   {
     if (*accum == *dest) {
         *dest = newval;
         return true;
     } else {
         *accum = *dest;
         return false;
     }
   }

This is the logic in the Intel Software Manual Vol 2A.
