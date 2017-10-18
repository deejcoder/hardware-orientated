#include <iostream>
#include <string> // No one specified we cannot use this...
#include "biguint.h"

using namespace std;

//Memory vs Performance? The application depends
#define BIGINT_SIZE 100

bigUInt::bigUInt() {
    this->p = new char[BIGINT_SIZE]();
    this->p[0] = '0';
}

bigUInt::bigUInt(unsigned int n) {

    string nstr = to_string(n);
    this->p = new char[nstr.length() + 1]();
    

    //for all values of size_t, size_t >= 0 since unsigned, end at 0 else breaking point
    int counter = 0;
    for (size_t i = nstr.length(); i-- > 0;) {
        this->p[counter] = nstr[i];
        counter++;
    }
}

bigUInt::bigUInt(const char *s) {
    size_t len = strlen(s);
    this->p = new char[len + 1]();

    int counter = 0;
    bool nonzero = false;
    for (size_t i = len; i-- > 0;) {

        //skip leading zeros
        if (!nonzero && s[i] == '0') continue;

        this->p[counter] = s[i];
        counter++;
    }
}

bigUInt::bigUInt(const bigUInt &x) {
    size_t len = strlen(x.get_p());
    this->p = new char[len + 1]();
    //strcpy(this->p, x.get_p());
}

bigUInt::~bigUInt() {
    if (this->p) {
        delete[](this->p); //free the array from heap
    }
}

void bigUInt::add(unsigned int n) {
    printf("n: %d\n", n);
    for (int i = n; i-- > 0;) {
        this->increment();
    }
}

void bigUInt::add(const bigUInt &x) {
    int multiplier = 1;
    int value;

    for (int i = 0; i < strlen(x.p); i++) {

        value = x.p[i] - '0'; //char as int
        this->add(value*multiplier);
        multiplier *= 10;
    }
}

void bigUInt::increment() {
    int index = 0;
    int len = strlen(this->p);
    
    //since the number is in reverse, find the first cell with a non-9
    char num = this->p[0];
    while (num == '9') {
        if (index > len) {
            index++; //set it to > len
            break;
        }
            
        num = this->p[index];
        index++;
    }

    //case 1: if the first cell is < 9
    if (index == 0) {
        this->p[index]++;
    }

    //case 2: if all digits are 999, add one @ end & set all else to 0
    if(index > len) {

        //adding one cell & set all cells to 0, assuring \0 @ end
        len++;
        char* temp = new char[len + 1]();
        memset(temp, '0', len);

        //set most significant to 1
        temp[len - 1] = '1';

        delete[](this->p);
        this->p = temp;
    }

    //case 3: increase the non-9 by one, set all before it to 0
    else {
        index--;
        this->p[index]++;
        for (; index-- > 0;) {
            this->p[index] = '0';
        }
    }
    printf("\nthis: %s, length: %d, %d", this->p, len, strlen(this->p));
}

void bigUInt::print() {
    const size_t len = strlen(this->get_p());

    for (size_t i = len; i-- > 0;) {
        cout << this->get_p()[i];
    }
    cout << endl;
}

bigUInt bigUInt::operator+(const bigUInt &x) {
    return 1;
}

bigUInt bigUInt::operator-(const bigUInt &x) {
    return 1;
}
/*
bigUInt & bigUInt::operator=(const bigUInt &x) {
    return x;
}

std::ostream & operator<<(std::ostream &out, const bigUInt &x) {
    return true;
}*/