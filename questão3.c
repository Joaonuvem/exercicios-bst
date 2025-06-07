#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore com dados de aluno
typedef struct Aluno {
    char nome[50];
    int matricula;
    float nota;
    struct Aluno* esquerdo;
    struct Aluno* direito;
} Aluno;

// Função para criar novo aluno
Aluno* criarAluno(char nome[], int matricula, float nota) {
    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->nota = nota;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

// Inserção de aluno ordenada por matrícula
Aluno* inserirAluno(Aluno* raiz, char nome[], int matricula, float nota) {
    if (raiz == NULL) {
        return criarAluno(nome, matricula, nota);
    }

    if (matricula < raiz->matricula) {
        raiz->esquerdo = inserirAluno(raiz->esquerdo, nome, matricula, nota);
    } else if (matricula > raiz->matricula) {
        raiz->direito = inserirAluno(raiz->direito, nome, matricula, nota);
    }
    return raiz;
}

// Busca um aluno pelo nome (busca in-order)
Aluno* buscarPorNome(Aluno* raiz, char nome[]) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->nome, nome) == 0)
        return raiz;

    Aluno* resultado = buscarPorNome(raiz->esquerdo, nome);
    if (resultado != NULL)
        return resultado;

    return buscarPorNome(raiz->direito, nome);
}

// Impressão da árvore in-ordem (por matrícula)
void imprimirInOrdem(Aluno* raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esquerdo);
        printf("Nome: %s | Matrícula: %d | Nota: %.2f\n",
               raiz->nome, raiz->matricula, raiz->nota);
        imprimirInOrdem(raiz->direito);
    }
}

// Libera toda a árvore da memória
void liberarArvore(Aluno* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerdo);
        liberarArvore(raiz->direito);
        free(raiz);
    }
}

// Função principal para teste
int main() {
    Aluno* raiz = NULL;

    // Inserindo alunos
    raiz = inserirAluno(raiz, "Ana", 101, 8.5);
    raiz = inserirAluno(raiz, "Bruno", 103, 7.2);
    raiz = inserirAluno(raiz, "Carlos", 100, 9.0);
    raiz = inserirAluno(raiz, "Daniela", 102, 6.8);

    printf("Árvore de alunos (ordem por matrícula):\n");
    imprimirInOrdem(raiz);

    // Buscar aluno pelo nome
    char nomeBusca[50];
    printf("\nDigite o nome do aluno a buscar: ");
    scanf("%49s", nomeBusca);

    Aluno* encontrado = buscarPorNome(raiz, nomeBusca);

    if (encontrado != NULL) {
        printf("\nAluno encontrado:\n");
        printf("Nome: %s | Matrícula: %d | Nota: %.2f\n",
               encontrado->nome, encontrado->matricula, encontrado->nota);
    } else {
        printf("\nAluno com nome '%s' não encontrado.\n", nomeBusca);
    }

    // Liberar memória
    liberarArvore(raiz);

    return 0;
}
