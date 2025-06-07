#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore binária de busca de alunos
typedef struct Aluno {
    char nome[50];
    int matricula;
    float nota;
    struct Aluno* esquerdo;
    struct Aluno* direito;
} Aluno;

// Cria um novo nó de aluno
Aluno* criarAluno(char nome[], int matricula, float nota) {
    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->nota = nota;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

// Insere aluno na árvore baseado na matrícula
Aluno* inserirAluno(Aluno* raiz, char nome[], int matricula, float nota) {
    if (raiz == NULL)
        return criarAluno(nome, matricula, nota);

    if (matricula < raiz->matricula)
        raiz->esquerdo = inserirAluno(raiz->esquerdo, nome, matricula, nota);
    else if (matricula > raiz->matricula)
        raiz->direito = inserirAluno(raiz->direito, nome, matricula, nota);
    return raiz;
}

// Busca um aluno pelo nome
Aluno* buscarPorNome(Aluno* raiz, char nome[]) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0) return raiz;
    Aluno* esq = buscarPorNome(raiz->esquerdo, nome);
    if (esq != NULL) return esq;
    return buscarPorNome(raiz->direito, nome);
}

// Calcula a média das notas dos alunos
float somaNotas(Aluno* raiz, int* total) {
    if (raiz == NULL) return 0;
    *total += 1;
    return raiz->nota +
           somaNotas(raiz->esquerdo, total) +
           somaNotas(raiz->direito, total);
}

float mediaNotas(Aluno* raiz) {
    int total = 0;
    float soma = somaNotas(raiz, &total);
    return total > 0 ? soma / total : 0;
}

// Percorre a árvore in-ordem
void inOrdem(Aluno* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerdo);
        printf("Nome: %s | Matricula: %d | Nota: %.2f\n", raiz->nome, raiz->matricula, raiz->nota);
        inOrdem(raiz->direito);
    }
}

// Remove todos os nós da árvore
void liberarArvore(Aluno* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerdo);
    liberarArvore(raiz->direito);
    free(raiz);
}

// Função principal para testes
int main() {
    Aluno* raiz = NULL;

    // Inserção de alguns alunos
    raiz = inserirAluno(raiz, "Ana", 101, 8.5);
    raiz = inserirAluno(raiz, "Bruno", 103, 7.0);
    raiz = inserirAluno(raiz, "Carlos", 100, 9.0);
    raiz = inserirAluno(raiz, "Daniela", 102, 6.5);

    printf("Alunos em ordem de matricula:\n");
    inOrdem(raiz);

    // Busca por nome
    char nomeBusca[50] = "Bruno";
    Aluno* encontrado = buscarPorNome(raiz, nomeBusca);
    if (encontrado != NULL) {
        printf("\nAluno encontrado:\n");
        printf("Nome: %s | Matricula: %d | Nota: %.2f\n", encontrado->nome, encontrado->matricula, encontrado->nota);
    } else {
        printf("\nAluno com nome '%s' nao encontrado.\n", nomeBusca);
    }

    // Média das notas
    float media = mediaNotas(raiz);
    printf("\nMedia das notas: %.2f\n", media);

    // Libera memória
    liberarArvore(raiz);

    return 0;
}
