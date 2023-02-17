#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>
#include <vector>
 
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

//Atualiza o arquivo bin com o vetor recebido
void update(Data *data, int size){
    ofstream fileCsv("base16_OK.csv", ios_base::in);

    if(fileCsv.is_open()){
        for (int i = 0; i < size; i++) {
            Data dataActual = data[i];

            fileCsv << dataActual.first << ";" << dataActual.second << ";" << dataActual.third << ";" << dataActual.fourth << ";" << dataActual.fifth << "\n";
        }

        generateBin();
        
    } else cout << "Erro ao atualizar o arquivo base16_OK.csv";
}

int busca(Data *data, int size){
    int i = 0, K = 0, posicao = -1;
    
    while (i < size) {
   	 if (data[i].second == K){
   		 posicao = i;
   	 }
   	 i++;
    }
    return posicao;
}

//Deleta posições do vetor
void remove(Data *data, int size){
    int num;
	
	cout << "Digite o id do cadastro que voce quer apagar" << endl;
    cin >> num;

    data[num-1].first[0] = '\0';
    data[num-1].second = 0;
    data[num-1].third[0] = '\0';
    data[num-1].fourth = 0;
    data[num-1].fifth = 0;

    size--;
    update(data, size);
}	

//Inserir dados
void insert(Data *data, int size){
    
    Data *novadata = new Data[size+1];
    copy(data,data+size,novadata);

	size++;
	
	//Procurar disponibilidade do vetor
	
	int out = busca(novadata, size);
	
    cout << "Digite uma string" << endl;
    cin >> novadata[out].first;
    cout << "Digite um numero" << endl;
    cin >> novadata[out].second;
    cout << "Digite uma string" << endl;
    cin >> novadata[out].third;
    cout << "Digite um numero" << endl;
    cin >> novadata[out].fourth;
    cout << "Digite um numero" << endl;
    cin >> novadata[out].fifth;
	
	
	delete [] data;
    //atualiza o tamanho do vetor
    update(novadata, size);
}

//Imprimir as posições do vetor
void showTable(Data *data, int size){
    //cout << i+1 aumenta as posições para que elas comecem em 1 e 
    //terminem em 1000 
    for(int i = 0; i < size; i++){
		if(data[i].second != 0){
			cout << i+1 << " - \t";
			cout << data[i].first << endl;
			cout << "\t" << data[i].second << endl;
			cout << "\t" << data[i].third << endl;
			cout << "\t" << data[i].fourth << endl;
			cout << "\t" << data[i].fifth << endl;
		}
    }
}

//Imprimir posições selecionadas do vetor
void showpartTable(Data *data, int size){
	int start, end;
	cout << "Digite a primeira posicao da impressao" << endl;
	cin >> start;
	cout << "Digite a ultima posicao da impressao" << endl;
	cin >> end;
	system("cls");
    // "start - 1" garante que todas as posições digitadas sejam impressas
    for(int i = start-1; i < end; i++){
		if(data[i].second != 0){
			cout << i+1 << " - \t";
			cout << data[i].first << endl;
			cout << "\t" << data[i].second << endl;
			cout << "\t" << data[i].third << endl;
			cout << "\t" << data[i].fourth << endl;
			cout << "\t" << data[i].fifth << endl;
		}
    }
}

//Imprime o Menu
void showMenu(){
    cout << "\n\t\t  ----------------------\n\t\t  |SISTEMA DE CADASTROS|\n\t\t  ----------------------\n\n";
    cout << "1-Inserir\t2-Deletar\t\t3-Imprimir parte do codigo\n4-Imprimir\t5-Ordenar por float\t6-Ordenar por long\n0-Sair\n";
}

int main(void) {
	generateBin();

    ifstream baseBin("base16_OK.bin", ios_base::binary);
    Data readData;

    if(baseBin.is_open()){
        // Pega a quantidade de dados do tipo Data salvo no arquivo binário
        int size = 0;
        while (baseBin.read(reinterpret_cast<char*>(&readData), sizeof(Data))) size++;

        // Fechando o arquivo pois com o metodo seekg não funciona
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
            
            while(selector != 0){       
                showMenu();
                       
                cin >> selector;
				system("cls");

                    //inserir
                    if(selector == 1){
                        insert(data, size);
                    //deletar
                    }else if(selector == 2){
                        remove(data, size);
                    //imprimir um trecho
                    }else if(selector == 3){
                        showpartTable(data, size);
                    //imprimir
                    }else if(selector == 4){
						showTable(data, size);
                    //ordenar 1 = Ordena pelo quarto campo(tipo float)
                    }else if(selector == 5){
						
                        update(data, size);
                    //ordenar 2 = Ordena pelo segundo campo(tipo long)
                    }else if(selector == 6){
						
						update(data, size);
                        //Correção de erros	
                    }else{
                        //Correção de erros	
                    }
            }

        } else {
            cout << "Erro ao abrir base.bin" << endl;
        }

    } else {
        cout << "Erro ao abrir base.bin" << endl;
    }

	return 0;
}
