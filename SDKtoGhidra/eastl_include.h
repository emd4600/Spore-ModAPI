// Simplified version of EASTL structures

#ifndef ASSERT_SIZE
#define ASSERT_SIZE(name, size) static_assert(sizeof(name) == size, "sizeof " #name " != " #size);
#endif

typedef unsigned int uintptr_t;
typedef char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t __attribute__ ((aligned (8)));
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t __attribute__ ((aligned (8)));
typedef unsigned int     size_t;

#define NULL 0

namespace eastl
{
    ASSERT_SIZE(int*, 4);
    static_assert(alignof(int64_t) == 8, "alignof(int64_t) != 8");

    struct allocator
    {
        void* padding;
    };

    template <typename T, typename _Allocator = allocator>
    struct vector
    {
        static allocator _DEFAULT__Allocator;
        
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        _Allocator mAllocator;
        int _garbage;
    };

    /*template <typename T1, typename T2=int>
    //template <typename T1>
	struct vector
	{
		T1 field_1;
		//_T2 field_2;
	};*/

    template <typename T1, typename T2>
    struct pair
    {
        T1 first;
        T2 second;
    };

    template <typename Key, typename T, typename _Allocator = allocator>
    struct vector_map
    {
        static allocator _DEFAULT__Allocator;
        
        pair<Key, T>* mpBegin;
        pair<Key, T>* mpEnd;
        pair<Key, T>* mpCapacity;
        _Allocator mAllocator;
        int _garbage;
        int mValueCompare;
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
    ASSERT_SIZE(string, 0x10);

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
    static_assert(sizeof(hash_map<int,int>) == 0x20, "sizeof(hash_map<int,int>) == 0x20");

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

    template <typename T>
    struct less
    {};

    template <typename Key, typename T, typename _Compare=less<Key>, typename _Allocator=allocator>
    struct map
    {
        static less<Key> _DEFAULT__Compare;
        static allocator _DEFAULT__Allocator;

        void* mCompare;
        rbtree_node_base mAnchor;
        unsigned int mnSize;
        _Allocator mAllocator;
    };
    static_assert(sizeof(map<int,int>) == 0x1c, "sizeof(map<int,int>) == 0x1c");

    template <typename T, typename _Compare=less<T>, typename _Allocator=allocator>
    struct set
    {
        static less<T> _DEFAULT__Compare;
        static allocator _DEFAULT__Allocator;

        void* mCompare;
        rbtree_node_base mAnchor;
        unsigned int mnSize;
        _Allocator mAllocator;
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
        T mBuffer[nodeCount];
    };

    struct intrusive_list_node
    {
        intrusive_list_node* mpNext;
        intrusive_list_node* mpPrev;
    };

    template <typename T>
    struct intrusive_list_iterator
    {
        T* mpNode;
    };

    template <typename T>
    struct intrusive_list
    {
        typedef intrusive_list_iterator<T> iterator;

        T mAnchor;
    };

    template <typename T>
    struct intrusive_ptr
    {
        T* ptr;

        intrusive_ptr();
        intrusive_ptr(T*);
        T* get() const;

        T& operator *() const;
		T* operator ->() const;
    };

// Python eval() can't do the ? :, so we will just assume the 0 case never happens
//#define BITSET_WORD_COUNT(N) (N == 0 ? 1 : ((N - 1) / (8 * 4) + 1))
#define BITSET_WORD_COUNT(N) ((N - 1) / (8 * 4) + 1)

    template <int count>
    struct bitset
    {
        int words[BITSET_WORD_COUNT(count)];
    };
}

namespace App
{
    struct Test
    {
        eastl::vector<int> test;
    };
}
//static_assert(sizeof(App::Test) == )