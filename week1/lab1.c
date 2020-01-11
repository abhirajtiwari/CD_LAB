#include <stdio.h>
#define abc #include <stdlib.h>
abc
int main(int argc, char const *argv[])
{
	FILE *fa,*fb;
	fa = fopen("sample.c","r");
	fb = fopen("sample_out.c","w");
	char ca,cb;
	ca = getc(fa);
	while(ca != EOF){
		if ( ca == '\"'){
			putc(ca,fb);
			cb = getc(fa);
			while(cb != '\"'){
				putc(cb,fb);
				cb = getc(fa);
			}
			putc(cb,fb);
		}
		else{
			if(ca == ' '){
				cb = getc(fa);
				while(cb == ' ' || cb == '\t'){
					cb = getc(fa);
				}
				putc(ca,fb);
				putc(cb,fb);
			}
			else if(ca == '\t'){
				cb = getc(fa);
				while(cb == ' ' || cb == '\t'){
					cb = getc(fa);
				}
				putc(ca,fb);
				putc(cb,fb);
			}
			else{
				putc(ca,fb);
			}
		}
		ca = getc(fa);
	}
	return 0;
}
/*
if(ca == ' '){
			cb = getc(fa);
			while(cb == ' '){
				cb = getc(fa);
			}
			putc(ca,fb);
			putc(cb,fb);
		}
		else{
			putc(ca,fb);
		}
		ca = getc(fa);
		*/