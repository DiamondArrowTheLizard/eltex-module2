#include "priority_queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

node* priority_queue_node_init(char* message, uint8_t priority, node* next)
{
    node* n = (node*)malloc(sizeof(*n));
    strncpy(n->message, message, MESSAGE_MAX_LEN);
    n->priority = priority;
    n->next = next;

    return n;
}

void priority_queue_node_destroy(node* node)
{
    if(node == NULL) return;

    node->next = NULL;

    free(node);
    node = NULL;
}

void priority_queue_node_print(FILE* stream, node* node)
{
    if(node == NULL)
    {
        fprintf(stderr, "Error: node is NULL.\n");
        return;
    }
    fprintf(stream, "[%d]: %s\n", node->priority, node->message);
}



priority_queue* priority_queue_init()
{
    priority_queue* pq = (priority_queue*)malloc(sizeof(*pq));

    pq->front = NULL;

    return pq;
}

void priority_queue_destroy(priority_queue* pq)
{
    if(pq == NULL) return;

    if(pq->front == NULL) 
    {
        free(pq);
        pq = NULL;
        return;
    }

    node* node = pq->front;
    pq->front = pq->front->next;
    priority_queue_node_destroy(node);

    priority_queue_destroy(pq);
}

int priority_queue_push(priority_queue* pq, char* message, uint8_t priority)
{
    if(pq == NULL) return PQ_PUSH_BAD;

    node* new_front = priority_queue_node_init(message, priority, pq->front);
    pq->front = new_front;

    return PQ_PUSH_OK;
}

node* priority_queue_pop_front(priority_queue* pq)
{
    if(pq == NULL) return NULL;

    node* front = priority_queue_node_init(pq->front->message, pq->front->priority, NULL);

    node* front_new = pq->front->next;
    priority_queue_node_destroy(pq->front);

    pq->front = front_new;

    return front;
}

node* priority_queue_pop_priority_exact(priority_queue* pq, uint8_t priority)
{
    if(pq == NULL) return NULL;

    if(pq->front->priority == priority) return priority_queue_pop_front(pq);

    node* found_node = NULL;
    node* tmp = NULL;

    for(node* node = pq->front; node->next != NULL; node = node->next)
    {
        if(node->next->priority == priority)
        {
            found_node = priority_queue_node_init(node->next->message, node->next->priority, NULL);
            tmp = node->next;
            node->next = node->next->next;
            priority_queue_node_destroy(tmp);

            return found_node;
        }
        if(node->priority == priority)
        {
            found_node = priority_queue_node_init(node->message, node->priority, NULL);
            priority_queue_node_destroy(node);

            return found_node;
        }
    }

    return found_node;
}

node* priority_queue_pop_priority_exact_more(priority_queue* pq, uint8_t priority)
{
    if(pq == NULL) return NULL;

    if(pq->front->priority >= priority) return priority_queue_pop_front(pq);

    node* found_node = NULL;
    node* tmp = NULL;

    for(node* node = pq->front; node->next != NULL; node = node->next)
    {
        if(node->next->priority >= priority)
        {
            found_node = priority_queue_node_init(node->next->message, node->next->priority, NULL);
            tmp = node->next;
            node->next = node->next->next;
            priority_queue_node_destroy(tmp);

            return found_node;
        }
        if(node->priority == priority)
        {
            found_node = priority_queue_node_init(node->message, node->priority, NULL);
            priority_queue_node_destroy(node);

            return found_node;
        }
    }

    return found_node;
}

void priority_queue_print_all(FILE* stream, priority_queue* pq)
{
    if(pq == NULL)
    {
        fprintf(stderr, "Error: Priority Queue is NULL.\n");
        return;
    }

    fprintf(stream, "Nodes in queue:\n");
    for(node* node = pq->front; node != NULL; node = node->next)
    {
        fprintf(stream, "   ");
        priority_queue_node_print(stream, node);
    }
}
