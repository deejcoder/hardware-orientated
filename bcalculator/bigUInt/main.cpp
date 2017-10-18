#include <iostream>
#include "biguint.h"

using namespace std;

int main()
{
    bigUInt* a = new bigUInt(199);
    a->print();
    a->increment();
    a->add(100);
    a->print();
    bigUInt* b = new bigUInt("099999999999999999999");
    b->print();
    b->increment();
    b->print();
    bigUInt* c = new bigUInt("123");
    c->print();
    c->add(*a);
    c->print();
    delete a;
    delete b;
    while (1);
}