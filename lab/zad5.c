#include <stdio.h>
#include <omp.h>

#define m 200
#define n 200

int main() {
	int i, j;
	int a1[m][n], a2[m][n], a3[m][n];
	omp_set_num_threads(4);
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			a1[i][j] = i + j + 1;
			a2[i][j] = i + j + 1;
			a3[i][j] = i + j + 1;
		}
	}

	double start = omp_get_wtime();
	for (i = 1; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			a1[i][j] = 2 * a1[i - 1][j];
		}
	}
	double end = omp_get_wtime();
	double t1 = end - start;

	start = omp_get_wtime();
	for (i = 1; i < m; ++i) {
		#pragma omp parallel for 
		for (j = 0; j < n; ++j) {
			a2[i][j] = 2 * a2[i - 1][j];
		}
	}
	end = omp_get_wtime();
	double t2 = end - start;

	start = omp_get_wtime();
	#pragma omp parallel for 
	for (j = 0; j < n; ++j) {
		for (i = 1; i < m; ++i) {
			a3[i][j] = 2 * a3[i - 1][j];
		}
	}
	end = omp_get_wtime();
	double t3 = end - start;

	printf("Sekvencijalno: %lf\n", t1);
	printf("Paralelno: %lf\n", t2);
	printf("Paralelno sa i unutra: %lf\n", t3);
	return 0;
}