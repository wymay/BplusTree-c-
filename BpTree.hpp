//
//  BpTree.h
//  BpTree
//
//  Created by May Wu on 16/6/30.
//  Copyright © 2016 May Wu All rights reserved.
//

#ifndef BpTree_h
#define BpTree_h

#include <iostream>
#include "Node.hpp"
using namespace std;

class BpTree
{
private:
    Node* head;
    int n;
    
public:

    BpTree(int);
    void insert(int, string);
    void remove(int);
    string find(int);
    void printKeys();
    void printValues();
    ~BpTree();
    
};


#endif /* BpTree_h */
