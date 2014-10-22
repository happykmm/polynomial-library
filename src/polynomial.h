#ifndef _polynomial_h
#define _polynomial_h

typedef struct Node *PtrToNode;
typedef PtrToNode Polynomial;

struct Node {
    int Coeff;
    int Power;
    PtrToNode Next;
};

#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"


 PtrToNode poly_node(int Coeff, int Power, PtrToNode Next);
 PtrToNode poly_NODE(PtrToNode Node);
Polynomial poly_clone(Polynomial Poly);
      void poly_insert(int Coeff, int Power, Polynomial Poly);
Polynomial poly_create(int *Coeff, int *Power, int length);
Polynomial poly_addition(Polynomial Poly1, Polynomial Poly2);
Polynomial poly_negative(Polynomial Poly);
Polynomial poly_subtract(Polynomial Poly1, Polynomial Poly2);
Polynomial poly_multiply(Polynomial Poly1, Polynomial Poly2);
      void poly_output(Polynomial Poly);


#endif
