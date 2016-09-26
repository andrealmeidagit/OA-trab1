//#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>


typedef struct fatlist_s {
	int m;
} fatlist;
//fatlist *lista;


int main (){
int i;
int lista[9];
//	lista = new fatlist[9];
	for (i=0;i<9;i++){
		lista[i] = i;
	}
	std::cout << lista << std::endl;
	lista.pushback(9);
	for (i=0;i<10;i++){
		lista[i] = i;
	}
	std::cout << lista << std::endl;



	return 0;
}