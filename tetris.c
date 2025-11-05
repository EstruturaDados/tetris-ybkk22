#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.



// 🧩 Nível Novato: Fila de Peças Futuras


#define MAX_FILA 5  // Tamanho máximo da fila (5 peças visíveis no jogo)

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único (sequencial)
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct {
    Peca itens[MAX_FILA]; // Vetor que armazena as peças
    int inicio;           // Índice da primeira peça (frente da fila)
    int fim;              // Índice da próxima posição livre (fim da fila)
    int qtd;              // Quantidade de peças atualmente na fila
    int prox_id;          // Próximo ID a ser usado nas peças
} Fila;

// ---------------------------
// Protótipos das Funções
// ---------------------------
Peca gerarPeca(Fila *f);
void inicializarFila(Fila *f);
int inserirPeca(Fila *f);
int jogarPeca(Fila *f);
void exibirFila(Fila *f);

// ---------------------------
// Função que gera uma nova peça aleatória
// ---------------------------
Peca gerarPeca(Fila *f) {
    // Lista de tipos possíveis de peças
    char tipos[] = {'I', 'O', 'T', 'L'};

    // Cria uma nova peça com tipo aleatório e ID único
    Peca nova;
    nova.nome = tipos[rand() % 4];  // Sorteia um tipo entre os 4 disponíveis
    nova.id = f->prox_id++;         // Define o ID e já prepara o próximo
    return nova;
}

// ---------------------------
// Inicializa a fila e gera as 5 primeiras peças
// ---------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    f->prox_id = 1; // IDs começam em 1

    // Gera e adiciona as peças iniciais na fila
    for (int i = 0; i < MAX_FILA; i++) {
        f->itens[f->fim] = gerarPeca(f);            // Gera nova peça
        f->fim = (f->fim + 1) % MAX_FILA;           // Atualiza posição de fim (fila circular)
        f->qtd++;                                   // Incrementa a quantidade
    }
}

// ---------------------------
// Insere uma nova peça no final da fila (enqueue)
// ---------------------------
int inserirPeca(Fila *f) {
    if (f->qtd == MAX_FILA) { // Se a fila estiver cheia, não insere
        printf(" Fila cheia! Não é possível inserir nova peça.\n");
        return 0;
    }

    // Adiciona uma nova peça gerada automaticamente
    f->itens[f->fim] = gerarPeca(f);
    f->fim = (f->fim + 1) % MAX_FILA; // Move o índice de fim circularmente
    f->qtd++;
    return 1;
}

// ---------------------------
// Remove a peça da frente da fila (dequeue)
// ---------------------------
int jogarPeca(Fila *f) {
    if (f->qtd == 0) { // Verifica se há peças
        printf(" Fila vazia! Nenhuma peça para jogar.\n");
        return 0;
    }

    // Pega a peça da frente da fila
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA; // Avança o início circularmente
    f->qtd--;

    // Mostra qual peça foi jogada
    printf(" Peça jogada: %c (ID %d)\n", p.nome, p.id);
    return 1;
}

// ---------------------------
// Exibe todas as peças da fila
// ---------------------------
void exibirFila(Fila *f) {
    printf("\n Fila de peças: ");
    if (f->qtd == 0) { // Caso não haja peças
        printf("[vazia]\n");
        return;
    }

    // Percorre a fila circularmente e mostra cada peça
    for (int i = 0, j = f->inicio; i < f->qtd; i++, j = (j + 1) % MAX_FILA)
        printf("[%c %d] ", f->itens[j].nome, f->itens[j].id);

    printf("\n");
}

// ---------------------------
// Função principal (menu do jogo)
// ---------------------------
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Fila f;   // Cria a fila de peças
    int op;   // Variável para armazenar a opção do usuário

    inicializarFila(&f); // Gera as peças iniciais

    do {
        exibirFila(&f); // Mostra a fila atual
        printf("\n MENU:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        // Executa a ação conforme a escolha do usuário
        switch (op) {
            case 1:
                if (jogarPeca(&f)) inserirPeca(&f); // Ao jogar, adiciona nova peça no final
                break;
            case 2:
                inserirPeca(&f);
                break;
            case 0:
                printf(" Saindo do jogo...\n");
                break;
            default:
                printf(" Opção inválida! Tente novamente.\n");
        }
    } while (op != 0);

    return 0;
}




    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

