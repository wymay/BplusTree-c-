//
//  Node.hpp
//  BpTree
//
//  Created by 空气微凉 on 16/6/30.
//  Copyright © 2016年 空气微凉. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node
{
public:
    vector<int> Keys;
    Node* Parent;
    bool isLeaf;
};

class LeafNode: public Node
{
public:
    Node* Next;
    vector<string> Value;
    LeafNode(){isLeaf=true; Next=NULL; Parent=NULL; }
};

class In_Node:public Node
{
public:
    vector<Node*> Children;
    In_Node(){isLeaf=false; Parent=NULL; }
};

#endif /* Node_hpp */
