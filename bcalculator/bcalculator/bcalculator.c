/*

    STUDENT ID: 16058989
    DYLAN TONKS
    HARDWARE ORIENTATED, 159.270
    ASSIGNMENT 1

*/


/*

_    _                _
| |  | |              | |
| |__| | ___  __ _  __| | ___ _ __
|  __  |/ _ \/ _` |/ _` |/ _ \ '__|
| |  | |  __/ (_| | (_| |  __/ |
|_|  |_|\___|\__,_|\__,_|\___|_|

        Function prototypes, includes & declarations

*/

#include "./bcalculator.h"

/*
_    _      _
| |  | |    | |
| |__| | ___| |_ __   ___ _ __ ___
|  __  |/ _ \ | '_ \ / _ \ '__/ __|
| |  | |  __/ | |_) |  __/ |  \__ \
|_|  |_|\___|_| .__/ \___|_|  |___/
                | |
                |_|

        These are the helper functions for operation
        related functions.

*/

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

/*

____                       _   _
/ __ \                     | | (_)
| |  | |_ __   ___ _ __ __ _| |_ _  ___  _ __  ___
| |  | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
| |__| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
\____/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
        | |
        |_|

        All operations that required further elaboration
        have their own functions defined below.
*/

unsigned int bshiftl(unsigned int n1, unsigned int n2) {
    // simply apply n2 left shifts
    while (n2 > 0) {
        n1 <<= 1;

        //move onto the next shift
        n2--;
    }
    return n1;
}

unsigned int bshiftr(unsigned int n1, unsigned int n2) {
    // simply apply n2 right shifts
    while (n2 > 0) {
        n1 >>= 1;
        n2--;
    }
    return n1;
}

unsigned int basr(unsigned int n1, unsigned int n2) {
    /*
        This is almost a carry over from a logical shift.
        Except the most significant bit is set to the previous
        most significant.
    */
 
    while (n2 > 0) {
        int MSB = GetMostSignificantBit(n1);
        n1 >>= 1;

        //Setting the bit to previous MSB
        int bits = sizeof(unsigned int) * 8;
        n1 |= MSB << bits - 1;

        n2--;
    }
    return n1;
}



unsigned int brol(unsigned int n1, unsigned int n2) {

    // for every shift...
    while (n2 > 0) {

        // get the most significant bit
        int MSB = GetMostSignificantBit(n1);

        // shift the bits left
        n1 = n1 << 1;

        //set the first bit to the most significant
        n1 |= MSB;
        n2--;
    }
    return n1;
}

unsigned int bror(unsigned int n1, unsigned int n2) {

    int bits = sizeof(unsigned int) * 8;

    while (n2 > 0) {

        // this time, the least significant goes to the front
        int LSB = GetLeastSignificantBit(n1);
        n1 = n1 >> 1;

        // set the last bit to being the least significant
        n1 |= LSB << (bits - 1);

        n2--;
    }
    return n1;
}



int main() {

    //Intro stuff
    printf("Welcome to the bitwise calculator.\n");
    printf("Available operations include,\n");

    
    //Print all available calculator operations
    for (size_t i = 0; i < length(b_Operations); i++) {
        printf("%s\t", b_Operations[i]);
    }

    printf("\nEnter an expression: ");

    /*
        Request input from the user. Max operation length is 3 chars.
        Arrays are pointers, hence not &op, just op
        Parameter length 3, returned by scanf if user gives all params
    */
    unsigned int n1; char op[4]; unsigned int n2;
    if (scanf("%x %3s %x", &n1, op, &n2) != 3) {
        return printf("You must follow the format NUMBER OPERATOR NUMBER");
    }

    unsigned int result = 0;

    if (strcmp("add", op) == 0) result = n1 + n2;
    else if (strcmp("sub", op) == 0) result = n1 - n2;
    else if (strcmp("and", op) == 0) result = n1 & n2;
    else if (strcmp("or", op) == 0) result = n1 | n2;
    else if (strcmp("xor", op) == 0) result = n1 ^ n2;
    else if (strcmp("shl", op) == 0) result = bshiftl(n1, n2);
    else if (strcmp("shr", op) == 0) result = bshiftr(n1, n2);
    else if (strcmp("asr", op) == 0) result = basr(n1, n2);
    else if (strcmp("rol", op) == 0) result = brol(n1, n2);
    else if (strcmp("ror", op) == 0) result = bror(n1, n2);

    else {
        return printf("You have used an invalid operator, \"%s\", try again.", op);
    }

    
    printf("The answer is: %x", result);

    //The following was used for testing purposes (pausing output)
    /*
    char inputs[4];
    scanf_s("%4s", &inputs, sizeof(inputs));
    */
    return 1;
}