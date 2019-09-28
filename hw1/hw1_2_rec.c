#include <stdio.h>

int Fib( int n )
{

	if( n < 2 )
			return (n);
	else
			return ( Fib(n-1) + Fib(n-2) );
}

int main()
{
	int i;

	scanf("%d",&i);

	i = Fib(i);

	printf("%d\n",i);

	return 0;
}
