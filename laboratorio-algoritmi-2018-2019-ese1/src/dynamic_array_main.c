#include "dynamic_array.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* field1;
    int field2;
}Record;

// Funzione che implementa una relazione d'ordine in
// base al valore della stringa tra i record
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

// Funzione che implementa una relazione d'ordine per il valore intero tra i record
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

static void load_array(const char* file_name, DynamicArray* array, int criterio) {
    FILE* file=fopen(file_name, "r");
    assert(file !=NULL);
    char buf[128];

    if(criterio==0) {
        while( !feof(file)) {
            int num;
            int num_fields=fscanf(file, "%127[^,],%d\n", buf, &num);
            assert(num_fields==2);

            Record* record=Record_new(strdup(buf), num);
            DynamicArray_insert_asc(array, record);

        }

        return;
    }

    while( !feof(file)) {
        int num;
        int num_fields=fscanf(file, "%127[^,],%d\n", buf, &num);
        assert(num_fields==2);

        Record* record=Record_new(strdup(buf), num);
        DynamicArray_insert_desc(array, record);
    }
}

static void print_array(DynamicArray* array) {
    size_t size=DynamicArray_size(array);

    for(size_t index=0; index<size; ++index) {
        Record* record=DynamicArray_at(array, index);
        printf("Record %ld -- field1:%s field2:%d\n", index, record->field1, record->field2);
    }
}

static void free_array(DynamicArray* array) {
    size_t size=DynamicArray_size(array);

    for(size_t index=0; index<size; ++index) {
        Record* record=DynamicArray_at(array, index);
        free(record->field1);
        free(record);
    }

    DynamicArray_free(array);
}

DynamicArray* merge(DynamicArray* first_array, DynamicArray* second_array, int (*compare)(void*, void*), int criterio) {
    size_t cont=0;
    size_t first_cont=0;
    size_t second_cont=0;
    size_t max=(DynamicArray_size(first_array))+(DynamicArray_size(second_array));
    DynamicArray* result=DynamicArray_new(DynamicArray_capacity(first_array)+DynamicArray_capacity(second_array), compare);

    if(criterio==0) {
        while(cont<max) {
            if(first_cont==DynamicArray_size(first_array) && second_cont<DynamicArray_size(second_array)) {
                while(second_cont<DynamicArray_size(second_array)) {
                    Record* new_record=DynamicArray_at(second_array, second_cont);
                    DynamicArray_insert_queue(result, new_record);
                    second_cont++;
                }

                break;
            }

            if(first_cont<DynamicArray_size(first_array) && second_cont==DynamicArray_size(second_array)) {
                while(first_cont<DynamicArray_size(first_array)) {
                    Record* new_record=DynamicArray_at(first_array, first_cont);
                    DynamicArray_insert_queue(result, new_record);
                    first_cont++;
                }

                break;
            }

            if(compare((DynamicArray_at(first_array, first_cont)), (DynamicArray_at(second_array, second_cont)))>0) {
                Record* new_record=DynamicArray_at(second_array, second_cont);
                DynamicArray_insert_queue(result, new_record);
                second_cont++;
            }

            else {
                Record* new_record=DynamicArray_at(first_array, first_cont);
                DynamicArray_insert_queue(result, new_record);
                first_cont++;
            }

            cont++;
        }

    }

    else {
        while(cont<max) {
            if(first_cont==DynamicArray_size(first_array) && second_cont<DynamicArray_size(second_array)) {
                while(second_cont<DynamicArray_size(second_array)) {
                    Record* new_record=DynamicArray_at(second_array, second_cont);
                    DynamicArray_insert_queue(result, new_record);
                    second_cont++;
                }

                break;
            }

            if(first_cont<DynamicArray_size(first_array) && second_cont==DynamicArray_size(second_array)) {
                while(first_cont<DynamicArray_size(first_array)) {
                    Record* new_record=DynamicArray_at(first_array, first_cont);
                    DynamicArray_insert_queue(result, new_record);
                    first_cont++;
                }

                break;
            }

            if(compare((DynamicArray_at(first_array, first_cont)), (DynamicArray_at(second_array, second_cont)))<0) {
                Record* new_record=DynamicArray_at(second_array, second_cont);
                DynamicArray_insert_queue(result, new_record);
                second_cont++;
            }

            else {
                Record* new_record=DynamicArray_at(first_array, first_cont);
                DynamicArray_insert_queue(result, new_record);
                first_cont++;
            }

            cont++;
        }
    }

    return result;
}

static void test_with_comparison_function(const char* first_file_name, const char* second_file_name, int criterio, int (*compare)(void*, void*)) {
    DynamicArray* first_array=DynamicArray_new(10, compare);
    DynamicArray* second_array=DynamicArray_new(10, compare);

    //caricamento del primo array dal primo file
    printf("---CARICAMENTO PRIMO ARRAY --\n");
    load_array(first_file_name, first_array, criterio);
    printf("---PRIMO ARRAY CARICATO --\n");
    printf("---PRIMO ARRAY: \n");
    print_array(first_array);
    printf("-------\n");

    //caricamente del secondo array dal secondo file
    printf("---CARICAMENTO SECONDO ARRAY --\n");
    load_array(second_file_name, second_array, criterio);
    printf("---SECONDO ARRAY CARICATO --\n");
    printf("---SECONDO ARRAY: \n");
    print_array(second_array);
    printf("-------\n");
    printf("CARICAMENTO ARRAY UNITO\n");
    DynamicArray* merge_array=merge(first_array, second_array, compare, criterio);
    printf("ARRAY UNITO CARICATO \n");
    printf("ARRAY MERGED: \n");
    print_array(merge_array);
    printf("-----------\n");

    DynamicArray_free(first_array);
    DynamicArray_free(second_array);
    DynamicArray_free(merge_array);
}



int main(int argc, char const *argv[]) {
    if(argc < 2) {
        printf("Usage: dynamic_array_main <file_name>\n");
        exit(1);
    }

    int criterio;
    printf("INSERISCI CRITERIO DI ORDINAMENTO (0: CRESCENTE/1:DECRESCENTE): ");
    scanf("%d", &criterio);
    test_with_comparison_function(argv[1], argv[2], criterio, Record_compare1);
    test_with_comparison_function(argv[1], argv[2], criterio, Record_compare2);

    return 0;
}