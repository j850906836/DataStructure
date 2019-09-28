#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef enum {head,entry} tagfield;

typedef struct {
		int row;
		int col;
		int value;
		int change;
}entryNode;
typedef struct matrixNode {
		struct matrixNode *down;
		struct matrixNode *right;
		tagfield tag;
		union {
			struct matrixNode *next;
			entryNode entry;
		} u;
}matrixPointer;
matrixPointer *mread(void);
matrixPointer *mmult(matrixPointer * , matrixPointer *);
void mwrite(matrixPointer *node);
matrixPointer *hdnode[MAX_SIZE];
int main()
{
	matrixPointer *a=NULL , *b=NULL, *c;
	a = mread();
	b = mread();
//	mwrite(a);
//	mwrite(b);
	c = mmult(a,b);
	mwrite(c);
	return 0;
}
matrixPointer *mread(void)
{
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrixPointer *temp, *last, *node;

	printf("Enter the number of rows, columns and number of nonzero terms: ");
	scanf("%d%d%d",&numRows, &numCols, &numTerms);
	numHeads = (numCols > numRows) ? numCols : numRows;
	node = (matrixPointer*) malloc(sizeof(matrixPointer));
	node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;

	if( !numHeads )
			node->right = node;
	else {
		for( i=0; i<numHeads; i++ ) {
			temp = (matrixPointer*) malloc(sizeof(matrixPointer));
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];
		for( i=0; i<numTerms; i++ ) {
			printf("Enter row, column and value: ");
			scanf("%d%d%d", &row, &col, &value);
			if (row>currentRow) {
				last->right = hdnode[currentRow];
				currentRow = row;
				last = hdnode[row];
			}
			temp = (matrixPointer*) malloc(sizeof(matrixPointer));
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;

			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[currentRow];
		for( i=0; i<numCols; i++ )
			hdnode[i]->u.next->down = hdnode[i];
		for( i=0; i<numHeads-1; i++ )
			hdnode[i]->u.next = hdnode[i+1];
		hdnode[numHeads-1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}
matrixPointer *mmult(matrixPointer *a , matrixPointer *b)
{
	matrixPointer *temp_a , *temp_b , *head_a = a->right , *head_b = b->right;

	if( a->u.entry.col != b->u.entry.row ){
		printf("error !! matrixA cant multiple matrixB\n");
		return NULL;
	}
	else {
	 	for( temp_a = head_a->right; temp_a !=head_a; temp_a = temp_a->right ) {
			for( temp_b =  head_b->right; temp_b != head_b; temp_b = temp_b->right ) {
				if( temp_a->u.entry.col == temp_b->u.entry.row ) {
					temp_b->u.entry.value = temp_a->u.entry.value*temp_b->u.entry.value;
					temp_b->u.entry.change = 1;
				}			
			}
		}
	}
	return b;
}

void mwrite(matrixPointer *node)
{
	int i;
	matrixPointer *temp, *head = node->right;

	printf(" \n numRows = %d, & numCols = %d \n", node->u.entry.row, node->u.entry.col);
	printf(" The matrix by row, column, and value: \n\n");
	for (i=0; i<node->u.entry.row; i++) {
		for( temp = head->right; temp != head; temp = temp->right){
			if( temp->u.entry.change == 1 )	
			printf("%5d%5d%5d \n",temp->u.entry.row,temp->u.entry.col, temp->u.entry.value);
		}
		head = head->u.next;
	}
}
