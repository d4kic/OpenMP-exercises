#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	const int n = 1000;
	const int numthreads = 10;
	omp_set_num_threads(numthreads);

	int* a = (int*)malloc(n * n * sizeof(int));
	int* b = (int*)malloc(n * n * sizeof(int));
	int* c = (int*)malloc(n * n * sizeof(int));

	for (int i = 0; i < n * n; ++i) {
		a[i] = i + 1;
		b[i] = i + 1;
	}

	double start = omp_get_wtime();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int tmp = 0;
			for (int k = 0; k < n; ++k) {
				tmp += a[i * n + k] * b[k * n + j];
			}
			c[i * n + j] = tmp;
		}
	}
	double end = omp_get_wtime();
	double t1 = end - start;

	int i;
	start = omp_get_wtime();
	#pragma omp parallel for schedule(static)
	for (i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int tmp = 0;
			for (int k = 0; k < n; ++k) {
				tmp += a[i * n + k] * b[k * n + j];
			}
			c[i * n + j] = tmp;
		}
	}
	end = omp_get_wtime();
	double t2 = end - start;

	//for (int i = 0; i < n; ++i) {
	//	for (int j = 0; j < n; ++j) {
	//		printf("%d ", c[i * n + j]);
	//	}
	//	printf("\n");
	//}
	printf("Sekvencijalno: %lf\n", t1);
	printf("Paralelno: %lf\n", t2);
	free(a);
	free(b);
	free(c);
	return 0;
}