#include "final_getNextToken.h"
//////////////////////////////Entry////////////////////////////////////////////////
typedef struct{
	int hval;
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	int row;
	int column;
	char* rtype;
	char * args;
}entry;
int sizeOf(char * str){
	if(strcmp(str,"int") == 0) return 4;
	else if(strcmp(str,"float") == 0) return 4;
	else if(strcmp(str,"char") == 0) return 2;
	else if(strcmp(str,"short") == 0) return 2;
	else if(strcmp(str,"long") == 0) return 8;
	else if(strcmp(str,"double") == 0) return 8;
}
char * itoa_(int a){
	char * str = (char *)malloc(sizeof(char)*1000);
	sprintf(str,"%d",a);
	return str;
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
	e->args = "";
	return e;
}
entry * entryPopulate(Token * tok, Token * temp, int type, int size,int nargs,int scope_count,char * args){
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
		a->args = "N/A";
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
		a->args = "N/A";
	}
	else if(type == 2){
		a->hval = h;
		a->lexeme = temp->lexeme;
		a->type = "Func";
		a->size = 0;
		a->scope = 'N';
		a->no_args = nargs;
		a->rtype = tok->lexeme;
		a->row = temp->row;
		a->column = temp->column;
		a->args = args;
	}
	else {
		int vsize = sizeOf(tok->lexeme);
		a->hval = h;
		a->lexeme = temp->lexeme;
			a->type = strcat(tok->lexeme,"*");
		for(int i = 0;i<size;i++){
			a->type = strcat(a->type,"*");
		}
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "N/A";
		a->row = temp->row;
		a->column = temp->column;
		a->args = "N/A";
	}
	return a;
}
void printEntry(entry * a){
	if(a->row == 13 && strcmp(a->lexeme,"n") == 0) return;
	printf("%6d|%7s|%5d|%8d|%6s|%6d|%9c|%9d|%11s|%12s\n",a->hval,a->lexeme,a->row,a->column,a->type,a->size,a->scope,a->no_args,a->rtype,a->args);
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
	eof = 43;
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
	printf("------------------------------------------------------------------------------------------\n");
	printf("| Hash | Lexeme | Row | Column | Type | Size | Scope | #Arguments | Return type |Arguments\n");	
	printf("------------------------------------------------------------------------------------------\n");
	for(int i = 0;i<10039;i++){
		node * ptr = table[i]->next;
		while(ptr){
			printEntry(ptr->a);
			ptr = ptr->next;
		}
	}
}
///////////////////////////Node///////////////////////////////////////////////////////