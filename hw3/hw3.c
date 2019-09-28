#include <stdio.h>

int main()
{
	int space , i=0, n ,j , k=1;
	scanf("%d",&n);
	
	for( j=0; j<n; j++ )
	{
		while( i<k )
		{
			printf("*");
			i++;
		}
		space = n-j*2-2;
		for( i=0; i<space; i++ )
		{
			printf(" ");
		}
		if( space > 0 )
			printf("*");
		k++;
		i=0;
		printf("\n");
	}

	return 0;
}
