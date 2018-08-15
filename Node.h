//
//  Node.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/5/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
// Templatized Node class containing Data and Priority fields.

#ifndef Node_h
#define Node_h

#include <iostream>
#include <functional>
#include <algorithm>

template<typename Data, typename Priority>
class Node {
public:
    
    Node();
    Node(Data d, Priority p);
    Node(Data d);
    Node(Priority p, Node<Data, Priority>* left, Node<Data, Priority>* right);
    ~Node();
    
    // returns node's Data
    const Data& getData() const {
        return data_;
    }
    
    // retirns node's Priority
    const Priority& getPriority() const {
        return priority_;
    }

    Node<Data, Priority>*& getLeft() {
        return left;
    }
    
    Node<Data, Priority>*& getRight() {
        return right;
    }
    
    // returns true if node is a branch, false otherwise
    bool isBranch() {
        return data_ == Data{};
    }
    
    
private:
    Data data_;
    Priority priority_;
    Node<Data, Priority>* left;
    Node<Data, Priority>* right;
    
};

// compares the Priorities of two nodes
template <typename Data, typename Priority>
struct Compare {
    bool operator()(const Node<Data, Priority>* lhs,
                    const Node<Data, Priority>* rhs) const {
        return lhs->getPriority() < rhs->getPriority();
    }
};

template<typename Data, typename Priority>
Node<Data, Priority>::Node() : data_(Data{}), priority_(Priority{}),
                               left(nullptr), right(nullptr) {}

template<typename Data, typename Priority>
Node<Data, Priority>::Node(Data d) : data_(d), priority_(Priority{}),
                                left(nullptr), right(nullptr) {}

template<typename Data, typename Priority>
Node<Data, Priority>::Node(Data d, Priority p) : data_(d), priority_(p),
                                                 left(nullptr), right(nullptr) {}

template<typename Data, typename Priority>
Node<Data, Priority>::Node(Priority p, Node<Data, Priority>* left,
                           Node<Data, Priority>* right) : data_(Data{}), priority_(p),
                           left(left), right(right) {}

template<typename Data, typename Priority>
Node<Data, Priority>::~Node() {}


#endif
