#include <iostream>
#include "RBTree.h"

int main()
{
    RBTree<int> *RB = new RBTree<int>();
    RB->insert(1, 1);
    RB->insert(2, 2);
    RB->print();
    RB->remove(1);
    RB->print();
    RB->insert(3, 3);
    RB->print();
}
