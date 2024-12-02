#ifndef _FIB_HEAP_H_
#define _FIB_HEAP_H_

#include "Dijkstra.h"
#include <cmath>

using namespace std;

struct node{
    pair<int,int> val;
    int mark;
    int degree;
    node* parent, *child, *left, *right;
};

struct heap{
    node* min;
    int n;
};

#endif