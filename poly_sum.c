#include <stdio.h>
#define MAX 100
typedef struct {
    int coeff;
    int expo;
} Term;
int inputPolynomial(Term poly[]) {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    printf("Enter each term as: coefficient exponent\n");
    for(int i = 0; i < n; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &poly[i].coeff, &poly[i].expo);
    }
    return n;
}
void displayPolynomial(Term poly[], int n) {
    for(int i = 0; i < n; i++) {
        if(poly[i].coeff != 0) {
            if(i != 0 && poly[i].coeff > 0)
                printf(" + ");
            else if(poly[i].coeff < 0)
                printf(" - ");
            else if(i == 0 && poly[i].coeff < 0)
                printf("-");
            printf("%d", poly[i].coeff < 0 ? -poly[i].coeff : poly[i].coeff);
            if(poly[i].expo != 0)
                printf("x^%d", poly[i].expo);
        }
    }
    printf("\n");
}
int addPolynomials(Term p1[], int n1, Term p2[], int n2, Term result[]) {
    int i = 0, j = 0, k = 0;
    while(i < n1 && j < n2) {
        if(p1[i].expo == p2[j].expo) {
            result[k].coeff = p1[i].coeff + p2[j].coeff;
            result[k].expo = p1[i].expo;
            i++; j++; k++;
        } else if(p1[i].expo > p2[j].expo) {
            result[k++] = p1[i++];
        } else {
            result[k++] = p2[j++];
        }
    }
    while(i < n1)
        result[k++] = p1[i++];
    while(j < n2)
        result[k++] = p2[j++];
    return k;
}
int main() {
    Term poly1[MAX], poly2[MAX], result[MAX];
    int n1, n2, nResult;
    printf("Enter first polynomial:\n");
    n1 = inputPolynomial(poly1);
    printf("\nEnter second polynomial:\n");
    n2 = inputPolynomial(poly2);
    nResult = addPolynomials(poly1, n1, poly2, n2, result);
    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1, n1);
    printf("Second Polynomial: ");
    displayPolynomial(poly2, n2);
    printf("Sum of Polynomials: ");
    displayPolynomial(result, nResult);
    return 0;
}
