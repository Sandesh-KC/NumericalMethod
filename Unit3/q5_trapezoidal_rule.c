#include <stdio.h>

/*
Algorithm:
1. Read the lower limit, upper limit, and number of segments.
2. Calculate the integral using the single-segment trapezoidal rule:
      I = (b - a) * [f(a) + f(b)] / 2
3. Calculate h = (b - a) / n for the multi-segment rule.
4. Add the two end values and twice every interior function value.
5. Multiply the sum by h / 2.
6. Print the results from both rules.
*/

/* Function to be integrated: f(x) = x^2 */
double function(double x) {
    return x * x;
}

int main() {
    int n, i;
    double a, b, h, x;
    double singleResult, sum, multiResult;

    printf("For the function f(x) = x^2\n");
    printf("Enter the lower limit: ");
    scanf("%lf", &a);

    printf("Enter the upper limit: ");
    scanf("%lf", &b);

    printf("Enter the number of segments: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The number of segments must be greater than zero.\n");
        return 1;
    }

    /* Ordinary trapezoidal rule using one segment. */
    singleResult = (b - a) * (function(a) + function(b)) / 2.0;

    /* Multi-segment (composite) trapezoidal rule. */
    h = (b - a) / n;
    sum = function(a) + function(b);

    for (i = 1; i < n; i++) {
        x = a + i * h;
        sum = sum + 2.0 * function(x);
    }

    multiResult = (h / 2.0) * sum;

    printf("\nResult using single trapezoidal rule = %.6f\n", singleResult);
    printf("Result using %d-segment trapezoidal rule = %.6f\n", n, multiResult);

    return 0;
}
