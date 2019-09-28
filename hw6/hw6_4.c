#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define SAVE 2
#define NOSAVE 3
#define MIN2(x,y) ( (x) < (y) ? (x) : (y) )
short int dfn[10];
short int low[10];
int save[10];
int num,a=0;
char matrix[10][10];
void input();
void init(void);
char visited[10];
void store(int);
void dfnlow(int , int );
int root;
int main()
{
	int n,i;
	printf("Enter integer as root\n");
	scanf("%d",&n);
	root = n;
	input();
	init();
	dfnlow(n,-1);
	for( i=0; i<10; i++ )
		printf("%d  dfn:%d low:%d \n",i,dfn[i],low[i]);	
	for( i=0; i<a; i++ )
		printf("%d ",save[i]);
	printf("\n");
	return 0;
}
void input()
{
	int i,j;
	matrix[0][1] = matrix[1][0] = matrix[1][2] = matrix[2][1] = matrix[1][3] = matrix[3][1] = 
	matrix[2][4] = matrix[4][2] = matrix[3][4] = matrix[4][3] = matrix[3][5] = matrix[5][3] = matrix[5][7] = matrix[7][5] = 
	matrix[5][6] = matrix[6][5] = matrix[6][7] = matrix[7][6] = matrix[7][9] = matrix[9][7] = matrix[7][8] = matrix[8][7] = 1; 
}
void init(void)
{
	int i;
	for( i=0; i<10; i++ ) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}
void dfnlow(int u, int v)
{
	int j,i,cnt=0;
	dfn[u] = low[u] = num++;

	
	for( j=0; j<10; j++ ) {
		if( !visited[j] && matrix[u][j] == 1 ) {
			if( dfn[j] < 0 ) {
				dfnlow(j,u);
				low[u] = MIN2(low[u],low[j]);
				if( low[j] >= dfn[u] ) {
					cnt = 0;	
					if(root == u){
						for(i=0; i<10; i++) {
							if(matrix[u][i] == 1){
								cnt++;
							}
						}
						if(cnt>1)
							store(u);
					}
					else	
						store(u);
				}
			}
			else if( j!=v )
				low[u] = MIN2(low[u],dfn[j]);
			
		}
	}
}
void store(int u)
{
	int i,state=NOSAVE;
	for(i=0; i<a; i++){
		state = NOSAVE;	
		if(save[i]==u){
			state = SAVE;
			break;
		}
	}
	if( state == NOSAVE )
		save[a++] = u;
}
