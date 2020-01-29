
#include "edit_distance.h"
#include "dynamic_array.h"
#include "dynamic_array.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct {
  char* field1;
} Record;

static  Record* Record_new(char* str) {
  Record* record = (Record*) malloc(sizeof(Record));
  record->field1 = str;
  return record;
}
char* rest(char* s){
	return s+1;
}
int minimo(int a,int b,int c){
	if(a<b && a<c) 
		return a;
	if(b<a && b<c )
		return b;
	return c;
}

int edit_distance(char* const s1,char* const s2){
	if(strlen(s1)==0)
		return strlen(s2);
	if(strlen(s2)==0)
		return strlen(s1);
	if(s1[0] == s2[0])
		return edit_distance (rest(s1),rest(s2));
	return 1+minimo(edit_distance(s1,rest(s2)),edit_distance(rest(s1),s2),edit_distance(rest(s1),rest(s2))); // minimo tra inserimento, rimozione e rimpiazzamento
}

/*int main(){
	FILE *f_open;
	FILE *f_open_two;
	char f_char[2],f_char_two[2],f_char_tmp,f_char_two_tmp;
	int m=0;
	char* s1=(char*)malloc(30*sizeof(char));
	
	char* s2=(char*)malloc(30*sizeof(char));
	int n =0;
	
	f_open = fopen("correctme.txt","r");
	f_open_two=fopen("dictionary.txt","r");
	if(f_open==NULL){
		printf("Errore nell'apertura del primo file\n");
		exit(EXIT_FAILURE);	
	}
	if(f_open_two==NULL){
		printf("Errore nell'apertura del secondo file\n");
		exit(EXIT_FAILURE);	
	}
	int (*compare)(void*, void*);
	DynamicArray *first_array=DynamicArray_new(49,compare);
	DynamicArray *second_array=DynamicArray_new(100,compare);
	while((f_char[0]=fgetc(f_open))!=EOF){
		
		
		while(f_char[0]!=' ' && f_char[0]!=EOF){
			if(f_char[0]>='A' && f_char[0]<='z'){
				f_char[0]=tolower(f_char[0]);
				f_char[1]='\0';
				strcat(s1,f_char);
				
			}
			f_char[0]=fgetc(f_open);
		}
		Record* record = Record_new(s1);
		DynamicArray_insert_queue(first_array,record);
		
		
		
		s1=(char*)malloc(30*sizeof(char));
	
	} 
	fclose(f_open);
	while((f_char_two[0]=fgetc(f_open_two))!=EOF){
			while(f_char_two[0]!='\n' && f_char_two[0]!=EOF){
				
				f_char_two[1]='\0';
				strcat(s2,f_char_two);
				f_char_two[0]=fgetc(f_open_two);
			}
		Record* record2 = Record_new(s2);
		DynamicArray_insert_queue(second_array,record2);
		
		s2=(char*)malloc(30*sizeof(char));
	}
	fclose(f_open_two);

    DynamicArray* edit_array=DynamicArray_new(50,compare);
	int cont1=0,cont2,edit_min=26;
	while (cont1<DynamicArray_size(first_array)){
		Record* prima_parola=DynamicArray_at(first_array,cont1);
		
		cont2=0;
		
		while(cont2<DynamicArray_size(second_array)){
			
			Record* seconda_parola=DynamicArray_at(second_array,cont2);
			
			
			int edit_curr=edit_distance(prima_parola->field1,seconda_parola->field1);
			if(edit_curr<edit_min && DynamicArray_size(edit_array)==0){
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=edit_curr;
			}
			else if(edit_curr==edit_min){
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=edit_curr;
			}
			else if(edit_curr<edit_min && DynamicArray_size(edit_array)>0){
				DynamicArray_free(edit_array);
				edit_array=DynamicArray_new(50,compare);
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=edit_curr;
			}
			cont2++;
			
			
		}
	if(edit_min!=0){
	printf("Parole con distanza minima da %s  sono %ld con distanza %d \n",prima_parola->field1,DynamicArray_size(edit_array),edit_min);
	
	
		for(size_t contatore=0;contatore<DynamicArray_size(edit_array);contatore++){
			Record* rec =DynamicArray_at(edit_array,contatore); 
			printf("Parola: %s\n",rec->field1);
		}
	}
	edit_min=26;
	DynamicArray_free(edit_array);
	edit_array=DynamicArray_new(50,compare);
	cont1++;
	
	}
		
	return 0;


}
*/

