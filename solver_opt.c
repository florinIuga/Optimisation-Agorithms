/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <string.h>

double* transpose(double* matrix, const int N) {

    double* res = malloc(N * N * sizeof(*res));
    int i;

    for(i = 0; i < N * N; ++i) {

        int j = i / N;
        int k = i % N;
        res[i] = matrix[N * k + j];
    }

    return res;
}

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {

    double* res;
    double* A_sq;
    double* BA_tr;
    double* A_sqB;

    double* A_tr = malloc(N * N * sizeof(*A_tr));
    memcpy(A_tr, A, N * N * sizeof(*A));

    res = malloc(N * N * sizeof(*res));
    A_sq = malloc(N * N * sizeof(*A_sq));
    BA_tr = malloc(N * N * sizeof(*BA_tr));
    A_sqB = malloc(N * N * sizeof(*A_sqB));

    int i, j, k;
    A_tr = transpose(A, N);

    /* A^2 */
    /* Multiply by A_tr in order to multiply
     * by line for efficient cache
     */
    for (i = 0; i < N; ++i) {
        register double *orig_pa = &A[i * N];

        for (j = 0; j < N; ++j) {
            register double *pa = orig_pa;
            register double *pb = &A_tr[j * N];
            register double sum = 0;

            for (k = 0; k < j + 1; ++k) {
                sum += *pa * *pb;
                pa++;
                pb++;
            }

            A_sq[i * N + j] = sum;
        }
    }

    /* B * A^t */
    for (i = 0; i < N; ++i) {
        register double *orig_pb = &B[i * N];

        for (j = 0; j < N; ++j) {
            register double *pb = orig_pb + j;
            register double *pa = &A[j * N + j];
            register double sum = 0;

            for (k = j; k < N; ++k) {
                sum += *pb * *pa;
                pb++;
                pa++;
            }

            BA_tr[i * N + j] = sum;
            res[i * N + j] = sum;
        }
    }

    /* A^2 * B */
    /* Transpose B in order to multiply
     * by line for efficient cache
     */

    B = transpose(B, N);

    for (i = 0; i < N; ++i) {
        register double *orig_pa = &A_sq[i * N + i];

        for (j = 0; j < N; ++j) {
            register double *pa = orig_pa;
            register double *pb = &B[j * N + i];
            register double sum = 0;

            for (k = i; k < N; ++k) {
                sum += *pa * *pb;
                pa++;
                pb++;
            }

            A_sqB[i * N + j] = sum;
            res[i * N + j] += sum;
        }
    }

    free(A_tr);
    free(A_sq);
    free(A_sqB);

    return res; 
}
