#include <stdio.h>
#include <omp.h>

int main() {
    const int outer = 10000;
    const int inner = 100000;
    unsigned long long counter = 0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:counter) schedule(static)
    for (int i = 0; i < outer; ++i) {
        for (int j = 0; j < inner; ++j) {
            counter++;
        }
    }

    double end = omp_get_wtime();
    printf("Done. Final counter: %llu\n", counter);
    printf("Time taken: %.2f seconds using %d threads\n", end - start, omp_get_max_threads());

    return 0;
}
