%{
	int flag = 0;	
%}
word [a-zA-Z]+
%%
(and|or|if) {flag = 1;}
%%
int main(){
	yyin = fopen("sample.txt","r");
	yylex();
	if(flag == 1){
		printf("Compound");
	}
	else{
		printf("Simple");
	}
}
int yywrap(){
	return 1;
}