#include <stdio.h>

/*
Algorithm:
1. Start.
2. Read the point x and height h from the user.
3. If h is zero, display an error and stop.
4. Calculate forward derivative = [f(x + h) - f(x)] / h.
5. Calculate backward derivative = [f(x) - f(x - h)] / h.
6. Display both derivative values.
7. Stop.
*/

/* The continuous function whose derivative is required: f(x) = x^2 */
float function(float x) {
    return x * x;
}

int main() {
    float x, h;
    float forwardDerivative, backwardDerivative;

    printf("For the function f(x) = x^2\n");
    printf("Enter the point x: ");
    scanf("%f", &x);

    printf("Enter the height h: ");
    scanf("%f", &h);

    if (h == 0) {
        printf("Height h cannot be zero.\n");
        return 1;
    }

    /* Two-point forward difference formula */
    forwardDerivative = (function(x + h) - function(x)) / h;

    /* Two-point backward difference formula */
    backwardDerivative = (function(x) - function(x - h)) / h;

    printf("\nForward difference derivative at x = %.2f is %.4f\n",
           x, forwardDerivative);
    printf("Backward difference derivative at x = %.2f is %.4f\n",
           x, backwardDerivative);

    return 0;
}
