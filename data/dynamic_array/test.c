#include <stdio.h>
#include "dynamicarray.h"


int main(){
	Dynamic_array* DA1 = CreateDA(1);
	Dynamic_array* DA2 = CreateDA(1);
	int val1 = 1 ; 
	int val2 = 2 ; 

	printf("DA1->size before Insertion : %d\n",DA1->size);
	InsertSDA(DA1,0, val1) ; 
	printf("DA1->size after Insertion : %d\n",DA1->size);
	for (int i = 0; i < DA1->size; i++){
		printf("DA1->aptr[%d] = %d\n",i,DA1->aptr[i]);
	}
	printf("\n");
	printf("DA2->size before Insertion : %d\n",DA2->size);
	InsertSDA(DA2,0, val2) ; 
	printf("DA2->size after Insertion : %d\n",DA2->size);
	for (int i = 0; i < DA2->size; i++){
		printf("DA2->aptr[%d] = %d\n",i,DA2->aptr[i]);
	}
	printf("\n");
	Dynamic_array* DA3 = JoinDA(DA1, DA2);
	for (int i = 0; i < DA3->size; i++){
		printf("DA3->aptr[%d] = %d\n",i,DA3->aptr[i]);
	}
	DestroyDA(DA1);
	DestroyDA(DA2);
	DestroyDA(DA3);
	
	return 0 ; 

}
