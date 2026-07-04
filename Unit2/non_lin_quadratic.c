#include <stdio.h>

int main() {
    int n, i, j, k;
    float x[20], y[20];
    float sx = 0, sx2 = 0, sx3 = 0, sx4 = 0;
    float sy = 0, sxy = 0, sx2y = 0;
    float a[3][4], factor;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);

        sx += x[i];
        sx2 += x[i] * x[i];
        sx3 += x[i] * x[i] * x[i];
        sx4 += x[i] * x[i] * x[i] * x[i];

        sy += y[i];
        sxy += x[i] * y[i];
        sx2y += x[i] * x[i] * y[i];
    }

    // Augmented matrix
    a[0][0] = n;   a[0][1] = sx;  a[0][2] = sx2; a[0][3] = sy;
    a[1][0] = sx;  a[1][1] = sx2; a[1][2] = sx3; a[1][3] = sxy;
    a[2][0] = sx2; a[2][1] = sx3; a[2][2] = sx4; a[2][3] = sx2y;

    // Gaussian Elimination
    for(i = 0; i < 2; i++) {
        for(j = i + 1; j < 3; j++) {
            factor = a[j][i] / a[i][i];
            for(k = i; k < 4; k++)
                a[j][k] -= factor * a[i][k];
        }
    }

    float a3 = a[2][3] / a[2][2];
    float a2 = (a[1][3] - a[1][2] * a3) / a[1][1];
    float a1 = (a[0][3] - a[0][2] * a3 - a[0][1] * a2) / a[0][0];

    printf("\na1 = %.4f", a1);
    printf("\na2 = %.4f", a2);
    printf("\na3 = %.4f", a3);

    printf("\n\nRegression Equation:\n");
    printf("y = %.4f + %.4fx + %.4fx^2\n", a1, a2, a3);

    return 0;
}