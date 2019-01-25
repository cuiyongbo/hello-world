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