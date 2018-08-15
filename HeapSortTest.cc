//
//  HeapSortTest.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/15/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  Simple test to verify Heap class using heap sort algorithm.

#include <iostream>

#include "Heap.h"

using namespace std;

int main() {
    
    Heap<Node<unsigned int, unsigned int>*, vector<Node<unsigned int, unsigned int>*>,
        Compare<unsigned int, unsigned int>> list;
    
    cout << "Before Heap-Sort: 5 10 2 7 14 1 0" << endl;
    
    // push nodes with priorities in the following order: 5 10 2 7 14 1 0
    list.push(new Node<unsigned int, unsigned int>(0, 5));
    list.push(new Node<unsigned int, unsigned int>(0, 10));
    list.push(new Node<unsigned int, unsigned int>(0, 2));
    list.push(new Node<unsigned int, unsigned int>(0, 7));
    list.push(new Node<unsigned int, unsigned int>(0, 14));
    list.push(new Node<unsigned int, unsigned int>(0, 1));
    list.push(new Node<unsigned int, unsigned int>(0, 0));
    
    cout << "After Heap-Sort: ";
    
    for (int i = 0; i < 7; i++) {
        Node<unsigned int, unsigned int>* temp = list.pop();
        cout << temp->getPriority() << " ";
    }
    // nodes should be printed in the following order: 0 1 2 5 7 10 14
    cout << endl;
    
    exit(0);
}
