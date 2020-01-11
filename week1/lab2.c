#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	FILE *fa,*fb;
	fa = fopen("sample.c","r");
	if(fa == NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("sample_out.c","w");
	char ca,cb,cprev,cmain;
	cmain = getc(fa);
	cprev = '\n';
	int lno = 1;
	while(cmain != EOF){
		if (cmain == '/'){
			ca = getc(fa);
			if(ca == '/'){
				//single comment state
				putc(cmain,fb);
				putc(ca,fb);
				cb = getc(fa);
				while(cb!='\n'){
					putc(cb,fb);
					cb = getc(fa);
				}
				putc(cb,fb);
			}
			else if(ca == '*'){
				//multiline state
				putc(cmain,fb);
				putc(ca,fb);
				do{
					cb = getc(fa);
					while(cb!='*'){
						putc(cb,fb);
						cb = getc(fa);
					}
					putc(cb,fb);
					ca = getc(fa);
				}while(ca!='/');
				putc(ca,fb);
			}
			else{
				putc(cmain,fb);
				putc(ca,fb);
			}
		}
		else{
			if(cmain == '#' && (cprev == '\n' || cprev =='\t')){
				cb = getc(fa);
				while(cb != '\n'){
					cb = getc(fa);
				}
				cprev = cb;
			}
			else{
				putc(cmain,fb);
				cprev = cmain;
			}
		}
		cmain = getc(fa);
	}
	return 0;
}
/*if(ca == '#' && (cprev == '\n' || cprev =='\t')){
			cb = getc(fa);
			while(cb != '\n'){
				cb = getc(fa);
			}
		}
		else{
			putc(ca,fb);
		}
		cprev = ca;
		ca = getc(fa);
		*/
