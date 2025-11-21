#include <stdio.h>

int main() {

    char c = 0x12;
    short s = 0x1234;
    int i = 0x12345678;
    long l = 0x1122334455;
    long long ll = 0x1122334455667788;
    float f = 3.5f;
    double d = 8.25;
    long double ld = 1.2345;

    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long *pl = &l;
    long long *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("Avant manipulation :\n");
    printf("i : adresse=%p valeur=%x\n", (void*)pi, i);
    printf("f : adresse=%p valeur=%x\n\n", (void*)pf, *(unsigned int*)pf);

    // manip via pointeurs
    *pi -= 1;
    *pf *= 2;

    printf("Après manipulation :\n");
    printf("i : adresse=%p valeur=%x\n", (void*)pi, i);
    printf("f : adresse=%p valeur=%x\n", (void*)pf, *(unsigned int*)pf);

    return 0;
}