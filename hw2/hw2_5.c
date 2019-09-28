#include <stdio.h>
#include <string.h>
#define MAX_LEN 100
void strinins( char [] );
int main()
{
	int n , i , t_len , s_len , c_len;
	char s[MAX_LEN] = {0} , t[MAX_LEN] = {0};
	

	printf("please insert string s\n");
	strinins(s);
	printf("please insert string t\n");
	strinins(t);
	printf("please insert integer i for concatenate t and s at ith position\n");
	scanf("%d",&n);

	printf("s:%s\n",s);	
	printf("t:%s\n",t);
	s_len = strlen(s);
	t_len = strlen(t);
	
	strcat( t , s );
	
	for( i=0; i<s_len-n+1; i++ ){
		s[s_len-i] = '\0';
	}
	
	strcat( s , t );

	for( i=n+t_len; i<s_len+t_len; i++ ){
		s[i] = s[i+n];	
	}

	c_len = strlen(s);

	for( i=i; i<c_len; i++ ){
		s[i] = '\0';	
	}
	
	printf("string after insertion:%s\n",s);

	return 0;
}
void strinins( char string[] )
{
	char tmp[MAX_LEN] = {0};	

	fgets( tmp , MAX_LEN , stdin );
	tmp[strlen(tmp)-1] = '\0';	
	string = strcpy( string , tmp );
}
