/*
Description:已知两个等长的升序整数序列｛a1, a2, ..., ak｝和{b1, b2, ..., bk}，求序列{ai+bj}的前k小元素，
其中1≤i≤k且1≤j≤k，要求时间复杂度尽可能低 
Date:2012/10/11
Author:Roger Liu
*/

#include <stdio.h>

#define INFINITESIMAL -65536

struct heap_element{
    int a_element;
    int b_element;
    int key;
};
typedef struct heap_element heap_element;

int heapsize = 0;
int * foo(int *, int *, int *, heap_element*, int);
void build_small_root_heap(heap_element *);
void small_root_heapify(heap_element *, int);
heap_element heap_extract_min(heap_element *);
int h_exist(heap_element *, heap_element);
void min_heap_insert(heap_element *, heap_element);
int parent(int);

int main()
{
    int a[5] = {0, 1, 2, 5, 8};
    int b[5] = {0, 2, 3, 6553, 10};
    int i, k = 8;
    int result[8] = {0};
    
    heap_element heap[16] = {0};
     
    printf("ai+bj的前%d小元素为：\n", k);
    foo(&a[0], &b[0], &result[0], &heap[0], 8); 
    
    for (i = 0; i < k; i++)
        printf("%d  ", result[i]); 
    
    system("pause");
    return 0;
}

int * foo(int *a, int *b, int *result, heap_element *heap, int k)
{
    int i = 1;
    int j = 1;
    int counter;
    heap_element h, h1, h2;
    
    result[0] = a[0] + b[0];
    counter = 1;
    
    heap[0].key = a[1] + b[0];
    heap[0].a_element = 1;
    heap[0].b_element = 0;
    heap[1].key = a[0] + b[1];
    heap[1].a_element = 0;
    heap[1].b_element = 1;
    
    heapsize = 2;
    build_small_root_heap(heap);
    while (heap != NULL && counter <= k){
        h = heap_extract_min(heap);//弹出堆顶元素
        result[counter] = h.key;
        
        h1.a_element = h.a_element;
        h1.b_element = h.b_element + 1;
        h1.key = a[h1.a_element] + b[h1.b_element];
        
        h2.a_element = h.a_element + 1;
        h2.b_element = h.b_element;
        h2.key = a[h2.a_element] + b[h2.b_element];
                
        if (!h_exist(heap, h1))
            min_heap_insert(heap, h1);
        if (!h_exist(heap, h2))
            min_heap_insert(heap, h2);//插入(i+1,j,key)和（i,j+1,key），插入前要判断并去重 
        counter++;
    }
}

void build_small_root_heap(heap_element *heap)
{
    int start = heapsize / 2;

    for (; start > 0; start--)
        small_root_heapify(heap, start);
}

void small_root_heapify(heap_element *heap, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest;
    heap_element temp;
    
    if (l < heapsize && heap[l].key < heap[i].key)
        smallest = l;
    else
        smallest = i;
        
    if (r < heapsize && heap[r].key < heap[smallest].key)
        smallest = r;
    
    if (i != smallest){
        temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;  
        small_root_heapify(heap, smallest);  
    }   
}

heap_element heap_extract_min(heap_element *heap)
{
    heap_element min;
    if (heapsize < 1)
        printf("***heap underflow***");
        
    min = heap[0];
    heap[0] = heap[heapsize-1];
    heapsize--;
    small_root_heapify(heap, 0);
    
    return min;
}

int h_exist(heap_element *heap, heap_element h)
{
    int i;
    for(i = 0; i < heapsize; i++){
        if (heap[i].a_element == h.a_element && heap[i].b_element == heap[i].b_element)
            return 1;      
    }    
    
    return 0;
}

void min_heap_insert(heap_element *heap, heap_element h)
{
    int i;
    heap_element temp;
    int par;
    
    heapsize = heapsize + 1;
    heap[heapsize-1].key = h.key;
    heap[heapsize-1].a_element = h.a_element;
    heap[heapsize-1].b_element = h.b_element;
    i = heapsize - 1;
    par = parent(i);
    while(i > 1 && heap[par].key > heap[i].key){
        temp = heap[i];
        heap[i] = heap[par];
        heap[par] = heap[i];
        par = parent(i);
        i = par;
    }
}

int parent(int i)
{
    if (i % 2 == 0)
        return i / 2 - 1;
    else
        return i / 2;    
}
