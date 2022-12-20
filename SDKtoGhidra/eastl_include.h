// Simplified version of EASTL structures

namespace eastl
{
    struct allocator
    {
        void* padding;
    };

    template <typename T, typename _Allocator=allocator>
    struct vector
    {
        static allocator _DEFAULT__Allocator;
        
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        _Allocator mAllocator;
        int _garbage;
    };

    template <typename T1, typename T2>
    struct pair
    {
        T1 first;
        T2 second;
    };

    template <typename T>
    struct function
    {
        void* ptr;
    };

    struct string
    {
        char* mpBegin;
        char* mpEnd;
        char* mpCapacity;
        int mAllocator;
    };

    struct string8
    {
        char* mpBegin;
        char* mpEnd;
        char* mpCapacity;
        int mAllocator;
    };

    struct string16
    {
        char16_t* mpBegin;
        char16_t* mpEnd;
        char16_t* mpCapacity;
        int mAllocator;
    };

    template <typename T, typename _Allocator=allocator>
    struct list
    {
        static allocator _DEFAULT__Allocator;

        void* mpPrev;
        void* mpNext;
        _Allocator mAllocator;
    };

    template <typename T>
    struct deque_iterator
    {
        T* mpCurrent;
        T* mpBegin;
        T* mpEnd;
        T** mpCurrentArrayPtr;
    };

    template <typename T, typename _Allocator=allocator>
    struct deque
    {
        static allocator _DEFAULT__Allocator;

        T** mpPtrArray;
        unsigned int mnPtrArraySize;
        deque_iterator<T> mItBegin;
        deque_iterator<T> mItEnd;
        _Allocator mAllocator;
    };

    template <typename T, typename _Allocator=allocator>
    struct queue
    {
        static allocator _DEFAULT__Allocator;

        T** mpPtrArray;
        unsigned int mnPtrArraySize;
        deque_iterator<T> mItBegin;
        deque_iterator<T> mItEnd;
        _Allocator mAllocator;
    };

    template <typename Key, typename T, typename _Allocator=allocator>
    struct hash_map
    {
        static allocator _DEFAULT__Allocator;

        int field_0;
        void* mpBucketArray;
        int mnBucketCount;
        int mnElementCount;
        float mfMaxLoadFactor;
        float mfGrowthFactor;
        int mnNextResize;
        _Allocator mAllocator;
    };

    struct rbtree_node_base
    {
        rbtree_node_base* mpNodeLeft;
        rbtree_node_base* mpNodeRight;
        rbtree_node_base* mpNodeParent;
        int color;
    };

    template <typename T>
    struct rbtree_node : public rbtree_node_base
    {
        T mValue;
    };

    struct less
    {};

    template <typename Key, typename T, typename _Compare=less, typename _Allocator=allocator>
    struct map
    {
        static less _DEFAULT__Compare;
        static allocator _DEFAULT__Allocator;

        void* mCompare;
        rbtree_node_base mAnchor;
        unsigned int mnSize;
        _Allocator mAllocator;
    };

    template <typename T, typename _Compare=less, typename _Allocator=allocator>
    struct set
    {
        static less _DEFAULT__Compare;
        static allocator _DEFAULT__Allocator;

        void* mCompare;
        rbtree_node_base mAnchor;
        unsigned int mnSize;
        _Allocator mAllocator,
    };

    struct fixed_vector_allocator
    {
        void* mOverflowAllocator;
        void* mpPoolBegin;
    };

    template <typename T, int nodeCount>
    struct fixed_vector
    {
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        fixed_vector_allocator mAllocator;
        int _garbage;
        T[nodeCount] mBuffer;
    };

    struct intrusive_list_node
    {
        intrusive_list_node* mpNext;
        intrusive_list_node* mpPrev;
    };

    template <typename T>
    struct intrusive_ptr
    {
        T* ptr;
    };

    template <typename T>
    struct intrusive_list_iterator
    {
        T* mpNode;
    };
}