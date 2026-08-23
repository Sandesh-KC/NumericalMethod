#include <stdio.h>

#define MAX_ORDER 10

/*
Algorithm:
1. Read the order n of the system.
2. Read the coefficient matrix A and constant values B.
3. Use forward elimination to change the augmented matrix into an
   upper-triangular matrix:
      ratio = a[k][i] / a[i][i]
      row k = row k - ratio * row i
4. Use back substitution, starting from the last equation, to calculate
   each unknown variable.
5. Print the values of all variables.
*/

int main() {
    int n, i, j, k;
    double a[MAX_ORDER][MAX_ORDER + 1];
    double x[MAX_ORDER], ratio, sum;

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
        scanf("%lf", &a[i][n]);
    }

    /* Forward elimination: convert the matrix to upper-triangular form. */
    for (i = 0; i < n - 1; i++) {
        if (a[i][i] == 0.0) {
            printf("Gauss elimination cannot continue because a pivot is zero.\n");
            return 1;
        }

        for (k = i + 1; k < n; k++) {
            ratio = a[k][i] / a[i][i];

            for (j = i; j <= n; j++) {
                a[k][j] = a[k][j] - ratio * a[i][j];
            }
        }
    }

    /* Back substitution: calculate variables from last to first. */
    for (i = n - 1; i >= 0; i--) {
        if (a[i][i] == 0.0) {
            printf("The system does not have a unique solution.\n");
            return 1;
        }

        sum = a[i][n];
        for (j = i + 1; j < n; j++) {
            sum = sum - a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
    }

    printf("\nValues of the variables:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }

    return 0;
}
