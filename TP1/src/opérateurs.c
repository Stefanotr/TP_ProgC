#include <stdio.h>

int main() {

    int a = 16;
    int b = 3;

    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);     // division entière (5)
    printf("a %% b = %d\n", a % b);     // reste = 1

    printf("a == b : %d\n", a == b);   // 0 = faux
    printf("a > b  : %d\n", a > b);    // 1 = vrai

    return 0;
}
