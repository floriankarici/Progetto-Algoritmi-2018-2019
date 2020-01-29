#include "dynamic_array.h"
#include "iterator.h"
#include "unity.h"
#include "unity_internals.h"

#include <stdlib.h>

// Definizione del tipo opaco
typedef struct _DynamicArray DynamicArray;


// Funzione che implementa la relazione dell'ordine tra numeri interi
int compare_int_ptr(void* elem1, void* elem2) {
  int int1 = *(int*) elem1;
  int int2 = *(int*) elem2;

  if(int1 == int2) {
    return 0;
  }

  if(int1 < int2) {
    return -1;
  }

  return 1;
}

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static DynamicArray* build_fixture() {
  DynamicArray* array = DynamicArray_new(6, compare_int_ptr);

  DynamicArray_insert_asc(array, new_int(1));
  DynamicArray_insert_asc(array, new_int(10));
  DynamicArray_insert_asc(array, new_int(4));
  DynamicArray_insert_asc(array, new_int(7));

  return array;
}

static Iterator* build_iterator_fixture(DynamicArray* array){
	Iterator* iter=create_iterator(array);
	return iter;
}
static void free_fixture(DynamicArray* array) {
  for(size_t i = 0; i<DynamicArray_size(array); ++i) {
    free( DynamicArray_at(array, i) );
  }

  DynamicArray_free(array);
}
static void free_iterator_fixture(Iterator* iter){
	delete_iterator(iter);
}
static void test_dynamic_array_new_not_null() {
  DynamicArray* array = DynamicArray_new(10, compare_int_ptr);
  TEST_ASSERT_NOT_NULL(array);

  DynamicArray_free(array);
}

static void test_dynamic_array_insert_desc(){
	 DynamicArray* array = DynamicArray_new(6, compare_int_ptr);

	  DynamicArray_insert_desc(array, new_int(1));
	  DynamicArray_insert_desc(array, new_int(10));
	  DynamicArray_insert_desc(array, new_int(4));
	  DynamicArray_insert_desc(array, new_int(7));

	  TEST_ASSERT_EQUAL_INT(10,  *(int*)DynamicArray_at(array, 0) );
	  TEST_ASSERT_EQUAL_INT(7,  *(int*)DynamicArray_at(array, 1) );
	  TEST_ASSERT_EQUAL_INT(4,  *(int*)DynamicArray_at(array, 2) );
	  TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 3) );
}

static void test_dynamic_array_new_capacity_is_correct() {
  DynamicArray* array = DynamicArray_new(10, compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(10, DynamicArray_capacity(array));

  DynamicArray_free(array);
}

static void test_dynamic_array_new_size_zero() {
  DynamicArray* array = DynamicArray_new(10, compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(0, DynamicArray_size(array));

  DynamicArray_free(array);
}

static void test_dynamic_array_free() {
  DynamicArray* array = DynamicArray_new(10, compare_int_ptr);
  DynamicArray_free(array);

  TEST_ASSERT_EQUAL_INT(1, 1);
}

static void test_dynamic_array_size() {
  DynamicArray* array = build_fixture();
  TEST_ASSERT_EQUAL_INT(4, DynamicArray_size(array));
  free_fixture(array);
}


static void test_dynamic_array_empty() {
  DynamicArray* array = DynamicArray_new(10, compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, DynamicArray_empty(array));
  DynamicArray_free(array);
}

static void test_dynamic_array_realloc() {
  DynamicArray* array = build_fixture();
  size_t old_capacity = DynamicArray_capacity(array);
  DynamicArray_insert_asc(array, new_int(10));
  DynamicArray_insert_asc(array, new_int(3));
  DynamicArray_insert_asc(array, new_int(4));
  DynamicArray_insert_asc(array, new_int(5));
  DynamicArray_insert_asc(array, new_int(7));
  DynamicArray_insert_asc(array, new_int(8));
  TEST_ASSERT_EQUAL_INT(1, DynamicArray_capacity(array) > old_capacity);
  TEST_ASSERT_EQUAL_INT(1, DynamicArray_capacity(array) >= DynamicArray_size(array));

  free_fixture(array);
}

static void test_dynamic_array_at() {
  DynamicArray* array = build_fixture();
  TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 0) );
  TEST_ASSERT_EQUAL_INT(4,  *(int*)DynamicArray_at(array, 1) );
  TEST_ASSERT_EQUAL_INT(7,  *(int*)DynamicArray_at(array, 2) );
  TEST_ASSERT_EQUAL_INT(10,  *(int*)DynamicArray_at(array, 3) );
  free_fixture(array);
}

