#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arv2 {
	int info;
	struct arv2 *esq1;
	struct arv2 *dir1;
} TArvABB;
typedef TArvABB *PArvABB;


PArvABB inserirABB(PArvABB a, int x) {

	if(a==NULL) {
		PArvABB novo=(PArvABB)malloc(sizeof(TArvABB));
		novo->info=x;
		novo->esq1=novo->dir1=NULL;
		return novo;
	}
	if(x<a->info) {
		a->esq1=inserirABB(a->esq1, x);
	} else {
		a->dir1=inserirABB(a->dir1, x);
	}
	return a;
}

PArvABB searchABB(PArvABB a, int x) {
	if(a==NULL) {
		return NULL;
	}
	if(a->info==x) {
		return a;
	} else if(x<a->info) {
		return searchABB(a->esq1, x);
	}
	return searchABB(a->dir1, x);
}

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

int altura(PArvABB a) {
	if(a==NULL) {
		return -1;
	}

	int alturaesq=altura(a->esq1);

	int alturadir=altura(a->dir1);

	if(alturaesq>alturadir) {

		return (alturaesq + 1);

	} else {

		return (alturadir+1);

	}

}

void buscaBinaria(int v[], int x) {
    int inicio = 0;
    int fim = 10000 - 1;

    while (inicio <= fim) {
        
        int meio = inicio + (fim - inicio) / 2;

        if (v[meio] == x) {
            printf("-----encontrado-----\n");
            return; 
        }

        if (v[meio] < x) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1; 
        }
    }

    return; 
}

void shellsort(int a[]){
    for (int gap = 10000 / 2; gap > 0; gap /= 2) { 
        for (int i = gap; i < 10000; i++) {
            int temp = a[i]; 
            int j = i;
            
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp; 
        }
    }
}

void busca(int v[], int x){
    
    for(int i=0; i<10000; i++){
        if(v[i]==x){
            printf("encontrado");
            return; 
        }
    }
    return;
}

int main() {
    int a=10000;
    int v[a];
    clock_t inicio_v = clock();
    
    srand(time(NULL));
    for (int i = 0; i < a; i++) {
        v[i] = (rand() % 10000) + 1;
    }
    clock_t fim_v = clock();
    double tempo_v = (double)(fim_v - inicio_v) / CLOCKS_PER_SEC;
    printf("Tempo de inserção vetor aleatorio: %f segundos\n", tempo_v);
    
    int v1[a];
    
    for (int i = 0; i < a; i++) {
        v1[i] = v[i];
    }
    shellsort(v1);
    
    int v2[a];
    
    clock_t inicio_v1 = clock();
    
    for (int i = 0; i < a; i++) {
        v2[i] = v[i];
    }
    
    
    clock_t fim_v1 = clock();
    double tempo_v1 = (double)(fim_v1 - inicio_v1) / CLOCKS_PER_SEC;
    printf("Tempo de inserção vetor ordenado: %f segundos\n", tempo_v1);
    
    PArvABB A = NULL;
    
    clock_t inicio_a = clock();
    
    for (int i = 0; i < a; i++) {
        A = inserirABB(A, v[i]);
    }
    
    clock_t fim_a = clock();
    double tempo_a = (double)(fim_a - inicio_a) / CLOCKS_PER_SEC;
    printf("Tempo de inserção árvore ABB: %f segundos\n", tempo_a);
    
    clock_t inicio_B = clock();
    
    busca(v, 50);
    
    clock_t fim_B = clock();
    double tempo_B = (double)(fim_B - inicio_B) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor aleatorio: %f segundos\n", tempo_B);
    
    clock_t inicio_B1 = clock();
    
    busca(v, 5000);
    
    clock_t fim_B1 = clock();
    double tempo_B1 = (double)(fim_B1 - inicio_B1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor aleatorio: %f segundos\n", tempo_B1);
    
    
    clock_t inicio_v1B = clock();
    buscaBinaria(v1, 50);
    clock_t fim_v1B = clock();
    double tempo_v1B = (double)(fim_v1B - inicio_v1B) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor ordenado: %f segundos\n", tempo_v1B);
    
    
    clock_t inicio_v1B2 = clock();
    buscaBinaria(v1, 5000);
    clock_t fim_v1B2 = clock();
    double tempo_v1B2 = (double)(fim_v1B2 - inicio_v1B2) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 vetor ordenado: %f segundos\n", tempo_v1B2);
    
    PArvABB C = NULL;
    PArvABB B = NULL;
    
    clock_t inicio_ab = clock();
    C = searchABB(A, 50);
    clock_t fim_ab = clock();
    double tempo_ab = (double)(fim_ab - inicio_ab) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvore: %f segundos\n", tempo_ab);
    
    clock_t inicio_ab1 = clock();
    
    B = searchABB(A, 5000);
    clock_t fim_ab1 = clock();
    double tempo_ab1 = (double)(fim_ab1 - inicio_ab1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvore: %f segundos\n", tempo_ab1);
    
    
    int h = altura(A->dir1);
    int h1 = altura(A->esq1);
    
    printf("Altura sub-esquerda: %d \n", h1);
    printf("Altura sub-direita: %d \n", h);


    return 0;
}
