#include <stdio.h>

#define MAX_POINTS 100

/*
Algorithm:
1. Read the number of tabulated data points.
2. Read all x and y values.
3. Assume the first y value is both the maximum and minimum.
4. Compare each remaining y value with the current maximum and minimum.
5. When a larger or smaller value is found, store it and its x value.
6. Print the maximum and minimum values with their corresponding x values.
*/

int main() {
    int n, i;
    double x[MAX_POINTS], y[MAX_POINTS];
    double maximum, minimum;
    double xAtMaximum, xAtMinimum;

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_POINTS) {
        printf("Please enter between 1 and %d data points.\n", MAX_POINTS);
        return 1;
    }

    printf("Enter the x and y values:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] y[%d]: ", i, i);
        scanf("%lf %lf", &x[i], &y[i]);
    }

    /* Initially, the first value is considered both maximum and minimum. */
    maximum = y[0];
    minimum = y[0];
    xAtMaximum = x[0];
    xAtMinimum = x[0];

    /* Compare the remaining tabulated values. */
    for (i = 1; i < n; i++) {
        if (y[i] > maximum) {
            maximum = y[i];
            xAtMaximum = x[i];
        }

        if (y[i] < minimum) {
            minimum = y[i];
            xAtMinimum = x[i];
        }
    }

    printf("\nMaximum value = %.6lf at x = %.6lf\n", maximum, xAtMaximum);
    printf("Minimum value = %.6lf at x = %.6lf\n", minimum, xAtMinimum);

    return 0;
}
