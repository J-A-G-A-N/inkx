#include <stdio.h>

void clearfile(){
	FILE *fptr = fopen("error.txt","w+");
	fputc('\n',fptr);
	fclose(fptr);
}

void perrorfile(char * message){
	FILE *fptr = fopen("error.txt","a+");
	fputs(message,fptr);
	fclose(fptr);
}

