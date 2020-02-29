#include "genfunc.h"
#define check_first check(first,la,first_size)
#define check_follow check(follow,la,follow_size)
#define error log_error(la,first,follow,first_size,follow_size)
void DEC();
void IDLIST();
void IDLIST2();
void IDLIST3();
void STMTLIST();
void STMT();
void ASSIGNSTMT();
void LOOP();
void DECNSTMT();
void DECN2();
void EXPN();
void PROG(){
	char * first[] = {"main"};
	char * follow[] = {"$"};
	int first_size = 1;
	int follow_size = 1;
	la = getNextToken(fa); //For int
	match(la);
	la = getNextToken(fa);
	if(check_first){
		match(la);
		for(int i = 0;i<3;i++){
			la = getNextToken(fa);
			match(la);
		}
		la = getNextToken(fa);
		if(strcmp(la->type,"id") == 0)
			DEC();
		else if(strcmp())
			STMTLIST();
	}
	else{
		error;
	}
}
void DEC(){
	char * first[] = {"int","char","^"};
	char * follow[] = {"id",";","}"};
	int first_size = 2;
	int follow_size = 3;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		IDLIST();
	}
	else if(check_follow){
		match(la);
	}
	else{
		lerror;
	}
}
void IDLIST(){
	char * first[] = {"id"};
	char * follow[] = {";"};
	int first_size = 1;
	int follow_size = 1;
	if(check_follow){
		match(la);
		la = getNextToken(fa);
		IDLIST2();
	}
	else{
		error;
	}
}
void IDLIST2(){
	char * first[] = {"^",",","["};
	char * follow[] = {";"};
	int first_size = 3;
	int follow_size = 1;
	if(check_first){
		if(strcmp(la->lexeme,",") == 0){
			match(la);
			la = getNextToken(fa);
			IDLIST();
		}
		else if(strcmp(la->lexeme,"[") == 0){
			match(la);
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			IDLIST3();
		}
		else{
			match(la);
			la = getNextToken(fa);
			IDLIST2();
		}
	}
	else if(check_follow){
		match(la);
		la = getNextToken(fa);
		if(strcmp(la->type,"id") == 0)
			DEC();
		else if(strcmp())
			STMTLIST();
	}
	else{
		error;
	}
}
void IDLIST3(){
	char * first[] = {"^",","};
	char * follow[] = {";"};
	int first_size = 2;
	int follow_size = 1;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		IDLIST2();
	}
	else(check_follow){
		match(la);
		la = getNextToken(fa);
		if(strcmp(la->type,"id") == 0)
			DEC();
		else if(strcmp())
			STMTLIST();
	}
	else{
		error;
	}
}
void STMTLIST(){
	char * first[] = {"id","if","for","while"};
	char * follow[] = {"}"};
}
void STMT(){
	
}