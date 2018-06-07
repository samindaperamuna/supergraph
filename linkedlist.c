#include <stddef.h>
#include <stdlib.h>

#include "linkedlist.h"

Vertex *constructList(int numVertices) {
    Vertex *adjLists = (Vertex*)malloc(sizeof(Vertex));
}

void destructList(Vertex **list, int size) {
    for (int i = 0; i < size; i++) {
        Neighbour *nextItem = list[i]->adjList->next;
        
        while (nextItem != NULL) {
            Neighbour *temp = nextItem;
            nextItem = nextItem->next;
            free(temp);
        }
    }
}