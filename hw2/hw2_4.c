#include <stdio.h>
#define COL 10
#define ROW 10
#define MAX_TERM 100
int main()
{
	char a_sparse[6][6] = {0} , a_value[8] = {0} , b_sparse[6][6] = {0} , b_value[MAX_TERM] = {0} , d_sparse[6][6] = {0} , d_value[MAX_TERM] = {0};	
	int i=0 , j=0 , a=0 , b=0 , d=0;
	
	a_sparse[0][0] = a_sparse[0][3] = a_sparse[0][5] = 1;
	a_sparse[1][1] = a_sparse[1][2] = a_sparse[2][3] = 1;
	a_sparse[4][0] = a_sparse[5][2] = 1;
	a_value[0] = 15 , a_value[1] = 22 , a_value[2] = -15 , a_value[3] = 11 , a_value[4] = 3 , a_value[5] = -6 , a_value[6] = 91 , a_value[7] = 28;

	b_sparse[0][3] = b_sparse[0][4] = b_sparse[0][5] = 1;
	b_sparse[1][0] = b_sparse[1][2] = b_sparse[1][4] = 1;
	b_sparse[2][4] = b_sparse[2][5] = b_sparse[3][4] = b_sparse[5][3] = 1;
	b_value[0] = 98 , b_value[1] = -61 , b_value[2] = -42 , b_value[3] = 53 , b_value[4] = 84 , b_value[5] = -12 ;
	b_value[6] = 142 , b_value[7] = 35 , b_value[8] = 13 , b_value[9] = -51;

	for( i=0; i<6; i++ ){
		for( j=0; j<6; j++ ){
			if( a_sparse[i][j] == b_sparse[i][j] )
				d_sparse[i][j] = a_sparse[i][j];
			else
				d_sparse[i][j] = 1;
		}
	}

	for( i=0; i<6; i++ ){
		for( j=0; j<6; j++ ){
			if( d_sparse[i][j] == 1 ){
				if( a_sparse[i][j] == b_sparse[i][j] ){
					d_value[d] = a_value[a] + b_value[b];
					a++ , b++ , d++;
				}
				else if( a_sparse[i][j] == 0 ){
					d_value[d] = b_value[b];
					b++ , d++;
				}
				else{
					d_value[d] = a_value[a];
					a++ , d++;
				}
			}
		}
	}
	printf("matrix d is below\n\n"); 
	for( i=0; i<6; i++ ){
		printf("|");	
		for( j=0; j<6; j++ ){
			printf(" %d ",d_sparse[i][j]);
		}
		printf("|\n");
	}
	printf("\n");
	for( i=0; i<d; i++ ){
		printf("|%4d|\n",d_value[i]);
	}
		return 0;
}
