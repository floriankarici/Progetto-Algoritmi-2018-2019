#include "edit_distance_dyn.h"
//#include "dynamic_array.h"
//#include "dynamic_array.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char* field1;
} Record;


int minimum(int a,int b,int c){
	int min=a;
	if(b<min) 
		min=b;
	if(c<min)
		min=c;
	return min;
}
//viene usata per riempire ogni cella riga corrente
void edit_distance_dyn_j(char* s1,char* s2,int**d, int m, int n,int i,int j){
	if(j==n+1)
		return;
	if(s1[i-1]==s2[j-1])
		d[i][j]=d[i-1][j-1];
	else {
		int k=minimum(d[i][j-1],d[i-1][j],d[i-1][j-1]);
		d[i][j]=k+1;
	}
	edit_distance_dyn_j(s1,s2,d,m,n,i,j+1);
}

//viene chiamata in ricorsione per inserire i dati all’interno delle righe della
//matrice
void edit_distance_dyn(char* s1,char* s2,int** d,int m,int n, int i){
	if(i==m+1)
		return;
	edit_distance_dyn_j(s1,s2,d,m,n,i,1);
	edit_distance_dyn(s1,s2,d,m,n,i+1);
	
}
static  Record* Record_new(char* str) {
  Record* record = (Record*) malloc(sizeof(Record));
  record->field1 = str;
  return record;
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
		Record *r1=DynamicArray_at(first_array,DynamicArray_size(first_array)-1);
		
		
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
	Record *r1=DynamicArray_at(second_array,0);
	Record* s=DynamicArray_at(first_array,0);
	
	
	
	printf("%ld\n",DynamicArray_size(first_array));
	printf("%ld\n",DynamicArray_size(second_array));
	DynamicArray* edit_array=DynamicArray_new(50,compare);
	int cont1=0,cont2,edit_min=26;
	while (cont1<DynamicArray_size(first_array)){
		Record* prima_parola=DynamicArray_at(first_array,cont1);
		
		int m=strlen(prima_parola->field1);
		
		cont2=0;
		
		while(cont2<DynamicArray_size(second_array)){
			
			Record* seconda_parola=DynamicArray_at(second_array,cont2);
			
			int n=strlen(seconda_parola->field1);
			
			int i, j;
			int **d = (int**) malloc((m + 1) * sizeof(int*));

			for(i = 0; i <= m; i++)
	      			d[i] = (int*) malloc((n + 1) * sizeof(int));
			for(i = 0; i <= m; i++)
				d[i][0] = i;

			for(j = 1; j <= n; j++)
				d[0][j] = j;

			edit_distance_dyn(prima_parola->field1,seconda_parola->field1,d,m,n,1);
			if(d[m][n]<edit_min && DynamicArray_size(edit_array)==0){
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=d[m][n];
			}
			else if(d[m][n]==edit_min){
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=d[m][n];
			}
			else if(d[m][n]<edit_min && DynamicArray_size(edit_array)>0){
				DynamicArray_free(edit_array);
				edit_array=DynamicArray_new(50,compare);
				Record* rec = Record_new(seconda_parola->field1);
				DynamicArray_insert_queue(edit_array,rec);
				edit_min=d[m][n];
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

