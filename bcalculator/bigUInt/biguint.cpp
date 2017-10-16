#include <iostream>
#include <string> // No one specified we cannot use this...
#include "biguint.h"

using namespace std;

//Memory vs Performance? The application depends
#define BIGINT_SIZE 33

bigUInt::bigUInt() {
    this->p = new char[BIGINT_SIZE];
    memset(this->p, '\0', BIGINT_SIZE);
    this->p[0] = '0';
}

bigUInt::bigUInt(unsigned int n) {

    string nstr = to_string(n);
    this->p = new char[BIGINT_SIZE];
    memset(this->p, '\0', BIGINT_SIZE);
    

    //for all values of size_t, size_t >= 0 since unsigned, end at 0 else breaking point
    int counter = 0;
    for (size_t i = nstr.length(); i-- > 0;) {
        this->p[counter] = nstr[i];
        counter++;
    }
}

bigUInt::bigUInt(const char *s) {
    size_t len = strlen(s);
    this->p = new char[BIGINT_SIZE];
    memset(this->p, '\0', BIGINT_SIZE);

    int counter = 0;
    for (size_t i = len; i-- > 0;) {
        this->p[counter] = s[i];
        counter++;
    }
}

bigUInt::bigUInt(const bigUInt &x) {
    size_t len = strlen(x.get_p());
    this->p = new char[len];
    memset(this->p, '\0', len);
    strcpy(this->p, x.get_p());
}

bigUInt::~bigUInt() {
    delete[] (this->p); //free the array from heap
}

void bigUInt::add(unsigned int n) {

}

void bigUInt::add(const bigUInt &x) {

}

void bigUInt::increment() {
    char num = this->get_p()[0]; int index = 0;
    
    while (num == '9') {
        num = this->get_p()[index];
    }

    this->p[index]++;
    for (size_t i = index; i-- > 0;) {
        this->p[i] = '0';
    }
}

void bigUInt::print() {
    const size_t len = BIGINT_SIZE;

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