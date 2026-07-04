#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    float x[20], y[20], Y;
    float sumx = 0, sumY = 0, sumxY = 0, sumx2 = 0;
    float A, a, b;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);

        Y = log(y[i]);      // Natural logarithm

        sumx += x[i];
        sumY += Y;
        sumxY += x[i] * Y;
        sumx2 += x[i] * x[i];
    }

    b = (n * sumxY - sumx * sumY) /
        (n * sumx2 - sumx * sumx);

    A = (sumY - b * sumx) / n;

    a = exp(A);

    printf("\na = %.4f\n", a);
    printf("b = %.4f\n", b);

    printf("\nRegression Equation:\n");
    printf("y = %.4fe^(%.4fx)\n", a, b);

    return 0;
}