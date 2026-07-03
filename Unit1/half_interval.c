#include <stdio.h>
#include <math.h>

// Define the function f(x) = x^3 - x - 2
double f(double x) {
    return x*x*x - x - 2;
}

int main() {
    double a, b, mid, fa, fb, fmid, error, tol;
    int iter = 1;

    printf("===== Half-Interval (Bisection) Method =====\n");
    printf("Function: f(x) = x^3 - x - 2\n\n");

    printf("Enter error precision (e.g. 0.0001): ");
    scanf("%lf", &tol);
    printf("\n");

    // Keep asking until valid bracketing guesses are given
    while (1) {
        printf("Enter initial guess a: ");
        scanf("%lf", &a);
        printf("Enter initial guess b: ");
        scanf("%lf", &b);

        fa = f(a);
        fb = f(b);

        if (fa * fb < 0) {
            printf("\nf(%.4f) = %.4f and f(%.4f) = %.4f\n", a, fa, b, fb);
            printf("Root is bracketed between %.4f and %.4f. Proceeding...\n\n", a, b);
            break;  // Valid bracket found
        } else {
            printf("f(%.4f) = %.4f and f(%.4f) = %.4f\n", a, fa, b, fb);
            printf("Root is NOT bracketed. f(a)*f(b) must be < 0.\n");
            printf("Please enter new guesses.\n\n");
        }
    }

    // Table header
    printf("%-6s %-10s %-10s %-12s %-12s %-12s %-12s %-12s\n",
           "Iter", "a", "b", "mid=(a+b)/2", "f(a)", "f(b)", "f(mid)", "Error");
    printf("------------------------------------------------------------------------------------------\n");

    // Bisection loop
    do {
        mid  = (a + b) / 2.0;
        fa   = f(a);
        fb   = f(b);
        fmid = f(mid);

        // Error = |b - a| / 2
        error = fabs(b - a) / fabs(b);

        printf("%-6d %-10.5f %-10.5f %-12.5f %-12.5f %-12.5f %-12.5f %-12.6f\n",
               iter, a, b, mid, fa, fb, fmid, error);

        // Narrow the bracket
        if (fa * fmid < 0)
            b = mid;   // Root is in left half
        else
            a = mid;   // Root is in right half

        iter++;

    } while (error > tol || fabs(fmid) > tol);  // Stop only when BOTH are within precision

    printf("------------------------------------------------------------------------------------------\n");
    printf("\nApproximate Root = %.5f\n", mid);
    printf("f(root) = %.6f\n", f(mid));

    return 0;
}