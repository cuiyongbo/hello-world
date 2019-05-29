**********************
Computer Terminology 3
**********************

#. Matroska
   
    The Matroska Multimedia Container is an open standard, free container format, 
    a file format that can hold an unlimited number of video, audio, picture, 
    or subtitle tracks in one file. It is a universal format for storing common 
    multimedia content, like movies or TV shows. Matroska is similar in concept 
    to other containers like AVI, MP4, but is entirely open in specification, 
    with implementations consisting mostly of open source software.

#. Brute force 
   
    Brute force (a.k.a. brute force cracking) is a trial and error method 
    used by application programs to decode encrypted data such as passwords 
    or :abbr:`DES (Data Encryption Standard)` keys, through exhaustive effort 
    rather than employing intellectual strategies.

    .. image:: images/brute-force-attack.jpg

#. Memory barrier
   
    A memory barrier, also known as a membar, memory fence or fence instruction, 
    is a type of barrier instruction that causes a CPU or compiler to enforce an 
    ordering constraint on memory operations issued before and after the barrier 
    instruction. This typically means that **operations issued prior to the barrier 
    are guaranteed to be performed before operations issued after the barrier.**

    Memory barriers are necessary because most modern CPUs employ performance optimizations 
    that can result in out-of-order execution. This reordering of memory operations (loads and stores) 
    normally goes unnoticed within a single thread of execution, but can cause unpredictable behaviour 
    in concurrent programs and device drivers unless carefully controlled.   

    Memory barriers are typically used when implementing low-level machine code that operates on memory 
    shared by multiple devices. Such code includes synchronization primitives and lock-free data structures 
    on multiprocessor systems, and device drivers that communicate with computer hardware.

#. Mutex vs spinlock

    +-------------+---------------------------------------+--------------------------------------+
    | Criteria    | Mutex                                 | Spinlock                             |
    +-------------+---------------------------------------+--------------------------------------+
    | Mechanism   | Test for lock.                        | Test for lock.                       |
    |             | If available, use the resource.       | If available, use the resource.      |
    |             | Otherwise, go to wait queue.          | Otherwise, keep busy polling.        |
    +-------------+---------------------------------------+--------------------------------------+
    | When to use | Used when putting process to sleep is | Used when process should not be      |
    |             | not harmful like user space programs, | put to sleep like Interrupt service  |
    |             | and there will be considerable        | routines, and lock will be           |
    |             | time before process gets the lock.    | granted in reasonably short time.    |
    +-------------+---------------------------------------+--------------------------------------+
    | Drawbacks   | Incur process context switch          | Processor is busy doing nothing till |
    |             | and scheduling cost.                  | lock is granted, wasting CPU cycles. |
    +-------------+---------------------------------------+--------------------------------------+

#. One-hot

    In digital circuits, one-hot refers to a group of bits among which the legal combinations of values 
    are only those with a single high (1) bit and all the others low (0). A similar implementation in 
    which all bits are '1' except one '0' is sometimes called one-cold.

#. Serialization
   
    In computer science, in the context of data storage, serialization is the process of translating data 
    structures or object state into a format that can be stored (for example, in a file or memory buffer, 
    or transmitted across a network connection link) and reconstructed later in the same or another computer environment.

    This process of serializing an object is also called *marshalling* an object. The opposite operation, 
    extracting a data structure from a series of bytes, is *deserialization* (also called *unmarshalling*).


#. Palindrome 
   
    A palindrome [回文] is a word, phrase, number, or other sequence of characters which reads the same backward or forward. 
    Allowances may be made for adjustments to capital letters, punctuation, and word dividers.