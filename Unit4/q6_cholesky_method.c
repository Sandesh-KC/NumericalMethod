#include <stdio.h>
#include <math.h>

#define MAX_ORDER 10
#define EPSILON 0.0000000001

/*
Algorithm:
1. Read the order n, coefficient matrix A, and constant values B.
2. Check that A is symmetric.
3. Decompose A into A = LL^T, where L is lower triangular:
   a. Calculate diagonal elements using a square root.
   b. Calculate the elements below the diagonal using division.
4. Solve LY = B using forward substitution.
5. Solve L^T X = Y using back substitution.
6. Print the values of all variables in X.
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

    /* Cholesky decomposition requires a symmetric matrix. */
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (absoluteValue(a[i][j] - a[j][i]) > EPSILON) {
                printf("Cholesky method requires a symmetric matrix.\n");
                return 1;
            }
        }
    }

    /* Construct the lower-triangular matrix L. */
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            sum = a[i][j];

            for (k = 0; k < j; k++) {
                sum = sum - lower[i][k] * lower[j][k];
            }

            if (i == j) {
                if (sum <= EPSILON) {
                    printf("The matrix is not positive definite.\n");
                    return 1;
                }
                lower[i][j] = sqrt(sum);
            } else {
                lower[i][j] = sum / lower[j][j];
            }
        }
    }

    /* Forward substitution: solve LY = B. */
    for (i = 0; i < n; i++) {
        sum = b[i];
        for (j = 0; j < i; j++) {
            sum = sum - lower[i][j] * y[j];
        }
        y[i] = sum / lower[i][i];
    }

    /* Back substitution: solve L-transpose X = Y. */
    for (i = n - 1; i >= 0; i--) {
        sum = y[i];
        for (j = i + 1; j < n; j++) {
            sum = sum - lower[j][i] * x[j];
        }
        x[i] = sum / lower[i][i];
    }

    printf("\nValues of the variables:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }

    return 0;
}
