
// binary_heap.cpp

#include <iostream>

struct BinaryHeap
{
    int* data;     // 数据
    int  size;     // 当前大小
    int  capacity; // 最大容量

    static BinaryHeap* Initialize(int max_elements);
    static void        Insert(int x, BinaryHeap* heap);
    static int         DeleteMin(BinaryHeap* heap);
};

BinaryHeap*
BinaryHeap::Initialize(int max_elements)
{
    BinaryHeap* heap = new BinaryHeap;

    heap->data     = new int[max_elements + 1]; // +1 为了留一个位置给mindata
    heap->size     = 0;
    heap->capacity = max_elements;
    heap->data[0]  = INT_MIN; // 0号位置存放最小值

    return heap;
}

void
BinaryHeap::Insert(int x, BinaryHeap* heap)
{
    if(heap->size == heap->capacity)
    {
        std::cout << "Heap is full" << std::endl;
        return;
    }

    int i;
    for(int i = ++heap->size; heap->data[i / 2] > x; i /= 2)
    {
        heap->data[i] = heap->data[i / 2];
    }
    heap->data[i] = x;
}

int
BinaryHeap::DeleteMin(BinaryHeap* heap)
{
    if(heap->size == 0)
    {
        std::cout << "Heap is empty" << std::endl;
        return heap->data[0];
    }

    int i, child;
    int min_element, last_element;

    min_element  = heap->data[1];
    last_element = heap->data[heap->size--];

    for(i = 1; i * 2 <= heap->size; i = child)
    {
        child = i * 2;
        if(child != heap->size /*不是所有节点都有两个孩子*/ && heap->data[child + 1] < heap->data[child])
        {
            child++; // child 为左右孩子中较小的那个
        }

        if(last_element > heap->data[child])
        {
            heap->data[i] = heap->data[child];
        }
        else
        {
            break;
        }
    }
    heap->data[i] = last_element;

    return min_element;
}

int
main()
{
    BinaryHeap* heap = BinaryHeap::Initialize(100);

    BinaryHeap::Insert(10, heap);
    BinaryHeap::Insert(20, heap);
    BinaryHeap::Insert(30, heap);
    BinaryHeap::Insert(40, heap);
    BinaryHeap::Insert(50, heap);
    BinaryHeap::Insert(60, heap);

    for(int i = 0; i < heap->size; i++)
    {
        std::cout << heap->data[i] << std::endl;
    }

    BinaryHeap::Insert(70, heap);
    BinaryHeap::Insert(80, heap);
    BinaryHeap::Insert(90, heap);
    BinaryHeap::Insert(100, heap);

    for(int i = 0; i < 10; i++)
    {
        std::cout << BinaryHeap::DeleteMin(heap) << std::endl;
    }

    return 0;
}
