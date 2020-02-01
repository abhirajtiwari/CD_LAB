#include <stdlib.h>
#include "hashfinal.h"
typedef struct{
	int count;
	char * args;
}arguments;

arguments * detectFuncArgs(FILE *fa){
	Token* temp = newToken();
	Token * args = newToken();
	Token * tok = newToken();
	arguments * send = (arguments*)malloc(sizeof(arguments));
	send->args = (char *) malloc(sizeof(char)*100000);
	tok = getNextToken(fa,row,column);
	while(strcmp(tok->lexeme,")")!=0){
		if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			if(isIdTok(temp)){
				args = getNextToken(fa,row,column);
				if(strcmp(args->lexeme,"*") == 0){
					strcat(send->args,"<");
					strcat(send->args,temp->lexeme);
					strcat(send->args," ");
					strcat(send->args,itoa_(Hash(temp)));
					strcat(send->args,">");
					strcat(send->args," ");
					entry * a = entryPopulate(tok,temp,3,0,0,scope_count,"");
					insert(a);
					send->count++;
				}
				else if(strcmp(args->lexeme,"[") == 0){
					args = getNextToken(fa,row,column);
					int size = atoi(args->lexeme);
					strcat(send->args,"<");
					strcat(send->args,temp->lexeme);
					strcat(send->args," ");
					strcat(send->args,itoa_(Hash(temp)));
					strcat(send->args,">");
					strcat(send->args," ");
					entry * a = entryPopulate(tok,temp,1,size,0,scope_count,"");
					insert(a);
					send->count++;

				}
				else if(strcmp(args->lexeme,")")!=0){
					strcat(send->args,"<");
					strcat(send->args,temp->lexeme);
					strcat(send->args," ");
					strcat(send->args,itoa_(Hash(temp)));
					strcat(send->args,">");
					strcat(send->args," ");
					entry * a = entryPopulate(tok,temp,0,0,0,1,"");
					insert(a);
					send->count++;
				}
			}
		}
		if(strcmp(args->lexeme,")") == 0){
			strcat(send->args,"<");
			strcat(send->args,temp->lexeme);
			strcat(send->args," ");
			strcat(send->args,itoa_(Hash(temp)));
			strcat(send->args,">");
			strcat(send->args," ");
			entry * a = entryPopulate(tok,temp,0,0,0,1,"");
			insert(a);
			send->count++;
			return send;
		}
		tok = getNextToken(fa,row,column);
	}
	return send;
}
void detectVariables(FILE * fa,Token * tok){
	Token* temp = newToken();
	Token * args = newToken();
	if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			while(strcmp(temp->lexeme,";")!=0){
				if(strcmp(temp->lexeme,"*") == 0){
					temp = getNextToken(fa,row,column);
					entry * a = entryPopulate(tok,temp,3,0,0,scope_count,"");
					insert(a);
				}
				else if(isIdTok(temp)){
					args = getNextToken(fa,row,column);
					if(strcmp(args->lexeme,"[") == 0){
						args = getNextToken(fa,row,column);
						int size = atoi(args->lexeme);
						entry * a = entryPopulate(tok,temp,1,size,0,scope_count,"");
						insert(a);
					}
					else if(strcmp(args->lexeme,"(") == 0){
						arguments * send;
						send = detectFuncArgs(fa);
						entry * a = entryPopulate(tok,temp,2,0,send->count,scope_count,send->args);
						insert(a);
					}
					else{
						entry * a = entryPopulate(tok,temp,0,0,0,scope_count,"");
						insert(a);
					}
					if(strcmp(args->lexeme,";") == 0){
						return;
					}

				}
				temp = getNextToken(fa,row,column);
			}
		}
}
int main(int argc, char const *argv[])
{
	FILE* fa = fopen("finsample.c","r");
	Token* tok = newToken();
	init();
	tok = getNextToken(fa,row,column);
	char* type_buf[80];
	char* id_buf[80];
	char c;
	while(tok->row != 26){
		detectVariables(fa,tok);
		tok = getNextToken(fa,row,column);
	}
	printf("_________________________________________________________\n");
	printf("Symbol table for the above token list:\n");
	printf("_________________________________________________________\n");
	printTable(table);
	return 0;
}
