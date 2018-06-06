#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void _init(int size) {
    max = size;
    queue = malloc(sizeof(int) * max);
}

int isFull() {
    return (size == max);
}

void enqueue(int i) {
    // If queue is initialised and is not full.
    if (max > 0 && isFull() != 1) {
        
    }
}

void _destroy() {
    free(queue);
}