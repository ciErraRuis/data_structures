#ifndef _BINHEAP_H_
#define _BINHEAP_H_
#include "Dijkstra.h"
const int MAXV = 23947345;

//define the node of binomial heap
struct Node {
    int dist;
    int idx;
};

Node* createNode(int idx, int dist) {
    Node *newNode = new Node();
    newNode->idx = idx;
    newNode->dist = dist;
    return newNode;
}

//function of binomial heap
class binHeap {
    int size;
    int capacity;
    Node **Elements;
public:
    std::unordered_map<int, int> idx_pos;
    //Constructor
    binHeap();
    binHeap(int capacity);

    //insert a vertex and its dist into the heap
    void insert(int idx, int dist);

    //deleteMin
    Node* deleteMin();

    //decreaseKey
    void decreaseKey(int idx, int newKey);

    ~binHeap() {
        delete Elements;
    }

    //get size
    int get_size();
    bool isEmpty();
    void print_heap();
    int idx_dist(int idx);
};

int dijkstra_bin(int fromn, int ton);

#endif