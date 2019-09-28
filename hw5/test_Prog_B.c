#include <stdio.h>

int cnt = 0;
void hanoi( int n , char start , char temp , char end )
{
	if( n > 0 )
	{
		hanoi( n-1 , start , end , temp );

		printf("%d %c -> %c \n" , n , start , end);
		cnt++;
		hanoi( n-1 , temp , start , end );
		if( n == 16 )
		{
			printf("%d\n",cnt);
		}
	
	}
}
int main()
{
	hanoi( 16 , 'A' , 'B' , 'C' );

	return 0;
}
