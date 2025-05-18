#include <stdio.h>
#include <time.h>

int main() {
    const int outer = 10000;
    const int inner = 100000;
    unsigned long long counter = 0;

    printf("Running nested loops: %d x %d = %llu iterations\n",
           outer, inner, (unsigned long long)outer * inner);

    clock_t start = clock();

    for (int i = 0; i < outer; ++i) {
        for (int j = 0; j < inner; ++j) {
            counter++;
        }
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Done. Final counter: %llu\n", counter);
    printf("Time taken: %.2f seconds\n", elapsed);

    return 0;
}
