#pragma once

#include<stddef.h>

typedef struct _Iterator {
	DynamicArray* da;
	size_t current;
	size_t size;
	size_t capacity;
} Iterator;

//creazione iteratore in O(1)
Iterator* create_iterator(DynamicArray* array);

//eliminazione e deallocazione in O(1)
void delete_iterator(Iterator* iter);

//recupera l'elemento corrente in O(1)
void* get_curr(Iterator* iter);

size_t get_capacity(Iterator* iter);

size_t get_size(Iterator* iter);

void get_next(Iterator* iter);

//controlla se l'iteratore e ancora valido in O(1)
int is_valid_iterator(Iterator *iter);

