#include <iostream>
#include "biguint.h"

using namespace std;

int main()
{
    bigUInt a;
    a.print();
    bigUInt b(1024);
    b.print();
    bigUInt c("099999999999999999999");
    c.print();
    bigUInt d(b);
    d.print();
    printf("------\n");
    b.increment();
    b.print();
    b.add(b);
    b.print();
    printf("------\n");
    b = a;
    b.print();
    cout << c << endl;
    bigUInt f(2000);
    b = b - f;
    b.print();

    while (1);
}