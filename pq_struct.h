#ifndef pq_structh
#define pq_structh

typedef int tipas;

struct node {
    tipas data;

    // Lower values indicate higher priority
    int priority;

    struct node* next;

};
typedef struct node Node;

#endif