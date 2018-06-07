#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct list_t {
        int vertexNum;
        struct list_t *next;
    } Neighbour;

    typedef struct vertex {
        int data;
        struct list_t *adjList;
    } Vertex;

    Vertex* constructList(int numVertices);

    void destructList(Vertex **list, int size);

#ifdef __cplusplus
}
#endif

#endif /* LINKEDLIST_H */

