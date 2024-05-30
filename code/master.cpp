/*Alunos desenvolvedores em ordem alfabética:
 - José Oliveira de Almeida Neto
 - Kayke Nícolas Ferreira Gonçalves Campos
 - Victor Vinícius de Araujo
 */
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

struct Nopart{ //Nó Participante
    string nome;
    string email;
    int num_ins;
    double frequencia;
    Nopart *prox;
    Nopart *ant;
};

struct Noatv{ //Nó Atividades
    string titulo;
    string data_hora;
    string tipo; //Ex: Painel, Palestra, Competição...
    Noatv *prox;
    Noatv *ant;
};

struct Descpart{ //Descritor Participantes
    int tam;
    Nopart *ini;
    Nopart *fim;
};

struct Descatv{ //Descritor Atividades
    int tam;
    Noatv *ini;
    Noatv *fim;
};

Descpart *criar_lista_part(){
    Descpart *novo = new Descpart;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

Descatv *criar_lista_atv(){
    Descatv *novo = new Descatv;
    novo -> tam = 0;
    novo -> fim = NULL;
    novo -> ini = NULL;
    return novo;
}

void inserir_fim_part(Descpart *l, string pessoa, string contato){
    Nopart *novo = new Nopart;
    novo -> nome = pessoa;
    novo -> email = contato;
    novo -> num_ins = l -> tam; //O num_ins é a posição dele na lista
    novo -> prox = NULL;
    novo -> ant = NULL;
    if(l -> tam == 0){
        l -> ini = novo;
        l -> fim = novo;
    }else{
        l -> fim -> prox = novo;
        novo -> ant = l -> fim;
        l -> fim = novo;
    }
    l -> tam++;
}

void inserir_fim_atv(Descatv *l, string nome, string tipo, string horario){
    Noatv *novo = new Noatv;
    novo -> titulo = nome;
    novo -> tipo = tipo;
    novo -> data_hora = horario;
    novo -> prox = NULL;
    novo -> ant = NULL;
    if(l -> tam == 0){
        l -> ini = novo;
        l -> fim = novo;
    }else{
        l -> fim -> prox = novo;
        novo -> ant = l -> fim;
        l -> fim = novo;
    }
    l -> tam++;
}

void cadastrar_part(Descpart *l) {
    string nome, email;
    cout << "CADASTRANDO PARTICIPANTES\n";
    do{
        cout << "Digite FIM, para encerrar o programa!!\n";
        cout << "Nome: ";
        getline(cin, nome);
        if(nome != "FIM") {
            cout << "Email: ";
            getline(cin, email);
            if(email != "FIM") 
                inserir_fim_part(l, nome, email);
            }
            cout << endl;
    } while(nome != "FIM" && email != "FIM");
}

void cadastrar_atv(Descatv *l){
    string titulo, tipo, data_hora;
    cout << "CADASTRANDO ATIVIDADES\n";
    do{
        cout << "Digite FIM, para encerrar o programa!!\n";
        cout << "Titulo: ";
        getline(cin, titulo);
        if(titulo != "FIM"){
            cout << "Tipo: ";
            getline(cin, tipo);
            if(tipo != "FIM"){
                cout << "Data e hora: ";
                getline(cin, data_hora);
                if(data_hora != "FIM")
                    inserir_fim_atv(l, titulo, tipo, data_hora);
            }
        }
        cout << endl;
    }while(titulo != "FIM" && tipo != "FIM" && data_hora != "FIM");
}

bool **criar_matriz(int lin, int col){
    if(lin > 0){
        bool **m = new bool *[lin];
        for(int i = 0; i < lin; i++){
            m[i] = new bool[col];
        }
        return m;
    }
    return NULL;
}

void registrar_presenca(Descpart *lista_part, Descatv *lista_atv, bool **mat){
    char verificador;
    Nopart *aux_part = lista_part -> ini;
    Noatv *aux_atv = lista_atv -> ini;
    for(int i = 0; i < lista_part -> tam; i++){
        for(int j = 0; j < lista_atv -> tam; j++){
            cout << aux_part -> nome << " foi para a atividade " << aux_atv -> titulo << "? [S/N]: ";
            cin >> verificador;
            if(verificador == 'N'){
                mat[i][j] = false;
            }else{
                mat[i][j] = true;
            }
            aux_atv = aux_atv -> prox;
        }
        aux_part = aux_part -> prox;
        aux_atv = lista_atv -> ini;
    }
}

void calcular_frequencia(Descpart *l, bool **mat, int lin, int col){
    Nopart *aux = l -> ini;
    double cont = 0; //Quantidade de casos favoráveis
    double result; //Resultado final
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(mat[i][j])
                cont++;
        }
        result = (cont/col)*100; //Quantas atividades ele foi, dividido pelo total de atividades e multiplicado por 100
        aux -> frequencia = result;
        aux = aux -> prox;
        cont = 0;
    }
}

Descpart *escolher_elegiveis(Descpart *l){
    Descpart *elegiveis = criar_lista_part();
    Nopart *aux = l -> ini;
    while(aux != NULL){
        if(aux -> frequencia >= 75.0)
            inserir_fim_part(elegiveis, aux -> nome, aux -> email);
        aux = aux -> prox;
    }
    return elegiveis;
}

void sorteio(Descpart *elegiveis){
    int sorteado;
    int cont = 3;
    int total_premios = 1;
    Nopart *aux = elegiveis -> ini;
    srand(time(NULL));
    if(elegiveis -> tam > 0){
        if(elegiveis -> tam == 1)
            cout << "O vencedor de todos os premios foi: " << elegiveis -> ini -> nome;
        else{
            for(int i = 0; i < cont; i++){
                sorteado = rand() % 3;
                if(sorteado+1 <= elegiveis -> tam){
                    cout << "Numero sorteado: " << sorteado << endl;
                    for(int i = 0; i < sorteado; i++){
                        aux = aux -> prox;
                    }
                    cout << "O vencedor do premio n " << total_premios << " foi: " << aux -> nome << endl;
                    total_premios++;
                    aux = elegiveis -> ini;
                }else
                    cont++;
            }
        }
    }
}

int main(){
    //Declarações
    Descpart *lista_part = criar_lista_part();
    Descpart *elegiveis;
    Descatv *lista_atv = criar_lista_atv();
    bool **matriz_presenca;
    int total_part, total_atv;

    //1. Cadastro de Participantes:
    cadastrar_part(lista_part);

    //2. Cadastro de Atividades:
    cadastrar_atv(lista_atv);

    //3. Registro de Presenças:
    total_part = lista_part -> tam;
    total_atv = lista_atv -> tam;
    matriz_presenca = criar_matriz(total_part, total_atv);
    registrar_presenca(lista_part, lista_atv, matriz_presenca);

    //4. Cálculo de Frequência:
    calcular_frequencia(lista_part, matriz_presenca, total_part, total_atv);

    //5. Sorteio de Brindes:
    elegiveis = escolher_elegiveis(lista_part);

    //6. Realização do Sorteio:
    sorteio(elegiveis);
}