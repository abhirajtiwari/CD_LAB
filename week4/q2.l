%{
	int words = 0;
	int chars  = 0;
	int blanks = 0;
	int lines = 0;
%}

%%
[a-zA-Z]+ {words++;
			chars+=strlen(yytext);}
\n {chars++; 
	lines++;}
" " {blanks++;}	
.  {chars++;}

%%

int main(){
	yyin = fopen("sample.txt","r");
	yylex();
	printf("Words:%d\n",words);
	printf("Charancters:%d\n",chars);
	printf("Blanks:%d\n",blanks);
	printf("Lines:%d\n",lines);
}
int yywrap(){
	return 1;
}