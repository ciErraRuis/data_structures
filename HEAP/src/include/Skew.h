#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

#include <unordered_map>
using namespace std;

template<class T>
class Skewheap {
    int size;
    //connect the vertex to the node in the heap for doing the decreaseKey
private:
    template<class U>
    class Node {
    public:
        int idx;
        U val;
        Node(int idx, U val) {
            this->idx = idx;
            this->val = val;
            this->parent = nullptr;
            this->left = nullptr;
            this->right = nullptr;
        }
        Node(): Node(0, 0) {}
        Node<U>* parent;
        Node<U>* left;
        Node<U>* right;
    };

    Node<T>* root;
    std::unordered_map<int, Node<T>*> idx_node;
    Node<T>* createNode(int idx, T val);
    Node<T>* _merge(Node<T>* left, Node<T>* right);
    T idx_val(int idx);
    Node<T>* deleteMin();
public:
    Skewheap();
    ~Skewheap();
    void merge(Skewheap& heap);
    void insert(int idx, T val);
    T pop();
    T peek();
    void decreaseKey(int idx, T newVal);
    bool isEmpty();
    int getSize() {
      return size;
    }
};

template<class T>
Skewheap<T>::Skewheap() {
    this->size = 0;
    this->idx_node = unordered_map<int, Node<T>*>();
    this->root = nullptr;
}

template<class T>
Skewheap<T>::~Skewheap() {
  for (auto& node : this->idx_node) {
    delete node.second;
  }
}

template<class T>
Skewheap<T>::Node<T>* Skewheap<T>::createNode(int idx, T val) {
    Node<T> *node = new Node<T>();
    node->idx = idx;
    node->val = val;
    return node;
}

// Recursively merge the right child and another heap.
// swap the two children every time.
template<class T>
Skewheap<T>::Node<T>* Skewheap<T>::_merge(Node<T>* h1, Node<T>* h2) {
    if (h1 == nullptr) {
        return h2;
    }
    if (h2 == nullptr) {
        return h1;
    }
    //swap H1 and H2
    if (h1->val > h2->val)
    {
        Node<T>* temp = h1;
        h1 = h2;
        h2 = temp;
    }
    if (h1->left == nullptr) {
        h1->left = h2;
        //update the parent
        h2->parent = h1;
    }
    else {
        h1->right = _merge(h1->right, h2);
        //update the parent
        if (h1->right != nullptr)
            h1->right->parent = h1;
        if (h1->left != nullptr)
            h1->left->parent = h1;
    }
    //swap the left child and right child of H1
    Node<T>* temp = h1->left;
    h1->left = h1->right;
    h1->right = temp;
    return h1;
}

template<class T>
void Skewheap<T>::merge(Skewheap<T>& heap) {
    root = __merge(this->root, heap.root);
}

//insert the index of vertex and its valance into the heap
template<class T>
void Skewheap<T>::insert(int idx, T val) {
    Node<T>* h = this->root;
    Node<T>* vertex = createNode(idx, val);
    idx_node[idx] = vertex;
    //insert by _merge the two Node<T>
    this->root = _merge(h, vertex);
    this->size++;
}

template<class T>
Skewheap<T>::Node<T>* Skewheap<T>::deleteMin() {
    //break up into two trees and _merge them
    Node<T>* h = this->root;
    Node<T>* left = h->left;
    Node<T>* right = h->right;
    this->root = _merge(left, right);
    //update the size
    this->size--;
    return h;
}

// To change the val of designated node.
template<class T>
void Skewheap<T>::decreaseKey(int idx, T newval) {
    //if idx > root->val(min val at present), set root to it
    Node<T>* node = idx_node[idx];
    node->val = newval;
    while (node->parent != nullptr) {
        //parent node's val larger than its
        Node<T>* parent = node->parent;
        if (newval < parent->val) {
            //update the map
            idx_node[idx] = parent;
            idx_node[parent->idx] = node;
            //change the value
            int temp1 = parent->idx;
            int temp2 = parent->val;
            parent->idx = node->idx;
            parent->val = node->val;
            node->val = temp2;
            node->idx = temp1;
            node = parent;
        } else
            break;
    }
}

template<class T>
// return whether the heap is empty
bool Skewheap<T>::isEmpty() {
    return this->size == 0;
}

// return the valance of specficial idx
template<class T>
T Skewheap<T>::idx_val(int idx) {
    Node<T>* node = idx_node[idx];
    return node->val;
}

//delete the min node and return its value.
template<class T>
T Skewheap<T>::pop() {
  return deleteMin()->val;
}

//return the min val without deleting it.
template<class T>
T Skewheap<T>::peek() {
  return root->val;
}
#endif