#pragma once

#include <stddef.h>

typedef int (*DynamicArrayCompareType)(void*, void*);

// Implementation of an ordered array

struct _DynamicArray {
  void** array;
  size_t size;
  size_t capacity;
  DynamicArrayCompareType compare;
};

// Defintion of the opaque type
typedef struct _DynamicArray DynamicArray;

/* 
   Returns a newly allocated DynamicArray
   The returned array should be deallocated by DynamicArray_free
   capacity: initial size of the array
   compare: function implementing the order relation between the array elements
 */
DynamicArray* DynamicArray_new(size_t capacity, DynamicArrayCompareType compare);


// Deallocates the ordered array
void DynamicArray_free(DynamicArray* array);

// Returns the number of elements currently stored in the ordered array
size_t DynamicArray_size(DynamicArray* array);

// Returns the capacity of the ordered array
size_t DynamicArray_capacity(DynamicArray* array);

// Returns 1 if array is empty, 0 otherwise
int DynamicArray_empty(DynamicArray* array);

// Returns the element of array at the specified position
void* DynamicArray_at(DynamicArray* array, size_t position);

void DynamicArray_insert(DynamicArray* array,void* element);

// Insert element in the ordered array
void DynamicArray_insert_queue(DynamicArray* array, void* element);

//
void DynamicArray_insert_pos(DynamicArray* array, void* element, size_t position);

//
void DynamicArray_delete_queue(DynamicArray* array);  

//
void DynamicArray_delete_pos(DynamicArray* array,size_t position);  

/*#include "iterator.h"

Iterator* iterator(DynamicArray* array);*/


