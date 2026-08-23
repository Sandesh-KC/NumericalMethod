#include <stdio.h>

#define MAX_POINTS 20

/*
Algorithm:
1. Read the number of data points and their x and y values.
2. Store the y values in the first column of the divided difference table.
3. Construct the remaining columns using:
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1])
                    / (x[i + j] - x[i])
4. Print the divided difference table.
5. Read the point at which the derivative is required.
6. Use the Newton coefficients from the first row of the table to
   evaluate the derivative of the interpolation polynomial.
7. Print the calculated derivative.
*/

int main() {
    int n, i, j;
    double x[MAX_POINTS], table[MAX_POINTS][MAX_POINTS];
    double point, polynomial, derivative;

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    if (n < 2 || n > MAX_POINTS) {
        printf("Please enter between 2 and %d data points.\n", MAX_POINTS);
        return 1;
    }

    printf("Enter the x and y values:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] y[%d]: ", i, i);
        scanf("%lf %lf", &x[i], &table[i][0]);
    }

    /* Construct the divided difference table. */
    for (j = 1; j < n; j++) {
        for (i = 0; i < n - j; i++) {
            if (x[i + j] == x[i]) {
                printf("The x values must be different.\n");
                return 1;
            }

            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1])
                          / (x[i + j] - x[i]);
        }
    }

    printf("\nDivided Difference Table:\n");
    printf("x\t\tf(x)");
    for (j = 1; j < n; j++) {
        printf("\t\tOrder %d", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%.4lf\t\t", x[i]);
        for (j = 0; j < n - i; j++) {
            printf("%.4lf\t\t", table[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the point where the derivative is required: ");
    scanf("%lf", &point);

    /*
       Newton's polynomial and its derivative are evaluated together
       using a nested form.  The first row contains the coefficients.
    */
    polynomial = table[0][n - 1];
    derivative = 0.0;

    for (i = n - 2; i >= 0; i--) {
        derivative = derivative * (point - x[i]) + polynomial;
        polynomial = polynomial * (point - x[i]) + table[0][i];
    }

    printf("Derivative at x = %.4lf is %.6lf\n", point, derivative);

    return 0;
}
