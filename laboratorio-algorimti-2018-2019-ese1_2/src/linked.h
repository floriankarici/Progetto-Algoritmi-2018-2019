#pragma once 

#include <stddef.h>

typedef int (*linked_list_compare_type)(void*, void*);

typedef struct node{
	void* elem;
	struct node* next;
	struct node* prev;
} node;

typedef struct linked_list {
	node* head;
	node* tail;
	size_t length;
	linked_list_compare_type compare;
}linked_list;

node* new_node(void* element);

linked_list* new_linked_list(linked_list_compare_type c);

void delete_node(node* n);

void delete_list(linked_list* l);

size_t get_length(linked_list* l);

int is_empty(linked_list* l);

void* get_element(linked_list* l,size_t position);

void insert_element_asc(linked_list* l, void* element);

void insert_element_desc(linked_list* l,void* element);

void insert_element_tail(linked_list* l,void* element);

void insert_element_pos (linked_list* l,void* element,size_t position);

void delete_element_tail(linked_list* l);

void delete_element_pos(linked_list* l,size_t position);

