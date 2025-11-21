#include <stdio.h>

struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

int main() {

    struct Couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff},
        {0x2c, 0xc8, 0x64, 0xff},
        {0xaa, 0xbb, 0xcc, 0xff},
        {0x10, 0x20, 0x30, 0xff},
        {0x00, 0x88, 0xff, 0xff},
        {0x77, 0x22, 0x11, 0xff},
        {0x11, 0x33, 0x55, 0xff},
        {0x44, 0x66, 0x88, 0xff},
        {0xab, 0xcd, 0xef, 0xff},
        {0x99, 0x00, 0x44, 0xff}
    };

    for (int i = 0; i < 10; i++) {
        printf("Couleur %d:\n", i+1);
        printf("Rouge : %d\n", couleurs[i].r);
        printf("Vert  : %d\n", couleurs[i].g);
        printf("Bleu  : %d\n", couleurs[i].b);
        printf("Alpha : %d\n\n", couleurs[i].a);
    }

    return 0;
}