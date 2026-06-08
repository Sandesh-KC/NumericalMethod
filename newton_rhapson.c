#include <stdio.h>
#include <math.h>

float f(float x)
{
    return x*x*x - x - 4;
}

float df(float x)
{
    return 3*x*x - 1;
}

int main()
{
    float x0, x1, e;

    printf("Enter initial guess: ");
    scanf("%f", &x0);

    printf("Enter error precision: ");
    scanf("%f", &e);

    printf("\nIter\t x0\t\t x1\t\t f(x1)\n");

    int iter = 1;

    do
    {
        x1 = x0 - f(x0)/df(x0);

        printf("%d\t %.6f\t %.6f\t %.6f\n",
               iter, x0, x1, f(x1));

        x0 = x1;

        iter++;

    } while (fabs(f(x1)) > e);

    printf("\nApproximate Root = %.6f\n", x1);

    return 0;
}