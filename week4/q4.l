%{
	int pf=0;
	int sf=0;	
%}
%%
"scanf" {sf++; 
		fwrite("READ",sizeof(char),4,yyout);}
"printf" {pf++;
		fwrite("WRITE",sizeof(char),5,yyout);}
%%
int main(){
	yyin = fopen("sample.txt","r");
	yylex();
	printf("\nThe number of printfs:%d",pf);
	printf("\nThe number of scanfs:%d",sf);
}
int yywrap(){
	return 1;
}