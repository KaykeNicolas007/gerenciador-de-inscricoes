# Gerenciador de Inscrições

Sistema de linha de comando, em C++, para gerenciar a participação em um evento: cadastra participantes e atividades, registra quem esteve presente em cada atividade, calcula a frequência de cada pessoa e sorteia brindes entre quem atingiu a frequência mínima.

Foi desenvolvido na disciplina **Linguagem de Programação I (LPI)**, ministrada pelo professor Ricardo Ribeiro, no Campus VII da Universidade Estadual da Paraíba (UEPB), no curso de Ciência da Computação. A ideia foi aplicar o que a disciplina ensinou (listas encadeadas, ponteiros, alocação dinâmica, matrizes e modularização) na modelagem de um problema próximo de um caso real.

## Autores

- José Oliveira de Almeida Neto
- Kayke Nícolas Ferreira Gonçalves Campos
- Victor Vinícius de Araujo

## Como funciona

O programa roda em uma única execução, em seis etapas sequenciais:

1. **Cadastro de participantes:** nome e e-mail. Cada participante recebe um número de inscrição, que corresponde à sua posição na lista (começando em 0).
2. **Cadastro de atividades:** título, tipo (painel, palestra, competição etc.) e data/hora, digitados como texto livre.
3. **Registro de presenças:** para cada par participante × atividade, o programa pergunta se a pessoa compareceu (`S`/`N`).
4. **Cálculo de frequência:** porcentagem de atividades a que cada participante compareceu.
5. **Seleção de elegíveis:** quem tem frequência **igual ou superior a 75%** entra na lista de elegíveis.
6. **Sorteio:** são sorteados 3 brindes entre os elegíveis, e os dados de cada vencedor (nome, e-mail e número de inscrição) são exibidos.

Nos cadastros, digite `FIM` (ou `fim`) para encerrar a etapa.

## Como compilar e executar

É necessário ter um compilador C++ (por exemplo, o `g++`).

```bash
g++ master.cpp -o gerenciador
./gerenciador
```

## Exemplo de uso

```
----------------------------------------
        CADASTRO DE PARTICIPANTES
----------------------------------------
Digite FIM, para encerrar o programa!!
Nome: Maria Silva
Email: maria@email.com

Digite FIM, para encerrar o programa!!
Nome: FIM

(... cadastro de atividades ...)

Maria Silva foi para a atividade Palestra de Abertura? [S/N]: S
(...)

O vencedor do premio de numero 1 foi: Maria Silva
Nome: Maria Silva
Email: maria@email.com
Numero de Inscricao: 0
```

## Estrutura do código

| Elemento                                      | Função                                                                     |
| --------------------------------------------- | -------------------------------------------------------------------------- |
| `Nopart` / `Noatv`                            | Nós das listas duplamente encadeadas de participantes e atividades         |
| `Descpart` / `Descatv`                        | Descritores das listas (tamanho, início e fim)                             |
| `criar_lista_part`, `criar_lista_atv`         | Criação das listas vazias                                                  |
| `inserir_fim_part`, `inserir_fim_atv`         | Inserção no final das listas                                               |
| `cadastrar_part`, `cadastrar_atv`             | Interação com o usuário para os cadastros                                  |
| `criar_matriz`, `registrar_presenca`          | Matriz booleana (participantes × atividades) e preenchimento das presenças |
| `calcular_frequencia`                         | Calcula a porcentagem de presença de cada participante                     |
| `escolher_elegiveis`                          | Filtra os participantes com frequência mínima de 75%                       |
| `sorteio`                                     | Sorteia os brindes entre os elegíveis                                      |
| `linha`, `cabecalho`, `imprimir_participante` | Funções auxiliares de saída                                                |

## Conhecimentos desenvolvidos

- **Colaboração em equipe:** primeira disciplina com projeto não individual, exigindo divisão de tarefas, comunicação e alinhamento sobre o funcionamento da aplicação.
- **Git e GitHub:** uso básico das ferramentas de versionamento e colaboração, comuns no mercado.
- **Estruturas de dados dinâmicas:** listas duplamente encadeadas, com descritores, para participantes e atividades.
- **Ponteiros e alocação dinâmica:** uso de `new` e ponteiros para criar listas e a matriz de presenças em tempo de execução.
- **Matrizes:** matriz booleana que relaciona participantes e atividades.
- **Modularização:** divisão do sistema em funções com responsabilidades específicas.
- **Algoritmos e lógica:** percursos em listas, repetições, condicionais, cálculo de porcentagem e filtragem por critério.
- **Entrada e saída:** `cin`, `cout`, `getline` e formatação com `iomanip`.
- **Números aleatórios:** `rand`, `srand` e `time` (`ctime`) para o sorteio.
- **Modelagem de um problema real:** transformação de um processo de eventos (inscrições, atividades, presenças e brindes) em entidades, operações e regras de negócio.

## Limitações conhecidas

Por ser um projeto acadêmico de segundo período, há pontos que ficaram de fora:

- O sorteio não remove o vencedor da lista, então a mesma pessoa pode ganhar mais de um brinde. Também sorteia sempre 3 prêmios, mesmo com menos de 3 elegíveis.
- No registro de presença, qualquer resposta diferente de `N` maiúsculo (inclusive `n`) é tratada como presença.
- Os dados não são salvos: tudo é perdido ao fim da execução.
- A memória alocada com `new` não é liberada.
- Data e hora das atividades são texto livre, sem validação, e não há validação de e-mail.
- O vencedor é localizado por nome, então participantes com nomes iguais teriam os dados exibidos juntos.

## Ideias de evolução

- Menu interativo para executar as etapas em qualquer ordem.
- Persistência dos dados em arquivo.
- Sorteio sem repetição de vencedores.
- Exibição de um relatório final com a frequência de cada participante.
- Liberação adequada da memória ao final do programa.
