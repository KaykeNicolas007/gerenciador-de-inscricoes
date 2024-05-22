//Alunos contribuintes em ordem alfabética:
// - José Oliveira de Almeida Neto 
// - Kayke Nícolas Ferreira Gonçalves Campos
// - Victor Vinícius de Araujo
#include <iostream>
#include <string>
using namespace std;

//Estruturas
struct NoParticipante{ //Nó da lista de participantes
    string email;
    string nome;
    int num_ins;
    NoParticipante *prox;
    NoParticipante *ant;
};

struct DescritorParticipante{ //Descritor de Participantes  //tenho que mudar esse código descritor_participante
    int tam;
    NoParticipante *ini;
    NoParticipante *fim;
};

struct NoAtividade{ //Nó de atividades
    string titulo;
    string data_hora;
    string tipo; //Ex: Painel, Palestra, Competição
    NoAtividade *prox;
    NoAtividade *ant;
}; // o no tem o proximo e o anterior e informações importantes, enquanto os descritores, apenas tamanho, inicio e fim.

struct DescritorAtividade{ //Descritor de atividades
    int tam;
    NoAtividade *ini;
    NoAtividade *fim;
};


//Funções
DescritorParticipante *criar_lista_part(){
    DescritorParticipante *novo = new DescritorParticipante; // descritor do tipo participantes criando novo descritor.
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
} // a função está sendo criada setando ,inicio e fim para NULL e tamanho para 0

DescritorAtividade *criar_lista_atv(){
    DescritorAtividade *novo = new DescritorAtividade;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

void inserir_fim_part(DescritorParticipante *l, string nome, string email){
    //Criando novo espaço de memória
    NoParticipante *novo = new NoParticipante;
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

void inserir_fim_atv(DescritorAtividade *l, string titulo, string tipo, string data_hora){
    //Criando novo espaço de memória
    NoAtividade *novo = new NoAtividade;
    novo -> titulo = titulo;
    novo -> tipo = tipo;
    novo -> data_hora = data_hora;
    novo -> prox = NULL;
    novo -> ant = NULL;

    //Colocando o elemento na lista
    if(l -> tam == 0){
        l -> ini = novo;
        l -> fim = novo;
    }else{
        l -> fim -> prox = novo; // lá o final da lista ta sendo criado o apontador que vai apontar para o proximo elemento
        novo -> ant = l -> fim; //voltando de ré kkkk
        l -> fim = novo;
    }
    l -> tam++; //Sempre adiciona mais um ao tamanho da lista
}

void imprimir_lista_part(DescritorParticipante *l){
    NoParticipante *aux = l -> ini;
    while(aux != NULL){
        cout << "Nome: " << aux -> nome << endl;
        cout << "E-mail: " << aux -> email << endl;
        cout << "Numero de Inscricao: " << aux -> num_ins << endl << endl;
        aux = aux -> prox;
    }
}

void imprimir_lista_atv(DescritorAtividade *l){
    NoAtividade *aux = l -> ini;
    while(aux != NULL){
        cout << "Titulo: " << aux -> titulo << endl;
        cout << "Tipo: " << aux -> tipo << endl;
        cout << "Data e Hora: " << aux -> data_hora << endl << endl;
        aux = aux -> prox;
    }
}

bool **criar_matriz(int lin, int col){
    bool **m = new bool *[lin];
    for(int i = 0; i < lin; i++){
        m[i] = new bool[col];
    }
    return m;
}

void preencher_matriz(DescritorParticipante *l, DescritorAtividade *a, bool **mat, int lin, int col){
    char verificador;
    NoParticipante *aux = l -> ini;
    NoAtividade *auxAtividade = a -> ini;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            cout << aux -> nome << " Esteve presente na atividade: " << auxAtividade -> titulo << "? [S/N]: "; //criar verificador que aceite minusculo ou maisuculo
            cin >> verificador;
            if(verificador == 'N'){
                mat[i][j] = false;
            }else{
                mat[i][j] = true;
            }
            auxAtividade = auxAtividade -> prox;
        }
        aux = aux -> prox;
        auxAtividade = a -> ini;
    }
}

void imprimir_matriz(DescritorParticipante *l, bool **mat, int lin, int col){
    NoParticipante *aux = l -> ini;
    for(int i = 0; i < lin; i++){
        cout << aux -> nome << ": ";
        for(int j = 0; j < col; j++){
            cout << mat[i][j] << " ";
        }
        aux = aux -> prox;
        cout << endl;
    }
}

int main(){
    //1. Cadastro de Participantes:
    DescritorParticipante *part = criar_lista_part(); //Part = Participantes
    inserir_fim_part(part, "Kayke", "Kayke@you");
    inserir_fim_part(part, "Nicolas", "Nicolas@me");
    imprimir_lista_part(part);

    //2. Cadastro de Atividades:
    DescritorAtividade *atv = criar_lista_atv();
    inserir_fim_atv(atv, "Hackathon", "Competicao", "Terca, 20:00");
    inserir_fim_atv(atv, "Desenvolvimento", "Aula", "Quarta, 20:00");
    imprimir_lista_atv(atv);

    //3. Registro de Presenças:
    int quantia_part = part -> tam;
    int quantia_atv = atv -> tam;
    bool **mat_presenca = criar_matriz(quantia_part, quantia_atv);
    
    preencher_matriz(part, atv, mat_presenca, quantia_part, quantia_atv);
   
    imprimir_matriz(part, mat_presenca, quantia_part, quantia_atv);

    //4. Cálculo de Frequência:
}

// esse comentario foi feito por neto.git