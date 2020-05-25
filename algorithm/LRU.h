#ifndef __LRU_H__
#define __LRU_H__
#include<iostream>
#include<map>

using namespace std;

template<typename KEY, typename VAL>
class LRU{
    struct Node {
    private:
        friend class DoubleList;
        friend class LRU;
        KEY k;
        VAL v;
        Node* next, prev;
        Node(KEY kk, VAL vv): k(kk), v(vv){}
        Node(): k(0), v(0), next(nullptr), prev(nullptr){}
    };
    class DoubleList {  
    private:
        friend class LRU;
        DoubleList(): head(new Node()), tail(head){}
        // 在链表头部添加节点 x，时间 O(1)
        void addFirst(const Node& x){
            Node* curr = new Node(x.k, x.v);
            curr->prev = head;
            curr->next = head->next;
            head->next = curr;
            if(tail == head)
                tail = curr;
            
            size ++;
        }

        // 删除链表中的 x 节点（x 一定存在）
        // 由于是双链表且给的是目标 Node 节点，时间 O(1)
        void remove(Node* x){
            Node* prev_node = x->prev;
            prev_node->next = x->next;
            x->next->prev = prev_node;
            delete x;
        }

        // 删除链表中最后一个节点，并返回该节点，时间 O(1)
        Node* removeLast(){
            if(tail == head){
                cout << "the double list is empty" << endl;
                return nullptr;
            }
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            size --;
            return tail;
        }

        // 返回链表长度，时间 O(1)
        int getSize(){return size;}
    private:
        Node* head;
        Node* tail;
        int size;
    };
    map<KEY, Node*> hash_map;
    // Node(k1, v1) <-> Node(k2, v2)...
    DoubleList cache;   
    int cap;

public:
    LRU(int capacity) {
        this->cap = capacity;
        hash_map = new map<KEY, Node*>();
        cache = new DoubleList();
    }

    VAL get(KEY k) {
        if (!hash_map.count(k))
            return -1;
        VAL val = hash_map[k]->v;
        // 利用 put 方法把该数据提前
        put(k, val);
        return val;
    }

    void put(KEY key, VAL val) {
        // 先把新节点 x 做出来
        Node* x = new Node(key, val);

        if (hash_map.count(key) != 0) {
            // 删除旧的节点，新的插到头部
            cache.remove(hash_map[key]);
            cache.addFirst(x);
            // 更新 map 中对应的数据
            hash_map[key] = x;
        } 
        else {
            if (cap == cache.getSize()) {
                // 删除链表最后一个数据
                Node* last = cache.removeLast();
                hash_map.remove(last->k);
            }
            // 直接添加到头部
            cache.addFirst(x);
            hash_map[key] = x;
        }
    }

};


#endif