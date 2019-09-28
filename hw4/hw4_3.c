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
polyPointer *pinsert( polyPointer * );
polyPointer *pread(int ,int , polyPointer*);
void eval( polyPointer *c , float x );
polyPointer *getNode(void);
void pwrite( polyPointer * );
int main()
{
	polyPointer *a = NULL , *b = NULL , *c;
	float x;	
	printf("insert polynomail A\n");				//insert polynomial A
	a = pinsert(a);
	
	printf("insert polynomail B\n");			//insert polynomial B
	b = pinsert(b);
	printf("The OutPut of polynomail A is below\n");	
	pwrite(a);
   	printf("\n\nThe OutPut of polynomail B is below\n");	
	pwrite(b);
	

	c = pmult( a ,b );
	pwrite(c);
	printf("X =  ");
	scanf("%f",&x);
	eval( c , x );

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
		printf("¡iif you are done, insert 'b'¡j\ninsert coef: ");	
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
void eval( polyPointer *c , float x )
{
	polyPointer *header;
	float sum=0, temp = x;
	int i;

	header = c;
	c = c->link;
	while( c != header ) {
		if( c->expon == 0 ) {
			sum += c->coef;
			c = c->link;
			continue;
		}
		for( i=0; i<c->expon-1; i++ )
			temp *= temp;
		temp = c->coef * temp;
		sum += temp;
		temp = x;
		c = c->link;
	}
	printf("The answer is :%.2f\n",sum);
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
