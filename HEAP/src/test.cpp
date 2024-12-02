#include <Heapsort.h>
#include <Skew.h>
#include <bits/stdc++.h>

using namespace std;

enum {
    RANDOM = 0,
    INCREASE,
    DECREASE,
    REPEART,
    MODE_NUM
};

//Class for check
class Check {
private:
    vector<int> v;
    int _randomInt(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min,max);

        return dis(gen);
    }

    //functions to generate corresponding test array
    //Random push_back
    void random(int n, int min=0, int max=1000000) {
        for (int i = 0; i < n; i++) {
            v.push_back(_randomInt(min,max));
        }
    }

    //N to 1
    void decreaseOrder(int n) {
        for (int i = n; i > 0; i--) {
            v.push_back(i);
        }
    }

    //1 to N
    void increaseOrder(int n) {
        for (int i = 1; i <= n; i++) {
            v.push_back(i);
        }
    }

    //somehow similar to random.
    void containRepeat(int n) {
        int num = 1;
        for (int i = 1; i <= n; i++) {
            v.push_back(num);
            if (_randomInt(0,1) % 2)
                num++;
        }
    }

public:
    Check():v(vector<int>()) {}

    void clear() {
        v = vector<int>();
    }

    //initialize the vector according to the mode
    void prepareData(int n, int mode=RANDOM) {
        cout << "Preparing data of size " << n << endl;
        switch (mode) {
            case RANDOM:   random(n);        break;
            case INCREASE: increaseOrder(n); break;
            case DECREASE: decreaseOrder(n); break;
            case REPEART:  containRepeat(n); break;
            default: cout << "Unrecognized mode" << endl; return;
        }
        cout << "Data Ready." << endl;
    }

    const vector<int>& array() {
        return v;
    }
};

// Argument:
// n: scale of data
// mode: how the test array is generated
template<template <typename> class Heap, typename T>
bool test(int n=1000000, int mode=RANDOM) {
    Heapsort<Heap, T> h;
    Check check;
    check.prepareData(n, mode);
    auto start = std::chrono::high_resolution_clock::now();
    h.sort(check.array());
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> runtime1 = end - start;
    cout << "Heapsort finished. Execution time: " << runtime1.count() << endl;
    cout << "Start Checking correctness." << endl;
    bool ret = false;
    if (ret = h.check()) {
        cout << "Correct!" << endl;
    } else {
        cout << "Error!" << endl;
        return ret;
    }
    //
    cout << "Running std heapsort." << endl;
    vector<int> v1 = check.array();
    make_heap(v1.begin(), v1.end());
    cout << "make_heap finished. Start Sorting." << endl;
    start = std::chrono::high_resolution_clock::now();
    sort_heap(v1.begin(), v1.end());
    end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> runtime2 = end - start;
    cout << "STD Sort finished. Execution time: " << runtime2.count() << endl;
    return ret;
}

// run all mode with the scale n
template<template <typename> class Heap, typename T>
bool test_for_all(int n) {
    for (int i = 0; i < MODE_NUM; i++) {

        cout << "----------[TEST " << i + 1 << "]----------" << endl;
        if (test<Heap, T>(n, i)) {
            cout << "Test" << i + 1 << " successes." << endl << endl;
        } else {
            cout << "Something wrong for test" << i + 1 << endl << endl;
            return false;
        }
    }
    return true;
}

int main() {
    Heapsort<Skewheap, int> h;
    Check check;
    int N = 1000000;
    test_for_all<Skewheap, int>(N);
}