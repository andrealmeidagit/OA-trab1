//#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

int main()
{
//VARIAVEIS

	string menu_opc[] = {"1 - Escrever Arquivo", "2 - Ler Arquivo", "3 - Apagar Arquivo", "4 - Mostrar Tabela FAT", "5 - Sair"};

	int menu_i1;
	int i, j;


	//MENU DE INICIALIZACAO
j=1;
while (j==1){
	cout << endl;
	for (i=0;i<5;i++)
		cout << menu_opc[i] << endl;
	cout << endl;
	cin >> menu_i1;

	switch (menu_i1){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			menu_i1 = menu_i1 - 1;
			cout << "voce escolheu " << menu_opc[menu_i1] << endl;
			j=0;
			break;
		default:
			cout << "opcao invalida!!" << endl;
			j=1;
	}
}








/*
	track_array *cylinder;
	
	typedef struct block {
		unsigned char bytes_s[512];
	} block;


	typedef struct sector_array {
		block sector[60];
	} sector_array;

	typedef struct track_array {
		sector_array track[5];
	} track_array;

	typedef struct fatlist_s {
		char file_name[100];
		unsigned int first_sector;
		} fatlist;


	typedef struct fatent_s {
		unsigned int used;
		unsigned int eof;
		unsigned int next;
	} fatent;
*/




	return 0;

}