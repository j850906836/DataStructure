#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define SAVE 2
#define DISCARD 3
short int visited[10];
char matrix[10][10];
void dfs(int);
void input();
int w=0;
char save[10];
void madetree();
void printMatrix();
int main()
{
	int v,i;
	printf("Enter a integer(0~9) as root\n");
	scanf("%d",&v);
	input();
	for( i=0; i<11; i++ ) 
		visited[i] = 0;
	printf("\nvertex traversal\n");
	dfs(v);
	printf("\n");
	madetree();
	printf("\nspanning tree by adjacency matrix\n\n");
	printMatrix();	
	return 0;
}
void input()
{
	int i,j;
	for(i=0; i<11; i++){
		for( j=0; j<11; j++ ){
			matrix[i][j] = 0;
		}
	}
	matrix[0][1] = matrix[1][0] = matrix[1][2] = matrix[2][1] = matrix[1][3] = matrix[3][1] = 
	matrix[2][4] = matrix[4][2] = matrix[3][4] = matrix[4][3] = matrix[3][5] = matrix[5][3] = matrix[5][7] = matrix[7][5] =  
	matrix[5][6] = matrix[6][5] = matrix[6][7] = matrix[7][6] = matrix[7][9] = matrix[9][7] = matrix[7][8] = matrix[8][7] = 1; 
}
void dfs( int v )
{
	int j;
	printf("\n%d",v);
	save[w++] = v;
	visited[v] = 1;

	for( j=0; j<10; j++ ) { 
		if( !visited[j] && matrix[v][j] == 1 ) 
			dfs(j);
	}	
			
	
}
void madetree()
{
	int i, j, k, state;
	for( i=0; i<10; i++ ) {
		for( j=0; j<10; j++ ) {
			if( matrix[i][j] == 1 ) {
				state = DISCARD;	
				for( k=0; k<10; k++ ){
					if( (i==save[k] && j==save[k+1]) ||	(j==save[k] && i==save[k+1]) )
							state = SAVE;
				}
				if( state == DISCARD )
					matrix[i][j] = 0;	
			}
		}
	}

}
void printMatrix()
{
	int i,j;
	for( i=0; i<10; i++ ) {
		for( j=0; j<10; j++ ) {
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}
