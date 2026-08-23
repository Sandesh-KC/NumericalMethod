#include <stdio.h>

#define MAX_ORDER 10
#define EPSILON 0.0000000001

/*
Algorithm:
1. Read the order n, coefficient matrix A, and constant values B.
2. Decompose A into lower and upper triangular matrices so that A = LU.
   In Doolittle's method, every diagonal element of L is 1.
3. Solve LY = B using forward substitution.
4. Solve UX = Y using back substitution.
5. Print the values of all variables in X.
*/

double absoluteValue(double value) {
    if (value < 0.0) {
        return -value;
    }
    return value;
}

int main() {
    int n, i, j, k;
    double a[MAX_ORDER][MAX_ORDER];
    double lower[MAX_ORDER][MAX_ORDER] = {0};
    double upper[MAX_ORDER][MAX_ORDER] = {0};
    double b[MAX_ORDER], y[MAX_ORDER], x[MAX_ORDER];
    double sum;

    printf("Enter the order of the matrix: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_ORDER) {
        printf("Please enter an order between 1 and %d.\n", MAX_ORDER);
        return 1;
    }

    printf("Enter the coefficients of matrix A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter the constant values B:\n");
    for (i = 0; i < n; i++) {
        printf("B[%d]: ", i + 1);
        scanf("%lf", &b[i]);
    }

    /* Doolittle decomposition: calculate one row of U at a time. */
    for (i = 0; i < n; i++) {
        for (k = i; k < n; k++) {
            sum = 0.0;
            for (j = 0; j < i; j++) {
                sum = sum + lower[i][j] * upper[j][k];
            }
            upper[i][k] = a[i][k] - sum;
        }

        if (absoluteValue(upper[i][i]) < EPSILON) {
            printf("Doolittle decomposition failed because a pivot is zero.\n");
            return 1;
        }

        lower[i][i] = 1.0;

        for (k = i + 1; k < n; k++) {
            sum = 0.0;
            for (j = 0; j < i; j++) {
                sum = sum + lower[k][j] * upper[j][i];
            }
            lower[k][i] = (a[k][i] - sum) / upper[i][i];
        }
    }

    /* Forward substitution: solve LY = B. */
    for (i = 0; i < n; i++) {
        sum = b[i];
        for (j = 0; j < i; j++) {
            sum = sum - lower[i][j] * y[j];
        }
        y[i] = sum;
    }

    /* Back substitution: solve UX = Y. */
    for (i = n - 1; i >= 0; i--) {
        sum = y[i];
        for (j = i + 1; j < n; j++) {
            sum = sum - upper[i][j] * x[j];
        }
        x[i] = sum / upper[i][i];
    }

    printf("\nValues of the variables:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }

    return 0;
}
