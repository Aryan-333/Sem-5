#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token {
	char tokenName[100];
	int row, col;
	char type[100];
}token;

FILE *fptr;
char filename[50], buff[50], c;
int ind = 0;
struct token *t;
int row = 1, col = 1;
int j;

char keys[32][10] = {"auto", "break", "case", "char", 
					   "const", "continue", "default", "do", 
					   "double", "else", "enum", "extern", 
					   "float", "for", "goto", "if", 
					   "int", "long", "register", "return", 
					   "short", "signed", "sizeof", "static", 
					   "struct", "switch", "typedef", "union", 
					   "unsigned", "while", "volatile", "void"};

char symbol[9][1] = {'[', ']', '(', ')', '{', '}', ',', ';','@'};

int findSymbol(char ch) {
	for(int i=0; i<9; i++)
		if(symbol[i][0]==ch) return 1;
	return 0;
}


token* getToken(FILE* fptr) {
	token* newToken = (struct token*)malloc(sizeof(*newToken));
	ind = 0;
	c = fgetc(fptr);
	while(c!=EOF){
		if(c==' ' || c=='\t') {
			while(c==' ' || c=='\t') {
				c=fgetc(fptr);
				col++;
			}
			continue;
		}
		if(c == '\n') {
			while(c=='\n') {
				row++;
				c=fgetc(fptr);
			}
			col = 1;
			continue;
		}
		if(c=='#') {
			while(c!='\n') {
				c = fgetc(fptr);
				col++;
			}
			row++;
			col = 1;
			c = fgetc(fptr);
			continue;
		}
		if(c=='/') {
			c = fgetc(fptr);
			col++;
			if(c=='/') {
				while(c!='\n') {
					c = fgetc(fptr);
					col++;
				}
				row++;
				col = 1;
				c = fgetc(fptr);
			}
			else if(c=='*') {
				while(1) {
					while(c!='*') {
						c = fgetc(fptr);
						col++;
					}
					c = fgetc(fptr);
					col++;
					if(c=='/') break;
					else continue;
				}
				c = fgetc(fptr);
				col++;
			}
			continue;
		}
		if(isalpha(c)!=0) {
			newToken->row = row;
			newToken->col = col;
			while(isalpha(c)!=0) {
				buff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			for(j = 0; j<32; j++) {
				if(strcmp(buff, keys[j])==0) {
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"keyword");
					memset(buff, 0, 50);
					break;
				}
			}
			if(j==32) {
			    strcpy(newToken->tokenName,"id");
			    strcpy(newToken->type,"identifier");
				memset(buff, 0, 50);
			}
		}
		else if(isdigit(c)!=0) {
			newToken->row = row;
			newToken->col = col;
			while(isdigit(c)!=0) {
				buff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			strcpy(newToken->tokenName,buff);
			strcpy(newToken->type,"NUM");
			memset(buff, 0, 50);
		}
		else if(findSymbol(c)==1) {
			newToken->tokenName[0] = c;
			newToken->tokenName[1] = '\0';
			newToken->row = row;
			newToken->col = col;
			strcpy(newToken->type,"Special Symbol");
			col++;
		}
		else if(c=='"') {
			newToken->row = row;
			newToken->col = col;
			buff[ind++]=c;
			c = fgetc(fptr);
			col++;
			while(c!='"') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
			}
			buff[ind++]=c;
			buff[ind]='\0';
			col++;
			strcpy(newToken->tokenName, buff);
			strcpy(newToken->type,"string literal");
		}
		else {
			newToken->row = row;
			newToken->col = col;
			if(c=='=') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"relop");
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"assignmentop");
					fseek(fptr, -1, SEEK_CUR);
				}
 			}
			else if(c=='<'||c=='>'||c=='!') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"relop");
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"relop");
					col--;
					fseek(fptr, -1, SEEK_CUR);
				}
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(buff[ind-1]=='+'||buff[ind-1]=='-') {
					if(c=='+'||c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						col++;
						strcpy(newToken->tokenName,buff);
						strcpy(newToken->type,"arop");
					}
					else if((buff[ind-1]=='+' && c=='+')||buff[ind-1]=='-' && c=='-') {
						buff[ind++]=c;
						buff[ind]='\0';
						col++;
						strcpy(newToken->tokenName,buff);
						strcpy(newToken->type,"arop");
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
						strcpy(newToken->type,"arop");
						fseek(fptr, -1, SEEK_CUR);
					}
				}
				else if(buff[ind-1]=='*'||buff[ind-1]=='/') {
					if(c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
						strcpy(newToken->type,"arop");
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
						strcpy(newToken->type,"arop");
						col--;
						fseek(fptr, -1, SEEK_CUR);
					}
				}
			}
			else if(c=='&'|| c=='|'||c=='!'){
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(buff[ind-1]=='&'&&c=='&'|| buff[ind-1]=='|'&&c=='|'){
					buff[ind++]=c;
					buff[ind]='\0';
					col++;
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"logop");
				}
				else if(buff[ind-1]=='!'){
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"logop");
					col--;
					fseek(fptr, -1, SEEK_CUR);
				}
				else{
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					strcpy(newToken->type,"bitwiseop");
					col--;
					fseek(fptr, -1, SEEK_CUR);
				}
			}
 		}
		return newToken;
	}
}

int main() {
	printf("Enter the first file to be opened: ");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
	int row=1;
	while(1) {
		t = getToken(fptr);
		
		if(t->row != row){
			row++;
			printf("\n");
		}
		printf("<%s, %d, %d, %s>   ", t->tokenName, t->row, t->col,t->type);
	}
	fclose(fptr);
	return 0;
}

