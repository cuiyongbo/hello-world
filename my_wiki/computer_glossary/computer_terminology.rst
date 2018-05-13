Computer Terminology
====================

| Rat’s nest
| Definition: A situation or condition that is characterized by messiness, disorder, disarray, or confusion. Commonly used in the technology sector to refer to a software design or implementation that is hopelessly convoluted and difficult to understand, analogous to how a rat might construct its nest (haphazardly and hastily thrown together from whatever materials happended to be readily available at the time).
| Usage: I tried to figure out which wire was causing the problem, but there’s a veritable rat’s nest of wires, chords, and cables down there.
| 
| Type coercison and conversion 
| Automatic coercison [强制转换]
| two’s complement [二进制补码]
| backward compatibility [向下兼容]
| regression test [回归测试]
| divide-and-conquer [分而治之]
| compile time
| run-time
| predecessor [前驱]
| successor  [后继]
| spam email [垃圾邮件]
| implementation-dependent
|
| PEP -- python enhancement proposal
| DoS  -- Denial-of-Service
| DDoS -- Distributed Denial-of-Service
| ISA = Instruction Set Architecture
| CISC = Complex Instruction Set Computing
| RISC = Reduced Instruction Set Computing
| SoC = System on Chip
| ALU = Arithmetic Logic Unit
|
| concatenate
| concatenation
| Definition: a concatenation of things or events is their occurrence one after another, because they are linked.
| 
| cipher
| Definition: A person or thing of no importance, especially a person who does the bidding of others and seems to have no will of their own.
| Definition: A sceret way of writing, especially six in which a set of letters or symbols is used to represent others.
| Usage: A message in cipher.
| 
| corrupt
| corruption
| Definition: the process by which something, typically a word or expression, is changed from its original use or meaning to one that is regarded as erroneous or debased.
| Usage: The word “holiday” is a corruption of “holy day”.
| Definition: the process of causing errors to appear in a computer program or database.
|
| heuristic
| Definition: enabling a person to discover or learn something for themselves.
| Usage: Heuristic teaching encourages you to learn by discovering things for yourself.
| Definition: (Computing) proceeding to a solution by trial and error or by rules that are loosely defined.
| 
| overhead == cost
| hover
| Definition: (Computing) use a mouse or other device to position the cursor over a particular area of a computer screen so as to cause a program to respond, without clicking a button on the device.
| Usage: You can hover your cursor over any button to see an explanation.
| 
| on the fly
| Definition: (of an addition or modification in computing) Carried out during the running of a program without interruption.
| 
| sync
| synchronize
| synchronization   
| Definition: occur at the same time or rate.
| Definition: (Computing) cause (a set of data or files) to remain identical in more than one location.
| Usage: you can synchronize your calendar with your GPS devices and get alerted when you need to leave for an appointment.
| 
| prefix  VS suffix 
| prepend VS append
| implicit    explicit
| modularity
| data hiding
| data corruption
| polymorphism
| class hierarchy
| inheritance
| public inheritance
| protected inheritance
| private inheritance
| 
| Qualcomm Snapdragon processor 高通骁龙处理器
| Samsung 三星
|
| breadth-first traversal 广度优先遍历
| depth-first traversal 深度优先遍历
|
| archive
| Definition: The archive or archives are a collection of documents and records that contain historical information.
| Usage: zip archive.
| portfolio
| Definition: a large, thin, flat case for loose sheets of paper such as drawing or maps.
| Definition: a portfolio is a set of pictures by someone, or photographs of examples of their work, which they use when entering competitions or applying for work.

.. figure:: images/portfolio.png

**Subscript vs Superscript [上标，下标]**

A subscript or superscript is a number, figure, symbol, or indicator
that is smaller than the normal line of type and is set slightly below
or above it. Subscripts appear at or below the baseline, while
superscripts are above.

**Co-Processor**

A coprocessor is a computer processor used to supplement the functions
of the primary processor (the CPU). Operations performed by the coprocessor
may be floating point arithmetic, graphics, signal processing, string processing,
encryption or I/O Interfacing with peripheral devices. By offloading processor-intensive
tasks from the main processor, coprocessors can accelerate system performance.
Coprocessors allow a line of computers to be customized, so that customers who
do not need the extra performance don't need to pay for it.

**Rate limiting**

In computer networks, rate limiting is used to control the rate
of traffic sent or received by a network interface controller
and is used to prevent :abbr:`DoS (Denial-of-Service)` attacks.

