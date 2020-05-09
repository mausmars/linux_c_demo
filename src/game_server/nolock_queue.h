//
// Created by root on 1/16/20.
//

#ifndef DEMO_LINUXC_NOLOCK_QUEUE_H
#define DEMO_LINUXC_NOLOCK_QUEUE_H

#include <jemalloc/jemalloc.h>

typedef struct QNode QueueNode;

struct QNode {
    QueueNode *next;
    void *data;
};

typedef struct {
    QueueNode *head;
    QueueNode *tail;
} Queue;

extern QueueNode *createQueueNode();
extern Queue *createQueue();
extern void addQueue(Queue *queue, void *data);
extern void *pollQueue(Queue *queue);

#endif //DEMO_LINUXC_NOLOCK_QUEUE_H
