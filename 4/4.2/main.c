#include "priority_queue.h"


int main()
{
    priority_queue* pq = priority_queue_init(); 
    
    priority_queue_push(pq, "Hello, World!", 1);
    priority_queue_push(pq, "Vasya", 21);
    priority_queue_push(pq, "poshel", 20);
    priority_queue_push(pq, "gulyat'.", 22);
    priority_queue_push(pq, "Gun", 2);

    priority_queue_print_all(stdout, pq);

    printf("FRONT: ");
    priority_queue_node_print(stdout, pq->front);

    node* gun = priority_queue_pop_front(pq);
    priority_queue_print_all(stdout, pq);
    priority_queue_node_destroy(gun);

    printf("FRONT: ");
    priority_queue_node_print(stdout, pq->front);

    node* hello = priority_queue_pop_priority_exact(pq, 1);
    priority_queue_print_all(stdout, pq);
    priority_queue_node_destroy(hello);

    printf("FRONT: ");
    priority_queue_node_print(stdout, pq->front);

    node* gulyat = priority_queue_pop_priority_exact_more(pq, 20);
    priority_queue_print_all(stdout, pq);
    priority_queue_node_destroy(gulyat);

    printf("FRONT: ");
    priority_queue_node_print(stdout, pq->front);

    node* poshel = priority_queue_pop_priority_exact_more(pq, 20);
    priority_queue_print_all(stdout, pq);
    priority_queue_node_destroy(poshel);

    printf("FRONT: ");
    priority_queue_node_print(stdout, pq->front);

    priority_queue_destroy(pq);
    return 0;
}
