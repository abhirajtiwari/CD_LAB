%{
	int posint = 0;
	int negint = 0;
	int posfloatint = 0;
	int negfloatint = 0;
%}
digit [0-9]
%%
\+?{digit}+	posint++;
-{digit}+	negint++;

\+?{digit}*\.{digit}+	posfloatint++;
-{digit}*\.{digit}+		negfloatint++;
. ;
%%
int main(){
	yyin = fopen("sample.txt","r");
	yylex();
	printf("Number of posdigits:%d\n",posint);
	printf("Number of negdigits:%d\n",negint);
	printf("Number of posfloatdigits:%d\n",posint);
	printf("Number of negfloatdigits:%d\n",negint);	
}
int yywrap(){
	return 1;
}