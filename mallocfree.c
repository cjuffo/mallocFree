
//  cjuffo
//  MyMalloc and MyFree
//  Implements my own version of malloc and free


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FREE_MEM_LEN 0x100000
#define FREE 0
#define USED 1


struct block
{
	int length ;
	struct block  * next ;
    	struct block * first;
    	int status;
} ;


struct block * memblock ;
//struct block * lastblock;

void mallocinit(int size)
{
	memblock = (struct block *) sbrk(size) ;
	memblock->length = size ;
	memblock->next = NULL ;
    	memblock->first = memblock;
    	memblock->status = FREE;
	return  ;
}

void * mymalloc(int size)
{
	struct block * fl ;
	int i = size + sizeof(struct block) ;
	if (size<2)
        	return NULL ;
	if (memblock->length<i )
        	return NULL ;
	fl = memblock ;
    	fl->first=memblock->first;
	memblock = (struct block *) ((char *)memblock) + i ;
	memblock->next = NULL ;
	memblock->first=fl->first;
	fl->next = memblock;
	memblock->length = fl->length - i ;
	fl->length = i ;
    	fl->status = USED;
	return (void *) (fl)+sizeof(struct block); 
}

void myfree(void * p)
{
	struct block * fl ;
	struct block * before= NULL; //to check blocks before
	struct block * after=NULL;	//to check after
	fl = memblock->first;
	while (fl) 
	{
		if((p-sizeof(struct block))==fl)
		{
			after = fl->next;
			break;
		}
		else
		{
			before = fl;
			fl = fl->next;
		}
	}

	if(fl != NULL)
	{
		p=NULL;
		fl->status=FREE;
	}
	
	if(before!=NULL && before->status==FREE)
	{
		before->next = fl->next;
		//merge and combine lengths
		before->length = before->length + fl->length;
		fl = before;
		fl->status = FREE;
	}

	if(after!=NULL)
	{
		if(after==memblock)
		{
			fl->length= fl->length + memblock->length;
			fl->next= memblock->next;
			if(fl==memblock->first)
			{
				fl->first = memblock->first;
			}
			memblock = fl;
		}
		else if(after->status==FREE)
		{
			fl->next = after->next;
			fl->status = FREE;
			fl->length= fl->length + after->length;
			after=NULL;	
		}
	}
}


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


