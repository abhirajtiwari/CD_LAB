#include "final_getNextToken.h"
FILE * fa;
Token * la ;
char matched[8000];
int m=0;
char *first_lexp[]={"num","id","("};
char *follow_lexp[]={"$","num","id","(",")"};
char *first_atom[]={"num","id"};
char *follow_atom[]={"$","num","id","(",")"};
char *first_list[]={"("};
char *follow_list[]={"$","num","id","(",")"};
char *first_lexp_seq[]={"num","id","("};
char *follow_lexp_seq[]={")"};
char *first_lexp_seq2[]={"num","id","("};
char *follow_lexp_seq2[]={")"};
int fisize_lexp = 3;
int fosize_lexp = 5;
int fisize_atom = 2;
int fosize_atom = 5;
int fisize_list = 1;
int fosize_list = 5;
int fisize_lexp_seq = 3;
int fosize_lexp_seq = 1;
int fisize_lexp_seq2 = 3;
int fosize_lexp_seq2 = 1;
int isInFirst(char *a[],Token * s,int size){
	for(int i = 0;i<size;i++){
		if(strcmp(a[i],s->type) == 0){
			return 1;
		}
		else if(strcmp(a[i],s->lexeme) == 0){
			return 1;
		}
	}
	return 0;
}
int isInFollow(char *a[],Token * s,int size){
	for(int i = 0;i<size;i++){
		if(strcmp(a[i],s->type) == 0){
			return 1;
		}
		else if(strcmp(a[i],s->lexeme) == 0){
			return 1;
		}
	}
	return 0;
}
void match(Token *a){
	int size = strlen(a->lexeme);
	for(int i = 0;i<size;i++)
		matched[m++] = a->lexeme[i];
	puts(matched);
}
void log_error(Token *a,char *first[],char *follow[],int s1,int s2){
	printf("ERROR:\nFound \"%s\"\nExpected:\n",a->lexeme);
	int first_size = s1;
	int follow_size = s2;
	int flag = 0;
	for (int i = 0; i < first_size; ++i){
		printf("\"%s\"\n",first[i]);
		if(first[i][0] == '^'){
			flag = 1;
		}
	}
	if(flag == 1){
		for (int i = 0; i < follow_size; ++i){
			printf("\"%s\"\n",follow[i]);		
		}
	}
	exit(0);
}
void finish(){
	char pa = la->lexeme[0];
	la = getNextToken(fa);
	if(pa == '$' || la->lexeme[0] == '$'){
		printf("Success!!\n");
	}
	else{
		printf("ERROR!!\n");
	}
	exit(0);
}
void ATOM_();
void LIST();
void LEXP_SEQ();
void LEXP_SEQ2();
void LEXP(){
	la = getNextToken(fa);
	if(isInFirst(first_lexp,la,fisize_lexp)){
		if( (strcmp(la->type ,"num")==0) || (strcmp(la->type,"id") == 0)){
			ATOM_();
		}
		else{	
			match(la);
			LIST();
		}
	}
	else{
		log_error(la,first_lexp,follow_lexp,fisize_lexp,fosize_lexp);
	}

}
void ATOM_(){
	if(isInFirst(first_atom,la,fisize_atom)){
		match(la);
	}
	else{
		log_error(la,first_atom,follow_atom,fisize_atom,fosize_atom);
	}

}
void LIST(){
	LEXP_SEQ();
}
void LEXP_SEQ(){
	LEXP();
	LEXP_SEQ2();
}
void LEXP_SEQ2(){
	printf("here\n");
	la = getNextToken(fa);
	if(isInFollow(follow_lexp_seq2,la,fosize_lexp_seq2)){
		printf("Epsilon route taken\n");
		match(la);
	}
	else{
		LEXP();
	}
}
int main(int argc, char const *argv[]){
	fa = fopen("sample.txt","r");
	la = newToken();
	LEXP();	
	finish();
	return 0;
}