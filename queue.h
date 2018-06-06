#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Node_t {
        void* data;
        struct Node_t* prev;
    } Node;

    /* The head of the queue, holds the data nodes within the queue. */
    typedef struct Queue {
        Node* head;
        Node* tail;
        int size;
        int limit;
    } Queue;
    
    Queue* constructQueue(int limit);
    void DestructQueue(Queue *queue);
    int Enqueue(Queue* pQueue, Node* item);
    Node* Dequeue(Queue* pQueue);
    int isEmpty(Queue* pQueue);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */

