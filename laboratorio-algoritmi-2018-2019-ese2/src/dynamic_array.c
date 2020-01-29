#include "dynamic_array.h"
#include <stdlib.h>
#include <stdio.h>


//creazione nuovo array dinamico
DynamicArray* DynamicArray_new(size_t capacity, DynamicArrayCompareType compare) {
  DynamicArray* result = (DynamicArray*) malloc(sizeof(DynamicArray));
  result->array = (void**) malloc(sizeof(void*)*capacity);
  result->size = 0;
  result->capacity = capacity;
  result->compare = compare;
  return result;
}
//deallocazione array dinamico
void DynamicArray_free(DynamicArray* array) {
  free(array->array);
  free(array);
  return;
}

//ritorna numero di elementi in O(1)
size_t DynamicArray_size(DynamicArray* array) {
  return array->size;
}
//ritorna la dimensione dell'array
size_t DynamicArray_capacity(DynamicArray* array) {
  return array->capacity;
}
//ritorna se l'array e' vuoto
int DynamicArray_empty(DynamicArray* array) {
  return array->size == 0;
}

void* DynamicArray_at(DynamicArray* array, size_t position) {
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    exit(EXIT_FAILURE);
  }
 return array->array[position];
}
//reallacozione
void DynamicArray_check_and_realloc(DynamicArray* array) {
  if( array->capacity > array->size )
    return;
  array->capacity *= 2;
  array->array = realloc(array->array, sizeof(void*) * array->capacity);
}

void DynamicArray_insert(DynamicArray* array, void* element) {
 DynamicArray_check_and_realloc(array);
 size_t i;
    
  for( i = DynamicArray_size(array); i > 0 && array->compare(array->array[i-1], element) > 0; --i ) {
    array->array[i] = array->array[i-1];
  }

  array->array[i] = element;
  array->size += 1;

  return;
}
//inserimento in coda
void DynamicArray_insert_queue(DynamicArray* array, void* element){
	
	DynamicArray_check_and_realloc(array);
	array->array[array->size]=element;
	array->size+=1;
	
}
//inserimento nella posizione i-esima in O(n)
void DynamicArray_insert_pos(DynamicArray* array, void* element, size_t position){
	DynamicArray_check_and_realloc(array);
	if(position>array->size){
		fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
	    exit(EXIT_FAILURE);
  	}
	if(position==array->size)
		DynamicArray_insert_queue(array,element);
	else {
		for(int i=array->size;i>position;i--){
			array->array[i]=array->array[i-1];	
		}
		array->array[position]=element;
		array->size+=1;
	}
}
//cancellazione ultimo elemento dell'array
void DynamicArray_delete_queue(DynamicArray* array){
	free(array->array[array->size-1]);
	array->size-=1;
}

//cancellazione i-esimo elmento in O(n)
void DynamicArray_delete_pos(DynamicArray* array,size_t position){
	if(position>=array->size){
		fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
	    exit(EXIT_FAILURE);
  	}
	if(position==array->size-1)
		DynamicArray_delete_queue(array);
	else{
		for(int i=position;i<array->size-1;i++)
			array->array[i]=array->array[i+1];
		array->size-=1;
		}
}

/*	ritorna elemento corrente in O(n)
void* DynamicArray_at(DynamicArray* array, size_t position) {
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    exit(EXIT_FAILURE);
  }
  else if(position==0)
  		return array->array[0];
  else {
  	int i=0;
  	while (i<=position){
  		i++;
	  }
  }
  return array->array[i];
}*/

