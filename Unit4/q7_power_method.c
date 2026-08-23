#include <stdio.h>

#define MAX_ORDER 10
#define MAX_ITERATIONS 100
#define TOLERANCE 0.000001
#define EPSILON 0.0000000001

/*
Algorithm:
1. Read the order n, matrix A, and an initial eigenvector X.
2. Normalize the initial vector using its largest absolute component.
3. Multiply the matrix by the vector to obtain Y = AX.
4. Select the component of Y with the largest absolute value and use it
   to normalize Y, producing the next approximation of X.
5. Find the largest change between the old and new vectors.
6. Repeat steps 3 to 5 until the change is below the tolerance or the
   maximum number of iterations is reached.
7. Calculate the final eigenvalue using the Rayleigh quotient.
8. Print the dominant eigenvalue and its corresponding eigenvector.
*/

double absoluteValue(double value) {
    if (value < 0.0) {
        return -value;
    }
    return value;
}

int main() {
    int n, i, j, iteration, pivotIndex;
    double a[MAX_ORDER][MAX_ORDER];
    double vector[MAX_ORDER], newVector[MAX_ORDER], product[MAX_ORDER];
    double largest, scale, error, difference;
    double numerator, denominator, eigenvalue;

    printf("Enter the order of the matrix: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_ORDER) {
        printf("Please enter an order between 1 and %d.\n", MAX_ORDER);
        return 1;
    }

    printf("Enter the elements of matrix A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter the initial eigenvector:\n");
    for (i = 0; i < n; i++) {
        printf("X[%d]: ", i + 1);
        scanf("%lf", &vector[i]);
    }

    /* Find and use the largest component to normalize the initial vector. */
    pivotIndex = 0;
    largest = absoluteValue(vector[0]);
    for (i = 1; i < n; i++) {
        if (absoluteValue(vector[i]) > largest) {
            largest = absoluteValue(vector[i]);
            pivotIndex = i;
        }
    }

    if (largest < EPSILON) {
        printf("The initial eigenvector cannot be a zero vector.\n");
        return 1;
    }

    scale = vector[pivotIndex];
    for (i = 0; i < n; i++) {
        vector[i] = vector[i] / scale;
    }

    /* Power-method iterations. */
    for (iteration = 1; iteration <= MAX_ITERATIONS; iteration++) {
        /* Matrix-vector multiplication: product = A * vector. */
        for (i = 0; i < n; i++) {
            product[i] = 0.0;
            for (j = 0; j < n; j++) {
                product[i] = product[i] + a[i][j] * vector[j];
            }
        }

        /* Find the largest component of the product for normalization. */
        pivotIndex = 0;
        largest = absoluteValue(product[0]);
        for (i = 1; i < n; i++) {
            if (absoluteValue(product[i]) > largest) {
                largest = absoluteValue(product[i]);
                pivotIndex = i;
            }
        }

        if (largest < EPSILON) {
            printf("The method cannot continue because AX is a zero vector.\n");
            return 1;
        }

        scale = product[pivotIndex];
        for (i = 0; i < n; i++) {
            newVector[i] = product[i] / scale;
        }

        /* Find the largest change between consecutive vectors. */
        error = 0.0;
        for (i = 0; i < n; i++) {
            difference = absoluteValue(newVector[i] - vector[i]);
            if (difference > error) {
                error = difference;
            }
            vector[i] = newVector[i];
        }

        if (error < TOLERANCE) {
            break;
        }
    }

    /* Calculate A * vector again for the Rayleigh quotient. */
    for (i = 0; i < n; i++) {
        product[i] = 0.0;
        for (j = 0; j < n; j++) {
            product[i] = product[i] + a[i][j] * vector[j];
        }
    }

    numerator = 0.0;
    denominator = 0.0;
    for (i = 0; i < n; i++) {
        numerator = numerator + vector[i] * product[i];
        denominator = denominator + vector[i] * vector[i];
    }
    eigenvalue = numerator / denominator;

    if (iteration > MAX_ITERATIONS) {
        printf("\nMaximum iterations reached; showing the latest approximation.\n");
    } else {
        printf("\nConverged after %d iterations.\n", iteration);
    }

    printf("Dominant eigenvalue = %.6f\n", eigenvalue);
    printf("Corresponding eigenvector:\n");
    for (i = 0; i < n; i++) {
        printf("%.6f\n", vector[i]);
    }

    return 0;
}
