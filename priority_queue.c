#ifndef priority_queuec
#define priority_queuec

#include <stdio.h>
#include <stdlib.h>

#include "pq_struct.h"
#include "priority_queue.h"

Node* new_node(int d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL){
        temp->data = d;
        temp->priority = p;
        temp->next = NULL;
    }

    return temp;
}

int queue_size (Node* ptr)
{
    int count = 0;
    while (ptr != NULL){
        ++count;
        ptr = ptr->next;
    }
    return count;
}

int is_empty(Node* head)
{
    return queue_size(head) <= 1;
}

int enque(Node** head, int d, int p)
{
    Node* start = (*head);
    Node* temp = new_node(d, p);

    if (temp != NULL){
        if ((*head)->priority > p) {
            temp->next = *head;
            (*head) = temp;
        } else {
            while (start->next != NULL &&
                start->next->priority <= p) {
                start = start->next;
            }
            temp->next = start->next;
            start->next = temp;
        }
    } else {
        return 0;
    }
    return 1;
}

int deque(Node** head)
{
    int value = (*head)->data;
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
    return value;
}

int top(Node** head)
{
    return (*head)->data;
}

int print_list(Node* ptr)
{
    if (is_empty(ptr)){
        return 0;
    }
    while (ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    return 1;
    printf("\n");
}

int destroy_list(Node** ptr)
{
    if (ptr == NULL){
        return 0;
    }
    while (ptr != NULL){
        Node* temp = *ptr;
        (*ptr) = (*ptr)->next;
        free(temp);
    }
    return 1;
}


int is_full (Node* ptr)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL){
        free(temp);
        return 0;
    }
    free(temp);
    return 1;
}

#endif