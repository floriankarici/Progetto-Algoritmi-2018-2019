#include "iterator.h"
#include "linked.h"
#include <stdio.h>
#include <stdlib.h>

Iterator* create_new_iter(linked_list* list){
	Iterator* iter=(Iterator*)malloc(sizeof(Iterator));
	iter->list=(void*)malloc(sizeof(linked_list));
        iter->curr_node=(void*)malloc(sizeof(node));
	iter->list=list;
	iter->curr_node=list->head;
	iter->current=0;
	iter->length=get_length(list);
}

size_t get_iter_length(Iterator* iter){
	return iter->length;
}

void get_iter_next(Iterator* iter){
       iter->curr_node=iter->curr_node->next;
       iter->current+=1;
}

void get_iter_prev(Iterator* iter){
	iter->curr_node=iter->curr_node->prev;
	iter->current-=1;
		
}
size_t get_current(Iterator* iter){
	return iter->current;
}
void* get_curr_element(Iterator* iter){
	return get_element(iter->list,iter->current);
}

int is_iterator_valid(Iterator* iter){
	return (iter->current<=iter->length-1 && iter->current>=0);
}

void delete_iter(Iterator* iter){
	
	free(iter);
}
