#include <stdio.h>
#include <stdlib.h>

#include "supergraph.h"

int main(int argc, char** argv) {
    query_helper* helper = engine_setup(5);

    result* result = find_all_reposts(helper->posts, helper->n_posts, 6607, helper);

    return (EXIT_SUCCESS);
}