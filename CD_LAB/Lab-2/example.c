//Program to remove single and multiline comments from a given ‘C’ file.
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * fa, * fb;
  int ca, cb;
  fa = fopen("test.c", "r");
  if (fa == NULL) {
    printf("Cannot open file \n");
    exit(0);
  }
  fb = fopen("testout.c", "w");

  ca = getc(fa);
  while (ca != EOF) {

  	    if(ca == '#'){
    	while (ca != '\n'){
          ca = getc(fa);
    	}
      putc(ca, fb);
    }

    if(ca=='#'){continue;
     while(ca=='#'){
     	continue;
     }
      ca = getc(fa);
 }

    if (ca == ' ') {
      putc(ca, fb);
      while (ca == ' ')
        ca = getc(fa);
    }

    if(ca == '\t'){
    	putc(' ' ,fb);
    	while(ca == '\t'){
    		ca = getc(fa);
    	}
    	
    }



    if (ca == '/') {
      cb = getc(fa);
      if (cb == '/') {
        while (ca != '\n')
          ca = getc(fa);
      } else if (cb == '*')
          {
          do {
            while (ca != '*')
              ca = getc(fa);
            ca = getc(fa);
          } while (ca != '/');
        }
      else {
        putc(ca, fb);
        putc(cb, fb);
      }
    } else putc(ca, fb);
    ca = getc(fa);
  }
  fclose(fa);
  fclose(fb);
  return 0;
}