#include<stdio.h>

void printhi(int x){
	printf("hi %d",x);
}

int print(int y){
	printf("%d",y);
}

int main(){
	int a,b;
	a=10;
	b=15;
	printhi(a);
	print(b);
}
