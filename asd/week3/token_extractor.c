#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
	Arithmetic operators - 0
	Relational operators - 1
	Logical operators - 2
	Special symbols - 3
	Keywords - 4
	Numerical costants - 5
	Identifiers - 6  
*/
int column = 1;
int row = 0;
const char *keywords[32] = {
	"auto",
	"double",
	"int",
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
	for (i = 0; i < 32; ++i) {
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
void print_token(char a[],int len){
	char b[len];
	int k = 0;
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
		printf("<%s,%d,%d,%s>\n",str,row,column,identify(str));
		column+=strlen(str);
	}
	
}
int main(int argc, char const * argv[])
{
	FILE *fa,*fb;
	fa = fopen("sample.c","r");
	fb = fopen("sample_out.c","w");
	int counter = 0;
	int token_start = 0;
	char c,x;
	c = getc(fa);
	char a[80];
	while(c!=EOF){
		if(c == '/'){
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
		else if(c == '"'){
			x = getc(fa);
			while(x != '"'){
				x = getc(fa);
			}
		}
		else if(c == '#'){
			x = getc(fa);
			while(x != '\n'){
				x = getc(fa);
			}
				row++;
				column = 1;
		}
		else{
			if(c == ' '){
				print_token(a,counter);
				column = column+1;
				counter = 0;
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
				print_token(a,counter);
				counter = 0;
				a[counter++] = c;
				print_token(a,counter);
				counter = 0;
			}
			else{
				
				a[counter++] = c;
			}
		}
		c = getc(fa);
	}
	return 0;
}
