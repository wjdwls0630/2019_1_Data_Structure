//
// Created by ParkJungJin on 2019-05-25.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AVLTree.hpp"
#include "BinaryNodeType.hpp"

int main(){
    srand((unsigned int)time(nullptr));
    int num;
    AVLTree<int> bt_test;
    bt_test.Add(3);
    bt_test.Add(2);
    bt_test.Add(1);
    bt_test.Add(4);
    bt_test.Add(5);
    bt_test.Add(6);
    bt_test.Add(10);
    bt_test.Add(7);
    bt_test.Add(9);
    bt_test.Add(8);

    std::cout<<"Count : "<<bt_test.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt_test.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt_test.GetHeight()<<'\n';
    bt_test.PrintInOrder();
    bt_test.Display(bt_test.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';


    AVLTree<int> bt;

    for (int i = 0; i < 10; i++) {
        num =rand()%100+1;
        std::cout<<num<<" ";
        bt.Add(num);
    }
    std::cout<<'\n';


    std::cout<<"Count : "<<bt.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt.GetHeight()<<'\n';
    bt.PrintInOrder();
    bt.PrintPreOrder();
    bt.PrintPostOrder();
    bt.Display(bt.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';

    std::cout<<"\n\n"<<"add 22"<<'\n';
    bt.Add(22);
    bt.PrintInOrder();
    bt.Display(bt.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';
    int target = 22 ;
    std::cout<<"Get : "<<bt.Get(target)<<'\n';
    bt.Delete(target);
    std::cout<<"\n\n"<<"delete 22"<<'\n';
    bt.PrintInOrder();
    bt.Display(bt.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';

    std::cout<<"DESCENDING bt"<<'\n';

    bt.SetDirection(0);
    bt.PrintInOrder();
    bt.Display(bt.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';

    std::cout<<"bt2 : ";

    AVLTree<int> bt2(0);
    for (int i = 0; i < 10; i++) {
        num =rand()%100+1;
        std::cout<<num<<" ";
        bt2.Add(num);
    }
    std::cout<<"Count : "<<bt2.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt2.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt2.GetHeight()<<'\n';
    std::cout<<'\n';
    bt2.PrintInOrder();
    bt2.Display(bt2.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';


    std::cout<<"bt3 : ";
    AVLTree<int> bt3(1);
    for (int i = 0; i < 10; i++) {
        num =rand()%100+1;
        std::cout<<num<<" ";
        bt3.Add(num);
    }
    std::cout<<"Count : "<<bt3.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt3.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt3.GetHeight()<<'\n';
    std::cout<<'\n';
    bt3.PrintInOrder();
    bt3.Display(bt3.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';

    std::cout<<"bt = bt3"<<'\n';

    bt = bt3;
    std::cout<<"bt"<<'\n';
    std::cout<<"Count : "<<bt.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt.GetHeight()<<'\n';
    bt.PrintInOrder();
    bt.Display(bt.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';
    std::cout<<"bt3"<<'\n';
    std::cout<<"Count : "<<bt3.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt3.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt3.GetHeight()<<'\n';
    bt3. PrintInOrder();
    bt3.Display(bt3.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';

    bt3.MakeEmpty();
    std::cout<<"Count : "<<bt3.GetCount()<<'\n';
    std::cout<<"Leaf : "<<bt3.GetLeafNodeCount()<<'\n';
    std::cout<<"Height : "<<bt3.GetHeight()<<'\n';
    bt3.PrintInOrder();
    bt3.Display(bt3.GetRoot(), 1);
    std::cout<<'\n';
    std::cout<<'\n';




    return 0;
}
