#ifndef __HEAP_MAX__
#define __HEAP_MAX__
#include <iostream>
using namespace std;

template<typename Elem>
class heap_max{

private:
    // 堆的容量
    int capacity;
    // 存储元素的数组
    Elem* content;
    // 当前堆中的元素数
    int num;    

    /* 上浮第 k 个元素，以维护最大堆性质 */
    void swim(int k);

    /* 下沉第 k 个元素，以维护最大堆性质 */
    void sink(int k);

    /* 交换数组的两个元素 */
    void exch(int i, int j) {
        Elem temp = content[i];
        content[i] = content[j];
        content[j] = temp;
    }

    int left(int pos){return 2 * pos + 1;}
    int right(int pos){return 2 * pos + 2;}
    int parent(int pos){return (pos - 1) / 2;}
    bool ifLeaf(int pos){return pos >= num / 2;}

public:

    heap_max(int cap): capacity(cap), content(new Elem(cap)), num(0) {}
    heap_max(Elem* other, int cap);
    /* 返回当前队列中最大元素 */
    Elem getMax() {
        return content[0];
    }

    /* 插入元素 e */
    void insert(Elem e);

    /* 删除并返回当前队列中最大元素 */
    Elem popMax();

};

template<typename Elem>
void heap_max<Elem>::sink(int pos){
    while(pos < num / 2){
        int lc = left(pos);
        int rc = right(pos);
        int larger = rc < num && content[rc] > content[lc] ? rc: lc;

        if(content[pos] < content[larger]){
            exch(pos, larger);
            pos = larger;
        }
        else
            break;
    }
    return;
}

template<typename Elem>
void heap_max<Elem>::swim (int pos){
    while(pos > 0 && content[pos] > content[parent(pos)]){
        exch(pos, parent(pos));
        pos = parent(pos);
    }
}

template<typename Elem>
heap_max<Elem>::heap_max(Elem* other, int cap){
    delete[] content;
    content = new Elem(cap);
    memcpy(content, other, sizeof(other[0] * cap));
    capacity = cap;
    num = cap;

    for(int i = num / 2 - 1; i != 0; i--){
        sink(i);
    }
}

template<typename Elem>
void heap_max<Elem>::insert(Elem e){
    if(num >= capacity){
        cout << "the heap is full" << endl;
        return;
    }
    
    content[num++] = e;
    swim(num - 1);
}

template<typename Elem>
Elem heap_max<Elem>::popMax(){
    if(num == 0){
        cout << "the heap is empty";
        return -1;
    }
        
    Elem max_e = content[0];
    exch(0, --num);
    sink(0);
    return max_e;
}




#endif