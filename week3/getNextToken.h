#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int row = 1;
int column = 1;
typedef struct{
	char * lexeme;
	int row;
	int column;
	char * type;
}Token;
Token * newToken(){
	Token * tok = (Token *) malloc(sizeof(Token)*1);
	tok->lexeme = "";
	tok->row = -1;
	tok->column = -1;
	tok->type = "";
	return tok;
}
Token * retNulltok(){
	Token * tok = newToken();
	tok->lexeme = "EOF";
	tok->row = -1;
	tok->column = -1;
	tok->type = "";
	return tok;
}
const char *keywords[34] = {
	"auto",
	"double",
	"int",
	"int*",
	"char*",
	"struct",
	"break",
	"else",
	"long",
	"switch",
	"case",
	"enum",
	"register",
	"typedef",
	"char",
	"extern",
	"return",
	"union",
	"continue",
	"for",
	"signed",
	"void",
	"do",
	"if",
	"static",
	"while",
	"default",
	"goto",
	"sizeof",
	"volatile",
	"const",
	"float",
	"short",
	"unsigned"
};
const char *aops[5]={
	"+","-","*","/","%"
};
const char *lops[3]={
	"&&","||","!"
};
const char *rops[6]= {
	">=","<=",">","<","==","!="
};
const char *ss[9]={
	"=","(",")","[","]","{","}",",",";"
};
int isKeyword (char *word) {
	int i;
	for (i = 0; i < 34; ++i) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
int isaops (char *word) {
	int i;
	for (i = 0; i < 5; ++i) {
		if (strcmp(word, aops[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
int islops (char *word) {
	int i;
	for (i = 0; i < 3; ++i) {
		if (strcmp(word, lops[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
int isrops (char *word) {
	int i;
	for (i = 0; i < 6; ++i) {
		if (strcmp(word, rops[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
int isss (char *word) {
	int i;
	for (i = 0; i < 9; ++i) {
		if (strcmp(word, ss[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
int isnnconst (char *word) {
	int i;
	int len = strlen(word);
	int flag = 0;
	for(int i = 0;i<len;i++){
		if(!isdigit(word[i])){
			return 0;
		}
	}
	return 1;
}
char * identify(char *str){
	if(isKeyword(str)){
		return "keyword";
	}
	else if(isaops(str)){
		return "Arithmetic Operator";
	}
	else if(isrops(str)){
		return "Relational Operator";
	}
	else if(islops(str)){
		return "Logical Operator";
	}
	else if(isss(str)){
		return "Special symbol";
	}
	else if(isnnconst(str)){
		return "Numeric costant";
	}
	else{
		return "Identifier";
	}
}
Token * print_token(char a[],int len){
	char b[len];
	int k = 0;
	Token * tok = newToken();
	for(int i = 0;i<len;i++){
		if(a[i] == ' ' || a[i] == '\t' || a[i] == '\n'){
			continue;
		}
		else{
			b[k++] = a[i];
		}
	}
	char *str = (char *) malloc(sizeof(char)*k);
	for(int i = 0;i<k;i++){
		str[i] = b[i];
	}
	if(strlen(str)>0){
		tok->lexeme = str;
		tok->row = row;
		tok->column = column;
		tok->type = identify(str);
		column+=strlen(str);
	}
	return tok;
}
void print_struct(Token *tok){
	printf("<%s,%d,%d,%s>\n",tok->lexeme,tok->row,tok->column,tok->type);
}
void ignoreComments(FILE *fa){
	char x;
	x = getc(fa);
	if(x == '/'){
		//Single line comment
		while(x != '\n'){
			x = getc(fa);
		}
		row++;
		column = 1;
	}
	else if(x == '*'){
		//Multiline comment 
		x = getc(fa);
		while(x != '*'){
			if(x == '\n'){
				row++;
			}
			x = getc(fa);
		}
			row++;
		x = getc(fa);
		x = getc(fa);
		row ++;
		column = 1;
	}
}
void ignoreStringLiterals(FILE *fa){
	char x;
	x = getc(fa);
	while(x != '"'){
		x = getc(fa);
	}
}
void ignorePreProcessorDirectives(FILE *fa){
	char x;
	x = getc(fa);
	while(x != '\n'){
		x = getc(fa);
	}
		row++;
		column = 1;
}
Token * getNextToken(FILE * fa,int r,int cl){
	row = r;
	column = cl;
	int counter = 0;
	char c,x;
	c = getc(fa);
	char a[80];
	Token *tok = newToken();
	while(c!=EOF){
		if(c == '/'){
			ignoreComments(fa);
		}
		else if(c == '"'){
			ignoreStringLiterals(fa);
		}
		else if(c == '#'){
			ignorePreProcessorDirectives(fa);
		}
		else{
			if(c == ' '){
				tok = print_token(a,counter);
				counter = 0;
				return tok;
			}
			else if(c == '\t'){
				column+=4;
				print_token(a,counter);
				counter = 0;
			}
			else if (c == '\n'){
				print_token(a,counter);
				row++;
				column = 1;
				counter = 0;
			}
			else if (c == '&'){
				print_token(a,counter);
				column = column+1;				
				counter = 0;
			}
			else if (c == '(' || c == ')' || c == '{' || c == '}' ||c == '[' || c == ']' ||c == ',' || c == ';' ){
				if(counter > 0){
					tok = print_token(a,counter);
					ungetc(c,fa);
					return tok;
				}
				else{
					a[counter++] = c;
					tok = print_token(a,counter);
					return tok;
				}
			}
			else{
				
				a[counter++] = c;
			}
		}
		c = getc(fa);
	}
	tok = retNulltok();
}
// int main(int argc, char const *argv[])
// {
// 	Token *tok = newToken();
// 	FILE * fa = fopen("sample.c","r");
// 	tok = getNextToken(fa,row,column);
// 	while(tok->row != -1){
// 		print_struct(tok);
// 		tok = getNextToken(fa,row,column);
// 	}
// 	return 0;
// }