#include "final_getNextToken.h"
char matched[8000];
int m = 0;
FILE * fa;
Token * la;
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
int check(char *a[],Token * s,int size){
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
	printf("ERROR:(%d,%d)\nFound \"%s\"\nExpected:\n",row+1,column,a->lexeme);
	int first_size = s1;
	int follow_size = s2;
	int flag = 0;
	for (int i = 0; i < first_size; ++i){
		if(first[i][0] == '^'){
			flag = 1;
		}
		else{
			printf("\"%s\"\n",first[i]);
		}
	}
	if(flag == 1){
		for (int i = 0; i < follow_size; ++i){
			printf("\"%s\"\n",follow[i]);		
		}
	}
	exit(0);
}
void log_error2(Token *a,char *str){
	printf("ERROR:(%d,%d)\nFound \"%s\"\nExpected:\"%s\"\n",row+1,column,a->lexeme,str);
	exit(0);

}
void finish();
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
