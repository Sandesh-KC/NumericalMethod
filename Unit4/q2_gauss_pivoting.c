#include <stdio.h>

#define MAX_ORDER 10
#define EPSILON 0.0000000001

/*
Algorithm:
1. Read the order, coefficient matrix A, and constant values B.
2. Make two copies of the augmented matrix.
3. Partial pivoting:
   a. In each pivot column, find the largest absolute element below or
      at the diagonal and exchange its row with the pivot row.
   b. Perform forward elimination and then back substitution.
4. Complete pivoting:
   a. Find the largest absolute element in the remaining coefficient
      submatrix.
   b. Exchange both its row and column with the pivot row and column.
   c. Record column exchanges, perform elimination, and back substitute.
   d. Restore the calculated variables to their original order.
5. Print the solutions from both methods.
*/

double absoluteValue(double value) {
    if (value < 0.0) {
        return -value;
    }
    return value;
}

void swapRows(double a[][MAX_ORDER + 1], int row1, int row2, int n) {
    int j;
    double temp;

    for (j = 0; j <= n; j++) {
        temp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = temp;
    }
}

int backSubstitution(double a[][MAX_ORDER + 1], double x[], int n) {
    int i, j;
    double sum;

    for (i = n - 1; i >= 0; i--) {
        if (absoluteValue(a[i][i]) < EPSILON) {
            return 0;
        }

        sum = a[i][n];
        for (j = i + 1; j < n; j++) {
            sum = sum - a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
    }

    return 1;
}

int solvePartialPivoting(double a[][MAX_ORDER + 1], double x[], int n) {
    int i, j, k, pivotRow;
    double largest, ratio;

    for (i = 0; i < n - 1; i++) {
        pivotRow = i;
        largest = absoluteValue(a[i][i]);

        /* Find the largest element in the current pivot column. */
        for (k = i + 1; k < n; k++) {
            if (absoluteValue(a[k][i]) > largest) {
                largest = absoluteValue(a[k][i]);
                pivotRow = k;
            }
        }

        if (largest < EPSILON) {
            return 0;
        }

        if (pivotRow != i) {
            swapRows(a, i, pivotRow, n);
        }

        /* Eliminate all entries below the pivot. */
        for (k = i + 1; k < n; k++) {
            ratio = a[k][i] / a[i][i];
            for (j = i; j <= n; j++) {
                a[k][j] = a[k][j] - ratio * a[i][j];
            }
        }
    }

    return backSubstitution(a, x, n);
}

int solveCompletePivoting(double a[][MAX_ORDER + 1], double x[], int n) {
    int i, j, k, pivotRow, pivotColumn;
    int order[MAX_ORDER], tempOrder;
    double largest, ratio, temp;
    double arrangedSolution[MAX_ORDER];

    for (i = 0; i < n; i++) {
        order[i] = i;
    }

    for (i = 0; i < n - 1; i++) {
        pivotRow = i;
        pivotColumn = i;
        largest = absoluteValue(a[i][i]);

        /* Find the largest element in the remaining coefficient matrix. */
        for (k = i; k < n; k++) {
            for (j = i; j < n; j++) {
                if (absoluteValue(a[k][j]) > largest) {
                    largest = absoluteValue(a[k][j]);
                    pivotRow = k;
                    pivotColumn = j;
                }
            }
        }

        if (largest < EPSILON) {
            return 0;
        }

        if (pivotRow != i) {
            swapRows(a, i, pivotRow, n);
        }

        /* Exchange coefficient columns and record the variable order. */
        if (pivotColumn != i) {
            for (k = 0; k < n; k++) {
                temp = a[k][i];
                a[k][i] = a[k][pivotColumn];
                a[k][pivotColumn] = temp;
            }

            tempOrder = order[i];
            order[i] = order[pivotColumn];
            order[pivotColumn] = tempOrder;
        }

        /* Eliminate all entries below the pivot. */
        for (k = i + 1; k < n; k++) {
            ratio = a[k][i] / a[i][i];
            for (j = i; j <= n; j++) {
                a[k][j] = a[k][j] - ratio * a[i][j];
            }
        }
    }

    if (!backSubstitution(a, arrangedSolution, n)) {
        return 0;
    }

    /* Place the variables back in their original order. */
    for (i = 0; i < n; i++) {
        x[order[i]] = arrangedSolution[i];
    }

    return 1;
}

int main() {
    int n, i, j;
    double input[MAX_ORDER][MAX_ORDER + 1];
    double partialMatrix[MAX_ORDER][MAX_ORDER + 1];
    double completeMatrix[MAX_ORDER][MAX_ORDER + 1];
    double partialSolution[MAX_ORDER], completeSolution[MAX_ORDER];

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
            scanf("%lf", &input[i][j]);
        }
    }

    printf("Enter the constant values B:\n");
    for (i = 0; i < n; i++) {
        printf("B[%d]: ", i + 1);
        scanf("%lf", &input[i][n]);
    }

    /* Copy the input so both methods solve the same original system. */
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            partialMatrix[i][j] = input[i][j];
            completeMatrix[i][j] = input[i][j];
        }
    }

    if (solvePartialPivoting(partialMatrix, partialSolution, n)) {
        printf("\nSolution using partial pivoting:\n");
        for (i = 0; i < n; i++) {
            printf("x%d = %.6f\n", i + 1, partialSolution[i]);
        }
    } else {
        printf("\nPartial pivoting: The system has no unique solution.\n");
    }

    if (solveCompletePivoting(completeMatrix, completeSolution, n)) {
        printf("\nSolution using complete pivoting:\n");
        for (i = 0; i < n; i++) {
            printf("x%d = %.6f\n", i + 1, completeSolution[i]);
        }
    } else {
        printf("\nComplete pivoting: The system has no unique solution.\n");
    }

    return 0;
}
