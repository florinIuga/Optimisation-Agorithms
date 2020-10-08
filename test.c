#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
	double* A;
	double* C;
	double* B;

	int N = 3, i, j, k;

	A = malloc(N * N * sizeof(*A));
	C = malloc(N * N * sizeof(*C));
	B = malloc(N * N * sizeof(*B));

	A[0] = 1;
	A[1] = 1;
	A[2] = 1;
	A[3] = 0;
	A[4] = 1;
	A[5] = 2;
	A[6] = 0;
	A[7] = 0;
	A[8] = 2;

	B[0] = 2;
	B[1] = 2;
	B[2] = 2;
	B[3] = 2;
	B[4] = 2;
	B[5] = 2;
	B[6] = 2;
	B[7] = 2;
	B[8] = 2;

	// A^2
	for (i = 0; i < N; ++i) {
        double *orig_pa = &A[i * N];
        for (j = 0; j < N; ++j) {
            double *pa = orig_pa;
            double *pb = &A[j];
            register double sum = 0;

            for (k = 0; k < j + 1; ++k) {
                sum += *pa * *pb;
                pa++;
                pb += N;
            }

            C[i * N + j] = sum;
        }
    }

	// A^2 * B
	// for (i = 0; i < N; ++i) {
 //        double *orig_pa = &A[i * N + i];
 //        for (j = 0; j < N; ++j) {
 //            double *pa = orig_pa;
 //            double *pb = &B[j];
 //            register double sum = 0;

 //            for (k = i; k < N; ++k) {
 //                sum += *pa * *pb;
 //                printf("*pa = %lf and *pb  =%lf\n", *pa, *pb);
 //                pa++;
 //                pb += N;
 //            }

 //            C[i * N + j] = sum;
 //        }
 //    }

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%lf ", C[i * N + j]);
		}
		printf("\n");
	}
	free(A);
	free(C);
	return 0;
}