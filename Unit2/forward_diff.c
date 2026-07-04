#include <stdio.h>

int main() {
    int n, i, j;
    float x[20], fd[20][20], xp, yp, p, term, h, fact;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &fd[i][0]);
    }

    // Construct forward difference table
    for(j = 1; j < n; j++) {
        for(i = 0; i < n - j; i++) {
            fd[i][j] = fd[i + 1][j - 1] - fd[i][j - 1];
        }
    }

    // Print forward difference table
    printf("\nForward Difference Table:\n");
    for(i = 0; i < n; i++) {
        printf("%.2f\t", x[i]);
        for(j = 0; j < n - i; j++) {
            printf("%.2f\t", fd[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the value of x: ");
    scanf("%f", &xp);

    h = x[1] - x[0];
    p = (xp - x[0]) / h;

    yp = fd[0][0];
    term = 1;
    fact = 1;

    for(i = 1; i < n; i++) {
        term *= (p - (i - 1));
        fact *= i;
        yp += (term * fd[0][i]) / fact;
    }

    printf("\nInterpolated value at x = %.2f is %.4f\n", xp, yp);

    return 0;
}