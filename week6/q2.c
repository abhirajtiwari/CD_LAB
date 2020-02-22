#include <stdio.h>
#include <stdlib.h>
char first_e[] = {'a','('};
char follow_e[] = {'$',')'};
char first_e2[] = {'a','('};
char follow_e2[] = {'$','*',')'};
char first_t[] = {'+','^'};
char follow_t[] = {'$','+',')'};
char first_t2[] = {'*','^'};
char follow_t2[] = {'$','+',')'};
char first_f[] = {'a','('};
char follow_f[] = {'$','*',')','+'};
char matched[8000];
int m = 0;
char la;
FILE * fa;
int isInFirst(char a[],char s,int size){
	//int size = sizeof(a)/sizeof(char);
	for(int i = 0;i<size;i++){
		if(a[i] == s){
			return 1;
		}
	}
	return 0;
}
int isInFollow(char a[],char s,int size){
	//int size = sizeof(a)/sizeof(char);
	for(int i = 0;i<size;i++){
		if(a[i] == s)
			return 1;
	}
	return 0;
}
void t();
void t2();
void e2();
void f();
void e(){
	printf("in e\n");
	t();
	e2();
}
void e2(){
	printf("in e2\n");
	la = getc(fa);
	printf("e2->%c\n",la);
	if(isInFirst(first_e2,la,2)){
		matched[m++] = la;
		puts(matched);
		if(la == '+'){
			t();
			e2();
		}
	}
	else if(isInFollow(follow_e2,la,3)){
		printf("Epsilon route taken\n");
		matched[m++] = la;
		puts(matched);
	}
	else{
		printf("ERROR\nFound %c\n Expected:",la);
		int size = sizeof(first_e2)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",first_e2[i]);
		}
		size = sizeof(follow_e2)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",follow_e2[i]);
		}
		printf("\n");
		exit(0);
	}
}
void t(){
	printf("in t\n");
	f();
	t2();
}
void t2(){
	printf("in t2\n");
	la = getc(fa);
	printf("t2->%c\n",la);
	if(isInFirst(first_t2,la,2)){
		matched[m++] = la;
		puts(matched);
		if(la == '*'){
			f();
			t2();
		}
	}
	else if(isInFollow(follow_t2,la,3)){
		printf("Epsilon route taken\n");
		matched[m++] = la;
		puts(matched);
	}
	else{
		printf("ERROR\nFound %c\n Expected:",la);
		int size = sizeof(first_t2)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",first_t2[i]);
		}
		size = sizeof(follow_t2)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",follow_t2[i]);
		}
		printf("\n");
		exit(0);
	}
}
void f(){
	printf("in f\n");
	la = getc(fa);
	printf("f->%c\n",la);
	if(isInFirst(first_f,la,2)){
		matched[m++] = la;
		puts(matched);
		if(la == '('){
			e();
		}
	}
	else{
		printf("ERROR\nFound %c\n Expected:",la);
		int size = sizeof(first_f)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",first_f[i]);
		}
		size = sizeof(follow_f)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",follow_f[i]);
		}
		printf("\n");
		exit(0);
	}
}
int main(int argc, char const *argv[]){
	fa = fopen("sample.txt","r");
	e();
	char pa = la;
	la = getc(fa);
	if(la == '$' || pa == '$'){
		puts(matched);
		printf("Success\n");
	}
	else{
		printf("ERROR\n");
	}
	return 0;
}
