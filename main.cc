#include <iostream>
#include <random>
#include "skiplist.hpp"

int main(){
    srand((unsigned)time(0));
    SkipList<int, int> list(4, 0.5);
    list.insertElem(1,2);
    list.insertElem(5,2);
    list.insertElem(2,2);
    list.insertElem(3,2);
    list.insertElem(6,2);
    list.insertElem(9,2);
    list.insertElem(8,2);
    list.displayList();
    Node<int, int>* node = list.searchElem(4);
    node = list.searchElem(6);
    return 0;
}