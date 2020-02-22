#include "genfunc.h"
//Declaration -> data-type identifier-list;
//data-type -> int | char
//identifier-list-> id
char * first_prog[] = {"main"};
char * follow_prog[] = {"$"};
char * first_dec[] = {"int","char"};
char * follow_dec[] = {"id",";","}"};
char * first_idlist[] = {"id"};
char * follow_idlist[] = {";"};
char * first_idlist2[] = {"id","[",","};
char * follow_idlist2[] = {";"};
char * first_idlist3[] = {","};
char * follow_idlist3[] = {";"};
char * first_stmt = {"id"};
char * follow_stmt = {";"};
char * first_assignstmt[] = {"id"};
char * follow_assignstmt[] = {";"};
void DEC();
void IDLIST();
void IDLIST2();
void IDLIST3();
void STMTLIST();
void STMT();
void ASSIGNSTMT();
void PROG(){
	la = getNextToken(fa);
	match(la);
	la = getNextToken(fa);
	if(isInFirst(first_prog,la,1)){
		match(la);
		for(int i = 0;i<3;i++){
			la = getNextToken(fa);
			match(la);
		}
		printf("here\n");
		la  = getNextToken(fa);
		if(isInFirst(first_dec,la,2))
			DEC();
		else
			STMTLIST();
		la = getNextToken(fa);
	}
	else{
		log_error(la,first_prog,follow_prog,1,1);
	}
}
void DEC(){
	printf("in dec\n");
	//la = getNextToken(fa);
	if(isInFirst(first_dec,la,2)){
		match(la);
		IDLIST();
	}
	else if(isInFollow(follow_dec,la,3)){
		match(la);
		printf("Epsilon route taken\n");
		if(strcmp(la->lexeme,"}") == 0){
			finish();
		}
	}
	else{
		log_error(la,first_dec,follow_dec,2,1);
	}
}
void IDLIST(){
	printf("in idlist\n");
	la = getNextToken(fa);
	if(isInFirst(first_idlist,la,1)){
		match(la);
		IDLIST2();
	}
	else{
		log_error(la,first_idlist,follow_idlist,1,1);
	}
}
void IDLIST2(){
	printf("in idlist2\n");
	la = getNextToken(fa);
	if(isInFirst(first_idlist2,la,3)){

		if(strcmp(la->lexeme,",") == 0){
			match(la);
			IDLIST();
		}
		else if(strcmp(la->lexeme,"[") == 0){
			match(la);
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			match(la);
			IDLIST3();
		}
		else{
			match(la);
			IDLIST2();
		}
	}
	else if(isInFollow(follow_idlist2,la,1)){
		printf("Epsilon route taken\n");
		match(la);
		la = getNextToken(fa);
		if(isInFirst(first_dec,la,2))
			DEC();
		else
			STMTLIST();
	}
	else{
		log_error(la,first_idlist2,follow_idlist2,3,1);
	}
}
void IDLIST3(){
	la = getNextToken(fa);
	if(isInFirst(first_idlist3,la,1)){
		match(la);
		IDLIST2();
	}
	else if(isInFollow(follow_idlist3,la,1)){
		printf("Epsilon route taken\n"); 
		match(la);
		la = getNextToken(fa);
		if(isInFirst(first_dec,la,2))
			DEC();
		else
			STMTLIST();
	}
	else{
		log_error(la,first_idlist3,follow_idlist3,1,1);
	}
}
void STMTLIST(){
	printf("in stmt\n");
	STMT();
	la = getNextToken(fa);
	if( (strcmp(la->type,"id") == 0) || (strcmp(la->lexeme,",") == 0)){
		if((strcmp(la->lexeme,",") == 0)){	
			match(la);
		}
		STMTLIST();
	}
	else if(strcmp(la->lexeme,"}") == 0){
			finish();
	}

}
void STMT(){
	ASSIGNSTMT();
	// la = getNextToken(fa);
	// if(strcmp(la->lexeme,";") == 0){
	// 	match(la);
	// }
	// else{
	// 	printf("ERROR:Found %s\nExpected\";\"\n",la->lexeme);
	// }
}
void ASSIGNSTMT(){
	//la = getNextToken(fa);
	printf("in ass\n");
	if(isInFirst(first_assignstmt,la,1)){
		match(la);
		la = getNextToken(fa);
		match(la);
		la = getNextToken(fa);
		do{
			if((strcmp(la->type,"id") == 0) || (strcmp(la->type,"num") == 0) || (strcmp(la->type,"aop") ==0)){
				match(la);
				la = getNextToken(fa);
			}
		}while((strcmp(la->type,"id") == 0) || (strcmp(la->type,"num") == 0) || (strcmp(la->type,"aop") ==0));
		if(strcmp(la->lexeme,";") == 0){
			match(la);
		}
		else{
			printf("ERROR:Found %s\nExpected\";\"\n",la->lexeme);
		}
	}
	else{
		log_error(la,first_assignstmt,follow_assignstmt,1,1);
	}
}
int main(int argc, char const *argv[])
{
	la = newToken();
	fa = fopen("sample.c","r");
	PROG();
	finish();
	return 0;
}