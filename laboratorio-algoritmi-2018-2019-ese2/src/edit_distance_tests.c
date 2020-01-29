#include "unity.h"
#include "unity_internals.h"
#include "edit_distance.h"
#include "edit_distance_dyn.h"

#include <stdlib.h>
#include <string.h>

int compare_int_ptr(void* elem1, void* elem2) {
    int int1=*(int*) elem1;
    int int2=*(int*) elem2;

    if(int1==int2) {
        return 0;
    }

    if(int1 < int2) {
        return -1;
    }

    return 1;
}

static int* new_int(int value) {
    int* elem=(int*) malloc(sizeof(int));
    *elem=value;
    return elem;
}

static char* build_fixture(char* new_string) {
    char* s1=new_string;
    return s1;
}


static void free_fixture(char* s1) {
    free(s1);

}

static void test_two_element() {
    char* s1=build_fixture("tassa");
    char* s2=build_fixture("passato");
    TEST_ASSERT_EQUAL_INT(3, edit_distance(s1, s2));
}

static void test_two_element_dyn() {
    char* s1=build_fixture("tassa");
    char* s2=build_fixture("passato");
    int m=strlen(s1);
    int n=strlen(s2);
    int i,
    j;
    int **d=(int**) malloc((m + 1) * sizeof(int*));

    for(i=0; i <=m; i++) d[i]=(int*) malloc((n + 1) * sizeof(int));
    for(i=0; i <=m; i++) d[i][0]=i;

    for(j=1; j <=n; j++) d[0][j]=j;
    edit_distance_dyn(s1, s2, d, m, n, 1);
    TEST_ASSERT_EQUAL_INT(3, d[m][n]);
}

static void test_with_empty_element() {
    char* s1=build_fixture("casa");
    char* s2=build_fixture("");
    TEST_ASSERT_EQUAL_INT(4, edit_distance(s1, s2));

}

static void test_with_empty_element_dyn() {
    char* s1=build_fixture("casa");
    char* s2=build_fixture("");
    int m=strlen(s1);
    int n=strlen(s2);
    int i,
    j;
    int **d=(int**) malloc((m + 1) * sizeof(int*));

    for(i=0; i <=m; i++) d[i]=(int*) malloc((n + 1) * sizeof(int));
    for(i=0; i <=m; i++) d[i][0]=i;

    for(j=1; j <=n; j++) d[0][j]=j;
    edit_distance_dyn(s1, s2, d, m, n, 1);
    TEST_ASSERT_EQUAL_INT(4, d[m][n]);
}

static void test_two_different_element() {
    char* s1=build_fixture("casa");
    char* s2=build_fixture("vonoo");
    TEST_ASSERT_EQUAL_INT(5, edit_distance(s1, s2));

}

static void test_two_different_element_dyn() {
    char* s1=build_fixture("casa");
    char* s2=build_fixture("vonoo");
    int m=strlen(s1);
    int n=strlen(s2);
    int i,
    j;
    int **d=(int**) malloc((m + 1) * sizeof(int*));

    for(i=0; i <=m; i++) d[i]=(int*) malloc((n + 1) * sizeof(int));
    for(i=0; i <=m; i++) d[i][0]=i;

    for(j=1; j <=n; j++) d[0][j]=j;
    edit_distance_dyn(s1, s2, d, m, n, 1);
    TEST_ASSERT_EQUAL_INT(5, d[m][n]);

}


int main() {
    UNITY_BEGIN();
    RUN_TEST(test_two_element);
    RUN_TEST(test_with_empty_element);
    RUN_TEST(test_two_different_element);
    RUN_TEST(test_two_element_dyn);
    RUN_TEST(test_with_empty_element_dyn);
    RUN_TEST(test_two_different_element_dyn);
    UNITY_END();
    return 0;
}