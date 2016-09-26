//UNIVERSIDADE DE BRASILIA - UnB
//DEPARTAMENTO DE CIENCIA DA COMPUTACAO - CIC
//DISCIPLINA: ORGANIZACAO DE ARQUIVOS
//PROFESSOR: ANDRE DRUMOND
//
//TITULO: SIMULACAO DE DISCO MAGNETICO RIGIDO
//
//AUTORES:
//	ANDRE ABREU RODRIGUES DE ALMEIDA - 12/0007100 - andre.almeida3@gmail.com
//	BRUNO TAKASHI TENGAN			 - 12/0167263 - bt.tengan@gmail.com
//
//RESUMO: O PROGRAMA A SEGUIR SIMULA EM LINGUAGEM C++ O FUNCIONAMENTO DE UM DISCO RIGIDO.
//		  OS PONTOS DE DESTAQUE DESTE PROJETO SAO:
//				- A SIMULACAO DE ARMAZENAMENTO DE ARQUIVOS;
//				- A SIMULACAO DE ACESSO AOS ARQUIVOS;
//				- A SIMULACAO DOS TEMPOS DE GRAVACAO E LEIRURA;
//				- A TABELA FAT.






#include<stdio.h>
#include<iostream>
#include<string>
#include<fcntl.h>
#include<fstream>

using namespace std;




/**********
* GLOBAIS *
**********/


	//estrutura do HD
typedef struct block {
	unsigned char bytes_s[512];		//bytes por setor
} block;

typedef struct sector_array {
	block sector[60];				//setores por trilha
} sector_array;

typedef struct track_array {
	sector_array track[5];			//trilhas por cilindro
} track_array;

track_array *cylinder;
int n_cyl;

	//Tabela FAT
typedef struct fatlist_s {
	char file_name[100];		//nome do arquivo
	unsigned int first_sector;	//numero do primeiro setor
} fatlist;

typedef struct fatent_s {
	unsigned int used;	//flag
	unsigned int eof;	//flag
	unsigned int next;	//numero do setor correspondente
} fatent;

fatent_s *fat_table;
fatlist_s listafat[1000];
int prim_livre = 0;




/********************
*	   FUNCOES		*
********************/




//FUNCOES DE ALOCACAO ----------------------------------------------------------------------


//TABELA FAT
void make_FAT (){
	int size, i;
	size = (300 * n_cyl) - 1;
	fat_table = new fatent[size];
	for (i = 0; i <= size; i++){
		fat_table[i].used = 0;
		fat_table[i].eof = 0;
		fat_table[i].next = 0;
	}
}
void free_FAT (){
	delete[] fat_table;
	cout << "FAT desmontada. ";
}


//ALOCA O DISCO RIGIDO
void make_disk (){
	unsigned int i, j;
	cout << "Quantos cilindros o disco deve ter?" << endl;
	i = 0;
	while (i==0){
		cin >> n_cyl;
		if (n_cyl<=30){
			j = n_cyl * 150;
			cout << "Voce escolheu " << n_cyl << " cilindros. Este disco possui " << j << "kB de espaco no total." << endl;
			n_cyl = n_cyl - 1;
			cylinder = new track_array[n_cyl];	//"n_cyl" definido como 10 pelo roteiro
			i = 1;
			n_cyl = n_cyl + 1;
		}
		else{
			cout << endl << "Por favor, escolha um valor menor que 30." << endl;
			i = 0;
		}
	}
}
//DESALOCA O DISCO RIGIDO
void free_disk (){
	delete[] cylinder;
	cout << "Disco desmontado. Memoria Liberada." << endl;
}




//FUNCOES AUXILIARES ---------------------------------------------------------------------------



int first_free(){
	int setor;
	int i, j, k;	//i==setor da trilha; j==cilindro; k==superficie;
	for (k=0; k<5; k++){
		for(j=0; j<n_cyl; j++){
			for(i=0; i<60; i=i+4){
				setor = (j * 300) + (k * 60) + i;	//indice que indica qual é o setor
				//cout << setor << endl;	//debug
				if (fat_table[setor].used == 0)
					break;
			}
			if (fat_table[setor].used == 0)
				break;
		}
		if (fat_table[setor].used == 0)
			break;
	}
	return setor;
}




int buscaprox(){
	return 0;
}

void salva (char[512] name, unsigned int address){
return;
}






//FUNCOES PRINCIPAIS - OPCOES DO MENU ----------------------------------------------------------


