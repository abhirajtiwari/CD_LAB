#include "getNextToken.h"
typedef struct{
	char* lexeme;
	char* type;
	int size;
	char scope;
	int no_args;
	char* rtype;
}entry;
int scope = 0;
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
int isVariable(Token * arr[],int i){
	if((strcmp(arr[i].type,"keyword"))==0 && (strcmp(arr[i+1].type,"Identifier"))==0){
		return 1;
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	Token *tok = newToken();
	Token* arr[10000];
	for(int i = 0;i<10000;i++){
		arr[i] = newToken();
	}
	FILE * fa = fopen("sample.c","r");
	arr[0] = getNextToken(fa,row,column);
	int i = 0;
	do{
		i++;
		arr[i] = getNextToken(fa,row,column);
	}while(arr[i]->row != -1);
	i = 0;
	while(arr[i] -> row != -1){
		if(isVariable(arr,i)){
			if(arr[i+2].lexeme == '('){
				//function
				int k = 1;
				int nargs = arr[i+1].lexeme == ')'?0:1;
			}
			else if(arr[i+2].lexeme == '['){
				//array
			}
			else (arr[i+2].lexeme == ','){
				//multiple declaration
			}
		}
	}
	return 0;
}