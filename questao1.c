#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da arvore binaria
typedef struct No {
    int dado;
    struct No* esquerdo;
    struct No* direito;
} No;

// Cria um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = valor;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

// Insere um valor na arvore binaria de busca
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->dado)
        raiz->esquerdo = inserir(raiz->esquerdo, valor);
    else if (valor > raiz->dado)
        raiz->direito = inserir(raiz->direito, valor);
    return raiz;
}

// Busca um valor na arvore
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return raiz;
    if (valor < raiz->dado)
        return buscar(raiz->esquerdo, valor);
    return buscar(raiz->direito, valor);
}

// Remove todos os nós da arvore
void remover(No* raiz) {
    if (raiz == NULL) return;
    remover(raiz->esquerdo);
    remover(raiz->direito);
    free(raiz);
}

// Percorre a arvore em ordem (in-ordem)
void inOrdem(No* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerdo);
        printf("%d ", raiz->dado);
        inOrdem(raiz->direito);
    }
}

// Percorre a arvore em pre-ordem
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdem(raiz->esquerdo);
        preOrdem(raiz->direito);
    }
}

// Percorre a arvore em pos-ordem
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerdo);
        posOrdem(raiz->direito);
        printf("%d ", raiz->dado);
    }
}

// Calcula a altura da arvore
int altura(No* raiz) {
    if (raiz == NULL) return -1;
    int altEsq = altura(raiz->esquerdo);
    int altDir = altura(raiz->direito);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

// Calcula a profundidade de um valor
int profundidade(No* raiz, int valor, int nivel) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return nivel;
    if (valor < raiz->dado)
        return profundidade(raiz->esquerdo, valor, nivel + 1);
    else
        return profundidade(raiz->direito, valor, nivel + 1);
}

// Soma os valores da arvore
int somaValores(No* raiz) {
    if (raiz == NULL) return 0;
    return raiz->dado + somaValores(raiz->esquerdo) + somaValores(raiz->direito);
}

// Retorna o nivel de um nó
int nivel(No* raiz, int valor) {
    return profundidade(raiz, valor, 0);
}

// Conta o total de nós
int contarNos(No* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esquerdo) + contarNos(raiz->direito);
}

// Conta o total de folhas
int contarFolhas(No* raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esquerdo == NULL && raiz->direito == NULL) return 1;
    return contarFolhas(raiz->esquerdo) + contarFolhas(raiz->direito);
}

// Função principal para testes
int main() {
    No* raiz = NULL;

    // Inserindo valores de exemplo
    int valores[] = {10, 5, 15, 3, 7, 12, 18};
    for (int i = 0; i < 7; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Percurso In-Ordem: ");
    inOrdem(raiz);
    printf("\n");

    printf("Percurso Pre-Ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso Pos-Ordem: ");
    posOrdem(raiz);
    printf("\n");

    printf("Altura da arvore: %d\n", altura(raiz));
    printf("Profundidade do valor 7: %d\n", profundidade(raiz, 7, 0));
    printf("Soma dos valores: %d\n", somaValores(raiz));
    printf("Nivel do valor 7: %d\n", nivel(raiz, 7));
    printf("Numero total de nos: %d\n", contarNos(raiz));
    printf("Numero de folhas: %d\n", contarFolhas(raiz));

    // Teste de busca
    No* encontrado = buscar(raiz, 12);
    if (encontrado != NULL)
        printf("Busca: valor %d encontrado na arvore.\n", encontrado->dado);
    else
        printf("Busca: valor nao encontrado.\n");

    // Liberar memoria
    remover(raiz);

    return 0;
}
