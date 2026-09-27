#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arv2 {
	int info;
	struct arv2 *esq1;
	struct arv2 *dir1;
} TArvABB;
typedef TArvABB *PArvABB;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node* searchAVL(Node *a, int x) {
    while (a != NULL && a->key != x) {
        if (x < a->key) {
            a = a->left;
        } else {
            a = a->right;
        }
    }
    return a;
}


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
    while (a != NULL && a->info != x) {
        if (x < a->info) {
            a = a->esq1;
        } else {
            a = a->dir1;
        }
    }
    return a;
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
            printf("encontrado\n");
            return; 
        }
    }
    return;
}

int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

int get_balance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* rotate_right(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
  
    return x;
}

Node* rotate_left(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
  
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


Node* insert_node(Node* node, int key) {
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert_node(node->left, key);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key);
    } else {
 
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
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
    
    clock_t inicio_v1 = clock();
    
    for (int i = 0; i < a; i++) {
        v1[i] = v[i];
    }
    shellsort(v1);
    
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
    
    Node *A2 = NULL;
    
    clock_t inicio_AVL = clock();
    
    for (int i = 0; i < a; i++) {
        A2 = insert_node(A2, v[i]);
    }
    
    clock_t fim_AVL = clock();
    double tempo_AVL = (double)(fim_AVL - inicio_AVL) / CLOCKS_PER_SEC;
    printf("Tempo de inserção árvore AVL: %f segundos\n", tempo_AVL);
    
    clock_t inicio_B = clock();
    
    busca(v, 50);
    
    clock_t fim_B = clock();
    double tempo_B = (double)(fim_B - inicio_B) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor aleatorio: %f segundos\n", tempo_B);
    
    clock_t inicio_B1 = clock();
    
    busca(v, 5000);
    
    clock_t fim_B1 = clock();
    double tempo_B1 = (double)(fim_B1 - inicio_B1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 vetor aleatorio: %f segundos\n", tempo_B1);
    
    
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
    printf("Tempo de busca 50 arvore: %f segundos\n", tempo_ab);
    
    clock_t inicio_ab1 = clock();
    
    B = searchABB(A, 5000);
    clock_t fim_ab1 = clock();
    double tempo_ab1 = (double)(fim_ab1 - inicio_ab1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvore: %f segundos\n", tempo_ab1);
    
    Node *B1 = NULL;
    Node *C1 = NULL;
    
    clock_t inicio_AVL1 = clock();
    
    C1 = searchAVL(A2, 50);
    
    clock_t fim_AVL1 = clock();
    double tempo_AVL1 = (double)(fim_AVL1 - inicio_AVL1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 arvoreAVL: %f segundos\n", tempo_AVL1);
    
    clock_t inicio_AVL2 = clock();
    
    B1 =  searchAVL(A2, 5000);
    
    clock_t fim_AVL2 = clock();
    double tempo_AVL2 = (double)(fim_AVL2 - inicio_AVL2) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvoreAVL: %f segundos\n", tempo_AVL2);
    
    
    int h = height(A2->right);
    int h1 = height(A2->left);
    
    printf("Altura sub-esquerda: %d \n", h1);
    printf("Altura sub-direita: %d \n", h);


    return 0;
}
