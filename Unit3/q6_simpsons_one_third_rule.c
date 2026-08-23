#include <stdio.h>

/*
Algorithm:
1. Read the lower limit, upper limit, and number of segments.
2. Check that the number of segments is positive and even.
3. Apply the ordinary Simpson's 1/3 rule using the two end points
   and their middle point.
4. For the composite rule, calculate h = (b - a) / n.
5. Give interior values at odd positions a weight of 4 and values
   at even positions a weight of 2.
6. Multiply the weighted sum by h / 3.
7. Print the results from both rules.
*/

/* Function to be integrated: f(x) = x^2 */
double function(double x) {
    return x * x;
}

int main() {
    int n, i;
    double a, b, h, x, middle;
    double singleResult, sum, multiResult;

    printf("For the function f(x) = x^2\n");
    printf("Enter the lower limit: ");
    scanf("%lf", &a);

    printf("Enter the upper limit: ");
    scanf("%lf", &b);

    printf("Enter an even number of segments: ");
    scanf("%d", &n);

    if (n <= 0 || n % 2 != 0) {
        printf("Simpson's 1/3 rule requires a positive even number of segments.\n");
        return 1;
    }

    /* Ordinary Simpson's 1/3 rule uses two segments. */
    middle = (a + b) / 2.0;
    singleResult = (b - a) *
                   (function(a) + 4.0 * function(middle) + function(b)) / 6.0;

    /* Composite Simpson's 1/3 rule. */
    h = (b - a) / n;
    sum = function(a) + function(b);

    for (i = 1; i < n; i++) {
        x = a + i * h;

        if (i % 2 == 0) {
            sum = sum + 2.0 * function(x);
        } else {
            sum = sum + 4.0 * function(x);
        }
    }

    multiResult = (h / 3.0) * sum;

    printf("\nResult using Simpson's 1/3 rule = %.6f\n", singleResult);
    printf("Result using composite Simpson's 1/3 rule with %d segments = %.6f\n",
           n, multiResult);

    return 0;
}
