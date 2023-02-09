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
    ifstream base("base.csv", ios_base::in);
    ofstream baseBin("base.bin", ios::binary);
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

void insert(){
 //inserir um dado
}

void delet(){
 //deletar um dado
}

void show(){
 //impimir os campos
}

void sort(){

}
/*
void alterar(){

}

void read(){

}

void write(){

}
*/
int main(void) {
	generateBin();

    ifstream baseBin("base.bin", ios_base::binary);
    Data readData;

    if(baseBin.is_open()){
        // Pega a quantidade de dados do tipo Data salvo no arquivo binário
        int size = 0;
        while (baseBin.read(reinterpret_cast<char*>(&readData), sizeof(Data))) size++;

        // To fechando o arquivo pois com o metodo seekg não funciona
        // Juliana disse que vai me ajudar a encontrar o error
        baseBin.close();
        baseBin.open("base.bin", ios_base::binary);

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


        } else {
            cout << "Erro ao abrir base.bin" << endl;
        }

    } else {
        cout << "Erro ao abrir base.bin" << endl;
    }

	return 0;
}
