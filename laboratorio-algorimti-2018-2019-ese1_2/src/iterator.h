#pragma once
#include "linked.h"
#include<stddef.h>

typedef struct _Iterator {
	linked_list* list;
	node* curr_node;
	size_t current;
	size_t length;
} Iterator;

Iterator* create_new_iter(linked_list* list);

size_t get_iter_length(Iterator* iter);

void get_iter_next(Iterator* iter);

void get_iter_prev(Iterator* iter);

size_t get_current(Iterator* iter);

void* get_curr_element(Iterator* iter);

int is_iterator_valid(Iterator* iter);

void delete_iter(Iterator* iter);
