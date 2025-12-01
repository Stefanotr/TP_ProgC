#ifndef OPERATOR_H
#define OPERATOR_H

int somme(int a, int b);
int difference(int a, int b);
int produit(int a, int b);
int quotient(int a, int b);
int modulo(int a, int b);
int et_bit(int a, int b);
int ou_bit(int a, int b);
int negation(int a);              // ~a

int appliquer_operateur(int a, int b, char op);

#endif