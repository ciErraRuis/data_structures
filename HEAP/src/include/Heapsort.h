#pragma once

#include <Skew.h>
#include <vector>
#include <iostream>
using namespace std;

template<template <typename> class Heap, typename T>
class Heapsort {
private:
    Heap<T>* heap;
    void _initialize();
    void insert(int index, T val);
public:
    Heapsort();
    ~Heapsort();
    T pop();
    T peek();
    void sort(std::vector<T> vector);
    bool check();
};

template<template <typename> class Heap, typename T>
void Heapsort<Heap, T>::_initialize() {
    this->heap = new Heap<T>();
    cout << "New heap initialized." << endl;
}

template<template <typename> class Heap, typename T>
Heapsort<Heap, T>::Heapsort() {
    _initialize();
}

template<template <typename> class Heap, typename T>
Heapsort<Heap, T>::~Heapsort() {
    delete this->heap;
}

template<template <class> class Heap, typename T>
void Heapsort<Heap, T>::insert(int index, T val) {
    heap->insert(index, val);
}

template<template <typename> class Heap, typename T>
T Heapsort<Heap, T>::pop() {
    return heap->pop();
}

template<template <typename> class Heap, typename T>
T Heapsort<Heap, T>::peek() {
    return heap->peek();
}

template<template <typename> class Heap, typename T>
void Heapsort<Heap, T>::sort(std::vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        insert(i, v[i]);
    }
    cout << "Sorted." << endl;
}

template<template <typename> class Heap, typename T>
bool Heapsort<Heap, T>::check() {
  	T prev = peek();
	while (!heap->isEmpty()) {
      T min = pop();
      if (min < prev) {
        cout << "Error in Heapsort: " << prev << "->" << min << endl;
        return false;
      }
      prev = min;
	}
    cout << "Check finish." << endl;
    return true;
}