//
//  main.cpp
//  BpTree
//
//  Created by 空气微凉 on 16/6/30.
//  Copyright © 2016年 空气微凉. All rights reserved.
//

#include <iostream>
#include "BpTree.hpp"

int main(int argc, const char * argv[]) {
   
    BpTree t(3);
//    while(true){
//        int c;
//        cout<<"Choose What You Want To Do:"<<endl;
//        cout<<"1--Insert"<<endl;
//        cout<<"2--Find"<<endl;
//        cout<<"3--Printkey"<<endl;
//        cout<<"4--PrintValue"<<endl;
//        cin>>c;
//        switch (c) {
//            case 1:{
//                int x;
//                string s;
//                cin>>x;
//                cin>>s;
//                t.insert(x, s);
//                break;}
//            case 2:{
//                int x;
//                cin>>x;
//                t.find(x);
//                break;
//            }
//            case 3:{
//                t.printKeys();
//                break;
//            }
//            case 4:{
//                t.printValues();
//            }
//                
//            default:
//                break;
//        }
//    }
    t.insert(2, "a");
    t.printKeys();

    t.insert(11, "c");
    t.printKeys();
    
    t.insert(13, "h");
    t.printKeys();
    
    t.insert(21, "i");
    t.printKeys();
    
    t.insert(64, "k");
    t.printKeys();
    
    t.insert(4, "b");
    t.printKeys();
    
    t.insert(23, "j");
    t.printKeys();
    
    t.insert(9, "e");
    t.printKeys();
    t.insert(19, "f");
    t.printKeys();
    t.insert(5, "d");
    t.printKeys();

    t.insert(10, "g");
    t.printKeys();
    
    t.insert(6, "g");
    t.printKeys();
    t.insert(7, "g");
    t.printKeys();
    t.insert(60, "g");
    t.insert(71, "g");
    t.insert(93, "g");
    t.insert(77, "g");
    t.printKeys();
    cout<<t.find(71)<<endl;
    t.insert(77, "z");

    return 0;
}
