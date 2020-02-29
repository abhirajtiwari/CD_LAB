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
void DECNSTMT();
void EXPN();
void DTYPE();
void MULOP();
void ADDOP();
void RELOP();
void DPRIME();
void SEPRIME();
void TPRIME();
void TERM();
void SIMPEXP();
void FACTOR();
void LOOPSTMT();
void EPRIME();
void dumEXPN();
void PROG(){
	char * first[] = {"main"};
	char * follow[] = {"$"};
	int first_size = 1;
	int follow_size = 1;
	la = getNextToken(fa);
	match(la);
	la = getNextToken(fa);
	match(la);
	if(check_first){
		for(int i = 0;i<3;i++){
			la = getNextToken(fa);
			match(la);
		}
		la = getNextToken(fa);
		if(strcmp(la->type,"dtype")==0){
			DEC();
		}
		else if( (strcmp(la->type,"id") == 0) || strcmp(la->type,"key")==0){
			STMTLIST();
		}
		else{
			printf("here\n");
			error;
		}
	}
	else{
		error;
	}
}
void DEC(){
	char * first[] = {"int","char","^"};
	char * follow[] = {"id","if","for","while","}"};
	int first_size = 3;
	int follow_size = 5;
	if(check_first){
		DTYPE();
		IDLIST();
	}
	else if(check_follow){
		STMTLIST();
	}
	else{
		error;
	}
}
void DTYPE(){
	char * first[] = {"int","char"};
	char * follow[] = {"id"};
	int first_size = 2;
	int follow_size = 1;
	if(check_first){
		match(la);
		la = getNextToken(fa);
	}
	else{
		error;
	}
}
void IDLIST(){
	char * first[] = {"id"};
	char * follow[] = {";"};
	int first_size = 1;
	int follow_size = 1;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		IDLIST2();
	}
	else{
		error;
	}
}
void IDLIST2(){
	char * first[] = {"^",",","[","^"};
	char * follow[] = {";"};
	int first_size = 3;
	int follow_size = 1;
	if(check_first){
		match(la);
		if(strcmp(la->lexeme,",")==0){
			la = getNextToken(fa);
			IDLIST();
		}
		else{
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			IDLIST3();
		}
	}
	else if(check_follow){
		match(la);
		la = getNextToken(fa);
		DEC();
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
		IDLIST();
	}
	else if(check_follow){
		match(la);
		la = getNextToken(fa);
		DEC();
	}
	else{
		error;
	}
}
void STMTLIST(){
	char * first[] = {"id","if","for","while","^"};
	char * follow[] = {"}"};
	int first_size = 4;
	int follow_size = 1;
	if(check_first){
		STMT();
		la = getNextToken(fa);
		STMTLIST();
	}
	else if(check_follow){
		printf("here123123\n");
		match(la);
	}
}
void STMT(){
	char * first[] = {"id","if","for","while"};
	char * follow[] = {"id","if","for","while","}"};
	int first_size = 4;
	int follow_size = 5;
	if(strcmp(la->type,"id") == 0){
		ASSIGNSTMT();
		printf("ass end\n");
	}
	else if(strcmp(la->lexeme,"if") == 0){
		DECNSTMT();
	}
	else{
		LOOPSTMT();
	}
}
void ASSIGNSTMT(){
	char * first[] = {"id"};
	char * follow[] = {";"};
	int first_size = 1;
	int follow_size = 1;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		match(la);
		la = getNextToken(fa);
		EXPN();
	}
	else{
		error;
	}
}
void EXPN(){
	printf("in expn\n");
	char * first[] = {"id","num"};
	char * follow[] = {";",")"};
	int first_size = 2;
	int follow_size = 2;
	if(check_first){
		SIMPEXP();
		EPRIME();
	}
	else{
		error;
	}
}
void dumEXPN(){
	char * first[] = {"id","num"};
	char * follow[] = {";",")"};
	int first_size = 2;
	int follow_size = 2;
	if(check_first){
		while(!check_follow){
			match(la);
			la = getNextToken(fa);
		}
		match(la);
	}
}
void EPRIME(){
	printf("in e'\n");
	char * first[] = {"==","!=","<=",">=",">","<","^"};
	char * follow[] = {";",")"};
	int first_size = 7;
	int follow_size = 2;
	if(check_first){
		RELOP();
		SIMPEXP();
	}
	else if(check_follow){
		match(la);
	}
	else{
		error;
	}
}
void SIMPEXP(){
	printf("in sexpn\n");
	char * first[] = {"id","num"};
	char * follow[] = {"==","!=","<=",">=",">","<",")",";"};
	int first_size = 2;
	int follow_size = 8;
	if(check_first){
		TERM();
		SEPRIME();
	}
	else if(check_follow){
		//match(la);
	}
	else{
		error;
	}
}
void SEPRIME(){
	printf("in s'\n");
	char * first[] = {"+","-","^"};
	char * follow[] = {"==","!=","<=",">=",">","<",")",";"};
	int first_size = 3;
	int follow_size = 8;
	if(check_first){
		ADDOP();
		TERM();
		SEPRIME();
	}
	else if(check_follow){
		//match(la);
	}
	else{
		error;
	}
}
void TERM(){
	printf("in term\n");
	char * first[] = {"id","num"};
	char * follow[] = {"+","-","==","!=","<=",">=",">","<",")",";"};
	int first_size = 2;
	int follow_size = 10;
	if(check_first){
		FACTOR();
		TPRIME();
	}
	else{
		error;
	}
}
void TPRIME(){
	printf("in t'\n");
	char * first[] = {"*","/","%","^"};
	char * follow[] = {"+","-","==","!=","<=",">=",">","<",")",";"};
	int first_size = 4;
	int follow_size = 10;
	if(check_first){
		MULOP();
		FACTOR();
		TPRIME();
	}
	else if(check_follow){
		//match(la);
	}
	else{
		error;
	}
}
void FACTOR(){
	printf("in factor\n");
	char * first[] = {"id","num"};
	char * follow[] = {"*","/","%"};
	int first_size = 2;
	int follow_size = 3;
	if(check_first){
		match(la);
		la = getNextToken(fa);
	}
	else{
		error;
	}
}
void DECNSTMT(){
	printf("in  decn;\n");
	char * first[] = {"if"};
	char * follow[] = {"id","if","for","while"};
	int first_size = 1;
	int follow_size = 4;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		match(la);
		la = getNextToken(fa);
		EXPN();
		la = getNextToken(fa);
		match(la);
		la = getNextToken(fa);
		STMTLIST();
		printf("her12312e\n");
		la = getNextToken(fa);
		DPRIME();
	}
	else{
		error;
	}
}
void DPRIME(){
	char * first[] = {"else","^"};
	char * follow[] = {"id","if","for","while"};
	int first_size = 2;
	int follow_size = 4;
	if(check_first){
		match(la);
		la = getNextToken(fa);
		match(la);
		la = getNextToken(fa);
		STMTLIST();
	}
	else if(check_follow){
		match(la);
	}
	else{
		error;
	}
}
void RELOP(){
	char * first[] = {"==","!=","<=",">=",">","<"};
	char * follow[] = {"id","num"};
	int first_size = 6;
	int follow_size = 2;
	if(check_first){
		match(la);
		la = getNextToken(fa);
	}
	else{
		error;
	}
}
void ADDOP(){
	char * first[] = {"+","-"};
	char * follow[] = {"id","num"};
	int first_size = 2;
	int follow_size = 2;
	if(check_first){
		match(la);
		la = getNextToken(fa);
	}
	else{
		error;
	}
}
void MULOP(){
	char * first[] = {"*","/","%"};
	char * follow[] = {"id","num"};
	int first_size = 3;
	int follow_size = 2;
	if(check_first){
		match(la);
		la = getNextToken(fa);
	}
	else{
		error;
	}
}
void LOOPSTMT(){
	char * first[] = {"for","while"};
	char * follow[] = {"id","if","for","while"};
	int first_size = 2;
	int follow_size = 4;
	if(check_first){
		match(la);
		if(strcmp(la->lexeme,"for") == 0){
			la = getNextToken(fa);
			ASSIGNSTMT();
			EXPN();
			ASSIGNSTMT();
			la =getNextToken(fa);
			match(la);
			STMTLIST();
		}
		else{
			la = getNextToken(fa);
			match(la);
			la = getNextToken(fa);
			EXPN();
			la = getNextToken(fa);
			match(la);
			STMTLIST();
		}
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