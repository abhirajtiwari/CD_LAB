#include <stdio.h>
/*
Ignoring directives in 
	Comments
	Brackets
*/

int main(int argc, char const *argv[])
{
	FILE *fa, *fb;
	fa = fopen("sample.c","r");
	fb = fopen("sample_out.c","w");
	char c,a;
	c = getc(fa);
	while(c != EOF){
		if(c == '/'){
			putc(c,fb);
			a = getc(fa);
			if(a == '/'){
				//Single line comment
				putc(a,fb);
				while(a != '\n'){
					a = getc(fa);
					putc(a,fb);
				}
			}
			else if(a == '*'){
				//Multiline comment 
				putc(a,fb);
				a = getc(fa);
				while(a != '*'){
					a = getc(fa);
					putc(a,fb);
				}
			}
		}
		else if(c == '('){
			//Bracket mode
			putc(c,fb);
			a = getc(fa);
			while(a != ')'){
				putc(a,fb);
				a = getc(fa);
			}
		}
		else if(c == '#'){
			a = getc(fa);
			while(a != '>'){
				a = getc(fa);
			}
		}
		else{
			putc(c,fb);
		}
		c = getc(fa);

	}
	return 0;
}