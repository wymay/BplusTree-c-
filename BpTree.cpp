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
    while (!t->isLeaf){ //find the proper location
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
    if(t->Keys.size()==0||key>t->Keys.back()){
        t->Keys.push_back(key);
        ((LeafNode*)t)->Value.push_back(value);
    }
    else{
        for(int i=0;i<t->Keys.size();++i){ //insert into the leaf node
            if(t->Keys[i]==key){
                cout<<"You cannot insert duplicate keys!"<<endl;
                return;
            }
            else if(t->Keys[i]>key){
                t->Keys.insert(t->Keys.begin() + i, key);
                ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.begin() + i, value);
                break;
            }
        }
    }
    if(t->Keys.size()>this->n){
        //split the leaf node
        Node* tnew = new LeafNode();
        tnew->Parent = t->Parent;
        tnew->Keys.insert(tnew->Keys.begin(), t->Keys.begin()+ceil((n+1)/2), t->Keys.end());
        ((LeafNode*)tnew)->Value.insert(((LeafNode*)tnew)->Value.begin(), ((LeafNode*)t)->Value.begin()+ceil((n+1)/2), ((LeafNode*)t)->Value.end());
        t->Keys.erase(t->Keys.begin()+ceil((n+1)/2), t->Keys.end());
        ((LeafNode*)t)->Value.erase(((LeafNode*)t)->Value.begin()+ceil((n+1)/2), ((LeafNode*)t)->Value.end());
        ((LeafNode*)tnew)->Next=((LeafNode*)t)->Next;
            ((LeafNode*)t)->Next=tnew;
        key = t->Keys[ceil((n+1)/2)-1];
        while(t->Parent!=NULL){
            t=t->Parent;
            for(int i=0;i<t->Keys.size();++i){
                if(key>t->Keys.back()){
                    t->Keys.push_back(key);
                    ((In_Node*)t)->Children.push_back(tnew);
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
                nright->Parent = t->Parent;
                nright->Keys.insert(nright->Keys.begin(), t->Keys.begin()+floor((n+2)/2), t->Keys.end());
                ((In_Node*)nright)->Children.insert(((In_Node*)nright)->Children.begin(), ((In_Node*)t)->Children.begin()+floor((n+2)/2), ((In_Node*)t)->Children.end());
                for(int i=floor((n+2)/2);i<((In_Node*)t)->Children.size();++i){
                    ((In_Node*)t)->Children[i]->Parent = nright;
                }
                key = t->Keys[floor((n+2)/2)-1];
                t->Keys.erase(t->Keys.begin()+floor((n+2)/2)-1, t->Keys.end());
                ((In_Node*)t)->Children.erase(((In_Node*)t)->Children.begin()+floor((n+2)/2), ((In_Node*)t)->Children.end());
                tnew = nright;
            }
            else{
                tnew->Parent = t;
                return;
            }
            
                
        }
        if(t->Parent==NULL){
            t->Parent = new In_Node();
            ((In_Node*)t->Parent)->Children.insert(((In_Node*)t->Parent)->Children.begin(), t);
            ((In_Node*)t->Parent)->Children.insert(((In_Node*)t->Parent)->Children.begin()+1,tnew);
            if(t->isLeaf){
                (t->Parent)->Keys.insert((t->Parent)->Keys.begin(),t->Keys.back());
            }
            else{
                (t->Parent)->Keys.insert((t->Parent)->Keys.begin(),((In_Node*)t)->Children.back()->Keys.back());
            }
            tnew->Parent=t->Parent;
            head = t->Parent;
        }
            
    }
    else{
        return;
    }
    
}


