*************
Copy-on-write
*************

**Overview**

Copy-on-write (CoW or COW), sometimes referred to as implicit sharing or shadowing, 
is a resource-management technique used in computer programming to efficiently implement 
a "duplicate" or "copy" operation on modifiable resources. If a resource is duplicated but 
not modified, it is not necessary to create a new resource; the resource can be shared between 
the copy and the original. Modifications must still create a copy, hence the technique: the copy 
operation is deferred to the first write. By sharing resources in this way, it is possible to 
significantly reduce the resource consumption of unmodified copies, while adding a small overhead 
to resource-modifying operations.


**In software**

In multithreaded systems, COW can be implemented without the use of traditional locking 
and instead use compare-and-swap to increment or decrement the internal reference counter. 
Since the original resource will never be altered, it can safely be copied by multiple threads 
(after the reference count was increased) without the need of performance-expensive locking such 
as mutexes. If the reference counter turns 0, then by definition only 1 thread was holding a 
reference so the resource can safely be de-allocated from memory, again without the use of 
performance-expensive locking mechanisms. The benefit of not having to copy the resource 
(and the resulting performance gain over traditional deep-copying) will therefore be valid 
in both single- and multithreaded systems.


**Examples**

The string class provided by the C++ standard library was specifically designed to allow 
copy-on-write implementations in the initial C++98 standard, but not in the newer 
C++11 standard::

   std::string x("Hello");
   std::string y = x;  // x and y use the same buffer
   y += ", World!";    // now y uses a different buffer while x still uses the same old buffer

In the PHP programming language, all types except references are implemented as copy-on-write. 
For example, strings and arrays are passed by reference, but when modified, they are duplicated 
if they have non-zero reference counts. This allows them to act as value types without the performance 
problems of copying on assignment or making them immutable.

In the Qt framework, many types are copy-on-write ("implicitly shared" in Qt's terms). Qt uses atomic 
compare-and-swap operations to increment or decrement the internal reference counter. Since the copies 
are cheap, Qt types can often be safely used by multiple threads without the need of locking mechanisms 
such as mutexes. The benefits of CoW are thus valid in both single- and multithreaded systems.


**In computer storage**

CoW may also be used as the underlying mechanism for snapshots, such as those provided by logical volume management, 
file systems such as Btrfs and ZFS, and database servers such as Microsoft SQL Server. Typically, the snapshots 
store only the modified data, and are stored close to the main array, so they are only a weak form of incremental 
backup and cannot substitute for a full backup. Some systems also use a CoW technique to avoid the fuzzy backups, 
otherwise incurred when any file in the set of files being backed up changes during that backup.

When implementing snapshots, there are two techniques:

   #. The original storage is never modified. When a write request is made, 
      it is redirected away from the original data into a new storage area. 
      (called "Redirect-on-write" or ROW)

   #. When a write request is made, the data are copied into a new storage area, 
      and then the original data are modified. (called "Copy-on-write" or CoW)

Despite their names, copy-on-write usually refers to the first technique. 
CoW does two data writes compared to ROW's one; it is difficult to implement 
efficiently and thus used infrequently.

The CoW technique can be used to emulate a read-write storage on media 
that require wear leveling or are physically write once read many.

Some Live CDs (and Live USBs) use copy-on-write techniques to give the impression 
of being able to add and delete files in any directory, without actually making 
any changes to the CD (or USB flash drive).


**In high-reliability software**

Phantom OS uses CoW at all levels, not just a database or file system. At any time, 
a computer running this system can fail, and then, when it starts again, the software 
and operating system resume operation. Only small amounts of work can be lost.

The basic approach is that all program data are kept in virtual memory. On some schedule, 
a summary of all software data are written to disk storage, forming a log that tracks 
the current value and location of each value.

When the computer fails, a recent copy of the log and other data remain safe on disk. When 
operation resumes, operating system software reads the log to restore consistent copies of 
all the programs and data.

This approach uses CoW at all levels in all software, including in application software. 
This requires support within the application programming language. In practice, Phantom OS 
permits only languages that generate Java byte codes.