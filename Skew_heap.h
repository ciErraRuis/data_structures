#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_
#include "Dijkstra.h"

struct skew_Node {
    int idx;
    int dist;
    skew_Node* parent;
    skew_Node* left;
    skew_Node* right;
};

skew_Node* create_skewNode(int idx, int dist) {
    skew_Node *node = new skew_Node();
    node->idx = idx;
    node->dist = dist;
    return node;
}

class skew_heap {
    int size;
    //connect the vertex to the node in the heap for doing the decreaseKey
public:
    skew_Node* root;

    skew_heap();
    void insert(int idx, int dist);
    skew_Node* deleteMin();
    void decreaseKey(int idx, int newDist);
    bool isEmpty();
    int idx_dist(int idx);
};

#endif