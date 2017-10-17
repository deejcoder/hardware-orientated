#include <iostream>
#include "biguint.h"

using namespace std;

int main()
{
    bigUInt* a = new bigUInt(2);
    a->add(20);
    a->print();
    a->increment();
    a->print();
    a->print();
    bigUInt* b = new bigUInt("099999999999999999999");
    b->print();
    delete a;
    delete b;
    while (1);
}