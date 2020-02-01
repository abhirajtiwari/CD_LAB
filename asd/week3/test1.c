#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int c,int a){
	int n;
	int x[4]={1,2,13,7};
	printf("Enter a number");
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	if(prime(x[i]))
		printf("A prime \n");
	else
		printf("not a prime \n");
	return 0;
}
int prime(int argv,int b){
	int i;
	for(i=0x2;i<sqrt(n);i++){
		if(n%i==0 && i<=n)	
			return 0;
	}
	return 1;
}