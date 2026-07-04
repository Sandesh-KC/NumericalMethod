#include <stdio.h>

int main() {
    int n, i;
    float x[20], y[20];
    float sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0;
    float a, b;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);

        sumx += x[i];
        sumy += y[i];
        sumxy += x[i] * y[i];
        sumx2 += x[i] * x[i];
    }

    b = (n * sumxy - sumx * sumy) /
        (n * sumx2 - sumx * sumx);

    a = (sumy - b * sumx) / n;

    printf("\nIntercept (a) = %.4f\n", a);
    printf("Slope (b) = %.4f\n", b);

    printf("\nRegression Equation:\n");
    printf("y = %.4f + %.4fx\n", a, b);

    return 0;
}