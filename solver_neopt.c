/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {

	double* res;
	double* A_sq;
	double* BA_tr;
	double* A_sqB;
	int i, j, k;

	res = malloc(N * N * sizeof(*res));
	A_sq = malloc(N * N * sizeof(*A_sq));
	BA_tr = malloc(N * N * sizeof(*BA_tr));
	A_sqB = malloc(N * N * sizeof(*A_sqB));

	/* A^2 */
	for (i = 0; i < N; ++i) {
   		for (j = 0; j < N; ++j) {
      		A_sq[i * N + j] = 0.0;
      		for (k = i; k < j + 1; ++k) {
				A_sq[i * N + j] += A[i * N + k] * A[k * N + j];
      		}
   		}
	}

	/* B * A^t */
	for (i = 0; i < N; ++i) {
   		for (j = 0; j < N; ++j) {
      		BA_tr[i * N + j] = 0.0;
      		for (k = j; k < N; ++k) {
				BA_tr[i * N + j] += B[i * N + k] * A[j * N + k];
      		}
			res[i * N + j] = BA_tr[i * N + j];
   		}
	}

	/* A^2 * B */
	for (i = 0; i < N; ++i) {
   		for (j = 0; j < N; ++j) {
      		A_sqB[i * N + j] = 0.0;
      		for (k = i; k < N; ++k) {
				A_sqB[i * N + j] += A_sq[i * N + k] * B[k * N + j];
      		}
			res[i * N + j] += A_sqB[i * N + j];
   		}
	}

	free(A_sq);
	free(BA_tr);
	free(A_sqB);

	return res;
}