**Octet**

The octet is a unit of digital information in computing and telecommunications
that consists of eight bits. The term is often used when the term **byte** might be
ambiguous, as the byte has historically been used for storage units of a variety of sizes.

**Datapath**

A datapath is a collection of functional units such as :abbr:`ALU (Arithmetic Logic Unit)`
or multipliers, that perform data processing operations, registers, and buses. Along with
the control unit it composes the :abbr:`CPU (Central Processing Unit)`. A larger datapath
can be made by joining more than one number of datapaths using multiplexer.

superset: a set that includes another set or sets.

**Bits, Bytes and Words**

A **bit** is a BInary digiT. So a bit is a zero or a one. Bits can be implemented in computer
hardware using switches. If the switch is on then the bit is one and if the switch is off
then the bit is zero. A bit is limited to representing two values.

Since the alphabet contains more than two letters, a letter cannot be represented by a bit.
A **byte** is a sequence of bits. Since the mid 1960's a byte has been 8 bits in length. 01000001
is an example of a byte. Since there are 8 bits in a byte there are :math:`2^8` different possible
sequences for one byte, ranging from 00000000 to 11111111. This means that a byte can be used to
represent any type of value with no more than 256 possible values. Since the number of things that
you can enter on a computer keyboard is smaller than 256 (including all keystoke pairs, like shift
or control plus another key), **a code for a keystoke is represented with a code within a byte**.

Since characters (letters, decimal digits and special characters such as punctuation marks, etc) can
be represented with bytes, a standard is needed to ensure that the code that's used on your computer
is the same as the code that is used on mine. There are two standard codes that use one byte to represent
a character, **ASCII** and **EBCDIC**. :abbr:`ASCII (American Standard Code for Information Interchange)` is
the code that is most commonly used today. :abbr:`EBCDIC (Extended Binary Coded Decimal Interchange Code)`,
was used by IBM on its large mainframe computers in the past. Wikipedia has more than you want to know
about ASCII and EBCDIC. Since these codes are limited to 256 possible combinations, certain character
sets, such as Chinese, Arabic, Japanese, Klingon and others, cannot be represented using these codes.
This problem is solved by using another code, **Unicode**, which uses 2 bytes for each character. This
extension allows :math:`2^{16}` different symbols to be represented, a total of 65,536. The use of Unicode
gives more flexibility in the representation of data. The drawback of using Unicode is that it takes twice
as much space to store the same number of characters.

A **word** is the number of bits that are manipulated as a unit by the particular CPU of the computer.
Today most CPUs have a word size of 32 or 64 bits. For example, the notebook computer that I bought in
May 2008 contains a core 2 duo 64 bit processor. Data is fetched from memory to the processor in word
size chunks and manipulated by the ALU in word size chunks. All other things being equal, (and they
never are), larger word size implies faster and more flexible processing.

**What is the difference between 32-bit and 64-bit versions of Windows?**

The terms 32-bit and 64-bit refer to the way a computer's processor (also called a CPU), handles information.
The 64-bit version of Windows handles large amounts of :abbr:`RAM (random access memory)` more effectively than
a 32-bit system. 

To install a 64-bit version of Windows, you need a CPU that's capable of running a 64-bit version of Windows.
The benefits of using a 64-bit operating system are most apparent when you have a large amount of RAM
installed on your computer, typically 4 GB of RAM or more. In such cases, because a 64-bit operating system
can handle large amounts of memory more efficiently than a 32-bit operating system, a 64-bit system can be
more responsive when running several programs at the same time and switching between them frequently. 

**Amortized analysis**

In computer science, amortized analysis is a method for analyzing a given algorithm's complexity,
or how much of a resource, especially time or memory, it takes to execute. The motivation for
amortized analysis is that looking at the worst-case run time per operation can be too pessimistic.

While certain operations for a given algorithm may have a significant cost in resources, other operations
may not be as costly. Amortized analysis considers both the costly and less costly operations together over
the whole series of operations of the algorithm. This may include accounting for different types of input,
length of the input, and other factors that affect its performance.


Concurrence vs Parallelism

+-----------------------------------+-----------------------------------+
| Concurrence                       | Parallelism                       |
+===================================+===================================+
| .. image:: images/concurrency.jpg | .. image:: images/parallelism.jpg |
+-----------------------------------+-----------------------------------+

Associative array： arrays whose indices are arbitrary strings or other complicated objects。
