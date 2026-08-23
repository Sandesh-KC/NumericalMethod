#include <stdio.h>

/*
Algorithm:
1. Read the lower limit, upper limit, and number of segments.
2. Check that the number of segments is positive and divisible by 3.
3. Apply the ordinary Simpson's 3/8 rule using three segments.
4. For the composite rule, calculate h = (b - a) / n.
5. Give interior values whose positions are divisible by 3 a weight of 2.
6. Give all other interior values a weight of 3.
7. Multiply the weighted sum by 3h / 8.
8. Print the results from both rules.
*/

/* Function to be integrated: f(x) = x^2 */
double function(double x) {
    return x * x;
}

int main() {
    int n, i;
    double a, b, h, x;
    double x1, x2, singleResult;
    double sum, multiResult;

    printf("For the function f(x) = x^2\n");
    printf("Enter the lower limit: ");
    scanf("%lf", &a);

    printf("Enter the upper limit: ");
    scanf("%lf", &b);

    printf("Enter the number of segments (a multiple of 3): ");
    scanf("%d", &n);

    if (n <= 0 || n % 3 != 0) {
        printf("Simpson's 3/8 rule requires a positive multiple of 3 segments.\n");
        return 1;
    }

    /* Ordinary Simpson's 3/8 rule uses three segments. */
    h = (b - a) / 3.0;
    x1 = a + h;
    x2 = a + 2.0 * h;
    singleResult = (3.0 * h / 8.0) *
                   (function(a) + 3.0 * function(x1) +
                    3.0 * function(x2) + function(b));

    /* Composite Simpson's 3/8 rule. */
    h = (b - a) / n;
    sum = function(a) + function(b);

    for (i = 1; i < n; i++) {
        x = a + i * h;

        if (i % 3 == 0) {
            sum = sum + 2.0 * function(x);
        } else {
            sum = sum + 3.0 * function(x);
        }
    }

    multiResult = (3.0 * h / 8.0) * sum;

    printf("\nResult using Simpson's 3/8 rule = %.6f\n", singleResult);
    printf("Result using composite Simpson's 3/8 rule with %d segments = %.6f\n",
           n, multiResult);

    return 0;
}
