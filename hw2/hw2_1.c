#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_TERM 100
typedef struct{
	float coef;
	int expo;	
}polynomial;
polynomial terms[MAX_TERM];
int avail;
void ptimes( int, int, int, int, int*, int*);
void psort( polynomial [] , int );
void attach( float, int, int * );
int main(){	

	int i=0 , startA , finishA, startB, finishB , *startD=malloc(sizeof(*startD)), *finishD=malloc(sizeof(*finishD));
	char tmpA[MAX_TERM] = {0} , tmpB[MAX_TERM] = {0} , *ptr , *lastp;
	
	printf("Please input A(X), ex:3x^2+2x+1, just input 3 2 2 1 1 0, expo input in reduce order\n");
	fgets( tmpA , 100 , stdin ); 

	printf("Please input B(X), ex:3x^2+2x+1, just input 3 2 2 1 1 0, expo input in reduce order\n");
	fgets( tmpB , 100 , stdin );
	printf("\n\n");
	ptr = lastp = tmpA;		
	while( *ptr != '\0'){
		if( isdigit(*ptr) || ispunct(*ptr) ){
			ptr++;
			continue;
		}
		else{	
				if( i%2 == 0 )
						terms[avail].coef = atof(lastp);
				
												
				else	
						terms[avail++].expo = atoi(lastp);
					
				lastp = ptr;
				ptr++;
				i++;
		}
	}

	startA = 0;
	finishA = avail-1;
	startB = avail;

	ptr = lastp = tmpB;
	i = 0;
	while( *ptr != '\0' ){
			
		if( isdigit(*ptr) || ispunct(*ptr) ){
			ptr++;
			continue;
		}
		else{	
				if( i%2 == 0 )
						terms[avail].coef = atof(lastp);
				
												
				else	
						terms[avail++].expo = atoi(lastp);
					
				lastp = ptr;
				ptr++;
				i++;
		}
	}

	finishB = avail-1;

	ptimes( startA , finishA , startB , finishB , startD , finishD );
	printf("coef|");
	for( i=startA; i<avail; i++ ){
		printf(" %5.1f|",terms[i].coef);	
	}
	printf("\n");
	printf("-----");
	for( i=startA; i<avail; i++ ){
		printf("-------");
	}
	printf("\n");
	printf("expo|");
	for( i=startA; i<avail; i++ ){
		printf(" %5d|",terms[i].expo);
	}
	printf("\n");
	printf("-----");
	for( i=startA; i<avail; i++ ){
		printf("-------");
	}
	printf("\n");
	printf("    |");
	for( i=startA; i<avail; i++ ){
		printf(" %5d|",i);
	}
	printf("\n");
	return 0;
}
void ptimes( int startA , int finishA , int startB , int finishB , int *startD , int *finishD )
{
	int i , j , exponent;
	float coefficient;
	char tmp[1] = {0};
	*startD = avail;

	for( i=startA; i <= finishA; i++ ){
			for( j=startB; j<=finishB; j++ ){
				coefficient = terms[i].coef * terms[j].coef;	
				exponent = terms[i].expo + terms[j].expo;
				attach( coefficient , exponent , startD );

			}
		}
		*finishD = avail-1;

		exponent = *startD;
	for( i=0; i<avail-*startD-1; i++ ){
		for( j=*startD; j<avail-i-1; j++ ){
			if( terms[j].expo < terms[j+1].expo ){
				tmp[0] = terms[j+1].coef;
				tmp[1] = terms[j+1].expo;
				terms[j+1].coef = terms[j].coef;
				terms[j+1].expo = terms[j].expo;
				terms[j].coef = tmp[0];
				terms[j].expo = tmp[1];
			}
		}
	}

		printf("startA=%d finishA=%d startB=%d finishB=%d startD=%d finishD=%d avail=%d \n",startA,finishA,startB,finishB,*startD,*finishD,avail);
} 
void attach( float coefficient , int exponent , int *startD )
{
	int i;

	if( avail >= MAX_TERM ){
		fprintf(stderr,"Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	for( i=*startD; i<avail; i++ ){
		if( terms[i].expo == exponent ){
			terms[i].coef += coefficient;	
			return;
		}
	}
	terms[avail].coef = coefficient;
	terms[avail++].expo = exponent;
}
