
#include "./bcalculator.h"


void bshiftl(unsigned int *n1, unsigned int *n2) {
    while (*n2 > 0) {
        *n1 = *n1 << 1;
        *n2 = *n2 - 1;
    }
}

void bshiftr(unsigned int *n1, unsigned int *n2) {
    while (*n2 > 0) {
        *n1 = *n1 >> 1;
        *n2 = *n2 - 1;
    }
}

void basr(unsigned int *n1, unsigned int *n2) {
    /*
        This is almost a carry over from a logical shift.
        Except the most significant bit is set to the previous
        most significant.
    */
 
    while (*n2 > 0) {
        int MSB = GetMostSignificantBit(*n1);
        *n1 = *n1 >> 1;

        //Setting the bit to previous MSB
        int bits = sizeof(unsigned int) * 8;
        *n1 |= MSB << bits - 1;

        *n2 = *n2 - 1;
    }
}

//Helper function
static int GetMostSignificantBit(unsigned int num) {
    /*
        sizeof returns a value in bytes,
        multiplying this by 8 returns # of bits.
    */
    int bits = sizeof(unsigned int) * 8;

    /*
        Because 1 is 000...0001 in binary, I want to
        shift this by the # of bits - 1
    */
    unsigned int mask = (unsigned int)1 << (bits - 1);

    /*
        I then want to compare the var with the mask:
        100...000 (in binary) i.e most significant
    */
    if (num & mask) {
        return 1;
    }
    return 0;
}

//Helper function
static int GetLeastSignificantBit(unsigned int num) {
    unsigned int mask = 1;
    if (num & mask) {
        return 1;
    }

    return 0;

}

void brol(unsigned int *n1, unsigned int *n2) {

    while (*n2 > 0) {
        int MSB = GetMostSignificantBit(*n1);
        *n1 = *n1 << 1;
        *n1 |= MSB;
        *n2 = *n2 - 1;
    }
    
}

void bror(unsigned int *n1, unsigned int *n2) {

    int bits = sizeof(unsigned int) * 8;

    while (*n2 > 0) {
        int LSB = GetLeastSignificantBit(*n1);
        printf("least significant bit: %d", LSB);
        *n1 = *n1 >> 1;
        *n1 |= LSB << (bits - 1);
        *n2 = *n2 - 1;
    }
}



int main() {

    printf("Welcome to the bitwise calculator.\n");
    printf("Available operations include,\n");

    printf("byte: %x", (1 << ((sizeof(unsigned int) - 1) * 8)));

    printf("byte: %x", ((unsigned int)1 << 31));
    printf(" sizeof: %d", sizeof(unsigned int) * 8);
    printf("-1: %x", (-1));
    printf("UINT_MAX:%u", UINT_MAX);


    
    for (size_t i = 0; i < length(b_Operations); i++) {
        printf("%s\t", b_Operations[i]);
    }

    printf("\n");

    puts("Enter an expression: ");

    unsigned int n1; char op[4]; unsigned int n2;
    if (scanf("%x %3s %x", &n1, op, &n2) != 3) {
        return printf("You must follow the format NUMBER OPERATOR NUMBER");
    }

    printf("sizeof first int: %d", sizeof(n1));
    if (strcmp("add", op) == 0) n1 += n2;
    else if (strcmp("sub", op) == 0) n1 -= n2;
    else if (strcmp("and", op) == 0) n1 = n1 & n2;
    else if (strcmp("or", op) == 0) n1 = n1 | n2;
    else if (strcmp("xor", op) == 0) n1 = n1 ^ n2;
    else if (strcmp("shl", op) == 0) bshiftl(&n1, &n2);
    else if (strcmp("shr", op) == 0) bshiftr(&n1, &n2);
    else if (strcmp("asr", op) == 0) basr(&n1, &n2);
    else if (strcmp("rol", op) == 0) brol(&n1, &n2);
    else if (strcmp("ror", op) == 0) bror(&n1, &n2);

    else {
        return printf("You have used an invalid operator, \"%s\", try again.", op);
    }

    
    printf("\nresult; %x %s %x", n1, op, n2);
    char inputs[4];
    scanf_s("%4s", &inputs, sizeof(inputs));
    return 1;
}