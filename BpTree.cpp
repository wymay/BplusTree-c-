//
//  BpTree.cpp
//  BpTree
//
//  Created by 空气微凉 on 16/6/30.
//  Copyright © 2016年 空气微凉. All rights reserved.
//

#include "BpTree.hpp"
#include <math.h>

BpTree::BpTree(int nptr)
{
    this->n = nptr;
    this->head = new LeafNode();
}

void BpTree::insert(int key, string value)
{
    Node* t=this->head;
    while (strcmp(typeid(t).name(),"LeafNode")){ //find the proper location
        int flag = 0;
        for (int i=0;i<t->Keys.size();++i){
            if(t->Keys[i]>key){
                t = ((In_Node*)t)->Children[i];
                flag = 1;
                break;
            }
        }
        if(!flag){
            t = ((In_Node*)t)->Children[t->Keys.size()];
        }
    }
    for(int i=0;i<t->Keys.size();++i){ //insert into the leaf node
        if(t->Keys[i]==key){
            cout<<"You cannot insert duplicate keys!"<<endl;
            return;
        }
        else if(t->Keys[i]>key){
            if((t->Keys.size()+1)<=this->n){
                t->Keys.insert(t->Keys.begin() + i, key);
                ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.begin() + i, value);
            }
            else{
                //split the leaf node
                Node* tnew = new LeafNode();
                for(i=0;i<t->Keys.size();++i){
                    tnew->Keys[i]=t->Keys[ceil(n/2)+i];
                    ((LeafNode*)tnew)->Value[i]=((LeafNode*)t)->Value[ceil(n/2)+i];
                }
                t->Keys.erase(t->Keys.begin()+ceil(n/2), t->Keys.begin()+t->Keys.size()-1);
                ((LeafNode*)t)->Value.erase(((LeafNode*)t)->Value.begin()+ceil(n/2), ((LeafNode*)t)->Value.begin()+((LeafNode*)t)->Value.size()-1);
                ((LeafNode*)tnew)->Next=((LeafNode*)t)->Next;
                ((LeafNode*)t)->Next=tnew;
                
                
            }
        }
    }
    
}