#include "a.h"
int table_counter = 0;
Token * table[8000];
void enter_Token(Token * tok,Token * temp,char * str){
	table[table_counter] = newToken();
	table[table_counter]->lexeme = temp->lexeme;
	table[table_counter]->type = tok->lexeme;	
	table[table_counter]->size = sizeOf(tok->lexeme,temp->lexeme);
	table[table_counter]->row = temp->row;
	table[table_counter]->column = temp->column;
	table[table_counter]->stype = str;
	table_counter++;
}	
void print_Table(){
	for (int i = 0; i < table_counter; ++i){
		printf("%s\t%s\t%d\t%d\t%d\t%s\n",table[i]->lexeme,table[i]->type,table[i]->size,table[i]->row,table[i]->column,table[i]->stype);
	}
}
int main(int argc, char const *argv[]){
	FILE * fa = fopen("ass_sample.txt","r");
	Token * tok = newToken();
	Token * temp = newToken();
	Token * args = newToken();
	Token * argT = newToken();
	Token * argL = newToken();
	tok = getNextToken(fa);
	while(tok->row!=-1){
		if(strcmp(tok->type,"id") == 0){
			temp = getNextToken(fa);
			if(strcmp(temp->lexeme,":") == 0){
				temp = getNextToken(fa);
				enter_Token(temp,tok,"var");
			}
			else if(strcmp(temp->lexeme,"(") == 0){
				argL = getNextToken(fa);
				argT = getNextToken(fa);
				argT = getNextToken(fa);
				if(strcmp(argT->type,"Dtype") == 0)
					enter_Token(argT,argL,"var");
				args = getNextToken(fa);
				args = getNextToken(fa);
				args = getNextToken(fa);
				if(strcmp(args->type,"Dtype") == 0)
					enter_Token(args,tok,"func");
			}
		}
		tok = getNextToken(fa);
	}
	print_Table();
	return 0;
}