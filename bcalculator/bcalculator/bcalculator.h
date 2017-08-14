#ifndef BIT_OPERATIONS
#define BIT_OPERATIONS

#include <stdlib.h>     //  malloc, calloc etc.
#include <stdio.h>      //  input/output lib
#include <string.h>     //  string operations


const char *b_Operations[] = {
    "add", "sub"
};

#define MAX_OPERATORS sizeof(b_Operations)

//sizeof returns the overall size of a variable/array: STR[0] per array index
#define length(STR) (sizeof(STR)/sizeof(STR[0]))

void bshiftl(unsigned int *n1, unsigned int *n2);
void bshiftr(unsigned int *n1, unsigned int *n2);
void basr(unsigned int *n1, unsigned int *n2);
static int GetMostSignificantBit(unsigned int num);

#else
#warning "You have included bitwise operations more than once in your script."
#endif