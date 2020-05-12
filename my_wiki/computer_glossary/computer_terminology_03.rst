***********************
Computer Terminology 03
***********************

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
    or transmitted across a network connection link) and reconstructed later in the same or
    another computer environment.

    This process of serializing an object is also called *marshalling* an object. The opposite operation,
    extracting a data structure from a series of bytes, is *deserialization* (also called *unmarshalling*).

#. Palindrome

    A palindrome [回文] is a word, phrase, number, or other sequence of characters which reads the same backward or forward.
    Allowances may be made for adjustments to capital letters, punctuation, and word dividers.

#. Codec

    A codec is a device or computer program for encoding or decoding a digital data stream or signal.
    Codec is a portmanteau of coder-decoder. A coder encodes a data stream or a signal for transmission or storage,
    possibly in encrypted form, and the decoder function reverses the encoding for playback or editing.
    Codecs are used in videoconferencing, streaming media, and video editing applications.

#. Memoization

   In computing, memoization is an optimization technique used primarily to speed up computer programs
   by storing the results of expensive function calls and returning the cached result when the same inputs occur again.

#. Framework

    In general, a framework is a real or conceptual structure intended to serve as a support or guide
    for the building of something that expands the structure into something useful.

    In computer systems, a framework is often a layered structure indicating what kind of programs can
    or should be built and how they would interrelate. Some computer system frameworks also include actual
    programs, specify programming interfaces, or offer programming tools for using the frameworks.
    A framework may be for a set of functions within a system and how they interrelate; the layers of an OS;
    the layers of an application subsystem; how communication should be standardized at some level of a network;
    and so forth. A framework is generally more comprehensive than a protocol and more prescriptive than a structure.

    .. [#] `Server framework <https://www.jianshu.com/p/63f664409183>`_


#. Random walk

    A random walk is a mathematical object, known as a stochastic or random process,
    that describes a path that consists of a succession of random steps on some mathematical
    space such as the integers. An elementary example of a random walk is the random walk on
    the integer number line, which starts at 0 and at each step moves +1 or −1 with equal probability.
    Other examples include the path traced by a molecule as it travels in a liquid or a gas, the search
    path of a foraging animal, the price of a fluctuating stock and the financial status of a gambler:
    all can be approximated by random walk models, even though they may not be truly random in reality.

#. RPC

    In distributed computing, a :abbr:`RPC (remote procedure call)` is when a computer program causes a procedure
    to execute in a different address space (commonly on another computer on a shared network), which is coded
    as if it were a local procedure call, without the programmer explicitly coding the details for the
    remote interaction. That is, the programmer writes essentially the same code whether the procedure is local
    to the executing program, or remote.

#. Distributed computing

    Distributed computing is a field of computer science that studies distributed systems.
    A distributed system is a system whose components are located on different networked computers,
    which communicate and coordinate their actions by passing messages to one another.
    The components interact with one another in order to achieve a common goal.
    Three significant characteristics of distributed systems are:

        - concurrency of components,
        - lack of a global clock,
        - and independent failure of components.

    A computer program that runs within a distributed system is called a distributed program
    There are many different types of implementations for the message passing mechanism,
    including pure HTTP, RPC-like connectors and message queues.

    Distributed computing also refers to the use of distributed systems to solve computational problems.
    In distributed computing, a problem is divided into many tasks, each of which is solved by one or more computers,
    which communicate with each other via message passing.

    Architectures:

        - Client–server
        - Peer-to-peer
        - Three-tier
        - n-tier

#. parallel edge

    In graph theory, multiple edges (also called parallel edges or a multi-edge),
    are two or more edges that are incident to the same two vertices.
    A simple graph has no multiple edges.

#.  failover

    A method of protecting computer systems from failure,
    in which standby equipment automatically takes over when the main system fails.
    e.g., the second server went into failover mode within a minute.
