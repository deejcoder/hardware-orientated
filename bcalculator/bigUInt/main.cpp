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
    bigUInt f(101);
    bigUInt g(100);
    (f + g).print();
    printf("-------\n");
    f = f - g;
    f.print();
    printf("-------\n");
    bigUInt e("0219382091382091380213210839210938210938908310928409175839759382759832798275938275982572983753982759328753298572983573295");
    bigUInt h("03480234830248204804832408324028430284203948203483049820394832094832409834098402948309483204980932483092842098409248093284092483029483024032948");
    (e + h).print();

    while (1);
}