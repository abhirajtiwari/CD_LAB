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
	int row;
	int column
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
	e->row = 0;
	e->column = 0;
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
		a->row = temp->row;
		a->column = temp->column;
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
		a->row = temp->row;
		a->column = temp->column;
	}
	else if(type == 2){
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = "N/A";
		a->size = 0;
		a->scope = s;
		a->no_args = nargs;
		a->rtype = tok->lexeme;
		a->row = temp->row;
		a->column = temp->column;
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
		a->row = temp->row;
		a->column = temp->column;
	}
	return a;
}
void printEntry(entry * a){
	printf("%6d|%7s|%3d|%6d|%6s|%6d|  %c|%9d|%11s>\n",a->hval,a->lexeme,a->row,a->column,a->type,a->size,a->scope,a->no_args,a->rtype);
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
	printf("| Hash | Lexeme | Row | Column | Type | Size | Scope | Arguments | Return type |\n");	
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