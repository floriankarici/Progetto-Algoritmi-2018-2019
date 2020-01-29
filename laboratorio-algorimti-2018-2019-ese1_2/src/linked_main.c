#include "linked.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct {
	char* field1;
	int field2;
}

Record;

// Function implementing an order relation by the string value between records
static int Record_compare1(void* obj1, void* obj2) {
	Record* rec1=(Record*) obj1;
	Record* rec2=(Record*) obj2;

	int compString=strcmp(rec1->field1, rec2->field1);

	if (compString !=0) return compString;

	if(rec1->field2 < rec2->field2) {
		return -1;
	}

	if(rec1->field2 > rec2->field2) {
		return 1;
	}

	return 0;
}

// Function implementing an order relation by the integer value between records
static int Record_compare2(void* obj1, void* obj2) {
	Record* rec1=(Record*) obj1;
	Record* rec2=(Record*) obj2;

	if(rec1->field2 < rec2->field2) {
		return -1;
	}

	if(rec1->field2 > rec2->field2) {
		return 1;
	}

	return strcmp(rec1->field1, rec2->field1);
}

static Record* Record_new(char* str, int num) {
	Record* record=(Record*) malloc(sizeof(Record));
	record->field1=str;
	record->field2=num;
	return record;
}

static void load_list(const char* file_name, linked_list* list, int criterio) {
	FILE* file=fopen(file_name, "r");
	assert(file !=NULL);
	char buf[128];

	if(criterio==0) {
		while( !feof(file)) {
			int num;
			int num_fields=fscanf(file, "%127[^,],%d\n", buf, &num);
			assert(num_fields==2);

			Record* record=Record_new(strdup(buf), num);
			insert_element_asc(list, record);
		}

		return;
	}

	while( !feof(file)) {
		int num;
		int num_fields=fscanf(file, "%127[^,],%d\n", buf, &num);
		assert(num_fields==2);

		Record* record=Record_new(strdup(buf), num);
		insert_element_desc(list, record);
	}
}

static void print_list(linked_list* list) {
	size_t size=get_length(list);

	size_t cont=0;

	while(cont<size) {
		Record* record=get_element(list, cont);
		printf("Record %ld -- field1:%s field2:%d\n", cont, record->field1, record->field2);
		cont++;
	}
}

static linked_list* merge(linked_list* first_list, linked_list* second_list, int (*compare)(void*, void*), int criterio) {
	linked_list* merge_list=new_linked_list(compare);

	size_t first_cont=0;
	size_t second_cont=0;

	if(criterio==0) {
		while(first_cont<get_length(first_list) || second_cont<get_length(second_list)) {

			if(first_cont==get_length(first_list) && second_cont<get_length(second_list)) {
				while(second_cont<get_length(second_list)) {
					Record* new_record=get_element(second_list, second_cont);
					insert_element_tail(merge_list, new_record);
					second_cont++;
				}

				break;
			}

			if(first_cont<get_length(first_list) && second_cont==get_length(second_list)) {
				while(first_cont<get_length(first_list)) {
					Record* new_record=get_element(first_list, first_cont);
					insert_element_tail(merge_list, new_record);
					first_cont++;
				}

				break;
			}

			if(compare(get_element(first_list, first_cont), get_element(second_list, second_cont))>0) {
				Record* new_record=get_element(second_list, second_cont);
				insert_element_tail(merge_list, new_record);
				second_cont++;
			}

			else {
				Record* new_record=get_element(first_list, first_cont);
				insert_element_tail(merge_list, new_record);
				first_cont++;
			}
		}

		return merge_list;
	}

	while(first_cont<get_length(first_list) || second_cont<get_length(second_list)) {

		if(first_cont==get_length(first_list) && second_cont<get_length(second_list)) {
			while(second_cont<get_length(second_list)) {
				Record* new_record=get_element(second_list, second_cont);
				insert_element_tail(merge_list, new_record);
				second_cont++;
			}

			break;
		}

		if(first_cont<get_length(first_list) && second_cont==get_length(second_list)) {
			while(first_cont<get_length(first_list)) {
				Record* new_record=get_element(first_list, first_cont);
				insert_element_tail(merge_list, new_record);
				first_cont++;
			}

			break;
		}

		if(compare(get_element(first_list, first_cont), get_element(second_list, second_cont))<0) {
			Record* new_record=get_element(second_list, second_cont);
			insert_element_tail(merge_list, new_record);
			second_cont++;
		}

		else {
			Record* new_record=get_element(first_list, first_cont);
			insert_element_tail(merge_list, new_record);
			first_cont++;
		}
	}

	return merge_list;
}

static void test_with_comparison_function(const char* first_file_name, const char* second_file_name, int criterio, int (*compare)(void*, void*)) {
	linked_list* first_list=new_linked_list(compare);
	linked_list* second_list=new_linked_list(compare);
	//caricamento 1
	printf("---CARICAMENTO PRIMA LISTA --\n");
	load_list(first_file_name, first_list, criterio);
	printf("---PRIMA LISTA CARICATA --\n");
	printf("---PRIMA LISTA : \n");
	print_list(first_list);
	printf("-------\n");
	// caricamento 2
	printf("---CARICAMENTO SECONDA LISTA --\n");
	load_list(second_file_name, second_list, criterio);
	printf("---SECONDA LISTA CARICATA --\n");
	printf("---SECONDA LISTA : \n");
	print_list(second_list);
	printf("-------\n");

	//caricamento merge list
	printf("---CARICAMENTO MERGE LIST--\n");
	linked_list* merge_list=merge(first_list, second_list, compare, criterio);
	printf("---MERGE LIST CARICATO--\n");
	printf("---MERGE LIST: \n");
	print_list(merge_list);
	printf("--------\n");


	delete_list(first_list);
	delete_list(second_list);
	delete_list(merge_list);
}

int main(int argc, char const *argv[]) {
	if(argc < 2) {
		printf("Usage: linked_list_main <file_name>\n");
		exit(1);
	}

	int criterio;
	printf("INSERISCI CRITERIO DI ORDINAMENTO (0: CRESCENTE/1: DECRESCENTE): ");
	scanf("%d", &criterio);
	test_with_comparison_function(argv[1], argv[2], criterio, Record_compare1);
	test_with_comparison_function(argv[1], argv[2], criterio, Record_compare2);

	return 0;
}