void BpTree:: remove(int key){
    Node* t=this->head;
    while (!t->isLeaf){ //find the proper location
        int flag = 0;
        for (int i=0;i<t->Keys.size();++i){
            if(t->Keys[i]>=key){
                t = ((In_Node*)t)->Children[i];
                flag = 1;
                break;
            }
        }
        if(!flag){
            t = ((In_Node*)t)->Children[t->Keys.size()];
        }
    }
    int flag=0;
    for(int i=0;i<t->Keys.size();++i){
        if(t->Keys[i]==key){
            t->Keys.erase(t->Keys.begin()+i);
            ((LeafNode*)t)->Value.erase(((LeafNode*)t)->Value.begin()+i);
            flag=1;
            break;
        }
    }
    if(!flag){
        cout<<"The key you want to delete does not exist!"<<endl;
        return;
    }
    if(((LeafNode*)t)->Value.size()<ceil((n+1)/2) && t->Parent!=NULL){
        
        Node* Rsibling;
        Node* Lsibling;
        Rsibling=Lsibling=NULL;
        
        int Child_num = -1;
        for(int i=0;i<((In_Node*)t->Parent)->Children.size();++i){
            if(((In_Node*)t->Parent)->Children[i]==t){
                Child_num=i;
                break;
            }
        }
        if(Child_num-1>=0){
            Lsibling = ((In_Node*)t->Parent)->Children[Child_num-1];
        }
        
        if(Child_num+1<((In_Node*)t->Parent)->Children.size()){
            Rsibling = ((In_Node*)t->Parent)->Children[Child_num+1];
        }

        if(Rsibling!=NULL && ((LeafNode*)Rsibling)->Value.size()-1>=ceil((n+1)/2)){
            t->Keys.push_back(Rsibling->Keys.front());
            ((LeafNode*)t)->Value.push_back(((LeafNode*)Rsibling)->Value.front());
            Rsibling->Keys.erase(Rsibling->Keys.begin());
            ((LeafNode*)Rsibling)->Value.erase(((LeafNode*)Rsibling)->Value.begin());
            t->Parent->Keys[Child_num]=t->Keys.back();
            return;
        }
        else if(Lsibling!=NULL && ((LeafNode*)Lsibling)->Value.size()-1>=ceil((n+1)/2)){
            t->Keys.insert(t->Keys.begin(), Lsibling->Keys.back());
            ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.begin(), ((LeafNode*)Lsibling)->Value.back());
            Lsibling->Keys.erase(Lsibling->Keys.end()-1);
            ((LeafNode*)Lsibling)->Value.erase(((LeafNode*)Lsibling)->Value.end()-1);
            t->Parent->Keys[Child_num-1]=Lsibling->Keys.back();
            return;
        }
        else {
            if(Rsibling!=NULL && ((LeafNode*)Rsibling)->Value.size()-1<ceil((n+1)/2)){
                t->Keys.insert(t->Keys.end(), Rsibling->Keys.begin(), Rsibling->Keys.end());
                ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.end(),((LeafNode*)Rsibling)->Value.begin(), ((LeafNode*)Rsibling)->Value.end());
                ((LeafNode*)t)->Next=((LeafNode*)Rsibling)->Next;
                
                t->Parent->Keys.erase(t->Parent->Keys.begin()+Child_num);
                ((In_Node*)t->Parent)->Children.erase(((In_Node*)t->Parent)->Children.begin()+Child_num+1);
            }
            else if(Lsibling!=NULL && ((LeafNode*)Lsibling)->Value.size()-1<ceil((n+1)/2)){
                Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(), t->Keys.end());
                ((LeafNode*)Lsibling)->Value.insert(((LeafNode*)Lsibling)->Value.begin(),((LeafNode*)t)->Value.begin(), ((LeafNode*)t)->Value.end());
                
                ((LeafNode*)Lsibling)->Next=((LeafNode*)t)->Next;
                
                t->Parent->Keys.erase(t->Parent->Keys.begin()+Child_num-1);
                ((In_Node*)t->Parent)->Children.erase(((In_Node*)t->Parent)->Children.begin()+Child_num);
                t = Lsibling;
            }
            
            while(t->Parent!=this->head){
                Rsibling=Lsibling=NULL;
                t=t->Parent;
                if(((In_Node*)t)->Children.size()>=floor((n+2)/2)){
                    return;
                }
                int Child_num = -1;
                for(int i=0;i<((In_Node*)t->Parent)->Children.size();++i){
                    if(((In_Node*)t->Parent)->Children[i]==t){
                        Child_num=i;
                        break;
                    }
                }
                if(Child_num-1>=0){
                    Lsibling = ((In_Node*)t->Parent)->Children[Child_num-1];
                }
                
                if(Child_num+1<((In_Node*)t->Parent)->Children.size()){
                    Rsibling = ((In_Node*)t->Parent)->Children[Child_num+1];
                }
                if(Rsibling!=NULL && ((In_Node*)Rsibling)->Children.size()-1>=floor((n+2)/2)){
                    ((In_Node*)t)->Children.push_back(((In_Node*)Rsibling)->Children.front());
                    t->Keys.push_back(t->Parent->Keys[Child_num]);
                    t->Parent->Keys[Child_num]=Rsibling->Keys.front();
                    ((In_Node*)Rsibling)->Children.erase(((In_Node*)Rsibling)->Children.begin());
                    Rsibling->Keys.erase(Rsibling->Keys.begin());
                    ((In_Node*)t)->Children.back()->Parent=t;
                    return;
                }
                else if(Lsibling!=NULL && ((In_Node*)Lsibling)->Children.size()-1>=floor((n+2)/2)){
                    ((In_Node*)t)->Children.insert(((In_Node*)t)->Children.begin(),((In_Node*)Lsibling)->Children.back());
                    t->Keys.insert(t->Keys.begin(), t->Parent->Keys[Child_num-1]);
                    t->Parent->Keys[Child_num]=Lsibling->Keys.back();
                    ((In_Node*)Lsibling)->Children.erase(((In_Node*)Lsibling)->Children.end()-1);
                    Lsibling->Keys.erase(Lsibling->Keys.end()-1);
                    ((In_Node*)t)->Children.front()->Parent=t;
                    return;
                }
                else if(Rsibling!=NULL && ((In_Node*)Rsibling)->Children.size()-1<floor((n+2)/2)){
                    ((In_Node*)Rsibling)->Children.insert(((In_Node*)Rsibling)->Children.begin(),((In_Node*)t)->Children.begin(),((In_Node*)t)->Children.end());
                    Rsibling->Keys.insert(Rsibling->Keys.begin(), t->Parent->Keys[Child_num]);
                    Rsibling->Keys.insert(Rsibling->Keys.begin(), t->Keys.begin(), t->Keys.end());
                    for(int i=0;i<((In_Node*)t)->Children.size();++i){
                        ((In_Node*)t)->Children[i]->Parent=Rsibling;
                    }
                    t->Parent->Keys.erase(t->Parent->Keys.begin()+Child_num);
                    ((In_Node*)t->Parent)->Children.erase(((In_Node*)t->Parent)->Children.begin()+Child_num);
                    t = Rsibling;
                }
                else if(Lsibling!=NULL && ((In_Node*)Lsibling)->Children.size()-1<floor((n+2)/2)){
                    ((In_Node*)Lsibling)->Children.insert(((In_Node*)Lsibling)->Children.end(), ((In_Node*)t)->Children.begin(), ((In_Node*)t)->Children.end());
                    Lsibling->Keys.insert(Lsibling->Keys.end(), t->Parent->Keys[Child_num-1]);
                    Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(), t->Keys.end());
                    for(int i=0;i<((In_Node*)t)->Children.size();++i){
                        ((In_Node*)t)->Children[i]->Parent=Lsibling;
                    }
                    t->Parent->Keys.erase(t->Parent->Keys.begin()+Child_num-1);
                    ((In_Node*)t->Parent)->Children.erase(((In_Node*)t->Parent)->Children.begin()+Child_num);
                    t = Lsibling;
                }
            }
            if(t->Parent==this->head && this->head->Keys.size()==0){
                this->head=t;
                return;
            }
            
        }
        
    }
    
}



