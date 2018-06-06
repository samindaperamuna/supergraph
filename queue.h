#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

    extern int* queue;
    extern int len = 0;
    extern int head = 0;

    int max = 0;
    
    void _init(int size);

    int isFull();

    void enqueue(int i);

    int dequeue();

    void _destroy();

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */

