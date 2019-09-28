#include <stdio.h>
#define MAX_TERMS 101

typedef struct{
		int col;
		int row;
		int value;
} term;
typedef struct{
		int rowTerms;
		int startingPos;
} comb;
void fastTranspose(term a[] , term b[]);
int main()
{
	term a[MAX_TERMS];
	term b[MAX_TERMS];
	int i = 0 , j = 0;
	char tmp;

	a[0].row = 6;
	a[1].row = 0;
	a[2].row = 0;
	a[3].row = 0;
	a[4].row = 1;
	a[5].row = 1;
	a[6].row = 2;
	a[7].row = 4;
	a[8].row = 5;
	a[0].col = 6;
	a[1].col = 0;
	a[2].col = 3;
	a[3].col = 5;
	a[4].col = 1;
	a[5].col = 2;
	a[6].col = 3;
	a[7].col = 0;
	a[8].col = 2;
	a[0].value = 8;
	a[1].value = 15;
	a[2].value = 22;
	a[3].value = -15;
	a[4].value = 11;
	a[5].value = 3;
	a[6].value = -6;
	a[7].value = 91;
	a[8].value = 28;
	fastTranspose(a,b);
	printf("\trow\tcol\tvalue\t\t\trow\tcol\tvalue\n");
	for( i=0; i<9; i++ ){
	printf("a[%d]\t%d\t%d\t%d\t\tb[%d]\t%d\t%d\t%d\n",i,a[i].row,a[i].col,a[i].value,i,b[i].row,b[i].col,b[i].value);
	}
	return 0;
}
void fastTranspose( term a[] , term b[] )
{
	comb trans[MAX_TERMS];int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];
	int i,j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;

	if(numTerms > 0){
		for( i=0; i<numCols; i++ )
				trans[i].rowTerms = 0;
		for( i=1; i<=numTerms; i++ )
				trans[a[i].col].rowTerms++;
		trans[0].startingPos = 1;
		for( i=1; i<numCols; i++ )
				trans[i].startingPos = trans[i-1].startingPos + trans[i-1].rowTerms;
		for( i=1; i<=numTerms; i++ ){
				j = trans[a[i].col].startingPos++;
				b[j].row = a[i].col;
				b[j].col = a[i].row;
				b[j].value = a[i].value;
		}
	}
}
