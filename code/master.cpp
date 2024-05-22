//Alunos contribuintes em ordem alfabética:
// - José Oliveira de Almeida Neto
// - Kayke Nícolas Ferreira Gonçalves Campos
// - Victor Vinícius de Araujo
#include <iostream>
#include <string>
using namespace std;

//Estruturas
struct Nopart{ //Nó da lista de participantes
    string email;
    string nome;
    int num_ins;
    double frequencia;
    Nopart *prox;
    Nopart *ant;
};

struct Despart{ //Descritor de Participantes
    int tam;
    Nopart *ini;
    Nopart *fim;
};

struct Noatv{ //Nó de atividades
    string titulo;
    string data_hora;
    string tipo; //Ex: Painel, Palestra, Competição
    Noatv *prox;
    Noatv *ant;
};

struct Desatv{ //Descritor de atividades
    int tam;
    Noatv *ini;
    Noatv *fim;
};


//Funções
Despart *criar_lista_part(){
    Despart *novo = new Despart;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

Desatv *criar_lista_atv(){
    Desatv *novo = new Desatv;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

void inserir_fim_part(Despart *l, string nome, string email){
    //Criando novo espaço de memória
    Nopart *novo = new Nopart;
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

void inserir_fim_atv(Desatv *l, string tit, string tipo, string data_hora){
    //Criando novo espaço de memória
    Noatv *novo = new Noatv;
    novo -> titulo = tit;
    novo -> tipo = tipo;
    novo -> data_hora = data_hora;
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

void imprimir_lista_part(Despart *l){
    Nopart *p = l -> ini;
    while(p != NULL){
        cout << "Nome: " << p -> nome << endl;
        cout << "E-mail: " << p -> email << endl;
        cout << "Numero de Inscricao: " << p -> num_ins << endl << endl;
        p = p -> prox;
    }
}

void imprimir_lista_atv(Desatv *l){
    Noatv *p = l -> ini;
    while(p != NULL){
        cout << "Titulo: " << p -> titulo << endl;
        cout << "Tipo: " << p -> tipo << endl;
        cout << "Data e Hora: " << p -> data_hora << endl << endl;
        p = p -> prox;
    }
}

bool **criar_matriz(int lin, int col){
    bool **m = new bool *[lin];
    for(int i = 0; i < lin; i++){
        m[i] = new bool[col];
    }
    return m;
}

void preencher_matriz(Despart *l, Desatv *a, bool **mat, int lin, int col){
    char foi;
    Nopart *p = l -> ini;
    Noatv *ap = a -> ini;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            cout << p -> nome << " foi para a atividade " << ap -> titulo << "? [S/N]: ";
            cin >> foi;
            if(foi == 'N'){
                mat[i][j] = false;
            }else{
                mat[i][j] = true;
            }
            ap = ap -> prox;
        }
        p = p -> prox;
        ap = a -> ini;
    }
}

void imprimir_matriz(Despart *l, bool **mat, int lin, int col){
    Nopart *p = l -> ini;
    for(int i = 0; i < lin; i++){
        cout << p -> nome << ": ";
        for(int j = 0; j < col; j++){
            cout << mat[i][j] << " ";
        }
        p = p -> prox;
        cout << endl;
    }
}

void calcular_frequencia(Despart *l, bool **mat, int lin, int col){
    Nopart *aux = l -> ini;
    double cont = 0; //Atividades que cada participante foi
    double result; //Resultado final
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(mat[i][j])
                cont++;
        }
        result = (cont/col)*100; //Quantas atividades ele foi, dividido pelo total de atividades e multiplicado por 100
        aux -> frequencia = result; //Guarda no struct
        aux = aux -> prox;
        cont = 0;
    }
}

int main(){
    //1. Cadastro de Participantes:
    Despart *part = criar_lista_part(); //Part = Participantes
    inserir_fim_part(part, "Juninho", "Junho@you");
    inserir_fim_part(part, "Capixaba", "Capixa@me");
    imprimir_lista_part(part);

    //2. Cadastro de Atividades:
    Desatv *atv = criar_lista_atv();
    inserir_fim_atv(atv, "Hackathon", "Competicao", "Terca, 20:00");
    inserir_fim_atv(atv, "Desenvolvimento", "Aula", "Quarta, 20:00");
    inserir_fim_atv(atv, "Sexo Anal", "Suruba", "Amanha, 20:00");
    imprimir_lista_atv(atv);

    //3. Registro de Presenças:
    int quantia_part = part -> tam;
    int quantia_atv = atv -> tam;
    bool **mat_presenca = criar_matriz(quantia_part, quantia_atv);
    preencher_matriz(part, atv, mat_presenca, quantia_part, quantia_atv);
    imprimir_matriz(part, mat_presenca, quantia_part, quantia_atv);

    //4. Cálculo de Frequência:
    calcular_frequencia(part, mat_presenca, quantia_part, quantia_atv);
    cout << "Presenca total de " << part -> ini -> nome << ": " << part -> ini -> frequencia << "%\n";
    cout << "Presenca total de " << part -> ini -> prox -> nome << ": " << part -> ini -> prox -> frequencia << "%\n";
}