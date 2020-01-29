#include "linked.h"
#include "iterator.h"
#include "unity.h"
#include "unity_internals.h"

#include <stdlib.h>




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

static linked_list* build_fixture() {
  linked_list* list=new_linked_list(compare_int_ptr);
  insert_element_asc(list, new_int(1));
  insert_element_asc(list, new_int(10));
  insert_element_asc(list, new_int(4));
  insert_element_asc(list, new_int(7));

  return list;
}






static void free_fixture(linked_list* list) {
 delete_list(list);
}
static void free_iterator_fixture(Iterator* iter){
	delete_iter(iter);
}

static void test_linked_list_new_not_null() {
  linked_list* list = new_linked_list(compare_int_ptr);
  TEST_ASSERT_NOT_NULL(list);

  delete_list(list);
}




static Iterator* build_iterator_fixture(linked_list* list){
	Iterator* iter=create_new_iter(list);
	return iter;
}



static void test_linked_list_empty() {
  linked_list* list = new_linked_list(compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, is_empty(list));

  delete_list(list);
}


static void test_linked_list_length() {
  linked_list* list= build_fixture();
  TEST_ASSERT_EQUAL_INT(4, get_length(list));
  free_fixture(list);
}






static void test_linked_list_insert_desc(){
	linked_list* list=new_linked_list(compare_int_ptr);
	insert_element_desc(list, new_int(1));
 	insert_element_desc(list, new_int(10));
	insert_element_desc(list, new_int(4));
	insert_element_desc(list, new_int(7));

	TEST_ASSERT_EQUAL_INT(10,  *(int*)get_element(list, 0) );
 	TEST_ASSERT_EQUAL_INT(7, *(int*)get_element(list, 1) );
  	TEST_ASSERT_EQUAL_INT(4,  *(int*)get_element(list, 2) );
  	TEST_ASSERT_EQUAL_INT(1, *(int*)get_element(list, 3) );

}


static void test_linked_list_insert_pos() {
  linked_list* list= build_fixture();

  insert_element_pos(list, new_int(8),1);
  TEST_ASSERT_EQUAL_INT(5, get_length(list));
  TEST_ASSERT_EQUAL_INT(1,  *(int*)get_element(list, 0) );
  TEST_ASSERT_EQUAL_INT(8, *(int*)get_element(list,1));
  TEST_ASSERT_EQUAL_INT(4, *(int*)get_element(list, 2) );
  TEST_ASSERT_EQUAL_INT(7,  *(int*)get_element(list, 3) );
  TEST_ASSERT_EQUAL_INT(10, *(int*)get_element(list, 4) );
  free_fixture(list);
}
static void test_linked_list_insert_tail() {
  linked_list* list = build_fixture();

  insert_element_tail(list, new_int(20));
  TEST_ASSERT_EQUAL_INT(5, get_length(list));
  TEST_ASSERT_EQUAL_INT(1,  *(int*)get_element(list, 0) );
  TEST_ASSERT_EQUAL_INT(4, *(int*)get_element(list, 1) );
  TEST_ASSERT_EQUAL_INT(7,  *(int*)get_element(list, 2) );
  TEST_ASSERT_EQUAL_INT(10, *(int*)get_element(list, 3) );
  TEST_ASSERT_EQUAL_INT(20, *(int*)get_element(list, 4));

  free_fixture(list);
}


static void test_linked_list_at() {
  linked_list* list= build_fixture();
  TEST_ASSERT_EQUAL_INT(1,  *(int*)get_element(list, 0) );
  TEST_ASSERT_EQUAL_INT(4, *(int*)get_element(list, 1) );
  TEST_ASSERT_EQUAL_INT(7,  *(int*)get_element(list, 2) );
  TEST_ASSERT_EQUAL_INT(10, *(int*)get_element(list, 3) );
  free_fixture(list);
}
static void test_linked_list_delete_tail(){
	linked_list* list=build_fixture();

	delete_element_tail(list);
	TEST_ASSERT_EQUAL_INT(3,get_length(list));
	TEST_ASSERT_EQUAL_INT(1,  *(int*)get_element(list, 0) );
  	TEST_ASSERT_EQUAL_INT(4, *(int*)get_element(list, 1) );
  	TEST_ASSERT_EQUAL_INT(7,  *(int*)get_element(list, 2) );

	free_fixture(list);
}


static void test_linked_list_delete_pos(){
	linked_list* list=build_fixture();

	delete_element_pos(list,1);
	TEST_ASSERT_EQUAL_INT(3,get_length(list));
	TEST_ASSERT_EQUAL_INT(1,*(int*)get_element(list,0));
	TEST_ASSERT_EQUAL_INT(7,*(int*)get_element(list,1));
	TEST_ASSERT_EQUAL_INT(10,*(int*)get_element(list,2));

	free_fixture(list);
}

static void test_iterator_length(){
	linked_list* list=build_fixture();
	Iterator* iter=build_iterator_fixture(list);
	
	TEST_ASSERT_EQUAL_INT(get_length(list),get_iter_length(iter));
	
	
	free_fixture(list);
	free_iterator_fixture(iter);
}
static void test_iterator_get_curr(){
	linked_list* list=build_fixture();
	Iterator* iter=build_iterator_fixture(list);
	
	TEST_ASSERT_EQUAL_INT(1,*(int*) get_curr_element(iter) );
	get_iter_next(iter);
	TEST_ASSERT_EQUAL_INT(4,*(int*) get_curr_element(iter) );
	get_iter_next(iter);
	TEST_ASSERT_EQUAL_INT(7,*(int*) get_curr_element(iter) );
	get_iter_next(iter);
	TEST_ASSERT_EQUAL_INT(10,*(int*) get_curr_element(iter) );

	free_fixture(list);
	free_iterator_fixture(iter);
}

static void test_iterator_is_valid(){
	linked_list* list=build_fixture();
	Iterator* iter=build_iterator_fixture(list);
	get_iter_next(iter);
	get_iter_next(iter);
	get_iter_next(iter);
	get_iter_next(iter);
	TEST_ASSERT_EQUAL_INT(0, is_iterator_valid(iter) );
	free_fixture(list);
	free_iterator_fixture(iter);
}
int main() {
  UNITY_BEGIN();

  RUN_TEST(test_linked_list_new_not_null);
  RUN_TEST(test_linked_list_empty);
  RUN_TEST(test_linked_list_length);
  RUN_TEST(test_linked_list_at);
  RUN_TEST(test_linked_list_insert_desc);
  RUN_TEST(test_linked_list_insert_pos);
  RUN_TEST(test_linked_list_insert_tail);
  RUN_TEST(test_linked_list_delete_tail);
  RUN_TEST(test_linked_list_delete_pos);
  RUN_TEST(test_iterator_length);
  RUN_TEST(test_iterator_get_curr);  
  RUN_TEST(test_iterator_is_valid);
  UNITY_END();

  return 0;
}

