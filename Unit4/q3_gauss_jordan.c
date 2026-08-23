#include <stdio.h>

#define MAX_ORDER 10
#define EPSILON 0.0000000001

/*
Algorithm:
1. Read the order n, coefficient matrix A, and constant values B.
2. Form the augmented matrix [A | B].
3. For each diagonal position:
   a. If the pivot is zero, exchange it with a lower row having a
      nonzero entry in that column.
   b. Divide the complete pivot row by the pivot to make the pivot 1.
   c. Subtract suitable multiples of the pivot row from every other row
      to make all other entries in the pivot column zero.
4. The coefficient part is now an identity matrix, so the final column
   contains the values of the variables.
5. Print all variable values.
*/

double absoluteValue(double value) {
    if (value < 0.0) {
        return -value;
    }
    return value;
}

int main() {
    int n, i, j, k, swapRow;
    double a[MAX_ORDER][MAX_ORDER + 1];
    double pivot, ratio, temp;

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

    for (i = 0; i < n; i++) {
        /* If the pivot is zero, search for a suitable lower row. */
        if (absoluteValue(a[i][i]) < EPSILON) {
            swapRow = -1;
            for (k = i + 1; k < n; k++) {
                if (absoluteValue(a[k][i]) >= EPSILON) {
                    swapRow = k;
                    break;
                }
            }

            if (swapRow == -1) {
                printf("The system does not have a unique solution.\n");
                return 1;
            }

            for (j = 0; j <= n; j++) {
                temp = a[i][j];
                a[i][j] = a[swapRow][j];
                a[swapRow][j] = temp;
            }
        }

        /* Divide the pivot row so that its diagonal element becomes 1. */
        pivot = a[i][i];
        for (j = 0; j <= n; j++) {
            a[i][j] = a[i][j] / pivot;
        }

        /* Make every other entry in the current pivot column zero. */
        for (k = 0; k < n; k++) {
            if (k != i) {
                ratio = a[k][i];
                for (j = 0; j <= n; j++) {
                    a[k][j] = a[k][j] - ratio * a[i][j];
                }
            }
        }
    }

    printf("\nValues of the variables:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, a[i][n]);
    }

    return 0;
}
