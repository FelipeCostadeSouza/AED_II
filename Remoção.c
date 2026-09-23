PArvABB remover(PArvABB a, int x) {
	PArvABB t,pai;
	if(a==NULL) {
		return NULL;
	}
	if(x<a->info) {
		a->esq1=remover(a->esq1, x);
	} else if(x>a->info) {
		a->dir1=remover(a->dir1, x);
	} else {
		if(a->esq1==NULL && a->dir1==NULL) {
			free(a);
			return NULL;
		}
		if(a->dir1==NULL) {
			t=a->esq1;
			free(a);
			return t;
		}
		if(a->esq1==NULL) {
			t=a->dir1;
			free(a);
			return t;
		}
		pai=a;
		t=a->esq1;
		while(t->dir1!=NULL) {
			pai=t;
			t=t->dir1;
		}
		a->info=t->info;
		if(pai==a) {
			pai->esq1=t->esq1;
		} else {
			pai->dir1=t->esq1;
		}
		free(t);
		return a;
	}
}
/////////////////////////////////////////////////////////////////////////
4
	////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó da Árvore
typedef struct No {
    int chave;
    struct No* esq;
    struct No* dir;
} No;

// Estrutura do Nó da Pilha (lista encadeada simples)
typedef struct NoPilha {
    No* noArvore;
    struct NoPilha* prox;
} NoPilha;

// Funções auxiliares para a Pilha
void empilhar(NoPilha** topo, No* noArvore) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->noArvore = noArvore;
    novo->prox = *topo;
    *topo = novo;
}

int pilhaVazia(NoPilha* topo) {
    return topo == NULL;
}

No* desempilhar(NoPilha** topo) {
    if (pilhaVazia(*topo)) return NULL;
    NoPilha* temp = *topo;
    No* noArvore = temp->noArvore;
    *topo = (*topo)->prox;
    free(temp);
    return noArvore;
}

// Função Principal: Percurso Em-Ordem Iterativo
void emOrdemIterativo(No* raiz) {
    NoPilha* pilha = NULL;
    No* atual = raiz;

    while (atual != NULL || !pilhaVazia(pilha)) {
        // 1. Navega até o nó mais à esquerda possível, empilhando os ancestrais
        while (atual != NULL) {
            empilhar(&pilha, atual);
            atual = atual->esq;
        }

        // 2. Desempilha e processa o nó
        atual = desempilhar(&pilha);
        printf("%d ", atual->chave);

        // 3. Move para a subárvore à direita
        atual = atual->dir;
    }
    printf("\n");
}