static void test_dynamic_array_insert_queue(){
	DynamicArray* array=build_fixture();

	DynamicArray_insert_queue(array,new_int(20));
	TEST_ASSERT_EQUAL_INT(5,DynamicArray_size(array));
	TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 0) );
  	TEST_ASSERT_EQUAL_INT(4,  *(int*)DynamicArray_at(array, 1) );
    TEST_ASSERT_EQUAL_INT(7,  *(int*)DynamicArray_at(array, 2) );
    TEST_ASSERT_EQUAL_INT(10, *(int*)DynamicArray_at(array, 3) );
	TEST_ASSERT_EQUAL_INT(20, *(int*)DynamicArray_at(array,4));
	
	
	free_fixture(array);
}

static void test_dynamic_array_insert_pos(){
	DynamicArray* array=build_fixture();

	DynamicArray_insert_pos(array,new_int(30),1);
	TEST_ASSERT_EQUAL_INT(5,DynamicArray_size(array));
	TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 0));
    TEST_ASSERT_EQUAL_INT(30,  *(int*)DynamicArray_at(array, 1));
    TEST_ASSERT_EQUAL_INT(4,  *(int*)DynamicArray_at(array, 2));
    TEST_ASSERT_EQUAL_INT(7, *(int*)DynamicArray_at(array, 3));
	TEST_ASSERT_EQUAL_INT(10, *(int*)DynamicArray_at(array, 4));
	
	free_fixture(array);
}
static void test_dynamic_array_delete_queue(){
	DynamicArray* array=build_fixture();

	DynamicArray_delete_queue(array);
	TEST_ASSERT_EQUAL_INT(3,DynamicArray_size(array));
	TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 0) );
    TEST_ASSERT_EQUAL_INT(4,  *(int*)DynamicArray_at(array, 1) );
    TEST_ASSERT_EQUAL_INT(7,  *(int*)DynamicArray_at(array, 2) );
  	
	

	free_fixture(array);
}

static void test_dynamic_array_delete_pos(){
	DynamicArray* array=build_fixture();

	DynamicArray_delete_pos(array,1);
	TEST_ASSERT_EQUAL_INT(3,DynamicArray_size(array));
	TEST_ASSERT_EQUAL_INT(1,  *(int*)DynamicArray_at(array, 0) );
  	TEST_ASSERT_EQUAL_INT(7,  *(int*)DynamicArray_at(array, 1) );
  	TEST_ASSERT_EQUAL_INT(10,  *(int*)DynamicArray_at(array, 2) );
	

	free_fixture(array);
}

static void test_iterator_get_curr(){
	DynamicArray* array=build_fixture();
	Iterator* iter=build_iterator_fixture(array);
	
	TEST_ASSERT_EQUAL_INT(1,*(int*)get_curr(iter) );
	get_next(iter);
	TEST_ASSERT_EQUAL_INT(4,*(int*) get_curr(iter) );
	get_next(iter);
	TEST_ASSERT_EQUAL_INT(7,*(int*) get_curr(iter) );
	get_next(iter);
	TEST_ASSERT_EQUAL_INT(10,*(int*) get_curr(iter) );
	free_fixture(array);
	free_iterator_fixture(iter);
}
static void test_iterator_is_valid(){
	DynamicArray* array=build_fixture();
	Iterator* iter=build_iterator_fixture(array);
	get_next(iter);
	get_next(iter);
	get_next(iter);
	get_next(iter);
	TEST_ASSERT_EQUAL_INT(0, is_valid_iterator(iter) );
	free_fixture(array);
	free_iterator_fixture(iter);
}





int main() {
  UNITY_BEGIN();
  RUN_TEST(test_dynamic_array_insert_desc);
  RUN_TEST(test_dynamic_array_insert_queue);
  RUN_TEST(test_dynamic_array_insert_pos);
  RUN_TEST(test_dynamic_array_delete_queue);
  RUN_TEST(test_dynamic_array_delete_pos);
  RUN_TEST(test_dynamic_array_new_not_null);
  RUN_TEST(test_dynamic_array_new_capacity_is_correct);
  RUN_TEST(test_dynamic_array_new_size_zero);
  RUN_TEST(test_dynamic_array_size);
  RUN_TEST(test_dynamic_array_empty);
  RUN_TEST(test_dynamic_array_realloc);
  RUN_TEST(test_dynamic_array_at);
  RUN_TEST(test_iterator_get_curr);
  RUN_TEST(test_iterator_is_valid);
  UNITY_END();

  return 0;
}