string BpTree:: find(int key){
    Node* t=this->head;
    while (!t->isLeaf){ //find the proper location
        int flag = 0;
        for (int i=0;i<t->Keys.size();++i){
            if(t->Keys[i]>=key){
                t = ((In_Node*)t)->Children[i];
                flag = 1;
                break;
            }
        }
        if(!flag){
            t = ((In_Node*)t)->Children[t->Keys.size()];
        }
    }
    for(int i=0;i<t->Keys.size();++i){
        if(t->Keys[i]==key){
            return ((LeafNode*)t)->Value[i];
        }
    }
    return "This key does not exist in this B+ tree!";
}


void BpTree:: printKeys()
{
    if(head->Keys.size()==0){
        cout<<"[]"<<endl;
        return;
    }
    vector<Node*> q;
    q.push_back(head);
    while(q.size()){
        unsigned long size = q.size();
        for(int i=0;i<size;++i){
            if(!q[i]->isLeaf){
                for(int j=0;j<((In_Node*)q[i])->Children.size();++j){
                        q.push_back(((In_Node*)q[i])->Children[j]);
                }
            }
            cout<<"[";
            int nk=0;
            for(nk=0;nk<q[i]->Keys.size()-1;++nk){
                cout<<q[i]->Keys[nk]<<",";
            }
            cout<<q[i]->Keys[nk]<<"] ";
        }
        q.erase(q.begin(),q.begin()+size);
        cout<<endl;
    }
    
}


void BpTree:: printValues()
{
    Node* t = this->head;
    while(!t->isLeaf){
        t = ((In_Node*)t)->Children[0];
    }
    while(t!=NULL){
        for(int i=0;i<t->Keys.size();++i){
            cout<<((LeafNode*)t)->Value[i]<<endl;
        }
        t=((LeafNode*)t)->Next;
    }
}

BpTree:: ~BpTree()
{
    if(this->head){
        delete this->head;
    }
}

