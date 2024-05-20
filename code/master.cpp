//Alunos contribuintes em ordem alfabética:
// - José Oliveira Neto (Nome completo pendente)
// - Kayke Nícolas Ferreira Gonçalves Campos
// - Victor Vinícius (Nome completo pendente)

#include <iostream>
#include <string>
using namespace std;

//Estruturas
struct Nolista{ //Nó da lista de participantes
    string email;
    string nome;
    int num_ins;
    Nolista *prox;
    Nolista *ant;
};

struct Descritor{
    int tam;
    Nolista *ini;
    Nolista *fim;
};


//Funções
Descritor *criar_lista(){
    Descritor *novo = new Descritor;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

void inserir_fim(Descritor *l, string nome, string email){
    //Criando novo espaço de memória
    Nolista *novo = new Nolista;
    novo -> email = email;
    novo -> nome = nome;
    novo -> num_ins = l -> tam+1; //O número de inscrição é a posição dele na lista
    novo -> prox = NULL;
    novo -> ant = NULL;

    //Colocando o elemento na lista
    if(l -> tam == 0){
        l -> ini = novo;
        l -> fim = novo;
    }else{
        l -> fim -> prox = novo;
        novo -> ant = l -> fim;
        l -> fim = novo;
    }
    l -> tam++; //Sempre adiciona mais um ao tamanho da lista
}

void imprimir_lista(Descritor *l){
    Nolista *p = l -> ini;
    while(p != NULL){
        cout << "Nome: " << p -> nome << endl;
        cout << "E-mail: " << p -> email << endl;
        cout << "Numero de Inscricao: " << p -> num_ins << endl << endl;
        p = p -> prox;
    }
}

int main(){
    //Declarações
    Descritor *part = criar_lista(); //Part = Participantes

    //Leitura de dados
    inserir_fim(part, "Kayke", "Kayke@you");
    inserir_fim(part, "Nicolas", "Nicolas@me");

    //Saída
    imprimir_lista(part);
}