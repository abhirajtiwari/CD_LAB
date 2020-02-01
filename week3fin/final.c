#include "getNextToken.h"
#include "hash.h"
int detectFuncArgs(FILE *fa){
	Token* temp = newToken();
	Token * args = newToken();
	Token * tok = newToken();
	int count = 0;
	tok = getNextToken(fa,row,column);
	while(strcmp(tok->lexeme,")")!=0){
		if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			if(isIdTok(temp)){
				args = getNextToken(fa,row,column);
				if(strcmp(args->lexeme,"*") == 0){
					//printf("Pointer argument detected\n");
					//printf("<%s,*%s, %d>\n",tok->lexeme,temp->lexeme,Hash(temp));
					entry * a = entryPopulate(tok,temp,3,0,0,1);
					printEntry(a);
					count++;
				}
				else if(strcmp(args->lexeme,"[") == 0){
					//printf("Array argument detected\n");
					//printf("<%s,%s, %d>\n",tok->lexeme,temp->lexeme,Hash(temp));
					entry * a = entryPopulate(tok,temp,1,1,0,1);
					printEntry(a);
					count++;
				}
				else{
					//printf("%s variable argument detected\n",tok->lexeme);
					//printf("<%s,%s,%d>\n",tok->lexeme,temp->lexeme,Hash(temp));
					entry * a = entryPopulate(tok,temp,0,0,0,1);
					printEntry(a);
					count++;
				}
			}
		}
		if(strcmp(args->lexeme,")") == 0) break;
		tok = getNextToken(fa,row,column);
	}
	return count;
}
void detectVariables(FILE * fa,Token * tok){
	Token* temp = newToken();
	Token * args = newToken();
	if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			while(strcmp(temp->lexeme,";")!=0){
				if(strcmp(temp->lexeme,"*") == 0){
					temp = getNextToken(fa,row,column);
					//printf("Pointer detected\n");
					//printf("<%s, *%s,%d>\n",tok->lexeme,temp->lexeme,Hash(temp)); 
					entry * a = entryPopulate(tok,temp,3,0,0,1);
					printEntry(a);
				}
				else if(isIdTok(temp)){
					args = getNextToken(fa,row,column);
					if(strcmp(args->lexeme,"[") == 0){
					//	printf("Array detected\n");
						args = getNextToken(fa,row,column);
						int size = atoi(args->lexeme);
						//printf("<%s , %s, [%d],%d>\n",tok->lexeme,temp->lexeme,size,Hash(temp));
						entry * a = entryPopulate(tok,temp,1,size,0,1);
						printEntry(a);
					}
					else if(strcmp(args->lexeme,"(") == 0){
					//	printf("Function detected\n");
						int count = 0;
						count = detectFuncArgs(fa);
						//printf("<%s , %s, (%d),%d>\n",tok->lexeme,temp->lexeme,count,Hash(temp));
						entry * a = entryPopulate(tok,temp,2,0,count,1);
						printEntry(a);
					}
					else{
					//	printf("%s variable detected \n",tok->lexeme);
						// printf("<%s,%s,%d>\n",tok->lexeme,temp->lexeme,Hash(temp));
						entry * a = entryPopulate(tok,temp,0,0,0,1);
						printEntry(a);
					}

				}
				temp = getNextToken(fa,row,column);
			}
		}
		else if(isIdTok(tok)){
		//	printf("Already declared variable detected:\n");
			printf("%s\n",tok->lexeme);
		}
}
int main(int argc, char const *argv[])
{
	FILE* fa = fopen("sample.c","r");
	Token* tok = newToken();

	tok = getNextToken(fa,row,column);
	char* type_buf[80];
	char* id_buf[80];
	char c;
	while(tok->row != -1){
		detectVariables(fa,tok);
		tok = getNextToken(fa,row,column);
	}
	return 0;
}
/*
if(isKeyTok(tok)){
			temp = getNextToken(fa,row,column);
			if(strcmp(temp->lexeme,"*") == 0){
				temp = getNextToken(fa,row,column);
				printf("Pointer detected\n");
				printf("<%s,* %s>\n",tok->lexeme,temp->lexeme);
			}
			else if(isIdTok(temp)){
				args = getNextToken(fa,row,column);
				if(strcmp(args->lexeme,"[") == 0){
					printf("Array detected\n");
					args = getNextToken(fa,row,column);
					int size = atoi(args->lexeme);
					printf("<%s,%s,[%d]>\n",tok->lexeme,temp->lexeme,size);			
				}
				else if(strcmp(args->lexeme,"(") == 0){
					printf("Function detected\n");
					printf("<%s,%s>\n",tok->lexeme,temp->lexeme);
				}
				else if(strcmp(args->lexeme,",") == 0){
					printf("First declaration\n");
					printf("<%s,%s>\n",tok->lexeme,temp->lexeme);
					printf("Multiple declaration detected\n");
					while(strcmp(args->lexeme, ";") !=0){
						if(isIdTok(args)){
							printf("<%s,%s>\n",tok->lexeme,args->lexeme);
						}	
						args = getNextToken(fa,row,column);
					}
				}
			}
		}
	/*/