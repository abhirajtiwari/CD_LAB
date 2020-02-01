#include <stdio.h>
#include <string.h>
#include "getNextToken.h"
int row = 1,column = 1;
typedef struct{
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	char* rtype;
}entry;
struct List{
	entry * a;
	struct List * next;
};
typedef struct List list;
entry * newEntry(){
	entry * e = (entry *)malloc(sizeof(entry)*1);
	e->lexeme = "";
	e->type = "";
	e->size = 0;
	e->scope='z';
	e->no_args=0;
	e->rtype = "";
	return e;
}
int Hash(Token * tok){
	int len = strlen(tok->lexeme);
	int hash = 0;
	for(int i = 0;i<len;i++){
		hash+=(int)tok->lexeme[i] * 31;
	}
	hash%=10039;
	return hash;
}
/*
Type:
0-> Normal Variable
1-> Array Variable
2-> Function 
*/
entry * entryPopulate(Token * tok, Token * temp, int type, int size,int nargs,int scope_count){
	char s = scope_count>0?'L':'G';
	entry * a = newEntry();	
	if(type == 0){
		int vsize = sizeOf(tok->lexeme);
		a->lexeme = temp->lexeme;
		a->type = tok->lexeme;
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "";
	}
	else if (type == 1){
		int vsize = sizeOf(tok->lexeme)*size;
		a->lexeme = temp->lexeme;
		a->type = tok->lexeme;
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "";
	}
	else{
		a->lexeme = temp->lexeme;
		a->type = "";
		a->size = 0;
		a->scope = s;
		a->no_args = nargs;
		a->rtype = tok->lexeme;
	}
	return a;
}
list table[10039];
void init(){
	for(int i = 0;i<10039;i++){
		table[i] =
	}
}
int main(int argc, char const *argv[]){
	init();
	return 0;
}