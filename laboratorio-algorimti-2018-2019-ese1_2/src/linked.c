#include "linked.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node* new_node(void* element) {
	node* n=(node*)malloc(sizeof(node));
	n->elem=(void*)malloc(sizeof(void*));
	n->next=(node*)malloc(sizeof(node*));
	n->prev=(node*)malloc(sizeof(node*));
	n->elem=element;
	n->next=NULL;
	n->prev=NULL;
	return n;
}

linked_list* new_linked_list(linked_list_compare_type c) {
	linked_list* ll=(linked_list*)malloc(sizeof(linked_list));
	ll->head=(node*)malloc(sizeof(node*));
	ll->tail=(node*)malloc(sizeof(node*));
	ll->head=new_node(NULL);
	ll->tail=new_node(NULL);
	ll->length=0;
	ll->compare=c;
	return ll;
}


void delete_list(linked_list* l) {
	node* delete_n=l->head;
	int i=0;

	while(i<l->length) {
		node* tmp=delete_n->next;
		free(delete_n);
		delete_n=tmp;
		i++;
	}

	free(l);
}

size_t get_length(linked_list* l) {
	return l->length;
}

int is_empty(linked_list* l) {
	return l->length==0;
}

//recupero dell'elemento in posizione i-esima in O(n)
void* get_element(linked_list* l, size_t position) {
	node* curr=l->head;
	int i=0;

	if(position==0) {
		return curr->elem;
	}

	else {
		while(i<position) {
			curr=curr->next;
			i++;
		}
	}

	return curr->elem;
}


void delete_node(node* n) {
	if(n==NULL) return;
	free(n);
}

//inserimento in i-esima posizione in O(n)
void insert_element_pos (linked_list* l, void* element, size_t position) {
	int i=0;
	node* new_element=new_node(element);

	if(position >l->length) {
		printf("ERROR: INDEX OUT OF BOUNDS \n");
		exit(EXIT_FAILURE);
	}

	if(position==l->length) {
		insert_element_tail(l, element);
	}

	else if(position==0 && is_empty(l)) {
		insert_element_tail(l, element);
	}

	else if(position==0 && !is_empty(l)) {
		if(l->length>1) {
			node* tmp=new_node(NULL);
			memcpy(tmp, l->head, sizeof(node));
			l->head->next->prev=tmp;
			tmp->next=l->head->next;
			free(l->head);
			l->head=new_node(NULL);
			memcpy(l->head, new_element, sizeof(node));
			l->head->next=tmp;
			tmp->prev=l->head;
			free(new_element);
			l->length+=1;
		}

		else {
			delete_node(l->head);
			l->head=new_node(NULL);
			memcpy(l->head, new_element, sizeof(node));
			l->head->next=l->tail;
			l->tail->prev=l->head;
			delete_node(new_element);
			l->length+=1;
		}
	}

	else {
		node* tmp=l->head;

		while(i<position) {
			tmp=tmp->next;
			i++;
		}

		tmp->prev->next=new_element;
		new_element->prev=tmp->prev;
		tmp->prev=new_element;
		new_element->next=tmp;
		l->length+=1;
	}
}

//manca inserimento ordinato in lista

//inserimento in coda in O(1)
void insert_element_tail(linked_list* l,void* element){
	node* new_element=new_node(element);
	if(is_empty(l)){
		memcpy(l->head,new_element,sizeof(node));
		memcpy(l->tail,new_element,sizeof(node));
		delete_node(new_element);
		l->length+=1;
	}
	else if(get_length(l)==1){
		free(l->tail);
		l->tail=new_node(NULL);
		memcpy(l->tail,new_element,sizeof(node));
		l->head->next=l->tail;
		l->tail->prev=l->head;
		free(new_element);
		l->length+=1;
	}
	else {
		node* tmp=new_node(NULL);
		memcpy(tmp,l->tail,sizeof(node));
		l->tail->prev->next=tmp;
		tmp->prev=l->tail->prev;
		free(l->tail);
		l->tail=new_node(NULL);
		memcpy(l->tail,new_element,sizeof(node));
		tmp->next=l->tail;
		l->tail->prev=tmp;
		free(new_element);
		l->length+=1;
	}
}



//inserimento ordinato in lista 
void insert_element_asc(linked_list* l, void* element) {
	if(l->length==0) {

		insert_element_tail(l, element);
	}

	else if(l->length==1) {
		int cont=1;
		if(l->compare(element, l->head->elem)>0) insert_element_tail(l, element);
		else insert_element_pos(l, element, 0);
	}

	else {
		int cont=l->length;
		node* tmp=new_node(element);
		node* curr=l->tail;

		while(cont>0 && l->compare(curr->elem, tmp->elem)>0) {
			curr=curr->prev;
			cont--;
		}

		insert_element_pos(l, element, cont);

	}
}



void insert_element_desc(linked_list* l, void* element) {
	if(l->length==0) {

		insert_element_tail(l, element);
	}

	else if(l->length==1) {
		int cont=1;
		if(l->compare(element, l->head->elem)<0) insert_element_tail(l, element);
		else insert_element_pos(l, element, 0);
	}

	else {
		int cont=l->length;
		node* tmp=new_node(element);
		node* curr=l->tail;

		while(cont>0 && l->compare(curr->elem, tmp->elem)<0) {
			curr=curr->prev;
			cont--;
		}

		insert_element_pos(l, element, cont);

	}
}

void delete_element_tail(linked_list* l) {
	if(l->length==1) {
		delete_node(l->head);
		delete_node(l->tail);
		l->length-=1;
	}

	else {
		node* tmp=new_node(NULL);
		memcpy(tmp, l->tail, sizeof(node));
		l->tail->prev->next=NULL;
		l->tail=l->tail->prev;
		delete_node(tmp);
		l->length-=1;
	}
}

void delete_element_pos(linked_list* l, size_t position) {
	int i=0;

	if(position>=l->length) {
		printf("ERROR:INDEX OUT OF BOUNDS\n");
		exit(EXIT_FAILURE);
	}

	if(position==0 && get_length(l)==1) {
		delete_element_tail(l);
	}

	else if(position==0 && get_length(l)>1) {
		node* tmp=new_node(NULL);
		memcpy(tmp, l->head, sizeof(node));
		l->head->next->prev=NULL;
		l->head=l->head->next;
		delete_node(tmp);
		l->length-=1;
	}

	else {
		node* tmp=l->head;

		while(i<position) {
			tmp=tmp->next;
			i++;
		}

		tmp->prev->next=tmp->next;
		tmp->next->prev=tmp->prev;
		delete_node(tmp);
		l->length-=1;
	}
}