/*

@author 2016051


functions that report if they are successful or not:
	enque
	print_list
	destroy_list
	is_full
	
1 - finished successfully
0 - finished unsuccessfully



Functions:

new_node	-------------------assigns queue to a variable				
	d - data
	p - priority  <- LOWER VALUES INDICATE HIGHER PRIORITY
	
queue_size  -------------------returns queue size as int
	ptr - your queue variable
	
is_empty	-------------------checks if queue is empty or not (first element counts as empty in case its for list size)
	head - your queue variable
	
enque		-------------------inserts element in queue
	head - your queue variable
	d - data
	p - priority <- LOWER VALUES INDICATE HIGHER PRIORITY
	
deque		-------------------removes element from queue, returns its value
	head - your queue variable
	
top 		-------------------returns first element in queue without removing it
	head - your queue variable
	
print_list 	-------------------prints list, reports if successfull or not
	ptr - your queue variable

destroy_list-------------------destroys list, reports if successfull or not
	ptr - your queue variable
	
is_full 	-------------------checks if its possible to allocate more memory
	ptr - your queue variable

*/

#ifndef priority_queueh
#define priority_queueh

#include "pq_struct.h"

Node* new_node(int d, int p);
int queue_size (Node* ptr);
int is_empty(Node* head);
int enque(Node** head, int d, int p);
int deque(Node** head);
int top(Node** head);
int print_list(Node* ptr);
int destroy_list(Node** ptr);
int is_full (Node* ptr);

#endif