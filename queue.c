#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

Queue *constructQueue(int limit) {
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    if (queue == NULL) {
        return NULL;
    }
    if (limit <= 0) {
        limit = 65535;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void destructQueue(Queue *queue) {
    Node *pN;
    while (!isEmpty(queue)) {
        pN = dequeue(queue);
        free(pN);
    }
    free(queue);
}

int enqueue(Queue *pQueue, Node *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || item == NULL) {
        return FALSE;
    }
    /* if queue is full */
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }

    /* The queue is empty */
    item->prev == NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;
    } else {
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }

    /* Increment size. */
    pQueue->size++;

    return TRUE;
}

Node* dequeue(Queue *pQueue) {
    /* The queue is empty or bad parameter. */
    Node *item;
    if (isEmpty(pQueue))
        return NULL;

    item = pQueue->head;
    pQueue->head = pQueue->head->prev;

    /* Decrement the size. */
    pQueue->size--;

    return item;
}

int isEmpty(Queue *pQueue) {
    if (pQueue == NULL)
        return FALSE;
    if (pQueue->size == 0)
        return TRUE;

    return FALSE;
}