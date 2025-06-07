#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó com dados do aluno
typedef struct Aluno {
    char nome[50];
    int matricula;
    float nota;
    struct Aluno* esquerdo;
    struct Aluno* direito;
} Aluno;

// Cria novo aluno
Aluno* criarAluno(char nome[], int matricula, float nota) {
    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->nota = nota;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

// Inserção ordenada por matrícula
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

// Busca aluno pelo nome (varre toda a árvore)
Aluno* buscarPorNome(Aluno* raiz, char nome[]) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->nome, nome) == 0)
        return raiz;

    Aluno* encontrado = buscarPorNome(raiz->esquerdo, nome);
    if (encontrado != NULL) return encontrado;

    return buscarPorNome(raiz->direito, nome);
}

// Impressão in-ordem (ordenado por matrícula)
void imprimirInOrdem(Aluno* raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esquerdo);
        printf("Nome: %s | Matrícula: %d | Nota: %.2f\n", raiz->nome, raiz->matricula, raiz->nota);
        imprimirInOrdem(raiz->direito);
    }
}

// Soma todas as notas e conta os alunos
void somarNotas(Aluno* raiz, float* soma, int* contador) {
    if (raiz == NULL) return;

    somarNotas(raiz->esquerdo, soma, contador);
    *soma += raiz->nota;
    (*contador)++;
    somarNotas(raiz->direito, soma, contador);
}

// Calcula a média das notas
float calcularMediaNotas(Aluno* raiz) {
    float soma = 0;
    int contador = 0;
    somarNotas(raiz, &soma, &contador);

    if (contador == 0) return 0;
    return soma / contador;
}

// Libera memória da árvore
void liberarArvore(Aluno* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerdo);
        liberarArvore(raiz->direito);
        free(raiz);
    }
}

// Função principal
int main() {
    Aluno* raiz = NULL;

    // Inserindo alunos
    raiz = inserirAluno(raiz, "Ana", 101, 8.5);
    raiz = inserirAluno(raiz, "Bruno", 103, 7.2);
    raiz = inserirAluno(raiz, "Carlos", 100, 9.0);
    raiz = inserirAluno(raiz, "Daniela", 102, 6.8);

    // Mostra a árvore in-ordem
    printf("Alunos na árvore (ordenados por matrícula):\n");
    imprimirInOrdem(raiz);

    // Buscar aluno pelo nome
    char nomeBusca[50];
    printf("\nDigite o nome do aluno a buscar: ");
    scanf("%49s", nomeBusca);

    Aluno* resultado = buscarPorNome(raiz, nomeBusca);

    if (resultado != NULL) {
        printf("\nAluno encontrado:\n");
        printf("Nome: %s | Matrícula: %d | Nota: %.2f\n", resultado->nome, resultado->matricula, resultado->nota);
    } else {
        printf("\nAluno com nome '%s' não encontrado.\n", nomeBusca);
    }

    // Calcular e mostrar a média das notas
    float media = calcularMediaNotas(raiz);
    printf("\nMédia das notas dos alunos: %.2f\n", media);

    // Libera a memória
    liberarArvore(raiz);

    return 0;
}
