#include "operator.h"

int somme(int a, int b) {
    return a + b;
}

int difference(int a, int b) {
    return a - b;
}

int produit(int a, int b) {
    return a * b;
}

int quotient(int a, int b) {
    if (b == 0) {
        return 0;   // à toi de gérer l'erreur côté appelant
    }
    return a / b;
}

int modulo(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a % b;
}

int et_bit(int a, int b) {
    return a & b;
}

int ou_bit(int a, int b) {
    return a | b;
}

int negation(int a) {
    return ~a;
}

int appliquer_operateur(int a, int b, char op) {
    switch (op) {
        case '+': return somme(a, b);
        case '-': return difference(a, b);
        case '*': return produit(a, b);
        case '/': return quotient(a, b);
        case '%': return modulo(a, b);
        case '&': return et_bit(a, b);
        case '|': return ou_bit(a, b);
        case '~': return negation(a);
        default:  return 0;
    }
}