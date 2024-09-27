#include "dynamicarray.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dynamic_array* CreateDA(uint16_t initial_size){
	
	/*
		Allocate Dynamic Array and aptr in Heap
	*/
	if (initial_size <=0){
		printf("Invalid size.");
		exit(-1);
	}
	Dynamic_array* DA = malloc(sizeof(Dynamic_array));
	if(!DA){
		printf("Cannot allocate memory for Dynamic Array");
		return NULL ;
	}

	DA->capacity = 	initial_size;
	DA->size = 0;

	DA->aptr = malloc(sizeof(int)*DA->capacity);

	if(!DA->aptr){
		printf("Cannot allocate memory for Dynamic Array");
		free(DA);
		return NULL ;
	}

	return DA; 
}



Dynamic_array* GrowDA(Dynamic_array* DA, uint16_t incremental_size) {
	if(!DA) return NULL;
    int reallocation_size = DA->capacity + ((incremental_size > DA->capacity) ? incremental_size : DA->capacity);

    // Reallocate the array to the new size
    int* temp = realloc(DA->aptr, sizeof(int)*reallocation_size);
    if (!temp) {
        perror("Reallocation failed");
        return NULL;  // Return NULL to signal failure
    }
    // Update the aptr and capacity with the new allocation
    DA->aptr = temp;
    DA->capacity = reallocation_size;

    return DA;  // Return the reallocated dynamic array
}



bool InsertSDA(Dynamic_array* DA, uint32_t index, int value){
	if (index > DA->capacity){
		return false;
	}

	if (DA->size + 1 > DA->capacity){
		if (!GrowDA(DA, DA->capacity / 2)){
			return false;
		}
	}

	//memmove(DA->aptr + index + strlength, DA->aptr + index, DA->size - index +1);
	memmove(DA->aptr + index + 1 , DA->aptr + index, (DA->size - index) * sizeof(int));
	
	DA->aptr[index] = value;
	DA->size += 1; 
	return true;
}



void clearDA(Dynamic_array* DA){
	if (!DA) return;
	memset(DA->aptr,'\0',DA->capacity);
	DA->size = 0;

}



Dynamic_array* JoinDA(Dynamic_array* DA1,Dynamic_array* DA2){
	
	{
		if (!DA1 || !DA2) return NULL;
		if (DA1->capacity + DA2->capacity <=0){
			printf("Invalid size.");
			exit(-1);
		}

	}

	Dynamic_array* finalDA = CreateDA(DA1->capacity+DA1->capacity);
	if (!finalDA) return NULL;

	memcpy(finalDA->aptr, DA1->aptr, DA1->size);

	memcpy(finalDA->aptr + DA1->size, DA2->aptr, DA2->size);

	finalDA->size = DA1->size + DA2->size;

	return finalDA;
}



void DestroyDA(Dynamic_array* DA){
	free(DA->aptr);
	free(DA);
}

