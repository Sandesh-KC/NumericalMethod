#include <stdio.h>
#include <math.h>

float f(float x)
{
    return x*x*x - x - 4;
}

int main()
{
    float a, b, c, e;

    printf("Enter lower guess (a): ");
    scanf("%f", &a);

    printf("Enter upper guess (b): ");
    scanf("%f", &b);

    printf("Enter error precision: ");
    scanf("%f", &e);

    while (f(a) * f(b) > 0)
    {
        printf("\nRoot is not bracketed.\n");
        printf("Enter another pair of guesses:\n");

        printf("a = ");
        scanf("%f", &a);

        printf("b = ");
        scanf("%f", &b);
    }

    printf("\nIter\t a\t\t b\t\t c\t\t f(c)\n");

    int iter = 1;

    do
    {
        // False Position Formula
        c = a - (f(a) * (b - a)) / (f(b) - f(a));

        printf("%d\t %.6f\t %.6f\t %.6f\t %.6f\n",
               iter, a, b, c, f(c));

        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;

        iter++;

    } while (fabs(f(c)) > e);

    printf("\nApproximate Root = %.6f\n", c);

    return 0;
}