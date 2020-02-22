#include <stdio.h>
#include <stdlib.h>
FILE * fa;
char la;
char matched[8000];
int m=0;
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
void match(char a){
	matched[m++] = a;
	puts(matched);
}
void log_error(char a,char first[],char follow[]){
	printf("ERROR:\nFound \"%c\"\nExpected:\n",a);
	int first_size = sizeof(first)/sizeof(char);
	int follow_size = sizeof(follow)/sizeof(char);
	int flag = 0;
	for (int i = 0; i < first_size; ++i){
		printf("\"%c\"\n",first[i]);
		if(first[i] == '^'){
			flag = 1;
		}
	}
	if(flag == 1){
		for (int i = 0; i < follow_size; ++i){
			printf("\"%c\"\n",follow[i]);		
		}
	}
	exit(0);
}
void finish(){
	char pa = la;
	la = getc(fa);
	if(pa == '$' || la == '$'){
		printf("Success!!\n");
		//puts(matched);
	}
	else{
		printf("ERROR!!\n");
	}
	exit(0);
}
void A();
void B();
void A2();
void S(){
	char first[]={'a'};
	char follow[]={'$'};
	int first_size = sizeof(first)/sizeof(char);
	int follow_size = sizeof(follow)/sizeof(char);
	la = getc(fa);
	if(isInFirst(first,la,first_size)){
		match(la);
		A();
		B();
		la = getc(fa);
		if(la == 'e'){
			match(la);
		}
		else{
			printf("ERROR:Found \"%c\"\nExpected e\n",la);
		}
	}
	else if(isInFirst(first,'^',first_size)){
		if(isInFollow(follow,la,follow_size)){
			printf("Epsilon route taken\n");
			match(la);		
		}
		else{
			log_error(la,first,follow);
		}
	}
	else{
		log_error(la,first,follow);
	}

}
void A(){
	char first[]={'b'};
	char follow[]={'c'};
	int first_size = sizeof(first)/sizeof(char);
	int follow_size = sizeof(follow)/sizeof(char);
	la = getc(fa);
	if(isInFirst(first,la,first_size)){
		match(la);
		A2();
	}
	else if(isInFirst(first,'^',first_size)){
		if(isInFollow(follow,la,follow_size)){
			printf("Epsilon route taken\n");
			match(la);

		}
		else{
			log_error(la,first,follow);
		}
	}
	else{
		log_error(la,first,follow);
	}

}
void A2(){
	char first[]={'b','^'};
	char follow[]={'c'};
	int first_size = sizeof(first)/sizeof(char);
	int follow_size = sizeof(follow)/sizeof(char);
	la = getc(fa);
	if(isInFirst(first,la,first_size)){
		match(la);
		A2();
	}
	else if(isInFirst(first,'^',first_size)){
		if(isInFollow(follow,la,follow_size)){
			printf("Epsilon route taken\n");
			match(la);
		}
		else{
			log_error(la,first,follow);
		}
	}
	else{
		log_error(la,first,follow);
	}
}
void B(){
	char first[]={'d'};
	char follow[]={'e'};
	int first_size = sizeof(first)/sizeof(char);
	int follow_size = sizeof(follow)/sizeof(char);
	la = getc(fa);
	if(isInFirst(first,la,first_size)){
		match(la);
	}
	else if(isInFirst(first,'^',first_size)){
		if(isInFollow(follow,la,follow_size)){
			printf("Epsilon route taken\n");
			match(la);
		}
		else{
			log_error(la,first,follow);
		}
	}
	else{
		log_error(la,first,follow);
	}
}
int main(int argc, char const *argv[]){
	fa = fopen("sample.txt","r");
	S();	
	finish();
	return 0;
}