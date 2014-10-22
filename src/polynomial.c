#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"


PtrToNode poly_node(int Coeff, int Power, PtrToNode Next) 
{
    PtrToNode Node;
    Node = (PtrToNode)malloc(sizeof(struct Node));
    Node->Coeff = Coeff;
    Node->Power = Power;
    Node->Next = Next;
    return Node;
}

PtrToNode poly_NODE(PtrToNode Node) 
{
    return poly_node(Node->Coeff, Node->Power, Node->Next);
}

Polynomial poly_clone(Polynomial Poly) 
{
    Polynomial NewPoly;
    PtrToNode Pi, Pj;
    NewPoly = poly_node(0, 0, NULL);
    Pi = NewPoly;
    Pj = Poly->Next;
    while (Pj != NULL) {
       Pi->Next = poly_NODE(Pj);
       Pi = Pi->Next;
       Pj = Pj->Next;
    }
    return NewPoly;
}

void poly_insert(int Coeff, int Power, Polynomial Poly)
{
    PtrToNode Pi, Pj;
    Pi = Poly;
    Pj = Poly->Next;
    while (Pj != NULL) {
        if  (Power >= Pj->Power)
            break; 
        Pi = Pj;
        Pj = Pj->Next;
    }
    if (Pj == NULL) {
        Pi->Next = poly_node(Coeff, Power, NULL);
    } else if (Power == Pi->Power) {
        Pi->Coeff += Coeff; 
    } else { // Power > Pi->Power
        Pi->Next = poly_node(Coeff, Power, Pi->Next);
    }
}

Polynomial poly_create(int *Coeff, int *Power, int length) 
{
    Polynomial Poly;
    Poly = poly_node(0, 0, NULL);
    int i;
    for (i=0; i<length; i++) {
        if (Coeff == 0) 
           continue;
        poly_insert(Coeff[i], Power[i], Poly);
    }
    return Poly;
}

Polynomial poly_addition(Polynomial Poly1, Polynomial Poly2) 
{
    Polynomial NewPoly;
    PtrToNode P1, P2, PN;
    NewPoly = poly_node(0, 0, NULL);
    P1 = Poly1->Next;
    P2 = Poly2->Next;
    PN = NewPoly;
    while (1) {
        if (P1 == NULL)
            if (P2 == NULL) 
                break;
            else { // P2 != NULL
                PN->Next = poly_NODE(P2);
                PN = PN->Next;
                P2 = P2->Next;
            }
        else // P1 != NULL
            if (P2 == NULL) {
                PN->Next = poly_NODE(P1);
                PN = PN->Next;
                P1 = P1->Next;
            } else { // P2 != NULL
                if (P1->Power > P2->Power) {
                    PN->Next = poly_NODE(P1);
                    PN = PN->Next;
                    P1 = P1->Next;
                } else if (P1->Power < P2->Power) {
                    PN->Next = poly_NODE(P2);
                    PN = PN->Next;
                    P2 = P2->Next;
                } else  { // P1->Power == P2->Power
                    if (P1->Coeff + P2->Coeff) {
                        PN->Next = poly_node(P1->Coeff+P2->Coeff, P1->Power, NULL);
                        PN = PN->Next;
                    }
                    P1 = P1->Next;
                    P2 = P2->Next;
                }
            }
    }
    return NewPoly;
}

Polynomial poly_negative(Polynomial Poly)
{
    Polynomial NewPoly = poly_clone(Poly);
    PtrToNode Ptr = NewPoly->Next;
    while (Ptr != NULL) {
        Ptr->Coeff *= -1;
        Ptr = Ptr->Next;
    }
    return NewPoly;
}

Polynomial poly_subtract(Polynomial Poly1, Polynomial Poly2)
{
    return poly_addition(Poly1, poly_negative(Poly2));
}

Polynomial poly_multiply(Polynomial Poly1, Polynomial Poly2)
{
    Polynomial NewPoly;
    PtrToNode P1, P2;
    NewPoly = poly_node(0, 0, NULL);
    P1 = Poly1->Next;
    while (P1 != NULL) {
        P2 = Poly2->Next;
        while (P2 != NULL) {
            poly_insert(P1->Coeff * P2->Coeff, 
                        P1->Power + P2->Power, NewPoly);
            P2 = P2->Next;
        }
        P1 = P1->Next;
    }
    return NewPoly;
}

void poly_output(Polynomial Poly) 
{
    PtrToNode Ptr;
    int coeff, power, flag = 0;
    Ptr = Poly->Next;
    while (Ptr != NULL) {
        coeff = Ptr->Coeff;
        power = Ptr->Power;
        if (flag==0) {
            flag = 1;
            if (coeff<0) printf("- ");
        } else
            (coeff>0 ? printf(" + ") : printf(" - "));
        coeff>0 ? 0 : (coeff*=-1);
        if (coeff == 1)
            power==0 ? printf("1") : 0;
        else
            printf("%d", coeff); 
        if (power > 1)
            printf("x^%d", power);
        else
            power == 1 ? printf("x") : 0;
        Ptr = Ptr->Next;
    }
    printf("\n");
}
