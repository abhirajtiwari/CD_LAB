#include <stdio.h>
#include <stdlib.h>
char first_s[] = {'a','>','('};
char follow_s[] = {'$',',',')'};
char first_t[] = {'a','>','('};
char follow_t[] = {')'};
char first_t2[] = {',','^'};
char follow_t2[] = {')'};
char matched[8000];
int m = 0;
char la;
FILE * fa;
int isInFirst(char a[],char s,int size){
	for(int i = 0;i<size;i++){
		if(a[i] == s){
			return 1;
		}
	}
	return 0;
}
int isInFollow(char a[],char s,int size){
	for(int i = 0;i<size;i++){
		if(a[i] == s)
			return 1;
	}
	return 0;
}
void t();
void t2();
void s(){
	la = getc(fa);
	if(isInFirst(first_s,la,3) == 1){
		matched[m++] = la;
		puts(matched);
		if(la == '('){
			t();
		}
	}
	else{
		printf("ERROR\nFound %c\n Expected:",la);
		int size = sizeof(first_s)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",first_s[i]);
		}
		size = sizeof(follow_s)/sizeof(char);
		for(int i = 0;i<size;i++){
			printf("\"%c\", ",follow_s[i]);
		}
		printf("\n");
		exit(0);
	}
}
void t(){
	s();
	t2();
}
void t2(){
	la = getc(fa);
	if(isInFirst(first_t2,la,2) == 1){
		matched[m++] = la;
		puts(matched);
		if(la == ','){
			s();
			t2();
		}
	}
	else if(isInFollow(follow_t2,la,1) == 1){
		printf("Epsilon route taken\n");
		matched[m++] = la;
		puts(matched);
	}
	else{
		printf("ERROR\nFound %c\nExpected:",la);
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
int main(int argc, char const *argv[]){
	fa = fopen("sample.txt","r");
	s();
	la = getc(fa);
	if(la == '$'){
		puts(matched);
		printf("Success\n");
	}
	else{
		printf("ERROR\n");
	}
	return 0;
}
