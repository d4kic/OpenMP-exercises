#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define numthreads 10

int main() {
	omp_set_num_threads(numthreads);
	const int n = 100000;
	int* a = (int*)malloc(n * sizeof(int));
	int i;

	for (i = 0; i < n; ++i) {
		a[i] = i + 1;
	}

	double start = omp_get_wtime();
	int max = a[0];
	for (i = 1; i < n; ++i) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	double end = omp_get_wtime();
	double t1 = end - start;

	start = omp_get_wtime();
	max = a[0];
	#pragma omp parallel
	{
		int loc_max = a[0];
		#pragma omp for schedule(static)
		for (i = 0; i < n; ++i) {
			if (a[i] > loc_max) {
				loc_max = a[i];
			}
		}
		#pragma omp critical
		{
			if (loc_max > max)
				max = loc_max;
		}
	}
	end = omp_get_wtime();
	double t2 = end - start;

	printf("Sekvencijalno: %lf\n", t1);
	printf("Paralelno: %lf\n", t2);
	return 0;
}