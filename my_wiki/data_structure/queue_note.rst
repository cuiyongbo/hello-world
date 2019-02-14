*****
Queue
*****

.. code-block:: none
    :caption: Taken from *Introduction to Algorithms*

    ENQUEUE-EMPTY(Q): return Q.head == Q.tail
    ENQUEUE-FULL(Q): return (Q.tail + 1) % Q.length == Q.head

    ENQUEUE(Q, x)
        if ENQUEUE-FULL(Q)
            error("overflow")

        Q[Q.tail] = x
        if Q.tail == Q.length
            Q.tail = 1
        else Q.tail = Q.tail + 1

    DEQUEUE(Q)
        if ENQUEUE-EMPTY(Q)
            error("underflow")

        x = Q[Q.head]
        if Q.head == Q.length
            Q.head = 1
        else Q.head = Q.head + 1
        return x

Each of the four queue operations takes **O(1)** time.

.. code-block:: cpp
    :caption: A C++ implementation

    #define isPowerof2(x) ((x)&((x)-1) == 0)

    template <typename ElementType>
    class TestQueue
    {
    public:
        TestQueue() { m_data = NULL; }
        ~TestQueue() { free(m_data); }
   
        void initWithCapacity(size_t capacity);
        size_t count() { return m_tail > m_head ? (m_tail - m_head) : (m_capacity - (m_head - m_tail)); }
   
        void pushBack(ElementType x);
        ElementType popFront();
   
    private:
        bool isFull() { (m_tail + 1) & m_capacityMask == m_head; }
        bool isEmpty() { return m_tail == m_head; }
        void expand();
      
    private:
        ElementType* m_data; // at most m_capacity-1 elements.
        size_t m_capacity, m_capacityMask;
        size_t m_head, m_tail;
    };
   
    template <typename ElementType>
    void TestQueue<ElementType>::expand()
    {
        size_t capacity = m_capacity << 1;
        m_data = (ElementType*)realloc(m_data, capacity*sizeof(ElementType));
        assert(m_data != NULL && "Failed to expand buffer for queue!");
        if (m_head > m_tail)
        {
            size_t copyNum = m_tail;
            if (copyNum != 0)
                memcpy(m_data+m_capacity, m_data, copyNum * sizeof(ElementType));
            m_tail += m_capacity;
        }
        m_capacity = capacity;
        m_capacityMask = m_capacity - 1;
    }
   
    template <typename ElementType>
    ElementType TestQueue<ElementType>::popFront()
    {
        assert(!isEmpty() && "Pop an empty queue!"); // underflow 
        ElementType x = m_data[m_head];
        m_head = (m_head + 1) & m_capacityMask;
        return x;
    }
   
    template <typename ElementType>
    void TestQueue<ElementType>::pushBack(ElementType x)
    {
        if (isFull())
            expand();
    
        m_data[m_tail] = x;
        m_tail = (m_tail + 1) & m_capacityMask;
    }
   
    template <typename ElementType>
    void TestQueue<ElementType>::initWithCapacity(size_t capacity)
    {
        if(capacity == 0)
            capacity = 16;
        else if(!isPowerof2(capacity))
            capacity = hibit2(capacity)>>1;
        m_head = m_tail = 0;
        m_capacity = capacity;
        m_capacityMask = m_capacity-1;
        m_data = (ElementType*)malloc(capacity * sizeof(ElementType));
    }

    inline int hibit2(int32 n)
    {
        n |= (n >> 1); // xx11xx
        n |= (n >> 2); // xx1111xx
        n |= (n >> 4); // xx1111111xx
        n |= (n >> 8); // xx11111111111111xx
        n |= (n >> 16); // set all the bits from highest order bit to the 0-th one to 1
        return n - (n >> 1);
    } 
