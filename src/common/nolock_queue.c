//
// Created by root on 1/16/20.
//
#include "nolock_queue.h"

QueueNode *createQueueNode() {
    QueueNode *queueNode = (QueueNode *) cover_malloc(sizeof(QueueNode));
    return queueNode;
}

Queue *createQueue() {
    Queue *queue = (Queue *) cover_malloc(sizeof(Queue));
    QueueNode *node = createQueueNode();
    queue->head = queue->tail = node;
    return queue;
}

void addQueue(Queue *queue, void *data) {
    QueueNode *node = createQueueNode();
    node->data = data;
    node->next = NULL;

    QueueNode *tail = NULL;
    QueueNode *next = NULL;
    while (true) {
        //先取一下尾指针和尾指针的next
        tail = queue->tail;
        next = tail->next;
        if (tail != queue->tail) {
            //如果尾指针已经被移动了，则重新开始
            continue;
        }
        if (next != NULL) {
            //如果尾指针的 next 不为NULL，则 fetch 全局尾指针到next
            __sync_bool_compare_and_swap(&queue->tail, tail, next);
            continue;
        }
        if (__sync_bool_compare_and_swap(&tail->next, next, node)) {
            //如果加入结点成功，则退出
            break;
        }
    }
    __sync_bool_compare_and_swap(&queue->tail, tail, node); //置尾结点
}

void *pollQueue(Queue *queue) {
    QueueNode *head = NULL;
    QueueNode *next = NULL;
    QueueNode *tail = NULL;
    void *data = NULL;

    while (true) {
        //取出头指针，尾指针，和第一个元素的指针
        head = queue->head;
        tail = queue->tail;
        next = head->next;

        if (head != queue->head) {
            // Q->head 指针已移动，重新取 head指针
            continue;
        }
        if (next == NULL) {
            // 如果是空队列
            return NULL;
        }
        if (head == tail) {
            //如果 tail 指针落后了
            __sync_bool_compare_and_swap(&queue->tail, tail, next);
            continue;
        }
        data = next->data;
        if (__sync_bool_compare_and_swap(&queue->head, head, next)) {
            //移动 head 指针成功后，取出数据
            break;
        }
    }
    cover_free(head); //释放老的dummy结点
    return data;
}