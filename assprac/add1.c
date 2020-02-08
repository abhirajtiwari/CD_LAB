#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
	char * lexeme;
	char * type;
	int row;
	int column;
}Token;
int sizeOf(char *str){
	if(strcmp(str,"int") == 0) return 4;
	if(strcmp(str,"void") == 0) return 0;
	else return 0;
}
Token * newToken(){
	Token * new = (Token *)malloc(sizeof(Token));
	new->lexeme = "";
	new->type = "";
	new->row = 0;
	new->column = 0;
	return new;
}
const char * key[2]={
	"scalar","foreach"
};
const char * aops[9]={
	"+","-","/","%","*","+=","-=","*=","/="
};
const char delimiter[10]={
	' ','=','+','{','}','(',')',';','\n','\t'
};
const char * ss[8] = {
	" ","=","+","{","}","(",")",";"
};
int isKeyword(char *str){
	for(int i = 0;i<2;i++){
		if(strcmp(str,key[i]) == 0){
			return 1;
		}
	}
	return 0;
}
int isAops(char *str){
	for(int i = 0;i<9;i++){
		if(strcmp(str,aops[i]) == 0){
			return 1;
		}
	}
	return 0;
}
int isSs(char *str){
	for(int i = 0;i<8;i++){
		if(strcmp(str,ss[i]) == 0){
			return 1;
		}
	}
	return 0;
}
int isDelimiter(char str){
	for(int i = 0;i<10;i++){
		if(str==delimiter[i]){
			return 1;
		}
	}
	return 0;
}
int isNc(char *str){
	for(int i = 0;i<strlen(str);i++){
		if(!isdigit(str[i])){
			return 0;
		}
	}
	return 1;
}
char * identify(char *str){
	if(isKeyword(str)){
		return "Keyword";
	}
	else if(isAops(str)){
		return "Arithmetic operator";
	}
	else if(strcmp(str,"=") == 0){
		return "Assignment operator";
	}
	else if(isSs(str)){
		return "Special Symbol";
	}
	else if(isNc(str)){
		return "Numeric constant";
	}
	else {
		return "Identifier";
	}
}
void print_Token(Token * tok){
	if( (strcmp(tok->lexeme,"\n")!=0) && (strcmp(tok->lexeme,"\t")!=0) )
	printf("<%s,%s>\n",tok->lexeme,tok->type);
}
Token * makeToken(char * a,int counter){
	Token * tok = newToken();
	//memcpy(tok->lexeme,a,sizeof(char)*counter);
	tok->lexeme = a;
	tok->type = identify(tok->lexeme);
	return tok;
}
Token * getNextToken(FILE * fa){
	char * a = (char *)malloc(sizeof(char)*8000);
	char c,f;
	int counter = 0;
	c = getc(fa);
	Token * tok = newToken();
	while(c!=EOF){
		if(c == '#'){
			f = getc(fa);
			if(f == '!'){
				printf("Path encountered\n");
			}
			else{
				printf("Comment encountered\n");
			}
			while(f != '\n'){
				f = getc(fa);
			}
		}
		else if(c == '$'){
			f = getc(fa);
			while(!isDelimiter(f)){
				a[counter++] = f;
				f = getc(fa);
			}
			ungetc(f,fa);
			tok = makeToken(a,counter);
			return tok;
		}
		else if(c == '@'){
			a[counter++] = c;
			f = getc(fa);
			a[counter++] = f;
			tok = makeToken(a,counter);
			return tok;
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/'){
			f = getc(fa);
			if(f == '='){
				a[counter++] = c;
				a[counter++] = f;
				tok = makeToken(a,counter);
				return tok;
			}
			else{
				ungetc(f,fa);
				a[counter++] = c;
				tok = makeToken(a,counter);
				return tok;
			}
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
		c = getc(fa);
	}
	tok->row = -1;
	return tok;

}
int main(int argc, char const *argv[])
{
	Token * tok = newToken();
	FILE * fa = fopen("sample.txt","r");
	tok = getNextToken(fa);
	while(tok -> row != -1){
		print_Token(tok);
		tok = getNextToken(fa);
	}
	return 0;
}