// S-->UVW
// U -->(S) | aSb | d
// V --> aV | 𝜖
// W --> cW | 𝜖
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr=0;
char str[100];

void S();
void U();
void V();
void W();


void invalid() {
	printf("Error");
	exit(0);
}

void valid() {
	printf("Success");
	exit(0);
}

void S(){
	U();
	V();
	W();
}


void U(){
	if(str[curr] == '('){
		curr++;
		S();
		if(str[curr] == ')'){
			curr++;
			return;
		} else {invalid();}
	}

	else if(str[curr] == 'a'){
		curr++;
		S();
		if(str[curr] == 'b'){
			curr++;
			return;
		}
		else {invalid();}
	}
	else if(str[curr] == 'd'){
		curr++;
		return;
	}
		else invalid();
}

void V() {
	if(str[curr]=='a'){
		curr++;
		V();
	}
}

void W() {
	if(str[curr]=='c'){
		curr++;
		W();
	}
}

int main() {
	printf("Enter the string\n");
	scanf("%s",str);
	S();
	if(str[curr]=='$') {
		valid();
	}
	else{
		invalid();
	}
}
