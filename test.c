
// cjuffo


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

#define FREE_MEM_LEN 0x100000
#define FREE 0
#define USED 1



int main(int argc, char * argv[]) {
	void * p[5];
	int i ;
	struct block * fl;
	char * status;


	mallocinit(FREE_MEM_LEN) ;
	printf("\n");
	printf("\t******************* MYMALLOC ******************\n");
	for ( i=0; i<5; i++ ) {
		p[i] = mymalloc(4); //bytes
		printf("Allocating Memory...\n");
		printf("Address %d:\t%p\n", i,p[i]);
	}
	printf("\n");
	printf("\t************* PRINTING BLOCKS **************\n");
	fl=memblock->first;
	while(fl){
		if(fl->status==FREE)
			status="FREE";
		else
			status="USED";
		printf("Address: %p\t\n", fl);
		printf("Size\t: %d bytes\t\n", fl->length);
		printf("Status\t: %s\t\n",status);
		printf("\n");
		fl=fl->next;
	}
	

	printf("\n");
	printf("\t******************* MYFREE ******************\n");
	for ( i=0; i<5; i++ ) {
		myfree(p[i]);
		printf("Freeing Memory...\n");
		printf("Address %d:\t%p\n", i,p[i]);
	}
	
	printf("\n");
	printf("\t************* PRINTING BLOCKS **************\n");
	fl=memblock->first;
	while(fl){
		if(fl->status==FREE)
			status="FREE";
		else
			status="USED";
		printf("Address: %p\t\n", fl);
		printf("Size\t: %d bytes\t\n", fl->length);
		printf("Status\t: %s\t\n",status);
		printf("\n");
		fl=fl->next;
	}

	return 0 ;
}