//ESCREVE ARQUIVO
void escreve_arq (){
/*
acha CLUSTER livre - seguir ordem sugerida no roteiro. (implementar conversor registro x cluster primeiro (tamanho 4))
gravar clusters consecutivos em mesmas posicoes do mesmo cilindro em trilhas diferentes (implementar funcao pra achar proximo)
atualiza tabela FAT
calcular tempo gasto (seek medio no primeiro cilindro)
*/
	unsigned int cluster1, cluster2;
	ifstream in_file;
	char nome[100];
	unsigned char buffer[512];
	unsigned int prox;

	cluster1 = first_free();
//cout << cluster << "cluster";	//debug
	cout << "Digite o nome do arquivo?" << endl;
	cin >> nome;

	

	in_file.open (nome);




	while (getline (in_file, buffer)) {
		listafat[prim_livre].first_sector = cluster;	//cria listafat
		listafat[prim_livre].file_name = nome;
		prim_livre++;

		fat_table[cluster1.used] = 1;		//atualiza fat_table
		prox = buscaprox();
		fat_table[cluster1.next] = prox;		//atualiza fat_table

		
		salva(buffer,cluster1);

		cluster2 = cluster1;
		cluster1 = prox;
	}
	in_file.close();

	fat_table[cluster2].eof = 1;

}

//LE ARQUIVO
void le_arq (){
/*Procurar nome do arquivo no HD virtual e gravar um arquivo "copia" no HD real com nome SAIDA.TXT*/

	char find_name[100];
	int flag, count, cyl, tra, sec;
	ofstream file;

	cout << "Entre com o nome do arquivo que quer buscar." << endl << "Nome: ";
	cin >> find_name;										// Pega nome do arquivo.

	flag = 0;
	count = 0;
	do {													// Avalia validade do arquivo.
		if (listafat[count].file_name == find_name){
			flag = 1;
		}
		else {
			count++;
		}
	} while ((flag == 0) && (count < 1000));

	if (flag == 0){											// Caso invalido.
		cout << "Arquivo invalido!" << endl;
	}
	else {													// Caso valido.
		file.open ("SAIDA.TXT", ios::in | ios::out | ios::trunc);	// Deleta saida antiga e faz o novo.

		count = listafat[count].first_sector;						// Busca setor inicial.
		while (fat_table[count].eof == 0){							// Checa se cluster final.
			cyl = count/300;										// Identifica cilindro.
			tra = (count%300)/60;									// Identifica trilha do cilindro.

			file << cylinder[cyl].track[tra].sector[count].bytes_s;
			file << cylinder[cyl].track[tra].sector[count+1].bytes_s;
			file << cylinder[cyl].track[tra].sector[count+2].bytes_s;
			file << cylinder[cyl].track[tra].sector[count+3].bytes_s;

			count = fat_table[count+3].next;							// Pega proximo cluster.
		}

		cyl = count/300;
		tra = (count%300)/60;
		flag = 0;
		sec = count;
		do {														// Ultimo cluster.
			file << cylinder[cyl].track[tra].sector[sec].bytes_s;
			sec++;
		} while (flag == (fat_table[count].eof - 1));

		cout << "Operação finalizada com sucesso." << endl;

		file.close();												// Fecha saida.txt.
	}
}


//APAGA ARQUIVO
void apaga_arq (){
/*varre a tabela FAT definindo o campo "used" como 0 nos registros correspondentes ao arquivo*/
}

//TABELA FAT
void show_FAT (){
/*mostra a tabela*/
}




//MENU DE INICIALIZACAO - Interface usuario
int menu (){
	string menu_opc[] = {"1 - Escrever Arquivo", "2 - Ler Arquivo", "3 - Apagar Arquivo", "4 - Mostrar Tabela FAT", "5 - Sair"};
	unsigned int menu_i;
	unsigned int i, j;
	j=1;
	while (j==1){			//Loop ate que o valor de entrada seja valido (nao forcar demais, as vezes buga)
		cout << endl;
		for (i=0;i<5;i++)
			cout << menu_opc[i] << endl;		//imprime as opcoes na tela
		cout << endl;
		cin >> menu_i;

		switch (menu_i){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				menu_i = menu_i - 1;			//o valor de "menu_i", de 0 a 4 indica qual opcao foi escolhida
				cout << "voce escolheu " << menu_opc[menu_i] << endl;
				j=0;
				break;
			default:
				cout << "opcao invalida!!" << endl;
				j=1;
		}
	}
return menu_i + 1;
}







int main()
{
//VARIAVEIS
	int menu_input, running;



//CORPO DO PROGRAMA
make_disk(); make_FAT();


running = 1;
while (running == 1){
	menu_input = menu();
	switch (menu_input){
		case 1:			//ESCREVE ARQUIVO
			escreve_arq();
			running = 1;
			break;
		case 2:			//LE ARQUIVO
			le_arq();
			running = 1;
			break;
		case 3:			//APAGA ARQUIVO
			apaga_arq();
			running = 1;
			break;
		case 4:			//TABELA FAT
			show_FAT();
			running = 1;
			break;
		case 5:			//SAIR
			cout << "Ate logo!" << endl;
			running = 0;
			break;
		default:
			running = 0;
			break;
	}

}



free_FAT(); free_disk();	//INDISPENSAVEL!!!!!
	return 0;
}







