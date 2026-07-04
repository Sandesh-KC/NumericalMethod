#include <stdio.h>

int main() {
    int n, i, j;
    float x[20], bd[20][20], xp, yp, p, term, fact, h;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &bd[i][0]);
    }

    // Construct backward difference table
    for(j = 1; j < n; j++) {
        for(i = n - 1; i >= j; i--) {
            bd[i][j] = bd[i][j - 1] - bd[i - 1][j - 1];
        }
    }

    // Print backward difference table
    printf("\nBackward Difference Table:\n");
    for(i = 0; i < n; i++) {
        printf("%.2f\t", x[i]);
        for(j = 0; j <= i; j++) {
            printf("%.2f\t", bd[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the value of x: ");
    scanf("%f", &xp);

    h = x[1] - x[0];
    p = (xp - x[n - 1]) / h;

    yp = bd[n - 1][0];
    term = 1;
    fact = 1;

    for(i = 1; i < n; i++) {
        term *= (p + (i - 1));
        fact *= i;
        yp += (term * bd[n - 1][i]) / fact;
    }

    printf("\nInterpolated value at x = %.2f is %.4f\n", xp, yp);

    return 0;
}