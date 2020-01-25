#include "getNextToken.h"
typedef struct{
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	char* rtype;
}entry;
int getArraySize(FILE *fa){
	int num = 0;
	char x = getc(fa);
	while ( x != ']'){
		num = num*10 + ((int)x-48);
		x = getc(fa);
	}
	return num;
}
int getNumArgs(FILE *fa){
	int num = 0;
	char x = getc(fa);
	while(x != ')'){
		if(x == ',') num++;
		x = getc(fa);
	}
	return num+1;
}
int main(int argc, char const *argv[])
{
	FILE* fa = fopen("sample.c","r");
	Token* tok = newToken();
	Token* temp = newToken();
	Token * args = newToken();
	tok = getNextToken(fa,row,column);
	char* type_buf[80];
	char* id_buf[80];
	char c;
	while(tok->row != -1){
		if(strcmp(tok->type,"keyword")==0){
			temp = getNextToken(fa,row,column);
			if(strcmp(temp->type,"Identifier")==0){	
				c = getc(fa);
				if(c == '['){
					int size = getArraySize(fa);
					printf("<%s,%s,array,%d>\n",temp->lexeme,tok->lexeme,size);
				}	
				else if(c == '('){
					int size = getNumArgs(fa);
					printf("<%s,%s,function,%d>\n",temp->lexeme,tok->lexeme,size);
				}
				else{
					printf("<%s,%s>\n",temp->lexeme,tok->lexeme);
					ungetc(c,fa);
				}
			}		
		}
		tok = getNextToken(fa,row,column);
	}
	return 0;
}