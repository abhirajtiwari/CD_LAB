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
}Token;
int sizeOf(char *str){
	if(strcmp(str,"int") == 0) return 4;
	if(strcmp(str,"void") == 0) return 0;
	else return 0;
}
const char delimiters[11]={
	' ','=','{','}','[',']','(',')',';',',','.'
};
const char * aops[1]={
	"+"
};
const char * dtypes[3]={
	"int","void","String"
};
const char * kwords[4]={
	"public","static","class","System"
};
int isDelimiter(char a){

	for (int i = 0; i < 11; ++i){
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
	for (int i = 0; i < 3; ++i){
		if(strcmp(a,dtypes[i]) == 0){
			return 1;
		}
	}
	return 0;
}
int isKword(char  * a){
	for (int i = 0; i < 4; ++i){
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
	tok->size = sizeOf(str);
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
		if(c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']' || c== ';' || c == ',' || c == '.')  {
			if(counter>0){
				tok = makeToken(a);
				ungetc(c,fa);
				return tok;
			}
			else{
				column++;
				a[counter++] = c;
				tok = makeToken(a);
				return tok;
			}
		}
		else if(c == '\n' || c ==' '|| c == '\t'){
			tok = makeToken(a);
			if(c == '\n'){
				row +=1;
				column = 1;
			}
			else if(c == ' '){
				column += 1;
			}
			else if(c == '\t'){
				column += 4;
			}
			return tok;
		}
		else if(c == '"'){
			column ++;
			f = getc(fa);
			column++;
			while(f != '"'){
				f = getc(fa);
				column++;
			}
		}
		else{
			a[counter++] = c;
			column++;
		}
		c = getc(fa);
	}
	tok->row = -1;
	return tok;
}
// int main(int argc, char const *argv[])
// {
// 	FILE * fa = fopen("sample.java","r");
// 	Token * tok = newToken();
// 	tok = getNextToken(fa);
// 	while(tok->row!=-1){
// 		print_Token(tok);
// 		tok = getNextToken(fa);
// 	}
// 	return 0;
// }