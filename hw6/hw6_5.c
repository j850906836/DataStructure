#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 10

typedef struct node{
		int vertex;
		int duration;
		struct node *link;
}nodePointer;

typedef struct {
		int count;
		nodePointer *link;
} hdnodes;
hdnodes graph[MAX_VERTICES];
void topSort(int n);
void made_graph();
void input( int , int , int );
int main()
{
	made_graph();
	topSort(10);
	return 0;
}
void made_graph()
{
	int i,j;
	nodePointer *ptr;
	input( 0,1,5 );	
	input( 0,2,6 );
	input( 1,3,3 );	
	input( 2,3,6 );	
	input( 2,3,4 );	
	input( 3,5,4 );	
	input( 3,6,4 );	
	input( 3,4,3 );	
	input( 4,6,1 );	
	input( 4,7,4 );	
	input( 5,9,4 );	
	input( 6,8,5 );	
	input( 7,8,2 );	
	input( 8,9,2 );
	
	for( i=0; i<10; i++ ) {
		ptr = graph[i].link;
		while( ptr != NULL ) {
			if( ptr == NULL )
				break;
			else {
				for( j=0; j<10; j++ ){	
					if( ptr->vertex == j ) {
						graph[j].count++;
					}
				}
			}
			ptr = ptr->link;

		}
			
	}
}	
void input( int n , int vex , int dur)
{
	nodePointer *ptr, *tmp;
	ptr = malloc(sizeof(nodePointer));
	ptr->vertex = vex;
	ptr->duration = dur;
	ptr->link = NULL;
	
	if( graph[n].link == NULL ) {
		graph[n].link = ptr;	
		return;
	}
	else {
		tmp = graph[n].link;	
		while( tmp->link != NULL ){
			tmp = tmp->link;
		
			if( tmp->link == NULL )	
				break;
		}
		tmp->link = ptr;
	}
}
void topSort(int n)	
{
	int i,j,k,w=0,top;
	nodePointer *ptr;
	char save[10] = {0} , earliest[10] = {0} ,latest[10],crity[10][10];
	top = -1;
	for(i=0;i<10;i++){
		latest[i]=23;
	}
	for( i=0; i<n; i++ ) {
		if(!graph[i].count) {
			graph[i].count = top;
			top =  i;
		}
	}
	for( i=0; i<n; i++ ) {
		if( top == -1 ) {
			fprintf(stderr,"\nNetwork has a cycle. Sort terminated, \n");
			exit(EXIT_FAILURE);
		}
		else {
			j=top;
			top = graph[top].count;
	//		printf("v%d\n",j);
			save[w++] = j;
			for( ptr=graph[j].link; ptr; ptr=ptr->link ) {
				k=ptr->vertex;
				graph[k].count--;
				if( !graph[k].count) {
					graph[k].count = top;
					top = k;
				}
				if(earliest[k]<(earliest[j]+ptr->duration))
					earliest[k] = earliest[j]+ptr->duration;	
			}
		}
	}
	w--;	
	while( w > -1 ){
		for( ptr=graph[save[w]].link; ptr; ptr=ptr->link ) {
			k=ptr->vertex;
			if( latest[save[w]] > (earliest[k]-ptr->duration) )
				latest[save[w]] = earliest[k]-ptr->duration;
		}
		
		w--;
	}
	for(i=0; i<10; i++){
		if(latest[i]-earliest[i] == 0)
			strcpy(crity[i]	,"YES");
		else
			strcpy(crity[i],"NO");
	}
	for(i=0;i<10;i++){
		printf("e(%d)=%d\tl(%d)=%d\tcriticality:%s\n",i,earliest[i],i,latest[i],crity[i]);
	}
	
}
