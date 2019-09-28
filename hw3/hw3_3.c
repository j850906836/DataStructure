#include <stdio.h>
#include <stdlib.h>
#define MAX_STACKS 10
#define TRUE 1
#define FALSE 0
typedef struct {
	int key;
} element;

int top[MAX_STACKS];
int boundary[MAX_STACKS];
int n;
int state;
int MEMORY_SIZE = 100;
element memory[100];
void push (int i, element item);
element pop(int i);
void stackFull(int i, element item);
void stackRealloc( int i, element item );
int main()
{
	int i, j , num;
	element insert;
	printf("insert number of stacks, but not bigger than 10\n");
	scanf( "%d", &n );
	top[0] = -1;
	boundary[0] = 0;
	for (j=1; j<n; j++) {
		boundary[j] = (MEMORY_SIZE/n)*j;
		top[j] = boundary[j]-1;
	}
	boundary[n] = MEMORY_SIZE;
	
	printf("insert which stack you want to store, stack begin from stack 0\n");
	while( scanf("%d",&i) != EOF ) {
		printf("insert number you want to store\n");
		scanf("%d",&num);
		insert.key = num;
		push( i, insert );
		printf("insert which stack you want to store, stack begin from stack 0, if you are done, enter Ctrl D\n");
	}
	for( i=0; i<n; i++ ) {
		for( j=boundary[i]; j<=top[i]; j++ ) {
			printf("%d is in stack[%d]\n",memory[j].key,i);
		}
	}
	return 0;		
}
void push (int i, element item)
{
	if (top[i] == boundary[i+1]-1) {
		stackFull (i,item);
		return;
	}

	memory[++top[i]] = item;

}
element pop (int i)
{
	if( top[i] == boundary[i] ) {
		printf("empty\n");	
	}
	return memory[top[i]--];
}
void stackFull (int i, element item)
{
	int j = i-1 , k;
	
	state = FALSE;
		
	while( j>=0 ) {
		if( top[j] < boundary[j+1]-1 ){
				
			for( k=boundary[j+1]; k<boundary[i+1]; k++ ) 
				memory[k-1] = memory[k];
			
			memory[top[i]++] = item;
			
			for( k=i; k>j; k-- ) {
				boundary[k]--;
			 	top[k]--;
			}
			state = TRUE;
			printf("The %d stack is full, but we find a space from the %d stack, and now the size of %d is %d, and the size of %d is %d\n",i,j,j,boundary[j+1]-boundary[j],i,boundary[i+1]-boundary[i]);
			break;
		}
		else j--;
	}
	if( state == FALSE ){
		j = i+1;	
		while( j<=n ){
			if( top[j] < boundary[j+1]-1 ) {
				for( k=top[j]; k>=top[i]+1; k-- ) 
					memory[k+1] = memory[k];	
				memory[++top[i]] = item;
				for( k=j; k>i; k-- ) {
					boundary[k]++;
					top[k]++;
				}
				
				state = TRUE;
				printf("The %d stack is full, but we find a space from the %d stack, and now the size of %d is %d, and the size of %d is %d\n",i,j,j,boundary[j+1]-boundary[j],i,boundary[i+1]-boundary[i]);
				break;
			}
			else 
				j++;
		
		}
	}
	
	if( state == FALSE )	
		stackRealloc(i,item);	
	
}
void stackRealloc(int i, element item)
{
	int j,k;
	element *ptr;
	ptr = (element*)malloc( sizeof(element) );
	memory[MEMORY_SIZE+1] = *ptr;
	MEMORY_SIZE++;

	j = i+1;	
		if( j == n ) 
			memory[++boundary[n]] = item;	
		
		else {
			while( j>=0 ){
				if( top[j] < boundary[j+1]-1 ) {
					for( k=top[j]; k>=top[i]+1; k-- ) 
						memory[k+1] = memory[k];	
					memory[++top[i]] = item;
					for( k=j; k>i; k-- ) {
						boundary[k]++;
						top[k]++;
					}
					state = TRUE;
					boundary[n]++;
					printf("The %d stack is full and the array is also full, but we create a new space for %d, and now the size of %d is %d\n",i,i,i,MEMORY_SIZE);
					break;
				}
				else 
					j++;
		
			}
		}
}
	
