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
	char ca,cb;
	ca = getc(fa);
	while(ca != EOF){
		if (ca == '/'){
			cb = getc(fa);
			if(cb == '/'){
				while(ca !='\n'){
					ca = getc(fa);
				}
			}
			else if (cb == '*'){
				do{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				}while(ca != '/');
			}
			else{
				putc(ca,fb);
				putc(cb,fb);
			}
		}
		else{
			putc(ca,fb);
		}
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	printf("\n");
	return 0;
}