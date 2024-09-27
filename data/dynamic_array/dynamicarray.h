#ifndef	DYNAMICARRAY_H
#define DYNAMICARRAY_H	
 

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	uint32_t capacity;
	uint32_t size;
	int *aptr;
}Dynamic_array;


Dynamic_array* CreateDA(uint16_t initial_size);
Dynamic_array* GrowcDA(Dynamic_array* DA, uint16_t incremental_size);
Dynamic_array* ShrinkDA(Dynamic_array* DA, uint16_t decremental_size);
Dynamic_array* JoinDA(Dynamic_array* DA1,Dynamic_array* DA2);
bool InsertSDA(Dynamic_array* DA, uint32_t index, int INDEX);
void clearDA(Dynamic_array* DA);
void DestroyDA(Dynamic_array* DA);

#endif // DYNAMICARRAY_H  
