/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <string.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {

	int i, j;

	double* A_copy = malloc(N * N * sizeof(*A_copy));
	memcpy(A_copy, A, N * N * sizeof(*A));

	double* B_copy = malloc(N * N * sizeof(*B_copy));
	memcpy(B_copy, B, N * N * sizeof(*B));

	double* res;
	res = malloc(N * N * sizeof(*res));

	/* B * A^t */
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, B, N);
	/* Now B contains B * A^t */

	/* Compute A^2 */
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A_copy, N, A, N);

	/* Now A = A^2 */

	/* Compute A^2 * B_copy */
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, B_copy, N);
	/* Now B_copy = A^2 * B_copy and B = B * A^t */

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			res[i * N + j] = B_copy[i * N + j] + B[i * N + j];
		}
	}

	free(A_copy);
	free(B_copy);

	return res;
}
