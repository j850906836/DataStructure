#include <stdio.h>
#define ROW 4
#define COL 4
void made_adjency_mx();
void made_Aplus_mx();
void made_Astar_mx();
char matrix[ROW][COL];
char Aplus[ROW][COL];
char Astar[ROW][COL];
int main()
{
	printf("The origin adjacency matrix\n\n");
	made_adjency_mx();
	printf("\nA+ matrix\n\n");
	made_Aplus_mx();
	printf("\nA* matrix\n\n");
	made_Astar_mx();
	
	return 0;
}
void made_adjency_mx()
{
	int i,j;
	
	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
			matrix[i][j] = 0;

	matrix[0][1] = matrix[0][3] = matrix[1][2] = matrix[2][0] = matrix[2][3] = 1;
	
	for( i=0; i<ROW; i++ ) {
		for( j=0; j<COL; j++ )
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
}
void made_Aplus_mx()
{
	int i,j,k, length=0;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
			if( matrix[i][j] == 1 )
				Aplus[i][j] = 1;
	
	for( k=0; k<ROW; k++ ) {
		for( i=0; i<COL; i++ ) {	
			for( j=0; j<ROW; j++ ) {	
				Aplus[i][j] = Aplus[i][j] || (Aplus[i][k] && Aplus[k][j] );	
			}
		}
	}
	for( i=0; i<ROW; i++ ) {
		for( j=0; j<COL; j++ )
			printf("%d ",Aplus[i][j]);
		printf("\n");
	}
}
void made_Astar_mx()
{
	int i,j;
	
	for( i=0; i<ROW; i++ ) {
		for( j=0; j<COL; j++ )
			if( Aplus[i][j] == 1 )
				Astar[i][j] = 1;	
	}
	
	for( i=0; i<ROW; i++ )
		Astar[i][i] = 1;

	for( i=0; i<ROW; i++ ) {
		for( j=0; j<COL; j++ )
			printf("%d ",Astar[i][j]);
		printf("\n");
	}
}
