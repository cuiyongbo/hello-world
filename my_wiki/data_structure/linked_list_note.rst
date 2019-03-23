***********
Linked List
***********

**IMPLEMENTATION: Doubly linked list**

.. code-block:: none
    :caption: Doubly linked list, taken from *Introduction to Algorithms*

    LIST-SEARCH(L, k)
        x = L.head
        while x != NIL and x.key != k
            x = x.next
        return x

    LIST-PUSHFRONT(L, x)
        x.next = L.head
        x.prev = NIL
        if L.head != NIL
            L.head.prev = x
        L.head = x

    LIST-PUSHBACK(L, x)
        if L.tail == NIL
            L.head = L.tail = x
        else
           x.prev = tail
           tail.next = x
           tail = x

    LIST-DELETE(L, x)
        if x.prev != NIL
            x.prev.next = x.next
        else
            L.head = x.next
        if x.next != NIL
            x.next.prev = x.prev

.. code-block:: none
    :caption: Circular, doubly linked list with a sentinel

    LIST-SEARCH'(L, k):
        x = L.nil.next
        while x != L.nil && x.key != k
           x = x.next
        return x

    LIST-DELETE'(L, x)
        x.prev.next = x.next
        x.next.prev = x.prev

    LIST-PUSHFRONT'(L, x):
        x.next = L.nil.next
        x.prev = L.nil
        L.nil.next.prev = x
        L.nil.next = x

The gain from using sentinels within loops is usually a matter of clarity of code rather than speed.

.. code-block:: cpp
    :caption: Circular, doubly linked list, taken from Jansson

    struct hashtable_list 
    {
        struct hashtable_list *prev;
        struct hashtable_list *next;
    };
    
    typedef hashtable_list list_t;

    static void list_init(list_t *list)
    {
        list->next = list;
        list->prev = list;
    }
    
    // push_front 
    static void list_insert(list_t *list, list_t *node)
    {
        node->next = list;
        node->prev = list->prev;
        list->prev->next = node;
        list->prev = node;
    }
    
    static void list_remove(list_t *list)
    {
        list->prev->next = list->next;
        list->next->prev = list->prev;
    }


**EXERCISES**

#. Give a :math:`\Theta(n)` time nonrecursive procedure that reverses a singly linked list of n elements.
   The procedure should use no more than constant storage beyond that needed for the list itself.

    .. code-block:: cpp
    
        namespace solution
        {
            struct Node
            {
                int data;
                Node* next;
                Node(): data(0), next(NULL) {}
            };
    
            Node* reversedLinkList(Node* l)
            {
                Node* tmp = NULL;
                Node* newHead = NULL;
                while (l != NULL)
                {
                    tmp = l->next;
                    l->next = newHead;
                    newHead = l;
                    l = tmp;
                }
                return newHead;
            }
        }