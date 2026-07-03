#include <stdio.h>

int main() {
    int n, i, j;
    float x[20], y[20], xp, yp = 0, term;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);
    }

    printf("Enter the value of x: ");
    scanf("%f", &xp);

    for(i = 0; i < n; i++) {
        term = y[i];

        for(j = 0; j < n; j++) {
            if(i != j) {
                term = term * (xp - x[j]) / (x[i] - x[j]);
            }
        }

        yp += term;
    }

    printf("Interpolated value at x = %.2f is %.4f\n", xp, yp);

    return 0;
}