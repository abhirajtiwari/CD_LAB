#include <stdio.h>
	char a[]={'a','a','a','a','a'};
int main(int argc, char const *argv[])
{
	printf("%d\n",sizeof(a)/sizeof(char));
	return 0;
}