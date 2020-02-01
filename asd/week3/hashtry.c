#include <stdio.h>
#include <string.h>
#include "getNextToken.h"
//////////////////////////////Entry////////////////////////////////////////////////
typedef struct{
	int hval;
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	char* rtype;
}entry;
int Hash(Token * tok){
	int len = strlen(tok->lexeme);
	int hash = 0;
	for(int i = 0;i<len;i++){
		hash+=(int)tok->lexeme[i] * 31;
	}
	hash%=10039;
	return hash;
}
int sizeOf(char * str){
	if(strcmp(str,"int") == 0) return 4;
	else if(strcmp(str,"float") == 0) return 4;
	else if(strcmp(str,"char") == 0) return 2;
	else if(strcmp(str,"short") == 0) return 2;
	else if(strcmp(str,"long") == 0) return 8;
	else if(strcmp(str,"double") == 0) return 8;
}
entry * newEntry(){
	entry * e = (entry *)malloc(sizeof(entry)*1);
	e->hval = 0;
	e->lexeme = "";
	e->type = "";
	e->size = 0;
	e->scope='z';
	e->no_args=0;
	e->rtype = "";
	return e;
}
entry * entryPopulate(Token * tok, Token * temp, int type, int size,int nargs,int scope_count){
	char s = scope_count>0?'L':'G';
	int h = Hash(temp);
	entry * a = newEntry();	
	if(type == 0){
		int vsize = sizeOf(tok->lexeme);
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = tok->lexeme;
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "N/A";
	}
	else if (type == 1){
		int vsize = sizeOf(tok->lexeme)*size;
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = tok->lexeme;
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "N/A";
	}
	else if(type == 2){
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = "N/A";
		a->size = 0;
		a->scope = s;
		a->no_args = nargs;
		a->rtype = tok->lexeme;
	}
	else {
		int vsize = sizeOf(tok->lexeme);
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = strcat(tok->lexeme,"*");
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "N/A";
	}
	return a;
}
void printEntry(entry * a){
	printf("%6d|%7s|%6s|%6d|  %c|%9d|%11s>\n",a->hval,a->lexeme,a->type,a->size,a->scope,a->no_args,a->rtype);
}
///////////////////////////Entry//////////////////////////////////////////////////////
///////////////////////////Node///////////////////////////////////////////////////////
struct node{
	entry * a;
	struct node * next;
};
typedef struct node node;
node * table[10039];
void init(){
	for(int i = 0;i<10039;i++){
		table[i] = (node *)malloc(sizeof(node));
	}
}
void insert(entry * a1){
	int ind = a1->hval;
	node * head = table[ind];
	node * new = (node *)malloc(sizeof(node));
	node * ptr = head;
	new->a = (entry*)malloc(sizeof(entry));
	new->a = a1;
	new->next = NULL;
	while(ptr->next!=NULL){
		ptr = ptr->next;
	}
	ptr->next = new;
}
void printTable(node * table[]){
	printf("-----------------------------------------------------------------\n");
	printf("| Hash | Lexeme | Type | Size | Scope | Arguments | Return type |\n");	
	printf("-----------------------------------------------------------------\n");
	for(int i = 0;i<10039;i++){
		node * ptr = table[i]->next;
		while(ptr){
			printEntry(ptr->a);
			ptr = ptr->next;
		}
	}
}
///////////////////////////Node///////////////////////////////////////////////////////
int main(int argc, char const *argv[]){
	init();
	FILE * fa = fopen("sample.c","r");
	Token * tok = newToken();
	Token * temp = newToken();
	tok = getNextToken(fa,row,column);
	temp = getNextToken(fa,row,column);
	entry * a1 = newEntry();
	a1 = entryPopulate(tok,temp,0,0,0,1);
	insert(a1);
	tok = getNextToken(fa,row,column);
	temp = getNextToken(fa,row,column);
	a1 = entryPopulate(tok,temp,0,0,0,1);
	insert(a1);
	printTable(table);
	return 0;
}