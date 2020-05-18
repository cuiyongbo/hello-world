Memcached Memory Management
===========================

#. memcached memory allocation related options

    .. code-block:: sh

        -I, --max-item-size=<num> adjusts max item size
                        (default: 1mb, min: 1k, max: 128m)

        -m, --memory-limit=<num>  item memory in megabytes (default: 64 MB)
        -f, --slab-growth-factor=<num> chunk size growth factor (default: 1.25)
        -n, --slab-min-size=<bytes> min space used for key+value+flags (default: 48)

    .. note::

        max_item_size range varies among different releases,
        for example in v1.6.3 the range is::

            #define ITEM_SIZE_MAX_LOWER_LIMIT 1024
            #define ITEM_SIZE_MAX_UPPER_LIMIT 1024 * 1024 * 1024


.. code-block:: c

    // slab_chunk_size_max < item_size_max < maxbytes/2
    struct settings {
        size_t maxbytes;        // -m option
        double factor;          /* chunk size growth factor, -f option */
        int chunk_size;         // -n option
        int item_size_max;      /* Maximum item size, -I option */
        int slab_page_size;     /* Slab's page units. hard-coded with 1M */
        int slab_chunk_size_max;  /* Upper end for chunks within slab pages. slab_page_size/2 */
        // ...
    };

    typedef struct {
        unsigned int size;      /* sizes of items, grows with factor of setting.factor */
        unsigned int perslab;   /* how many items per slab, settings.slab_page_size/size */

        void *slots;           /* list of item ptrs */
        unsigned int sl_curr;   /* total free items in list */

        unsigned int slabs;     /* how many slabs were allocated for this class */

        void **slab_list;       /* array of slab pointers */
        unsigned int list_size; /* size of prev array */
    } slabclass_t;

    static slabclass_t slabclass[MAX_NUMBER_OF_SLAB_CLASSES];

    /* slab class max is a 6-bit number, -1. */
    #define MAX_NUMBER_OF_SLAB_CLASSES (63 + 1)

    // sizeof(item) = 48
    struct _stritem {
        struct _stritem *next;
        struct _stritem *prev;
        struct _stritem *h_next;
        rel_time_t time;
        rel_time_t exptime;
        int nbytes;
        unsigned short refcount;
        uint16_t it_flags;
        uint8_t slabs_clsid;
        uint8_t nkey;
        union {
            uint64_t cas;
            char end;
        } data[];
    } item;

    // Determines the chunk sizes and initializes the slab class descriptors accordingly.
    // the largest slab chunk size is ``settings.slab_chunk_size_max``.
    void slabs_init();

    /*
     * Given object size, return id to use when allocating/freeing memory for object
     * 0 means error: can't store such a large object
     */
    unsigned int slabs_clsid(const size_t size);

    // what a SET command would do,
    // Allocate an item struct only, final workhorse is ``read_into_chunked_item``
    item *item_alloc(char *key, size_t nkey, int flags, rel_time_t exptime, int nbytes);

    // Does a looped read to fill data chunks
    static int read_into_chunked_item(conn *c);
