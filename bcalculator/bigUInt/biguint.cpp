/*
    Dylan Tonks
    Student ID 16058989
    159.270 Assignment 5

*/


#include <iostream>
#include <string> // No one specified we cannot use this...
#include "biguint.h"

using namespace std;

/*
        CONSTRUCTORS
*/
bigUInt::bigUInt() : bigUInt((unsigned int)0) {}

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

//WARNING: size != actual size, to be fixed ->> fixed
bigUInt::bigUInt(const char *s) {
    size_t len = strlen(s);
    int zeros = 0;

    //skip leading zeros
    for (int i = 0; i < len; i++) {
        if (s[i] != '0') break;
        zeros++;
    }

    this->p = new char[(len - zeros) + 1]();

    int counter = 0;
    bool nonzero = false;

    //range: between len & zeros
    for (size_t i = len; i-- > zeros;) {

        this->p[counter] = s[i];
        counter++;
    }
}

//Deep copy
bigUInt::bigUInt(const bigUInt &x) {
    size_t len = strlen(x.get_p());

    //since p is a pointer, free memory
    delete[] this->p;
    //reallocate with new size
    this->p = new char[len + 1]();

    //copy the values
    for (int i = 0; i < len; i++) {
        this->p[i] = x.get_p()[i];
    }
}

/*
        DESTRUCTOR
*/
bigUInt::~bigUInt() {
    if (this->p) {
        delete[](this->p); //free the array from heap
    }
}


/*
        OPERATORS
*/
void bigUInt::add(unsigned int n) {
    bigUInt *tmp = new bigUInt(n);
    this->add(*tmp);
    delete tmp;
}

void bigUInt::add(const bigUInt &x) {
    int lenthis = strlen(this->p);
    int lenx = strlen(x.get_p());

    int maxlen = (lenthis > lenx) ? lenthis : lenx;

    string str;
    bool carry = false;

    for (int i = 0; i < maxlen; i++) {
        
        //get the # in the ith index, if ith index doesn't exist, zero
        int num1 = (i >= lenthis) ? 0 : this->p[i] - '0';
        int num2 = (i >= lenx) ? 0 : x.get_p()[i] - '0';

        //do they sum over 9?
        int sum = num1 + num2 + ((carry) ? 1 : 0);

        //if they do we must carry over
        if (sum > 9) {
            sum -= 10;
            carry = true;
        }
        //else simply add
        else {
            carry = false;
        }

        str.push_back(sum + '0'); //keep least significant at index 0
    }
    if (carry) {
        str.insert(str.begin(), '1'); //insert 1 @ most significant
    }

    delete[](this->p);
    this->p = new char[str.length() + 1]();
    for (int i = 0; i < str.length(); i++) {
        this->p[i] = str[i];
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
    if (index > len) {

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
}

void bigUInt::print() {
    const size_t len = strlen(this->get_p());
    for (size_t i = len; i-- > 0;) {
        cout << this->get_p()[i];
    }
    cout << endl;
}

bigUInt bigUInt::operator+(const bigUInt &x) {
    bigUInt result(*this);
    result.add(x);
    return result;
}

bigUInt bigUInt::operator-(const bigUInt &x) {
    bigUInt result(*this);

    int m = strlen(result.p);
    int n = strlen(x.get_p());

    try {
        if (m - n < 0) {
            throw(1);
        }

        int carry = 0;
        for (int i = 0; i < m; i++) {

            //since subtracting no need to subtract '0' as well i.e if p[i] = 2 and x[i] = 1 then 2 - 1 = 50 - 49 = 1
            int sub = (result.p[i] - x.get_p()[i]) - carry;

            if (sub < 0) {
                carry = 1;
                sub = result.p[i];
            }
            else {
                carry = 0;
            }
            
            result.p[i] -= sub;
        }
        if (carry) {
            throw(1);
        }

    }
    catch (int error) {
        switch (error) {
        case 1: printf("Invalid subtraction"); break;

        }
    }

    return result;
}

//assignment
bigUInt & bigUInt::operator=(const bigUInt &x) {
    if (this != &x) {

        //first clear any memory used in the heap
        delete[](this->p);

        //reallocate with correct array size
        this->p = new char[strlen(x.get_p()) + 1]();
        //copy
        for (int i = 0; i < strlen(x.get_p()); i++) {
            this->p[i] = x.get_p()[i];
        }
    }
    return *this;
}

//cout
std::ostream & operator<<(std::ostream &out, const bigUInt &x) {
    
    for (int i = 0; i < strlen(x.get_p()); i++) {
        out << x.get_p()[i];
    }
    return out;
}