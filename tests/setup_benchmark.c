#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../supergraph.h"

int main() {
    clock_t begin = clock();

    query_helper* helper = engine_setup(5);

    clock_t end = clock();
    double time_elapsed = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %f\n", time_elapsed);

    engine_cleanup(helper);
    
    return 0;
}