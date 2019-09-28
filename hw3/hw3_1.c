#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct {
		short int vert;
		short int horiz;
		short int updown;
} offsets;
typedef struct {
		short int row;
		short int col;
		short int updn;
		short int dir;
} element;
int top = -1;
offsets move[26];
char imaze[8][8][8];
char maze[10][10][10];
char mark[10][10][10];

void make_maze();
void insert_maze();
void temp_maze(int , int , int);
void insert_maze();
void initial_move();
void path(int , int , int);
void push( element [] , element , int );
element pop();
void stackFull();
void stackEmpty();

int main()
{
	initial_move();
	make_maze();

	return 0;
}
void make_maze()
{
	int i , j , k, X, Y, Z;
	char tmp[10];
	printf("insert the size of the maze\n");
	printf("maze[X][Y][Z] just enter X Y Z with a space between number\n");
	fgets( tmp, 10, stdin );
	sscanf( tmp, "%d %d %d", &X, &Y, &Z );
	memset( tmp , 0 , sizeof(tmp) );
	

	for( i=0; i<X; i++ ){
		for( j=0; j<Y; j++ ){
			for( k=0; k<Z; k++ ){
				imaze[i][j][k] = 1;
			}
		}
	}
	printf("insert row col updn , to let matrix[row][col][updn] = 0 , others will denotes as 1\n");
	while (fgets( tmp , 10, stdin ) ){
		sscanf( tmp, "%d %d %d", &i, &j, &k	);
		imaze[i][j][k] = 0;
		printf("insert again, if you are done, enter CTRL^D\n");
		memset( tmp , 0 , sizeof(tmp) );

	}
	for( i=0; i<X; i++ ){
		for( j=0; j<Y; j++ ){
			for( k=0; k<Z; k++ ){	
//				printf("imaze[%d][%d][%d] = %d ",i , j , k , imaze[i][j][k]);
			}
//			printf("\n");
		}
//		printf("\n");
	}
	temp_maze( X , Y , Z );
}

void temp_maze( int X , int Y , int Z )
{
	int i , j , k;
	for( i=0; i<X+2; i++ ){
		for( j=0; j<Y+2; j++ ){
			for( k=0; k<Z+2; k++ ){
				maze[i][j][k] = 1;
			}
		}
	}
	for( i=0; i<X; i++ ){
		for( j=0; j<Y; j++ ){
			for( k=0; k<Z; k++ ){
				maze[i+1][j+1][k+1] = imaze[i][j][k];
			}
		}
	}	
	
	for( i=0; i<X+2; i++ ){
		for( j=0; j<Y+2; j++ ){
			for( k=0; k<Z+2; k++ ){	
//				printf("maze[%d][%d][%d] = %d ",i , j , k , maze[i][j][k]);
			}
//			printf("\n");
		}
//		printf("\n");
	}
	path( X+1 , Y+1 , Z+1 );
}
void initial_move()
{
	move[0].updown = -1 , move[0].vert = 0  , move[0].horiz = 0;
	move[1].updown = -1 , move[1].vert = -1 , move[1].horiz = 0;
	move[2].updown = -1 , move[2].vert = -1 , move[2].horiz = 1;
	move[3].updown = -1 , move[3].vert = 0  , move[3].horiz = 1;
	move[4].updown = -1 , move[4].vert = 1  , move[4].horiz = 1;
	move[5].updown = -1 , move[5].vert = 1  , move[5].horiz = 0;
	move[6].updown = -1 , move[6].vert = 1  , move[6].horiz = -1;
	move[7].updown = -1 , move[7].vert = 0  , move[7].horiz = -1;
	move[8].updown = -1 , move[8].vert = -1 , move[8].horiz = -1;
	move[9].updown = 0  , move[9].vert = -1 , move[9].horiz = 0;
	move[10].updown = 0 , move[10].vert = -1 , move[10].horiz = 1;
	move[11].updown = 0 , move[11].vert = 0 , move[11].horiz = 1;
	move[12].updown = 0 , move[12].vert = 1 , move[12].horiz = 1;
	move[13].updown = 0 , move[13].vert = 1 , move[13].horiz = 0;
	move[14].updown = 0 , move[14].vert = 1 , move[14].horiz = -1;
	move[15].updown = 0 , move[15].vert = 0 , move[15].horiz = -1;
	move[16].updown = 0 , move[16].vert = -1 , move[16].horiz = -1;
	move[17].updown = 1 , move[17].vert = 0 , move[17].horiz = 0;
	move[18].updown = 1 , move[18].vert = -1 , move[18].horiz = 0;
	move[19].updown = 1 , move[19].vert = -1 , move[19].horiz = 1;
	move[20].updown = 1 , move[20].vert = 0 , move[20].horiz = 1;
	move[21].updown = 1 , move[21].vert = 1 , move[21].horiz = 1;
	move[22].updown = 1 , move[22].vert = 1 , move[22].horiz = 0;
	move[23].updown = 1 , move[23].vert = 1 , move[23].horiz = -1;
	move[24].updown = 1 , move[24].vert = 0 , move[24].horiz = -1;
	move[25].updown = 1 , move[25].vert = -1 , move[25].horiz = -1;
}
void path( int EXIT_ROW, int EXIT_COL , int EXIT_UPDN )
{
	int i, row, col, updn, nextRow, nextCol, nextUpdn, dir, MAX_SIZE = (EXIT_ROW-1)*(EXIT_COL-1)*(EXIT_UPDN-1) , found = FALSE;
	element stack[MAX_SIZE] , position;
	mark[1][1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].updn = 1; stack[0].dir  = 1;
	while (top > -1 && !found) {
		position = pop(stack);
		row = position.row; col = position.col; updn = position.updn; dir = position.dir;
		while (dir < 26 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			nextUpdn = updn + move[dir].updown;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL && nextUpdn == EXIT_UPDN ) 
				found = TRUE;
			else if (!maze[nextRow][nextCol][nextUpdn] && !mark[nextRow][nextCol][nextUpdn]) {
				mark[nextRow][nextCol][nextUpdn] = 1;
				position.row = row; position.col = col; position.updn = updn; position.dir = ++dir;
				push (stack , position , MAX_SIZE);
				row = nextRow; col = nextCol; updn = nextUpdn; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is:\n");
		printf("row col updn\n");
		for (i=0; i<=top; i++) 
			printf("%2d%4d%4d\n",stack[i].row-1,stack[i].col-1,stack[i].updn-1);
		printf("%2d%4d%4d\n",row-1,col-1,updn-1);
		
	}
	else printf("The maze does not have a path\n");
}
void push( element stack[] , element item , int MAX_SIZE )
{
	if( top >= MAX_SIZE-1 )
			stackFull();
	stack[++top] = item;
}
element pop( element stack[] )
{
	if( top == -1 ) {
		fprintf(stderr, "Stack is Empty\n");
		exit(EXIT_FAILURE);	
	}
	return stack[top--];
}
void stackFull()
{
	fprintf(stderr, "Stack is full,cannot add element\n");
	exit(EXIT_FAILURE);
}
