#include <stdio.h>

#define MAX_POINTS 20

/*
Algorithm:
1. Read the tabulated x and y values.
2. Check that the x values are equally spaced.
3. Construct the forward and backward difference tables.
4. Print both difference tables.
5. Read the point where the derivative is required.
6. Calculate the derivative using Newton's forward difference formula.
7. Calculate the derivative using Newton's backward difference formula.
8. Print both calculated derivative values.
*/

int main() {
    int n, i, j;
    double x[MAX_POINTS];
    double forward[MAX_POINTS][MAX_POINTS] = {0};
    double backward[MAX_POINTS][MAX_POINTS] = {0};
    double h, point, p, spacingDifference;
    double term, derivativeTerm;
    double forwardDerivative, backwardDerivative;

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    if (n < 2 || n > MAX_POINTS) {
        printf("Please enter between 2 and %d data points.\n", MAX_POINTS);
        return 1;
    }

    printf("Enter the x and y values:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] y[%d]: ", i, i);
        scanf("%lf %lf", &x[i], &forward[i][0]);
        backward[i][0] = forward[i][0];
    }

    /* Check that all x values have the same spacing h. */
    h = x[1] - x[0];
    if (h == 0) {
        printf("The x values must be different.\n");
        return 1;
    }

    for (i = 2; i < n; i++) {
        spacingDifference = (x[i] - x[i - 1]) - h;
        if (spacingDifference < 0) {
            spacingDifference = -spacingDifference;
        }

        if (spacingDifference > 0.000001) {
            printf("The x values must be equally spaced.\n");
            return 1;
        }
    }

    /* Construct the forward difference table. */
    for (j = 1; j < n; j++) {
        for (i = 0; i < n - j; i++) {
            forward[i][j] = forward[i + 1][j - 1] - forward[i][j - 1];
        }
    }

    /* Construct the backward difference table. */
    for (j = 1; j < n; j++) {
        for (i = j; i < n; i++) {
            backward[i][j] = backward[i][j - 1] - backward[i - 1][j - 1];
        }
    }

    printf("\nForward Difference Table:\n");
    printf("x\t\tf(x)");
    for (j = 1; j < n; j++) {
        printf("\t\tDelta^%d", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%.4f\t\t", x[i]);
        for (j = 0; j < n - i; j++) {
            printf("%.4f\t\t", forward[i][j]);
        }
        printf("\n");
    }

    printf("\nBackward Difference Table:\n");
    printf("x\t\tf(x)");
    for (j = 1; j < n; j++) {
        printf("\t\tNabla^%d", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%.4f\t\t", x[i]);
        for (j = 0; j <= i; j++) {
            printf("%.4f\t\t", backward[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the point where the derivative is required: ");
    scanf("%lf", &point);

    /*
       Newton forward formula uses p = (point - x[0]) / h and the
       differences in the first row of the forward table.
    */
    p = (point - x[0]) / h;
    forwardDerivative = 0.0;
    term = 1.0;
    derivativeTerm = 0.0;

    for (j = 1; j < n; j++) {
        derivativeTerm = (derivativeTerm * (p - (j - 1)) + term) / j;
        term = term * (p - (j - 1)) / j;
        forwardDerivative += derivativeTerm * forward[0][j];
    }
    forwardDerivative = forwardDerivative / h;

    /*
       Newton backward formula uses p = (point - x[n - 1]) / h and the
       differences in the last row of the backward table.
    */
    p = (point - x[n - 1]) / h;
    backwardDerivative = 0.0;
    term = 1.0;
    derivativeTerm = 0.0;

    for (j = 1; j < n; j++) {
        derivativeTerm = (derivativeTerm * (p + (j - 1)) + term) / j;
        term = term * (p + (j - 1)) / j;
        backwardDerivative += derivativeTerm * backward[n - 1][j];
    }
    backwardDerivative = backwardDerivative / h;

    printf("\nDerivative using forward difference  = %.6f\n",
           forwardDerivative);
    printf("Derivative using backward difference = %.6f\n",
           backwardDerivative);

    return 0;
}
