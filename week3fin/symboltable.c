#include "getNextToken.h"
typedef struct{
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	char* rtype;
}entry;
/*
Populate entry:
0->Normal integer variable
1->Second integer variable
*/
entry * newEntry(){
	entry * e = (entry *)malloc(sizeof(entry)*1);
	entry->lexeme = "";
	entry->type = "";
	entry->size = 0;
	entry->scope='z';
	entry->no_args=0;
	entry->rtype = "";
	return e;
}
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
		if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			if(strcmp(temp->lexeme,""))
		}
		tok = getNextToken(fa,row,column);
	}
	return 0;
}
/*
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
*/
