#ifndef _BINOMIAL_H_
#define _BINOMIAL_H_

#include <bits/stdc++.h>
#include "Dijkstra.h"
using namespace std;

class bNode {
public:
	int value;
	bNode* parent;
	vector<bNode*> children;
	int degree;
	bool marked;
	int index;

	bNode(int val, int idx) {
		index = idx;
		value = val;
		parent = nullptr;
		children.clear();
		degree = 0;
		marked = false;
	}
};

class BinomialHeap {
public:
	vector<bNode*> trees;
	bNode* min_node;
	int count;

	BinomialHeap();
	bool is_empty();
	void insert(int idx, int value);
	int get_min();
	bNode* extract_min();
	void merge(BinomialHeap& other_heap);
	void _find_min();
	void decrease_key(bNode* node, int new_value);
	void delete_node(bNode* node);
	void _bubble_up(bNode* node);
	void _link(bNode* tree1, bNode* tree2);
	void _consolidate();
	int size();
};

int dijkstra_binomail(int fromn, int ton);
#endif