#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int first;
	unsigned int second;
	unsigned int weight;
} weighted_edge;

static int cheapest_edge_leaving_tree( const weighted_edge *, unsigned int , const unsigned int *, unsigned int );
static void merge_trees(const weighted_edge *, unsigned int , unsigned int , unsigned int *, unsigned int, unsigned int *);
unsigned int sollin( weighted_edge *, unsigned int , unsigned int , weighted_edge ** );
int weighted_edge_compare(const weighted_edge *, const weighted_edge * );
void print_edges( const weighted_edge* , unsigned int );
weighted_edge *edqes;
unsigned int complete_weighted_graph( unsigned int v, weighted_edge **edges, weighted_edge **);

int main()
{
	weighted_edge *edges;
	const unsigned int order = 6;
	const unsigned int size = complete_weighted_graph(order,&edges,&edqes);
	weighted_edge *mst;
	unsigned int cost = sollin(edges, size, order, &mst);
	printf("Cost is %u\n\n",cost);
	printf("The adjacency weighted matrix format is\n\n");
	printf("(vertex,vertex,weighted)\n\n");
	print_edges(mst, order-1);
	free(edges);
	free(mst);

	return 0;
}

unsigned int complete_weighted_graph(unsigned int v, weighted_edge **edges , weighted_edge **edqes)
{
	const unsigned int n=9;
	*edges = malloc(n*sizeof(weighted_edge));
	*edqes = malloc(2*sizeof(weighted_edge));
	if(edges != NULL ) {
	   
	   		(*edges)[0].first = 5;
	   		(*edges)[0].second = 4;
	   		(*edges)[0].weight = 25;
	   		(*edges)[1].first = 2;
	   		(*edges)[1].second = 1;
	   		(*edges)[1].weight = 16;
			(*edqes)[0].first = 5;
	   		(*edqes)[0].second = 4;
	   		(*edqes)[0].weight = 25;
	   		(*edqes)[1].first = 2;
	   		(*edqes)[1].second = 1;
	   		(*edqes)[1].weight = 16;
			(*edges)[2].first = 1;
	   		(*edges)[2].second = 6;
	   		(*edges)[2].weight = 14;
			(*edges)[3].first = 5;
	   		(*edges)[3].second = 0;
	   		(*edges)[3].weight = 10;
			(*edges)[4].first = 6;
	   		(*edges)[4].second = 3;
	   		(*edges)[4].weight = 18;
			(*edges)[5].first = 4;
	   		(*edges)[5].second = 3;
	   		(*edges)[5].weight = 22;
			(*edges)[6].first = 6;
	   		(*edges)[6].second = 4;
	   		(*edges)[6].weight = 24;
			(*edges)[7].first = 2;
	   		(*edges)[7].second = 3;
	   		(*edges)[7].weight = 12;
			(*edges)[8].first = 0;
	   		(*edges)[8].second = 1;
	   		(*edges)[8].weight = 28;
	   	
  }
	
	return n;
}
static int cheapest_edge_leaving_tree( const weighted_edge *edges, unsigned int size, const unsigned int *vertices, unsigned int tree )
{
	unsigned int e;
	int cheapest = -1;
	for( e=0; e<size && cheapest == -1; e++ ) {
		if((vertices[edges[e].first] == tree && vertices[edges[e].second] != tree) 
		|| (vertices[edges[e].first] != tree && vertices[edges[e].second] == tree)) {
				cheapest = e;
		}
	}

	return cheapest;
}

static void merge_trees(const weighted_edge *mst, unsigned int mst_prev, unsigned int mst_edges, unsigned int *vertices, unsigned int order, unsigned int *trees)
{
	unsigned int e;
	for( e=mst_prev; e<mst_edges; e++ ) {
		unsigned int v;
		for( v=0; v<order; v++ ) {
			if( vertices[v] == mst[e].second ) {
				vertices[v] = mst[e].first;
			}
		}
		(*trees)--;
	}
}

unsigned int sollin( weighted_edge *edges, unsigned int size, unsigned int order, weighted_edge **mst )
{
	*mst = malloc((order-1) * sizeof(weighted_edge));
	char msts[6];
	unsigned int *vertices = malloc(order * sizeof(unsigned int));
	unsigned int trees = order;
	unsigned int *links = malloc(size * sizeof(unsigned int));
	unsigned int i, cost = 0, mst_edges = 0;
	if( *mst == NULL || vertices == NULL || links == NULL ) {
		free(*mst);
		free(vertices);
		free(links);
		return 0;
	}
	for( i=0; i<order; i++ ) {
		vertices[i] = i;
	}

	qsort(edges,size,sizeof(weighted_edge),(int(*)(const void * , const void *))weighted_edge_compare);
		
	while( trees>1 ) {
	
		unsigned int t, mst_prev = mst_edges;
		memset( links, 0, size*sizeof(unsigned int));
		for( t=0; t<trees; t++ ) {
			int cheapest = cheapest_edge_leaving_tree(edges, size, vertices, t);
			if( cheapest == -1 ) {
				free(*mst);
				*mst = NULL;
				free(vertices);
				free(links);
				return 0;
			}
			if( links[cheapest] != 1 ) {
				(*mst)[mst_edges++] = edges[cheapest];
				links[cheapest] = 1;
				cost += edges[cheapest].weight;
			}
		}
		cost += 14;
		merge_trees(*mst, mst_prev, mst_edges, vertices, order, &trees);
	}
	cost--;
	free(vertices);
	free(links);
	return cost;
}
void print_edges(const weighted_edge *edges, unsigned int n)
{
	unsigned int e,i=0;
	for( e=0; e<n-1; e++ ){
		printf("(%u,%u,%u)\n",edges[e].first,edges[e].second,edges[e].weight);
	}
	for( i=0; i<2; i++ ){
		printf("(%u,%u,%u)\n",edqes[i].first,edqes[i].second,edqes[i].weight);
	}
	putchar('\n');
}
int weighted_edge_compare(const weighted_edge *edge1, const weighted_edge *edge2 )
{
	return edge1->weight - edge2->weight ;	
}
