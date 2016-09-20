//UNIVERSIDADE DE BRASILIA - UnB
//DEPARTAMENTO DE CIENCIA DA COMPUTACAO - CIC
//DISCIPLINA: ORGANIZACAO DE ARQUIVOS
//PROFESSOR: ANDRE DRUMOND
//
//TITULO: SIMULACAO DE DISCO MAGNETICO RIGIDO
//
//AUTORES:
//	ANDRE ABREU RODRIGUES DE ALMEIDA - 12/0007100 - andre.almeida3@gmail.com
//	BRUNO TAKASHI TENGAN			 - 12/XXXXXXX - xxxxxxx@gmail.com
//
//RESUMO: O PROGRAMA A SEGUIR SIMULA EM LINGUAGEM C++ O FUNCIONAMENTO DE UM DISCO RIGIDO.
//		  OS PONTOS DE DESTAQUE DESTE PROJETO SAO:
//				- A SIMULACAO DE ARMAZENAMENTO DE ARQUIVOS;
//				- A SIMULACAO DE ACESSO AOS ARQUIVOS;
//				- A SIMULACAO DOS TEMPOS DE GRAVACAO E LEIRURA;
//				- A TABELA FAT.




//PONTOS DE INTERESSE E IDEIAS:
/*
0 - Lembrar do ponto extra pro acesso mais rapido: focar agilidade - otimizacao de espaco e secundaria.

1 - PROVAVELMENTE organizacao por cluster UNSPANNED e a mais rapida.
	Cluster spanned precisa procurar pedacos de registro em outros cluster.
3 - pensar em algoritmo para armazenagem focando tempo de gravacao e leitura:
		*gravar cluster de um mesmo arquivo em sequencia/mesmo cilindro - EVITAR SEEK!!
		*possibilidade de pensar em um DEFRAG simplificado em ultimo caso. Provavelmente nao sera necessario -> DIFICIL;
		*pensar em opcoes mais simples de otimizar o acesso;
4 - O slide mostra 4 metodos para melhorar o acesso:
		multiprogramacao, stripping, RAM disk e cashing.
	O unico fazivel e o cashing.

*/




//#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;





//GLOBAIS

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

track_array *cylinder;		//	!!!	use com parcimonia - cada cilindro ocupa 150kB de RAM !!!
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

fatent *fat_table;






//FUNCOES

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


//TABELA FAT
void make_FAT (){
	int size, i;
	size = (300 * n_cyl) - 1;
	fat_table = new fatent[size];
	for (i = 0; i <= size; i++){
		fat_table[i].used = 0;
		fat_table[i].eof = 1;
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






//ESCREVE ARQUIVO
void escreve_arq (){
/*
acha CLUSTER livre - seguir ordem sugerida no roteiro. (implementar conversor registro x cluster primeiro (tamanho 4))
gravar clusters consecutivos em mesmas posicoes do mesmo cilindro em trilhas diferentes (implementar funcao pra achar proximo)
atualiza tabela FAT
calcular tempo gasto (seek medio no primeiro cilindro)
*/
int cluster;
	cluster = first_free ();

}

//LE ARQUIVO
void le_arq (){
/*Procurar nome do arquivo no HD virtual e gravar um arquivo "copia" no HD real com nome SAIDA.TXT*/
}

//APAGA ARQUIVO
void apaga_arq (){
/*varre a tabela FAT definindo o campo "used" como 0 nos registros correspondentes ao arquivo*/
}

//TABELA FAT
void show_FAT (){
/*mostra a tabela*/
}




//SUB-FUNCOES
int first_free(){
	int sector;
	sector = 0; /*apagar*/

/*Esta funcao deve encontrar o primeiro setor livre, percorrendo a tabela FAT de acordo com o algoritmo indicado no roteiro*/

	return sector;
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







