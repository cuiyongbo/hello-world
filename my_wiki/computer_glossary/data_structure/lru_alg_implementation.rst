*************
LRU Algorithm
*************

DESIGN
======
   
   * double linked list
      - LIST-ADD
      - LIST-DELETE
      
   * hash map
      - SERARCH   (TODO)

   * element
     - key
     - m_prev, m_next
       

IMPLEMENTATION
==============

   .. code-block:: c++

      struct LruNode
      {
         int data;
         LruNode* prev;
         LruNode* next;
      };
      
      LruNode* LruNode_make(int val)
      {
         LruNode* node = new LruNode;
         node->data = val;
         node->prev = node->next = NULL;
         return node;
      }
      
      class LocalLru
      {
      public:
         LocalLru()
         {
            m_count = m_capacity = 0;
            m_head = m_tail = NULL;
         }
      
         ~LocalLru()
         {
            LruNode* p = m_head;
            while (p != NULL)
            {
               LruNode* q = p->next;
               delete p;
               p = q;
            }
         }
      
         void setCapacity(int capacity) { m_capacity = capacity; }
         int hotKey() { return m_tail->data; }
      
         void addKey(int key)
         {
            LruNode* node = search(key);
            if (node != NULL)
            {
               touch(node);
            }
            else
            {
               ensureFreeSlot();
               node = LruNode_make(key);
               append(node);
            }
         }
      
         void removeKey(int key)
         {
            LruNode* node = search(key);
            if (node != NULL)
            {
               detach(node);
               delete node;
               m_count--;
            }
         }
      
         void append(LruNode* node)
         {
            if (m_tail == NULL)
            {
               m_head = m_tail = node;
            }
            else
            {
               node->prev = m_tail;
               m_tail->next = node;
               m_tail = node;
            }
      
            m_count++;
         }
      
         void detach(LruNode* node)
         {
            if (node == m_head)
               m_head = m_head->next;
            if (node == m_tail)
               m_tail = m_tail->prev;
            if (node->prev != NULL)
               node->prev->next = node->next;
            if (node->next != NULL)
               node->next->prev = node->prev;
            node->prev = node->next = NULL;
         }
      
         void touch(LruNode* node)
         {
            detach(node);
            append(node);
         }
      
         LruNode* search(int key)
         {
            LruNode* node = m_head;
            while (node != NULL)
            {
               if (node->data == key)
                  break;
      
               node = node->next;
            }
            return node;
         }
      
      private:
         void ensureFreeSlot()
         {
            while (m_head != NULL && m_count+1 > m_capacity)
            {
               LruNode* p = m_head;
               m_head = p->next;
               m_head->prev = NULL;
               delete p;
               m_count--;
            }
         }
      
      private:
         LruNode* m_head; // the least recently used node.
         LruNode* m_tail; // the most recently used node.
         int m_count;
         int m_capacity;
      };
      
      
      class LruTester : public ::testing::Test
      {
      protected:
         void SetUp()
         {
            m_lru = new LocalLru;
         }
      
         void TearDown()
         {
            delete m_lru;
         }
      
      protected:
         LocalLru* m_lru;
      };
      
      TEST_F(LruTester, basic)
      {
         m_lru->setCapacity(3);
         m_lru->addKey(1);
         m_lru->addKey(2);
         m_lru->addKey(3);
         m_lru->addKey(4);
      
         // 2 -> 3 -> 4
         EXPECT_EQ(m_lru->hotKey(), 4);
         EXPECT_TRUE(m_lru->search(1) == NULL);
      
         // 3 -> 4 -> 2
         m_lru->addKey(2);
         EXPECT_EQ(m_lru->hotKey(), 2);
      
         // 3 -> 4
         m_lru->removeKey(2);
         EXPECT_EQ(m_lru->hotKey(), 4);
      }
