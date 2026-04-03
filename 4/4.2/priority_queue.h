#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdint.h>
#include <stdio.h>

#define MESSAGE_MAX_LEN 200

#define PQ_PUSH_OK 0
#define PQ_PUSH_BAD -1

typedef struct priority_queue_node
{
    char message[MESSAGE_MAX_LEN];
    uint8_t priority;
    struct priority_queue_node* next;
} node;

node* priority_queue_node_init(char* message, uint8_t priority, node* next);
void priority_queue_node_destroy(node* node);
void priority_queue_node_print(FILE* stream, node* node);



typedef struct priority_queue
{
    node* front;
} priority_queue;

priority_queue* priority_queue_init();
void priority_queue_destroy(priority_queue* pq);

int priority_queue_push(priority_queue* pq, char* message, uint8_t priority);

node* priority_queue_pop_front(priority_queue* pq);
node* priority_queue_pop_priority_exact(priority_queue* pq, uint8_t priority);
node* priority_queue_pop_priority_exact_more(priority_queue* pq, uint8_t priority);

void priority_queue_print_all(FILE* stream, priority_queue* pq);

#endif
