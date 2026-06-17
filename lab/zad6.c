#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define numthreads 4

int main() {
	omp_set_num_threads(numthreads);
	const int n = 1000;
	int* a = (int*)malloc(n * sizeof(int));
	int i;

	for (i = 0; i < n; ++i) {
		a[i] = i + 1;
	}

	double start = omp_get_wtime();
	int sum = 0;
	for (i = 0; i < n; ++i) {
		sum += a[i];
	}
	double avg = (double)(sum / n);
	double end = omp_get_wtime();
	double t1 = end - start;

	start = omp_get_wtime();
	sum = 0;
	int tmp[numthreads];
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int loc = 0;
		#pragma omp for
		for (i = 0; i < n; ++i) {
			loc += a[i];
		}
		tmp[tid] = loc;
	}
	for (i = 0; i < numthreads; ++i) {
		sum += tmp[i];
	}
	avg = (double)(sum / n);
	end = omp_get_wtime();
	double t2 = end - start;

	start = omp_get_wtime();
	sum = 0;
	#pragma omp parallel for reduction(+:sum) schedule(static)
	for (i = 0; i < n; ++i) {
		sum += a[i];
	}
	avg = (double)(sum / n);
	end = omp_get_wtime();
	double t3 = end - start;

	printf("Sekvencijalno: %lf\n", t1);
	printf("Paralelno: %lf\n", t2);
	printf("Paralelno sa redukcijom: %lf\n", t3);
	free(a);
	return 0;
}