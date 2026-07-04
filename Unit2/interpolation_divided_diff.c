#include <stdio.h>

int main() {
    int n, i, j;
    float x[20], dd[20][20], xp, yp, term;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &dd[i][0]);
    }

    // Construct divided difference table
    for(j = 1; j < n; j++) {
        for(i = 0; i < n - j; i++) {
            dd[i][j] = (dd[i + 1][j - 1] - dd[i][j - 1]) /
                       (x[i + j] - x[i]);
        }
    }

    // Print divided difference table
    printf("\nDivided Difference Table:\n");

    for(i = 0; i < n; i++) {
        printf("%.2f\t", x[i]);

        for(j = 0; j < n - i; j++) {
            printf("%.4f\t", dd[i][j]);
        }

        printf("\n");
    }

    printf("\nEnter the value of x: ");
    scanf("%f", &xp);

    yp = dd[0][0];
    term = 1;

    for(i = 1; i < n; i++) {
        term *= (xp - x[i - 1]);
        yp += term * dd[0][i];
    }

    printf("\nInterpolated value at x = %.2f is %.4f\n", xp, yp);

    return 0;
}