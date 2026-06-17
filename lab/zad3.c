#include <stdio.h>
#include <omp.h>
#include <math.h>

#define numthreads 4

int prost(int br) {
	if (br < 2) return 0;
	if (br == 2) return 1;
	if (br % 2 == 0) return 0;
	for (int i = 3; i < sqrt(br); ++i) {
		if (br % i == 0)
			return 0;
	}
	return 1;
}

int main() {
	const int n = 10000;
	omp_set_num_threads(numthreads);

	int i, cnt = 0;
	double start = omp_get_wtime();
	for (i = 2; i <= n; ++i) {
		if (prost(i))
			cnt++;
	}
	double end = omp_get_wtime();
	double t1 = end - start;

	cnt = 0;
	int tmp[numthreads];
	start = omp_get_wtime();
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int c = 0;
		#pragma omp parallel for
		for (i = 2; i <= n; ++i) {
			if (prost(i))
				c++;
		}
		tmp[tid] = c;
	}
	for (i = 0; i < numthreads; ++i) {
		cnt += tmp[i];
	}
	end = omp_get_wtime();
	double t2 = end - start;

	cnt = 0;
	start = omp_get_wtime();
	#pragma omp parallel for reduction(+:cnt) schedule(static)
	for (i = 2; i <= n; ++i) {
		if (prost(i))
			cnt++;
	}
	end = omp_get_wtime();
	double t3 = end - start;

	printf("Sekvencijalno: %lf\n", t1);
	printf("Paralelno: %lf\n", t2);
	printf("Paralelno sa redukcijom: %lf\n", t3);
	return 0;
}