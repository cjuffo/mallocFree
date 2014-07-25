

struct block
{
	int length ;
	struct block  * next ;
    struct block * first;
    int status;
} ;


struct block * memblock ;

void mallocinit(int size);
void * mymalloc(int size);
void myfree(void * p);
