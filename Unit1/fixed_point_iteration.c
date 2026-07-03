#include <stdio.h>
#include <math.h>

float g(float x)
{
    return cbrt(x + 4);
}

float f(float x)
{
    return x*x*x - x - 4;
}

int main()
{
    float x0, x1, e;
    int iter = 1;

    printf("Enter initial guess: ");
    scanf("%f", &x0);

    printf("Enter error tolerance: ");
    scanf("%f", &e);

    printf("\nIter\t x0\t\t x1\t\t f(x1)\t\t Error\n");

    while (1)
    {
        x1 = g(x0);

        float err = fabs(x1 - x0);
        float fx = fabs(f(x1));

        printf("%d\t %.6f\t %.6f\t %.6f\t %.6f\n",
               iter, x0, x1, fx, err);

        iter++;

        // STOP CONDITIONS (important part)
        if (err < e && fx < e)
            break;

        x0 = x1;
    }

    printf("\nApproximate Root = %.6f\n", x1);

    return 0;
}