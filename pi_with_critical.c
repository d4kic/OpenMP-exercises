#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

const int num_steps = 10000;

int main() {
	double step = 1.0 / (double)num_steps;
	double pi = 0.0;
	omp_set_num_threads(NUM_THREADS);
	double start = omp_get_wtime();
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int nthrds = omp_get_num_threads();
		double sum = 0.0;
		for (int i = id; i < num_steps; i += nthrds) {
			double x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}
		#pragma omp critical
			pi += sum * step;
	}
	double end = omp_get_wtime();
	printf("%.5lf, time needed %.5lf\n", pi, end - start);
	return 0;
}
