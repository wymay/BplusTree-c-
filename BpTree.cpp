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
        else if(key>t->Keys.back()){
            t->Keys.push_back(key);
            ((LeafNode*)t)->Value.push_back(value);
            break;
        }
        else if(t->Keys[i]>key){
            t->Keys.insert(t->Keys.begin() + i, key);
            ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.begin() + i, value);
            break;
        }
    }
    
    if(t->Keys.size()>this->n){
        //split the leaf node
        Node* tnew = new LeafNode();
        tnew->Keys.insert(tnew->Keys.begin(), t->Keys.begin()+ceil(n/2), t->Keys.end());
        ((LeafNode*)tnew)->Value.insert(((LeafNode*)tnew)->Value.begin(), ((LeafNode*)t)->Value.begin()+ceil(n/2), ((LeafNode*)t)->Value.end());
        t->Keys.erase(t->Keys.begin()+ceil(n/2), t->Keys.end());
        ((LeafNode*)t)->Value.erase(((LeafNode*)t)->Value.begin()+ceil(n/2), ((LeafNode*)t)->Value.end());
        ((LeafNode*)tnew)->Next=((LeafNode*)t)->Next;
            ((LeafNode*)t)->Next=tnew;
        key = t->Keys[ceil(n/2)-1];
        while(t->Parent!=NULL){
            t=t->Parent;
            for(int i=0;i<t->Keys.size();++i){
                if(key>t->Keys.back()){
                    t->Keys.push_back(key);
                    ((In_Node*)t)->Children[t->Keys.size()]=tnew;
                    break;
                }
                else if(t->Keys[i]>key){
                    t->Keys.insert(t->Keys.begin() + i, key);
                    ((In_Node*)t)->Children.insert(((In_Node*)t)->Children.begin()+i+1, tnew);
                    break;
                }
            }
            if(t->Keys.size()>this->n){
                Node* nright = new In_Node();
                nright->Keys.insert(nright->Keys.begin(), t->Keys.begin()+floor((n+1)/2), t->Keys.end());
                ((In_Node*)nright)->Children.insert(((In_Node*)nright)->Children.begin(), ((In_Node*)t)->Children.begin()+floor((n+1)/2), ((In_Node*)t)->Children.end());
                tnew->Parent = nright;
                key = t->Keys[floor((n+1)/2)-1];
                t->Keys.erase(t->Keys.begin()+floor((n+1)/2)-1, t->Keys.end());
                ((In_Node*)t)->Children.erase(((In_Node*)t)->Children.begin()+floor((n+1)/2), ((In_Node*)t)->Children.end());
                tnew = nright;
            }
            else{
                tnew->Parent = t;
                return;
            }
            
                
        }
        if(t->Parent==NULL){
            t->Parent = new Node();
            ((In_Node*)t->Parent)->Children[0]=t;
            ((In_Node*)t->Parent)->Children[1]=tnew;
            ((In_Node*)t->Parent)->Keys[0]=t->Keys.back();
            tnew->Parent=t->Parent;
            head = t->Parent;
        }
            
    }
    else{
        return;
    }
    
}

void BpTree:: printKeys()
{
    
}