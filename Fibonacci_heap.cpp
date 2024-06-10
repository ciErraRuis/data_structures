#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <unordered_map>
using namespace std;


struct node {
    int idx;
    int dist;
    bool mark;
    int degree;
    node* left;
    node* right;
    node* parent;
    node* child;
};

unordered_map<int, node*> idx_node;

node* create_node(int idx, int dist) {
    node* n = new node();
    n->dist = dist;
    n->idx = idx;
    n->degree = 0;
    n->mark = false;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    n->child = nullptr;
    idx_node[idx] = n;
    return n;
}

struct heap {
    int size;
    //for check
    int root_num;
    node* min;

    //construct and deconstruct
    heap();
    //key functions
    void insert(int idx, int dist);
    void decreaseKey(int idx, int newDist);
    node* deleteMin();
    //helper functions
    void add_root(node* n);  //put a node existing already to the root
    void remove_list(node* n); //remove a node from the doubly linked list
    void consolidate(); //merge the node with the same degree after deleteMin
    void cut(node* son, node* par);  //cut the node from the parent;
    void cascade_cut(node* n);
    void link(node* son, node* par); //link son to the child of par;
};

//implementation
heap::heap() {
    this->size = 0;
    this->min = nullptr;
    this->root_num = 0;
}


//remove from the list, NO CHANGE OF PARENT AND CHILD RELATIONSHIP
void heap::remove_list(node* n) {
    if (n == min) {
        min = nullptr;
        return;
    }
    if (n->parent && n->right == n) {
        n->parent->child = nullptr;
        return;
    }
    n->left->right = n->right;
    n->right->left = n->left;
}

//add a node into the root_list, NO CHANGE OF PARENT AND CHILD RELATIONSHIP
void heap::add_root(node* n) {
    this->root_num++;
    if (min) {
        //add to the root
        min->right->left = n;
        n->right = min->right;
        min->right = n;
        n->left = min;
        if (n->dist < min->dist) {
            min = n;
        }
    } else {
        //没节点, be the root
        min = n;
        n->right = n;
        n->left = n;
        root_num++;
    }
    n->mark = false;
}

void heap::insert(int idx, int dist) {
    node* n = create_node(idx, dist);
    //no nodes now
    add_root(n);
    //if smaller, change the min
    if (n->dist < min->dist) {
        min = n;
    }
    size++;
}

node* heap::deleteMin() {
    //if empty
    if (!min) {
        cout << "error, deleteMin while the heap is empty" << endl;
        return nullptr;
    }

    node* res = min;
    //insert all child into the root
    node* curr = min->child;
    int num = res->degree;
    for (int i = 0; i < num; i++) {
        node* next = curr->right;
        curr->parent = nullptr;
        remove_list(curr);
        add_root(curr);
        res->degree--;
        curr = next;
    }
    //change the min and remove, consolidate, return
    min = res->right;
    remove_list(res);
    consolidate();
    size--;
    return res;
}

//link to the child
void heap::link(node* son, node* par) {
    son->parent = par;
    //no child
    if (!par->child) {
        par->child = son;
        son->left = son;
        son->right = son;
    } else {
        //add to the right of child
        node* child = par->child;
        child->right->left = son;
        son->right = child->right;
        child->right = son;
        son->left = child;
    }
    par->degree++;
}

//after delete, merge the root with the same degree
void heap::consolidate() {
    //no node or only one node
    if (!min || min->right == min)
        return;
    int max_degree = (log(size) / log(2)) + 1;
    node* A[max_degree+1];
    //initialize
    for (int i = 0; i < max_degree + 1; i++) {
        A[i] = nullptr;
    }
    node* flag = min; //first node to modify, judge the end of circle
    node* curr = min;
    node* next;
    do {
        next = curr->right;
        int d = curr->degree;
        while (A[d]) {
            //let the small be the curr
            if (curr->dist > A[d]->dist) {
                node* temp = A[d];
                A[d] = curr;
                curr = temp;
            }
            link(A[d], curr);
            A[d] = nullptr;
            d++;
        }
        A[d] = curr;
        //move the ptr forward
        curr = next;
    } while (flag != curr);
    //insert all the node in A[d] to root
    min = nullptr;
    root_num = 0;
    for (int i = 0; i < max_degree + 1; i++) {
        if (A[i] != nullptr) {
            add_root(A[i]);
            A[i]->parent = nullptr;
            root_num++;
        }
    }
}

//remove son from the parent;
void heap::cut(node* son, node* par) {
    if (!par) {
        cout << "error from CUT: par is null" << endl;
        return;
    }
    if (son->parent != par) {
        cout << "error form CUT: son doesn't match parent" << endl;
        return;
    }
    node* child = par->child;
    son->parent = nullptr;
    //only one child
    if (child->right == child) {
        par->child = nullptr;
    } else if (child == son) {
        //son is the leftmost child
        par->child = son->right;
        remove_list(son);
    } else {
        //son is not the par->child
        remove_list(son);
    }
    //add to the root
    add_root(son);
    par->degree--;
}

void heap::cascade_cut(node* n) {
    node* par = n->parent;
    //not root and par marked
    if (par != nullptr) {
        if (par->mark) {
            cut(n, par);
            cascade_cut(par);
        } else {
            par->mark = true;
        }
    }
}

void heap::decreaseKey(int idx, int newDist) {
    node* curr = idx_node[idx];
    curr->dist = newDist;
    //cascade
    node* par = curr->parent;
    if (par != nullptr && newDist < par->dist) {
        cut(curr, par);
        cascade_cut(par);
    }
    //change the min if needed
    if (newDist < min->dist) {
        min = curr;
    }
}