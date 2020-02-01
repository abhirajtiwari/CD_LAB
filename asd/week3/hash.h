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
		hash+=(int)tok->lexeme[i] * 10;
	}
	hash/=100;
	return hash;
}
/*
Type:
0-> Normal Variable
1-> Array Variable
2-> Function 
3-> Pointer 
*/
int sizeOf(char * str){
	if(strcmp(str,"int") == 0) return 4;
	else if(strcmp(str,"float") == 0) return 4;
	else if(strcmp(str,"char") == 0) return 2;
	else if(strcmp(str,"short") == 0) return 2;
	else if(strcmp(str,"long") == 0) return 8;
	else if(strcmp(str,"double") == 0) return 8;
}
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
		a->rtype = "N/A";
	}
	else if (type == 1){
		int vsize = sizeOf(tok->lexeme)*size;
		a->lexeme = temp->lexeme;
		a->type = tok->lexeme;
		a->size = vsize;
		a->scope = s;
		a->no_args = 0;
		a->rtype = "N/A";
	}
	else if(type == 2){
		a->lexeme = temp->lexeme;
		a->type = "N/A";
		a->size = 0;
		a->scope = s;
		a->no_args = nargs;
		a->rtype = tok->lexeme;
	}
	else {
		int vsize = sizeOf(tok->lexeme);
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
	printf("<%s,%s,%d,%c,%d,%s>\n",a->lexeme,a->type,a->size,a->scope,a->no_args,a->rtype);
}