#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int row = 1;
int column = 1;
typedef struct {
	char * lexeme;
	char * type;
	int row;
	int column;
} Token;
const char * key[2]={
	"Scalar","foreach"
};
const char * ss[5]={
	"{","}","(",")",";"
};
const char * aop[8]={
	"+","-","*","/","+=","-=","*=","/="
};
int isKeyword(char *str){
	for(int i = 0;i<2;i++){
		if(strcmp(key[i],str) == 0){
			return 1;
		}
	}
	return 0;
}
int isSs(char *str){
	for(int i = 0;i<5;i++){
		if(strcmp(ss[i],str) == 0){
			return 1;
		}
	}
	return 0;
}
int isAop(char *str){
	for(int i = 0;i<8;i++){
		if(strcmp(aop[i],str) == 0){
			return 1;
		}
	}
	return 0;
}

char * _typeof(char * a){
	if(isKeyword(a)){
		return "Keyword";
	}
	else if(isSs(a)){
		return "Special Symbol";
	}
	else if(isAop(a)){
		return "Arithmetic Operator";
	}
	else{
		return "Identifier";
	}
}
Token * newToken(){
	Token * tok = (Token *)malloc(sizeof(Token));
	tok->lexeme = "";
	tok->type = "";
	tok->row = -1;
	tok->column = -1;
}
Token * formToken(char * a,int counter){
	Token * tok = newToken();
	printf("%s\n",a);
	if(counter > 0){
		tok->lexeme = a;
		tok->type = _typeof(a);
		tok->row = row;
		tok->column = column-strlen(a);
	}
	return tok;
}
Token * getNextToken(FILE * fa){
	Token * tok = newToken();
	char c,f;
	char a[80];
	int counter = 0;
	c = getc(fa);
	while(c != EOF){
		if(c == '#'){
			f = getc(fa);
			if(f == '!'){
				printf("Path to be ignored\n");
				f = getc(fa);
				while(f != '\n'){
					f = getc(fa);
					printf("%c",f);
				}
			}
			row++;
			column = 1;
		}
		else if(c == '$'){
			column++;
			f = getc(fa);
			column++;
			while(f != ' '){
				a[counter ++] = f;
				f = getc(fa);
				column++;
			}
			column--;
			tok = formToken(a,counter);
			return tok;
		}
		else if(c == '@'){
			column++;
			f = getc(fa);
			column++;
			if(f == '_'){
				a[counter++] = c;
				a[counter ++] = f;
			}
			else{
				a[counter++] = c;
				ungetc(f,fa);
				column--;
			}
			tok = formToken(a,counter);
			return tok;
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/'){
			column++;
			f = getc(fa);
			column++;
			if(f == '='){
				a[counter++] = c;
				a[counter ++] = f;
			}
			else{
				a[counter++] = c;
				ungetc(f,fa);
				column--;
			}
			tok = formToken(a,counter);
			return tok;
		}
		else if(c == ' ' || c == '{' || c == '}' || c == '(' || c == ')' || c == ';'){			
			if(counter > 0){
				tok = formToken(a,counter);
				column++;
				return tok;
			}
			else {
				if(c != ' '){
					a[counter++] = c;
					tok = formToken(a,counter);
					column++;
					return tok;
				}
			}
		}
		else if(c == '\n'){		
			row++;	
			tok = formToken(a,counter);
			column = 1;
			return tok;
		}
		else{
			column++;
			a[counter++] = c;
		}
	}
}
void print_Token(Token * tok){
	printf("<%s,%s,%d,%d>\n",tok->lexeme,tok->type,tok->row,tok->column);
}
int main(int argc, char const *argv[])
{
	FILE * fa  =fopen("sample.perl","r");
	Token * tok = newToken();
	printf("here\n");
	tok = getNextToken(fa);
	while(tok->row != -1){
		print_Token(tok);
		tok = getNextToken(fa);
	}
	return 0;
}