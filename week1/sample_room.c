#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//This is a comment
/*
 This is a multiline comment 
 hey
 #include <unistd.h>
 there
 stranger
 */
int main( int argc, char const * argv[] )
{
	int num;
	scanf("%d",&num);
	printf("Value of  #include <unistd.h> num is: %d\n",num);
	return 0;
}