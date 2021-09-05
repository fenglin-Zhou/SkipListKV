#include <iostream>
#include <random>
#include "skiplist.h"

int main(){
    srand((unsigned)time(0));
    SkipList<int, int> list(4, 0.5);
    bool flag = list.insertElem(1,2);
    flag = list.insertElem(5,2);
    flag = list.insertElem(2,2);
    flag = list.insertElem(3,2);
    flag = list.insertElem(6,2);
    flag = list.insertElem(9,2);
    flag = list.insertElem(8,2);
    list.displayList();
    return 0;
}