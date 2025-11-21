#include <stdio.h>

int main() {

    signed char c1 = -12;
    unsigned char c2 = 200;

    signed short s1 = -1234;
    unsigned short s2 = 50000;

    signed int i1 = -123456;
    unsigned int i2 = 4000000000U;

    signed long int l1 = -123456789L;
    unsigned long int l2 = 123456789UL;

    signed long long int ll1 = -9876543210LL;
    unsigned long long int ll2 = 9876543210ULL;

    float f = 3.14f;
    double d = 2.718281828;
    long double ld = 1.234567890123456789L;

    printf("signed char            = %d\n", c1);
    printf("unsigned char          = %u\n", c2);

    printf("signed short           = %d\n", s1);
    printf("unsigned short         = %u\n", s2);

    printf("signed int             = %d\n", i1);
    printf("unsigned int           = %u\n", i2);

    printf("signed long int        = %ld\n", l1);
    printf("unsigned long int      = %lu\n", l2);

    printf("signed long long int   = %lld\n", ll1);
    printf("unsigned long long int = %llu\n", ll2);

    printf("float                  = %f\n", f);
    printf("double                 = %lf\n", d);
    printf("long double            = %Lf\n", ld);

    return 0;
}