#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
	char * lexeme;
	char * type;
	int row;
	int column
}Token;
char * delimiters[9]={
	"{","}","[","]","(",")",";",",","."
};
char * keywords[7]={
	"public","static","void","main","System","out","println"
}
char * aops[10]={
	"+","-","/","%","*","+=","-=","*=","/=","%="
};
char * dtypes[4]={
	"int","double","float","String"
};
int isDelimiter(char * str){
	for(int i = 0;i<9;i++){
		if(strcmp(str,delimiters[i]) == 0)
			return 1;
	}
}
int isKey(char * str){
	for(int i = 0;i<7;i++){
		if(strcmp(str,keywords[i]) == 0)
			return 1;
	}
}
int isAops(char * str){
	for(int i = 0;i<10;i++){
		if(strcmp(str,aops[i]) == 0)
			return 1;
	}
}
int isDtypes(char * str){
	for(int i = 0;i<4;i++){
		if(strcmp(str,dtypes[i]) == 0)
			return 1;
	}
	return 0;
}
int isNc(char * str){
	for(int i = 0;i<strlen(str);i++){
		if(!isdigit(str[i]))
			return 0;
	}
	return 1;
}
char * identify(char * str){
	if(isDtypes(str)){
		return "Dtype";
	}
	if(isAops(str)){
		return "AOP";
	}
	if(isDelimiter(str)){
		return "Special symbol";
	}
	if(isNc(str)){
		return "Number";
	}
	if(isKey(str)){
		return "keyword";
	}
	else{
		return "Identifier"
	}
}
Token * newToken(){
	Token * new = (Token *)malloc(sizeof(Token));
	new->lexeme = "";
	new->type = "";
	new->row = 0;
	new->column = 0;
	return new;
}
Token * makeToken(char *str,int counter){
	Token * tok = newToken();
	new->lexeme = str;
	new->type = identify(str);
	new->row = grow;
	new->column = gcol;
	return tok;
}
void print_Token(Token * tok){
	printf("<%s,%s>\n",tok->lexeme,tok->type);
}

Token * getNextToken(FILE * fa){
	Token * tok = newToken();
	char * a = (char *)malloc(sizeof(char)*80);
	int counter;
	char c,f;
	c = getc(fa);
	while(c!=EOF){
		if(c == '/'){
			f = getc(fa);
			if(f =='/'){
				while(f!='\n'){
					f = getc(fa);
				}
			}
			else if(f == '*'){
				do{
					f = getc(fa);
					while(f!='*'){
						f = getc(fa);
					}
				}while(f != '/');

			}
		}
		else if(c == ' ' || c == '\t'){
			tok = makeToken(a,counter);
			return tok;
		}
		else if(isDelimiter(c)){
			if(counter > 0){
				tok = makeToken(a,counter);
				ungetc(c,fa);
				return tok;
			}
			else{
				a[counter++] = c;
				tok = makeToken(a,counter);
				return tok;
			}
		}
		else{
			a[counter++] = c;
		}
	}
	tok->row = -1;
	return tok;
}
int main(int argc, char const *argv[])
{
	FILE * fa = fopen("sample.java","r");
	Token * tok = newToken();
	tok = getNextToken(fa);
	while(tok->row != -1){
		print_Token(tok);
		tok = getNextToken(fa);
	}
	return 0;
}