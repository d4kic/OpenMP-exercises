#include <omp.h>
#include <stdio.h>
#include <math.h>

#define NUM_THREADS 4

const int num_steps = 10000;

int main() {
	double step = 1.0 / (double)num_steps;
	double sum = 0.0;
	int i;
	omp_set_num_threads(NUM_THREADS);
	double start = omp_get_wtime();
	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < num_steps; i++) {
		double x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	double end = omp_get_wtime();
	double pi = step * sum;
	printf("%.5lf, time needed %.5lf\n", pi, end - start);
	return 0;
}
