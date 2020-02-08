#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
int row = 1;
int column = 1;
typedef struct{
	char * lexeme;
	char * type;
	int size;
	int row;
	int column;
	char * stype;
}Token;
int sizeOf(char *str,char * lex){
	if(strcmp(str,"Int") == 0) return 4;
	if(strcmp(str,"String") == 0) return 2*strlen(lex);
	else return 0;
}
const char delimiters[9]={
	'=','{','}','(',')',';',',','.',':'
};
const char * aops[1]={
	"+"
};
const char * dtypes[2]={
	"Int","String"
};
const char * kwords[1]={
	"class"
};
int isDelimiter(char a){

	for (int i = 0; i < 9; ++i){
		if(a==delimiters[i]){
			return 1;
		}
	}
	return 0;
}
int isAops(char * a){
	for (int i = 0; i < 1; ++i){
		if(strcmp(aops[i],a) == 0){
			return 1;
		}
	}
	return 0;
}
int isDtype(char * a){
	for (int i = 0; i < 2; ++i){
		if(strcmp(a,dtypes[i]) == 0){
			return 1;
		}
	}
	return 0;
}
int isKword(char  * a){
	for (int i = 0; i < 1; ++i){
		if(strcmp(a,kwords[i]) == 0){
			return 1;
		}
	}
	return 0;
}
char * identify(char * str){
	if(isDelimiter(str[0])){
		return "Symbol";
	}
	else if(isAops(str)){
		return "Operator";
	}
	else if(isDtype(str)){
		return "Dtype";
	}
	else if(isKword(str)){
		return "Kword";
	}
	else{
		return "id";
	}
}
Token * newToken(){
	Token * new = (Token *)malloc(sizeof(Token));
	new->lexeme = "";
	new->type = "";
	new->row = 0;
	new->column = 0;
	new->size = 0;
	return new;
}
Token * makeToken(char * str){
	Token * tok = newToken();
	tok->lexeme = str;
	tok->type = identify(str);
	tok->row = row;
	tok->column = column-strlen(str);
	tok->size = sizeOf(tok->type,tok->lexeme);
	return tok;
}
void print_Token(Token * tok){
	if(strlen(tok->lexeme)>0)
		printf("<%s,%s,%d,%d>\n",tok->lexeme,tok->type,tok->row,tok->column);
}
Token * getNextToken(FILE *fa){
	Token * tok = newToken();
	char * a = (char *)malloc(sizeof(char)*80);
	int counter = 0;
	char c,f;
	c = getc(fa);
	while(c!=EOF){
		if(c == '-'){
			f = getc(fa);
			if(f == '-'){
				while(f != '\n'){
					f = getc(fa);
				}
			}
		}
		else if(c == '"'){
			f = getc(fa);
			while(f != '"'){
				f = getc(fa);
			}
		}
		else if(c == '\n'){
			tok = makeToken(a);
			row ++;
			column = 1;
				return tok;
		}
		else if(c == '\t'){
			tok = makeToken(a);
			row+=4;
				return tok;
		}
		else if(c == ' '){
			tok = makeToken(a);
			row ++;
				return tok;
		}
		else if(isDelimiter(c)){
			if(counter > 0){
				tok = makeToken(a);
				ungetc(c,fa);
				return tok;
			}
			else{
				a[counter++] = c;
				tok = makeToken(a);
				row ++;
				return tok;
			}
		}
		else{
			row++;
			a[counter ++ ] = c;
		}
		c = getc(fa);
	}
	tok->row = -1;
	return tok;
}
int main(int argc, char const *argv[])
{
	FILE * fa = fopen("ass_sample.txt","r");
	Token * tok = newToken();
	tok = getNextToken(fa);
	while(tok->row!=-1){
		print_Token(tok);
		tok = getNextToken(fa);
	}
	return 0;
}