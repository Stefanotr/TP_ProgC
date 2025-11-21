#include <stdio.h>

void afficher_octets(void *p, int taille) {
    unsigned char *octet = p;

    for (int i = 0; i < taille; i++) {
        printf("%02x ", octet[i]);
    }
    printf("\n");
}

int main() {

    short s = 0x0203;
    int i = 0x01020304;
    long l = 0x0102030405060708;
    float f = 3.14f;
    double d = 3.14;
    long double ld = 3.14L;

    printf("Octets de short :\n");
    afficher_octets(&s, sizeof(s));

    printf("\nOctets de int :\n");
    afficher_octets(&i, sizeof(i));

    printf("\nOctets de long int :\n");
    afficher_octets(&l, sizeof(l));

    printf("\nOctets de float :\n");
    afficher_octets(&f, sizeof(f));

    printf("\nOctets de double :\n");
    afficher_octets(&d, sizeof(d));

    printf("\nOctets de long double :\n");
    afficher_octets(&ld, sizeof(ld));

    return 0;
}