#pragma once

#include<stddef.h>

int minimum(int a,int b,int c);

void edit_distance_dyn_j(char* s1,char* s2,int**d, int m, int n,int i,int j);

void edit_distance_dyn(char* s1,char* s2,int** d,int m,int n, int i);
