%{
	#include <stdio.h>
	int vowels = 0;
	int consonants = 0;	
%}

%%
[aeiouAEIOU] {vowels++;}
[a-zA-z] {consonants++;}
%%
int main(){
	yyin = fopen("sample.txt","r");
	yylex();
	printf("Vowels: %d\n",vowels);
	printf("Consonants: %d\n",consonants);
	return 0;
}
int yywrap(){
	return 1;
}