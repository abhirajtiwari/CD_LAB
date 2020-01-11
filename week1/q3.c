#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
int isKeyword(char* str) 
{ 
    if (!strcmp(str, "auto") || !strcmp(str, "default")  
        || !strcmp(str, "signed") || !strcmp(str, "enum")  
        ||!strcmp(str, "extern") || !strcmp(str, "for")  
        || !strcmp(str, "register") || !strcmp(str, "if")  
        || !strcmp(str, "else")  || !strcmp(str, "int") 
        || !strcmp(str, "while") || !strcmp(str, "do") 
        || !strcmp(str, "break") || !strcmp(str, "continue")  
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "const") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto") 
        || !strcmp(str, "union") || !strcmp(str, "volatile")) 
        return (1); 
    return (0); 
} 
void print_token(char a[],int len){
	char b[len];
	int k = 0;
	for(int i = 0;i<len;i++){
		if(a[i] == ' ' || a[i] == '\t' || a[i] == '\n' || a[i] == ';'){
			continue;
		}
		else{
			b[k++] = a[i];
		}
	}
	char *str = (char *) malloc(sizeof(char)*k);
	for(int i = 0;i<k;i++){
		str[i] = b[i];
	}
	puts(str);
}
int main(int argc, char const *argv[])
{
	FILE *fa,*fb;
	fa = fopen("sample.c","r");
	fb = fopen("sample_out.c","w");
	int column = 0;
	int row = 0;
	int counter = 0;
	int token_start = 0;
	char c,x;
	c = getc(fa);
	char a[80];
	while(c!=EOF){
		if(c == '/'){
			x = getc(fa);
			if(x == '/'){
				//Single line comment
				while(x != '\n'){
					x = getc(fa);
				}
			}
			else if(x == '*'){
				//Multiline comment 
				x = getc(fa);
				while(x != '*'){
					x = getc(fa);
				}
				x = getc(fa);
				x = getc(fa);
			}
		}
		else{
			if(c == ' '){
				print_token(a,counter);
				counter = 0;
			}
			else if (c == '\n'){
				print_token(a,counter);
				counter = 0;
			}
			else{
				a[counter++] = c;
			}
		}
		c = getc(fa);
	}
	return 0;
}
// if(c == ' '){
		// 	print_token(a,counter);
		// 	counter = 0;
		// }
		// else if (c == '\n'){
		// 	print_token(a,counter);
		// 	counter = 0;
		// }
		// else{
		// 	a[counter++] = c;
		// }