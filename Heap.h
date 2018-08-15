//
//  heap.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/4/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  Templatized priority queue using heap implementation.

#ifndef Heap_h
#define Heap_h

#include <vector>
#include <iostream>
#include <algorithm>
#include "Node.h"

// priority queue contains object T, list Container,
// and comparable function Compare
template<typename T, typename Container, typename Compare>
class Heap {
public:
    
    Heap();
    ~Heap();
    
    // adds object to priority queue
    void push(T object);
    
    // pops off first object with highest priority (lowest priority number)
    T pop();
    
    // returns if priority queue is empty, false otherwise
    bool is_empty();
    // return size of priority queue
    int getSize();

    // prints content of priority queue
    void dump();
    // checks to see if priority queue retains binary heap property
    bool verify();
    
private:
    
    Container pq;
    Compare compare;
    int size;
    
    // percolates highest priority object up
    void heapify_up(int index);
    
    // percolates lowest priority object down
    void heapify_down(int index, bool done);
    
    void swap(int index1, int index2);
    void verify_Helper(bool& result, int index);
};

template<typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap() {
    pq.push_back(T{});
    size = static_cast<int>(pq.size());
}

template<typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::~Heap() {}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::push(T object) {
    pq.push_back(object); // adds placeholder at index 0
    size++;
    heapify_up(size - 1);
}

template<typename T, typename Container, typename Compare>
T Heap<T, Container, Compare>::pop() {
    T result = pq[1];
    pq[1] = pq[size - 1];
    pq.pop_back();
    size--;
    bool done = false;
    if (size > 2) {
        heapify_down(1, done);
    }
    return result;
}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::heapify_up(int index) {
    if (index == 1) return;
    
    T child = pq[index];
    T parent = pq[index / 2];
    
    if (compare(child, parent)) {
        swap(index, index / 2);
        index = index / 2;
        heapify_up(index);
    }
}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::heapify_down(int index, bool done) {
    if (index <= (size - 1) / 2 && !done) {
        done = true;
        if (index * 2 == size - 1) {
            T parent = pq[index];
            T leftChild = pq[index * 2];
            if (compare(leftChild, parent)) {
                swap(index, index * 2);
                done = false;
            }
            index = index * 2;
        } else {
            T parent = pq[index];
            T leftChild = pq[index * 2];
            T rightChild = pq[(index * 2) + 1];
            if (compare(leftChild, parent) || compare(rightChild, parent)) {
                if (compare(leftChild, rightChild)) {
                    swap(index, index * 2);
                    index = index * 2;
                } else {
                    swap(index, (index * 2) + 1);
                    index = index * 2 + 1;
                }
                done = false;
            }
        }
        heapify_down(index, done);
    }
}

template<typename T, typename Container, typename Compare>
bool Heap<T, Container, Compare>::verify() {
    bool result = true;
    verify_Helper(result, 1);
    if (!result) {
        std::cerr << "BAD HEAP" << std::endl;
    } else {
        std::cerr << "GOOD HEAP" << std::endl;
    }
    dump();
    return result;
}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::verify_Helper(bool& result, int index) {
    if (index <= (size - 1) / 2) {
        if ((size - 1) % 2 == 0) {
            T parent = pq[index];
            T leftChild = pq[index * 2];
            if (compare(leftChild, parent)) {
                result = false;
            }
        } else {
            T parent = pq[index];
            T leftChild = pq[index * 2];
            T rightChild = pq[(index * 2) + 1];
            if (compare(leftChild, parent) || compare(rightChild, parent)) {
                result = false;
            }
        }
        verify_Helper(result, index + 1);
    }
}

template<typename T, typename Container, typename Compare>
bool Heap<T, Container, Compare>::is_empty() {
    return size == 1;
}

template<typename T, typename Container, typename Compare>
int Heap<T, Container, Compare>::getSize() {
    return size - 1;
}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::swap(int index1, int index2) {
    T temp = pq[index1];
    pq[index1] = pq[index2];
    pq[index2] = temp;
}

template<typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::dump() {
    std::cerr << "--" << std::endl;
    for (int i = 1; i < size; i++) {
        if (pq[i]->isBranch()) {
            std::cerr << " " << pq[i]->getPriority() << std::endl;
        } else {
            char c = static_cast<char>(pq[i]->getData());
            std::cerr << (isprint(c) ? c : ' ') << " " << pq[i]->getPriority() << std::endl;
        }
    }
    std::cerr << std::endl;
}


#endif
