#include <unordered_map>
using namespace std;

unordered_map<int, skew_Node*> idx_node;

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

//constructor
skew_heap::skew_heap() {
    this->size = 0;
    this->root = nullptr;
}

skew_Node* merge(skew_Node* h1, skew_Node* h2) {
    if (h1 == nullptr) {
        return h2;
    }
    if (h2 == nullptr) {
        return h1;
    }
    //swap H1 and H2
    if (h1->dist > h2->dist)
    {
        skew_Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }
    if (h1->left == nullptr) {
        h1->left = h2;
        //update the parent
        h2->parent = h1;
    }
    else {
        h1->right = merge(h1->right, h2);
        //update the parent
        if (h1->right != nullptr)
            h1->right->parent = h1;
        if (h1->left != nullptr)
            h1->left->parent = h1;
    }
    //swap the left child and right child of H1
    skew_Node* temp = h1->left;
    h1->left = h1->right;
    h1->right = temp;
    return h1;
}

//insert the index of vertex and its distance into the heap
void skew_heap::insert(int idx, int dist) {
    skew_Node* h = this->root;
    skew_Node* vertex = create_skewNode(idx, dist);
    idx_node[idx] = vertex;
    //insert by merge the two skewNode
    this->root = merge(h, vertex);
    this->size++;
}

skew_Node* skew_heap::deleteMin() {
    //break up into two trees and merge them
    skew_Node* h = this->root;
    skew_Node* left = h->left;
    skew_Node* right = h->right;
    this->root = merge(left, right);
    //update the size
    this->size--;
    return h;
}

void skew_heap::decreaseKey(int idx, int newDist) {
    //if idx > root->dist(min dist at present), set root to it
    skew_Node* node = idx_node[idx];
    node->dist = newDist;
    while (node->parent != NULL) {
        //parent node's dist larger than its
        skew_Node* parent = node->parent;
        if (newDist < parent->dist) {
            //update the map
            idx_node[idx] = parent;
            idx_node[parent->idx] = node;
            //change the value
            int temp1 = parent->idx;
            int temp2 = parent->dist;
            parent->idx = node->idx;
            parent->dist = node->dist;
            node->dist = temp2;
            node->idx = temp1;
            node = parent;
        } else 
            break;
    }
}

// return whether the heap is empty
bool skew_heap::isEmpty() {
    return this->size == 0;
}

// return the distance of specficial idx
int skew_heap::idx_dist(int idx) {
    skew_Node* node = idx_node[idx];
    return node->dist;
}