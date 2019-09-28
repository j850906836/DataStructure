#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define IN 1
#define OUT 0
typedef struct polyNode{
		int coef;
		int expon;
		struct polyNode *link;
}polyPointer;
polyPointer *avail;
polyPointer *pmult( polyPointer* , polyPointer* );
polyPointer *psub( polyPointer* , polyPointer* );
polyPointer *pinsert( polyPointer * );
polyPointer *pread(int ,int , polyPointer*);
void cerase(polyPointer *);
polyPointer *getNode(void);
void attach(int , int , polyPointer ** );
void retNode(polyPointer *);
int COMPARE( int , int );
void pwrite( polyPointer * );
int main()
{
	polyPointer *a=NULL , *b=NULL , *c , *eraceC;
		
	printf("insert polynomail A\n");				//insert polynomial A
	a = pinsert(a);
	
	printf("insert polynomail B\n");			//insert polynomial B
	b = pinsert(b);
	printf("The OutPut of polynomail A is below\n");	
	pwrite(a);
   	printf("\n\nThe OutPut of polynomail B is below\n");	
	pwrite(b);
	

	c = pmult( a ,b );
	printf("\n\nThe OutPut of polynomail C( A*B ) is Below\n");

	pwrite(c);

	eraceC = c;

	cerase(eraceC);
	c = psub( a , b );

	printf("\n\nThe OutPut of polynomial C( A-B ) is Below\n");
	pwrite(c);

	return 0;
}
polyPointer *pinsert(polyPointer *ptr)
{
	polyPointer *header , *temp;
	int co , ex;
	char tmp[10], tmp1[10];
	printf("please insert exponent in a decending way\n");
	printf("insert coef: ");
	while( fgets(tmp , 10 , stdin) ) {
		if( tmp[0] == 'b' )
			break;	
		printf("insert expon: ");
		fgets(tmp1 , 10 , stdin);
		printf("*/if you are done, insert 'b'/*\ninsert coef: ");	
		co = atoi(tmp);
		ex = atoi(tmp1);
		ptr = pread( co , ex , ptr );
		
		memset( tmp , 0 , sizeof(tmp) );
		memset( tmp1 , 0 , sizeof(tmp1) );
	}
	printf("\n");
	header = temp = ptr;
	while( temp != NULL ) {
		if( temp->link == NULL ) {
			temp->link = header;
			break;
		}
		temp = temp->link;
	}
	return ptr;
}
polyPointer *pread( int co , int ex , polyPointer* list)
{
	polyPointer *ptr , *newp;
	newp = getNode();
	newp->coef = co;
	newp->expon = ex;

	if( list == NULL ) {
		list = getNode();
		list->expon = -1;	
		list->link = newp;
	}
	else {
		ptr = list;	
		while( ptr != NULL ) {
	
			if( ptr->link == NULL ) {
				ptr->link = newp;
				break;
			}
			ptr = ptr->link;
		}
	}
	return list;
}
polyPointer *pmult( polyPointer* a , polyPointer* b )
{
	polyPointer *header_a , *header_b , *header_c , *ptr_a , *ptr_b , *ptr_c , *c = NULL, *first , *lastp; 
	int state, instate;
	header_a = a;
	header_b = b;
	a = ptr_a = a->link;
	b = ptr_b = b->link;
	first = getNode();
	first->coef = a->coef*b->coef;
	first->expon = a->expon+b->expon;
	
	b = b->link;
	if( c == NULL ) 
		c = getNode();	
	header_c = c;
	c->expon = -1;
	c->link = first;
	instate = OUT;
	while( a != header_a ) {
		while( b != header_b ) {	
			polyPointer *newp;
			newp = getNode();	
			newp->coef = a->coef*b->coef;
			newp->expon = a->expon+b->expon;
			ptr_c = lastp = c->link;
			state = FALSE;
			instate = IN;
			while( ptr_c->expon > newp->expon ) {
					lastp = ptr_c;
					if( ptr_c->link == NULL ) {
							state = TRUE;
							break;
					}
					ptr_c = ptr_c->link;
			}
		
			if( state == TRUE ) 
				ptr_c->link = newp;	
			else if( ptr_c->expon == newp->expon ) {
				lastp = c;
				while( c != ptr_c ) {
					c = c->link;
				}
				c->coef = c->coef + newp->coef;
				c = lastp;
			}
			else if( ptr_c->expon < newp->expon ) {
				lastp->link = newp;
				newp->link = ptr_c;
			}
			b = b->link;
		}
	
		a = a->link;
		b = b->link;
	}
	if( instate == IN ) {
		ptr_c = ptr_c->link;
		ptr_c->link = header_c;
	}
	else {
		c = c->link;
		c->link = header_c;
		c = c->link;
	}
	return c;

}
polyPointer *psub( polyPointer *a , polyPointer *b )
{
	polyPointer *startA	, *c , *lastC;
	int sum , done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1;
	lastC = c;
	do {
		switch (COMPARE(a->expon , b->expon)) {
				case -1:
						attach((b->coef)*-1,b->expon,&lastC);
						b = b->link;
				case 0:
						if( startA == a ) done = TRUE;
						else {
							sum = a->coef - b->coef;
							if (sum != 0)
								attach(sum,a->expon,&lastC);
							a = a->link;
							b = b->link;
						}
						break;
				case 1:
						attach(a->coef,a->expon,&lastC);
						a = a->link;
		}
	} while(!done);
	lastC->link = c;
	return c;
}
int COMPARE( int a , int b )
{
	if( a>b )
		return 1;
	if( a==b )
		return 0;
	else
		return -1;
}
void attach(int co , int ex , polyPointer **ptr )
{
	polyPointer *temp;	
	temp = getNode();
	temp->coef = co;
	temp->expon = ex;
	(*ptr)->link = temp;
	*ptr = temp;
}
void cerase(polyPointer *ptr)
{
	polyPointer *temp;
//	printf("in\n");
	if(ptr) {
		temp = ptr->link;
		ptr->link = avail;
		avail = temp;
		ptr = NULL;
	}
}
polyPointer *getNode(void)
{
	polyPointer *node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else
		node = (polyPointer*) malloc(sizeof(polyPointer));	

	return node;
}
void retNode(polyPointer *node)
{
	node->link = avail;
	avail = node;
}
void pwrite(polyPointer* list)
{
	polyPointer *header;	
	header = list;	
	if( list->link == NULL ) {
			printf("this list only has header\n");
			return;
	}
	list = list->link;

	printf("coef |");
	while( list != header ) {
		printf("  %2d  |",list->coef);
		list = list->link;
	}
	list = list->link;
	printf("\nexpon|");
	while( list != header ) {
		printf("  %2d  |",list->expon);
		list = list->link;
	}
	printf("\n");
}
