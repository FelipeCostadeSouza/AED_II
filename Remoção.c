typedef struct arv {     //feito por mim semestre passado
    int info;
    struct arv *esq1; 
    struct arv *dir1;
}TArvABB;
typedef TArvABB *PArvABB;


PArvABB remover(PArvABB a, int x) {
	PArvABB t,pai;
	if(a==NULL) {    //arvore vazia
		return NULL;
	}
	if(x<a->info) {
		a->esq1=remover(a->esq1, x);  
	} else if(x>a->info) {
		a->dir1=remover(a->dir1, x);    //percorre a árvore até encontrar o nó
	} else {
		if(a->esq1==NULL && a->dir1==NULL) {
			free(a);
			return NULL;  //remove se for uma folha
		}
		if(a->dir1==NULL) {   //nó só possui um filho a esquerda
			t=a->esq1;       //guardo o filho a esquerda
			free(a);         //removo o nó
			return t;        //retorno o filho a esquerda para se conectar ao pai de a
		}
		if(a->esq1==NULL) {   //mesma coisa só que o inverso
			t=a->dir1;
			free(a);
			return t;
		}
		pai=a;      
		t=a->esq1;
		while(t->dir1!=NULL) {   //procuro o filho mais a direita na sub árvore esquerda
			pai=t;
			t=t->dir1;
		}
		a->info=t->info;     //troco as informações, agora t é quem devo remover
		if(pai==a) {           //o filho a esquerda de a não possui nenhum filho a direita
			pai->esq1=t->esq1;  //a deve receber os filhos a esquerda de t
		} else {
			pai->dir1=t->esq1;    //o último caso, em a deve receber todos os filhos a esquerda de t para não perde-los
		}
		free(t);           //remove o nó
		return a;
	}
}


//Código do exercício 4, usei ia para achar um código para usar e sua fonte


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
