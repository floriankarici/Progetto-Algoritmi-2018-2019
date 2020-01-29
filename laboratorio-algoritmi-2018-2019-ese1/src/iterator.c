#include "dynamic_array.h"
#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>

//creazione iteratore in O(1)
Iterator* create_iterator(DynamicArray* array){
	Iterator* iter = (Iterator*) (malloc(sizeof(Iterator)));
	iter->da=(void*)(malloc(sizeof(DynamicArray_size(array))));
	iter->da=array;
	iter->current=0;
	iter->capacity=DynamicArray_capacity(array);
	iter->size=DynamicArray_size(array);
	return iter;
}

//eliminazione e deallocazione in O(1)
void delete_iterator(Iterator* iter){
	iter->da=NULL;
	free(iter->da);
	free(iter);
}

//recupera l'elemento corrente in O(1)
void* get_curr(Iterator* iter){
	return DynamicArray_at(iter->da,iter->current);
}


size_t get_capacity(Iterator* iter){
	return iter->capacity;
}

size_t get_size(Iterator* iter){
	return iter->size;
}
//sposta l'iteratore all'elemento successivo in O(1)
void get_next(Iterator* iter){
	
	iter->current+=1;
}

//controlla se l'iteratore e ancora valido in O(1)
int is_valid_iterator(Iterator *iter){
	return iter->current<=iter->size-1;
}

