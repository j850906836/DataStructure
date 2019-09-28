#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct polyNode{
		int coef;
		int expon;
		struct polyNode *link;
}polyPointer;
polyPointer *avail;
polyPointer *pinsert( polyPointer * );
polyPointer *pread(int ,int , polyPointer*);
polyPointer *getNode(void);
void pwrite( polyPointer * );
int main()
{
	polyPointer *a = NULL;
		
	printf("insert polynomail A\n");				//insert polynomial A
	a = pinsert(a);
	
	printf("The OutPut of polynomail A is below\n");	
	pwrite(a);
   
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
		printf("¡iif you are done, insert 'b'¡j/*\ninsert coef: ");	
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
