#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main(int argc, char *argv[])
{
    Polynomial Poly1, Poly2, Poly3;
    int coeff1[] = {2,1,3,7,1,8};
    int power1[] = {5,3,2,4,17,0};
    int coeff2[] = {3,5,1,4,2};
    int power2[] = {0,5,3,9,1};
    Poly1 = poly_create(coeff1, power1, sizeof(coeff1)/sizeof(int));
    Poly2 = poly_create(coeff2, power2, sizeof(coeff2)/sizeof(int));
    poly_output(Poly1);
    poly_output(Poly2);
    Poly3 = poly_addition(Poly1, Poly2);
    poly_output(Poly3);
    Poly3 = poly_negative(Poly2);
    poly_output(Poly3);
    Poly3 = poly_subtract(Poly1, Poly2);
    poly_output(Poly3);
    Poly3 = poly_multiply(Poly1, Poly2);
    poly_output(Poly3);
    system("pause");
    return 0;
}
