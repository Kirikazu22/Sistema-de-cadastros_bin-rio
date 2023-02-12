#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>
 
using namespace std;

struct Data {
    char first[252];
    long long second;
    char third[252];
    float fourth;
    float fifth;
};

// Gera o arquivo binário
void generateBin() {
    ifstream base("base16_OK.csv", ios_base::in);
    ofstream baseBin("base16_OK.bin", ios::binary);
    string aux;

    if(base.is_open()){
        cout << "Iniciando leitura do arquivo ..." << endl;

        while (getline(base, aux)) {
            // É uma biblioteca que permite trabalhar com strings de forma mais fácil, permitindo que você leia a string como uma linha de arquivo 
            stringstream linestream(aux);
            string cell;
            Data data;

            // O getLine lê as informações da linestream, que recebeu os dados de aux do arquivo binário, até encontrar o ; e armazena em cell
            // Após a leitura, pelo o que eu entendi, ela passa o ponteiro para o próximo caracter delimitador
            getline(linestream, cell, ';');
            strcpy(data.first, cell.c_str());

            getline(linestream, cell, ';');
            data.second = stoll(cell);

            getline(linestream, cell, ';');
            strcpy(data.third, cell.c_str());

            getline(linestream, cell, ';');
            // Troca a , pelo . para fazer a conversão em float
            cell = regex_replace(cell, regex(","), ".");
            data.fourth = stof(cell);

            getline(linestream, cell);
            cell = regex_replace(cell, regex(","), ".");
            data.fifth = stof(cell);

            // Armazena a informação da struct Data no arquivo binário
            baseBin.write(reinterpret_cast<char*>(&data), sizeof(Data));
        }

        base.close();
        baseBin.close();
            
        cout << "Arquivo binario gerado com sucesso" << endl;
        
    } else cout << "Nao foi possivel abrir o arquivo base.csv" << endl;
}

void selectionSort(Data vetor[], int tam){
    int menor; 
    Data a;

    for (int indice = 0; indice < tam-1; indice++) {
   	 menor = indice;
   	 for (int j = indice + 1; j < tam; j++) {
   		 if (vetor[j].fourth < vetor[menor].fourth){
   			 menor = j;
   		 }
   	 }
   	 a = vetor[indice];
   	 vetor[indice] = vetor[menor];
   	 vetor[menor] = a;
    }
}

void insert(Data *data, int size){
    ofstream baseBin("base16_OK.bin", ios::binary);
    

        for(int i = 0; i < size; i++) {
            // É uma biblioteca que permite trabalhar com strings de forma mais fácil, permitindo que você leia a string como uma linha de arquivo 
           

            // Armazena a informação da struct Data no arquivo binário
            baseBin.write(reinterpret_cast<char*>(&data[i]), sizeof(Data));
        }

        baseBin.close();
}

void deletar(){

}

void showTable(Data readData, int size){
    int aux = 0;
    ifstream baseBin("base16_OK.bin", ios_base::binary);
    Data *data = new Data[size];

    while (baseBin.read(reinterpret_cast<char*>(&readData), sizeof(Data))) {
        data[aux] = readData;   
        aux++;
    }
    
    for(int i = 0; i < size; i++){
        cout << data[i].first << endl;
        cout << data[i].second << endl;
        cout << data[i].third << endl;
        cout << data[i].fourth << endl;
        cout << data[i].fifth << endl;
    }

    baseBin.close();
}

void showMenu(){
    cout << "\n\t\t\tSISTEMA DE CADASTROS\n\n1-Inserir\t\t2-Deletar\t\t3-Imprimir\n4-Ordenar por preco\t5-Ordenar por nome\t0-Sair\n";
}

int main(void) {
	generateBin();

    ifstream baseBin("base16_OK.bin", ios_base::binary);
    Data readData;

    if(baseBin.is_open()){
        // Pega a quantidade de dados do tipo Data salvo no arquivo binário
        int size = 0;
        while (baseBin.read(reinterpret_cast<char*>(&readData), sizeof(Data))) size++;

        // To fechando o arquivo pois com o metodo seekg não funciona
        // Juliana disse que vai me ajudar a encontrar o error
        baseBin.close();
        baseBin.open("base16_OK.bin", ios_base::binary);

        if(baseBin.is_open()){
            Data *data = new Data[size];

            // Salva as informações do arquivo binário em Data
            int aux = 0;
            while (baseBin.read(reinterpret_cast<char*>(&readData), sizeof(Data))) {
                data[aux] = readData; 
                aux++;
            }
            
            cout << "Array de dados gerado com sucesso, pode comecar os filtros" << endl;
            // A PARTIR DAQUI É POSSÍVEL APLICAR OS FILTROS NO ARRAY DATA!
            

        //INTERFACE
            int selector;
            
            do{         
                showMenu();
                       
                cin >> selector;

                switch (selector){
                    //inserir
                    case 1:
                
                
                    //deletar
                    case 2:

                
                    //imprimir
                    case 3:
                        showTable(readData, size);
                
                    //ordenar 1
                    case 4:
                        selectionSort(data, size);
                        insert(data, size);
                
                    //ordenar 2
                    case 5:

                
                    //erros
                    default:
                    

                    };

                //limpar da tela e voltar para função inicial
            }while(selector != 0);



        } else {
            cout << "Erro ao abrir base.bin" << endl;
        }

    } else {
        cout << "Erro ao abrir base.bin" << endl;
    }

	return 0;
}
