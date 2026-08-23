#include <stdio.h>

#define MAX_LEVELS 10

/*
Algorithm:
1. Read the lower limit, upper limit, and number of Romberg levels.
2. Calculate the first column of the Romberg table using the composite
   trapezoidal rule with 1, 2, 4, 8, ... segments.
3. Improve each result using Richardson extrapolation:
      R[i][j] = R[i][j-1] +
                (R[i][j-1] - R[i-1][j-1]) / (4^j - 1)
4. Print the triangular Romberg table.
5. Print the last diagonal entry as the final integral value.
*/

/* Function to be integrated: f(x) = x^2 */
double function(double x) {
    return x * x;
}

int main() {
    int levels, i, j, k, segments;
    double a, b, h, x, sum, factor;
    double romberg[MAX_LEVELS][MAX_LEVELS] = {0};

    printf("For the function f(x) = x^2\n");
    printf("Enter the lower limit: ");
    scanf("%lf", &a);

    printf("Enter the upper limit: ");
    scanf("%lf", &b);

    printf("Enter the number of Romberg levels (1 to %d): ", MAX_LEVELS);
    scanf("%d", &levels);

    if (levels < 1 || levels > MAX_LEVELS) {
        printf("Please enter a level between 1 and %d.\n", MAX_LEVELS);
        return 1;
    }

    segments = 1;

    for (i = 0; i < levels; i++) {
        /* First column: composite trapezoidal rule. */
        h = (b - a) / segments;
        sum = function(a) + function(b);

        for (k = 1; k < segments; k++) {
            x = a + k * h;
            sum = sum + 2.0 * function(x);
        }

        romberg[i][0] = (h / 2.0) * sum;

        /* Remaining columns: Richardson extrapolation. */
        factor = 4.0;
        for (j = 1; j <= i; j++) {
            romberg[i][j] = romberg[i][j - 1] +
                            (romberg[i][j - 1] - romberg[i - 1][j - 1]) /
                            (factor - 1.0);
            factor = factor * 4.0;
        }

        segments = segments * 2;
    }

    printf("\nRomberg Integration Table:\n");
    for (i = 0; i < levels; i++) {
        for (j = 0; j <= i; j++) {
            printf("%.8f\t", romberg[i][j]);
        }
        printf("\n");
    }

    printf("\nCalculated integral = %.8f\n",
           romberg[levels - 1][levels - 1]);

    return 0;
}
