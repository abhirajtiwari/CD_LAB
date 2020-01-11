#include <stdio.h>
int main(int argc, char const *argv[])
{
	FILE *fa,*fb;
	fa = fopen("sample.c","r");
	fb = fopen("sample_out.c","w");
	char c;
	char a;
	c = getc(fa);
	while(c != EOF){
		if(c == ' ' || c == '\t'){
			a = getc(fa);
			while(a == ' ' || a == '\t'){
				a = getc(fa);
			}
			putc(' ',fb);
			putc(a,fb);
		}
		else{
			putc(c,fb);
		}
		c = getc(fa);
	}
	return 0;
}